#include "func_sys.h"
#include <iostream>
 
using namespace std;



//---------------------------------- SUPER BLOCK -----------------------------------------------------------

//FUNCION QUE VERIFICA QUE LA PARTICION ESTE ACTIVA
Respuesta getParticionInicial(MasterBootRecord *disco, char name[], int *init){
    int i;
    for(i = 0; i < 4; i++){
        //RECORRER LAS PARTICIONES DEL DISCO Y VERIFICAR EL STATUS
        if(disco->particiones[i].part_status == ACTIVO){
            //VALIDAR EL NOMBRE 
            if(strcmp(disco->particiones[i].part_name, name) == 0){
                //asignar el valor de inicio de la particion 
                *init = disco->particiones[i].part_start;
                return CORRECTO;
            }
        }
    }
    return ERR_PART_NOEX;
}

//FUNCION PARA ESCRIBIR EL SUPER BLOQUE
void CrearArchivoSuperBlock(SuperBlock *superb, char path[], int init){
    //UBICAR EL PUNTERO AL INICIO DEL SUPER BLOQUE DEL DISCO
    FILE *arch;
    arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL ARCHIVO... "<<endl;
        return;
    }
    fseek(arch, init, SEEK_SET);
    //ESCRIBIR EL SUPER BLOQUE
    fwrite(superb, sizeof(SuperBlock),1,arch);
    fclose(arch);
}

//FUNCION QUE LEE EL SUPER BLOQUE
SuperBlock *ReadSuperBlock(char path[], char name[],int *startsuperb){
    MasterBootRecord *disco = getDataMBR(path);
    if(disco==NULL){
        cout<<"ERROR AL ABIR EL DISCO... \n";
        return NULL;
    }
    Respuesta res = getParticionInicial(disco,name,startsuperb);
    if(res!=CORRECTO){
        return NULL;
    }
    delete disco;
    FILE *arch = fopen(path,"rb+");
    if(arch==NULL){
        cout<<"ERROR AL ABRIR EL DISCO...  \n";
        return NULL;
    }
    SuperBlock *superb = (SuperBlock*)malloc(sizeof(SuperBlock));
    fseek(arch, *startsuperb, SEEK_SET);
    fread(superb, sizeof(SuperBlock), 1, arch);
    fclose(arch);
    return superb;
}

//FUNCION QUE LEE EL SUPER BLOQUE
SuperBlock *ReadSuperBlock(char path[], char name[]){
    //OBTENER LOS DATOS DEL MBR
    MasterBootRecord *disco = getDataMBR(path);
    if(disco == NULL){
        cout<<"ERROR AL ABRIR EL ARCHIVO... "<<endl;
        return NULL;
    }
    int init;
    //OBTENER LA PARTICION 
    Respuesta res = getParticionInicial(disco, name, &init);
    if(res != CORRECTO){
        return NULL;
    }
    //LIMPIAR LA MEMORIA
    delete disco;
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL ARCHIVO... "<<endl;
        return NULL;
    }
    //INICIALIZAR EL SUPER BLOQUE
    SuperBlock *superb = (SuperBlock*)malloc(sizeof(SuperBlock));
    //UBICAR EL PUNTERO EN EL INICIO DE LA ESCRITURA DEL SUPER BLOQUE
    fseek(arch, init, SEEK_SET);
    //LEER INFORMACION ESCRITA EN EL SUPER BLOQUE
    fread(superb, sizeof(SuperBlock), 1, arch);
    fclose(arch);
    return superb;
}

//FUNCION QUE RETORNA EL BLOQUE INICIAL
int getBloqueInicial(SuperBlock *bloque, int indice){
    return bloque->s_block_start + (bloque->s_block_size * indice);
}

//---------------------------------- BITMAPS ----------------------------------------------------------------
//FUNCION QUE RETORNA EL INDICE DONDE SE ENCUENTRA EL BIT SELECCIONADO EN EL BITMAP
int getBM_index(int primerBM, int ultimoBM, char path[]){
    //VERIFICAR QUE EXISTA EL DISCO
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL DISCO... \n";
        return -1;
    }
    char aux;
    //UBICAR EL PUNTERO EN EL INICIO DEL BITMAP
    fseek(arch, primerBM, SEEK_SET);
    int cont = 0;
    bool flag = false;
    //LEER LOS BITMAPS HASTA LA ULTIMA POSICION ENVIADA
    while(cont < ultimoBM){
        fread(&aux, sizeof(char),1,arch);
        if(aux == '0'){
            //VERIFICAR QUE EL BIT NO HAYA SIDO MARCADO
            if(!flag){
                //UBICAR EL PUNTERO AL FINAL
                fseek(arch, -1, SEEK_CUR);
                //SE ESCRIBE EL 1 EN ESA POSICION PARA MARCAR EL BITMAP
                fwrite("1", sizeof(char), 1, arch);
                flag = true;
            }else{
                break;
            }
        }
        cont++;
    }
    fclose(arch);
    //RETORNAR EL VALOR DEL INDICE
    return cont;
}


//FUNCION QUE ESCRIBE LA TABLA DE BITMAPS
void CrearBitmapTable(int numInodos, int primero, char path[]){
    int cont = 0;
    //UBICAR EL PUNTERO DEL ARCHIVO EN EL APARTADO PARA EL BITMAPTABLE 
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL DISCO... \n";
    }
    fseek(arch, primero, SEEK_SET);
    while(cont < numInodos){
        fwrite("0", sizeof(char), 1, arch);
        cont++;
    }
    fclose(arch);
}

//------------------------- JOURNAL -----------------------------------
//FUNCION PARA ESCRIBIR EL JOURNAL INICIALMENTE
void EscribirJournal(int inicio, int cant, char path[]){
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL DISCO... \n";
        return;
    }
    //INICIALIZAR UN OBJETO DE TIPO JOURNAL
    Journal *journal = new Journal();
    //UBICAR EL PUNTERO AL INICIO DEL JOURNAL DE LA PARTICION MONTADA
    fseek(arch, inicio, SEEK_SET);
    int contador = 0;
    //SE ESCRIBE UN OBJETO JOURNAL CADA TRANSACCION REALIZADA
    while(contador < cant){
        fwrite(journal, sizeof(Journal), 1, arch);
        contador++;
    }
    fclose(arch);
}

//FUNCION PARA AGREGAR EL JOURNAL AL ARCHIVO
void CrearArchivoJournal(SuperBlock *auxsuperb, int primersuperb, char path[], Journal *auxJournal){
    //DEFINIR EL TAMANO INICIAL DEL SUPER BLOQUE
    int startOp = primersuperb+sizeof(SuperBlock);
    int contador = 0;
    //VERIFICAR EL DISCO
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL DISCO... \n";
        return;
    }
    //CREAR ESPACIO DE MEMORIA PARA ESCRIBIR EL JOURNAL
    Journal *journal = (Journal*)malloc(sizeof(Journal));
    //UBICAR EL PUNTERO EN EL INICIO DE DONDE SE ESCRIBIRA EL JOURNAL
    fseek(arch, startOp, SEEK_SET);
    //RECORRER LOS INODOS
    while(contador < auxsuperb->s_inodes_count){
        //LEER EL JOURNAL ASOCIADO AL INODO
        fread(journal, sizeof(Journal), 1, arch);
        //SI EL JOURNAL ESTA VACIO SALIR DEL CICLO
        if(journal == NULL){
            return;
        }
        //ESCRIBIR EL JOURNAL EN EL ARCHIVO
        if(journal->j_operation == VACIO){
            //UBICAR EL PUNTERO UN ESPACIO DE JOURNAL ANTES PARA IR FORMANDO LA TABLA
            fseek(arch, -sizeof(Journal), SEEK_CUR);
            //ESCRIBIR EL JOURNAL
            fwrite(auxJournal, sizeof(Journal), 1, arch);
            fclose(arch);
            return;
        }
        contador++;
    }
    fclose(arch);
}

//----------------------- INODOS ------------------------------------

//FUNCION QUE INICIALIZA LOS VALORES DEL INODO
TablaInodos *CrearInodo(Tipoinodo tipo, int permisos, int tam){
    //INICIALIZAR ESPACIO DE MEMORIA PARA EL INODO
    TablaInodos *nuevo = (TablaInodos*)malloc(sizeof(TablaInodos));
    //INICIALIZAR LOS VALORES DEL INODO
    nuevo->i_uid = 1;
    nuevo->i_gid = 1;
    nuevo->i_size = tam;
    getFecha(nuevo->i_atime);
    getFecha(nuevo->i_ctime);
    getFecha(nuevo->i_mtime);
    for(int i = 0; i < TAM_BLOQUES_INODOS; i++){
        nuevo->i_block[i] = -1;
    }
    nuevo->i_type = tipo;
    nuevo->i_perm = permisos;
    return nuevo;
}

//FUNCION QUE DEVUELVE LA POSICION DEL PRIMER INODO
int getInodoInicial(SuperBlock *auxsuperb, int indice){
    return auxsuperb->s_inode_start + (auxsuperb->s_inode_size * indice);
}

//FUNCION PARA ESCRIBIR EL INODO EN EL ARCHIVO
void CrearArchivoInodo(TablaInodos *inodo, char path[], int inicio){
    //PUNTERO AL DISCO
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL DISCO... \n";
        return;
    }
    //UBICAR EL PUNTERO EN EL ESPACIO DESIGNADO PARA ESCRIBIR EL INODO
    fseek(arch, inicio, SEEK_SET);
    //ESCRIBIR EL INODO
    fwrite(inodo, sizeof(TablaInodos), 1, arch);
    fclose(arch);
}


//FUNCION QUE LEE EL INODO 
TablaInodos *ReadInodo(char path[], int inicio){
    //PUNTERO AL ARCHIVO DEL DISCO
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL DISCO... \n";
        return NULL;
    }
    //INICIALIZAR EL ESPACIO DE MEMORIA PARA EL INODO A LEER
    TablaInodos *inodo = (TablaInodos*)malloc(sizeof(TablaInodos));
    //UBICAR EL PUNTERO EN EL INICIO DEL INODO
    fseek(arch, inicio, SEEK_SET);
    //LEER EL ARCHIVO
    fread(inodo, sizeof(TablaInodos), 1, arch);
    fclose(arch);
    //SI EL INODO NO ESTA ACTIVO RETORNA NULL
    if(inodo->i_ctime[0] == '\0'){
        return NULL;
    }
    return inodo;
}

//FUNCION PARA LIMPIAR LOS APUNTADORES DE UN INODO
void LimpiarInodo(TablaInodos *inodo){
    //RECORRER EL INODO E INICIALIZAR TODOS LOS PUNTEROS EN -1 QUE ES EL VALOR POR DEFECTO
    if(inodo != NULL){
        for(int i = 0; i < 15; i++){
            inodo->i_block[i] = -1;
        }
    }
}

//------------------------BLOQUE DE APUNTADORES----------------------

//FUNCION PARA ESCRIBIR EN EL SUPERBLOCK UN BLOQUE DE APUNTADORES
void CrearArchivoBloqueApuntadores(BloquesApuntadores *bloque, char path[], int inicio){
    //UBICAR EL PUNTERO DEL DISCO EN EL ESPACIO PARA ESCRIBIR ESTE BLOQUE
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL DISCO... \n";
        return;
    }
    fseek(arch, inicio, SEEK_SET);
    //ESCRIBIR EN LA PARTICION UN BLOQUE DE APUNTADORES
    fwrite(bloque, sizeof(BloquesApuntadores), 1, arch);
    fclose(arch);
}

//FUNCION PARA LEER LA INFORMACION DEL BLOQUE DE APUNTADORES
BloquesApuntadores *ReadBloquesApuntadores(char path[], int inicio){
    //APUNTAR AL BLOQUE DE APUNTADORES DE LA PARTICION
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL DISCO... \n";
        return NULL;
    }
    //INICIALIZAR UN ESPACIO DE MEMORIA PARA LA LECTURA
    BloquesApuntadores *bloque = (BloquesApuntadores*)malloc(sizeof(BloquesApuntadores));
    //UBICAR EL PUNTERO
    fseek(arch, inicio, SEEK_SET);
    //LEER EL BLOQUE
    fread(bloque, sizeof(BloquesApuntadores), 1, arch);
    fclose(arch);
    return bloque;
}

//FUNCION PARA INICIALIZAR UN BLOQUE DE APUNTADORES
BloquesApuntadores *CrearBloqueApuntadores(){
    //INICIALIZAR EL ESPACIO DE MEMORIA
    BloquesApuntadores *bloque = (BloquesApuntadores*)malloc(sizeof(BloquesApuntadores));
    //INICIALIZAR LOS PUNTEROS
    for(int i = 0; i < 16; i++){
        //ASIGNAR EL VALOR INICIAL
        bloque->b_pointers[i] = -1;
    }
    //RETORNAR EL BLOQUE
    return bloque;
}

//FUNCION QUE DEVUELVE EL INDICE DE UN ESPACIO LIBRE EN LOS BLOQUES DE APUNTADORES
int getBloqueApuntadorLibre(int level, TablaInodos *inodo, int indiceBloqueActual, char path[], SuperBlock *bloque, int *indiceLibre){
    //VALIDAR QUE EXISTA EL BLOQUE
    if(inodo->i_block[level] != -1){
        //VALIDAR QUE SEA BLOQUE DE APUNTADORES
        if(level == 12){
            //LEER EL BLOQUE DE APUNTADORES
            BloquesApuntadores *apuntadores = ReadBloquesApuntadores(path, getBloqueInicial(bloque, indiceBloqueActual));
            //VALIDAR QUE SE HAYA LEIDO LA INFORMACION
            if(apuntadores == NULL){
                return ERR_DIR_NOEX;
            }
            int indiceBloqueAp;
            //RECORRER LOS APUNTADORES
            for(indiceBloqueAp = 0; indiceBloqueAp < TAM_BLOQUES_INODOS; indiceBloqueAp++){
                //VALIDAR QUE SEA EL PRIMER APUNTADOR
                if(apuntadores->b_pointers[indiceBloqueAp] == -1){
                    //ASIGNAR EL VALOR AL ESPACIO LIBRE
                    *indiceLibre = indiceBloqueAp;
                    //RETORNAR EL INDICE ACTUAL
                    return indiceBloqueActual;
                }
            }
        }else{
            //LEER EL BLOQUE DE APUNTADORES SI EL PRIMERO NO ESTA LIBRE
            BloquesApuntadores *ap = ReadBloquesApuntadores(path, getBloqueInicial(bloque, indiceBloqueActual));
            //VALIDAR QUE SE HAYA LEIDO LA INFORMACION
            if(ap == NULL){
                return ERR_DIR_NOEX;
            }
            //VALIDAR RECURSIVAMENTE QUE SE ESTEN LEYENDO TODOS LOS APUNTADORES DEL BLOQUE 
            int indiceBloqueP;
            for(indiceBloqueP = 0; indiceBloqueP < TAM_BLOQUES_INODOS; indiceBloqueP++){
                //VALIDAR QUE SE LEAN LOS APUNTADORES DEL BLOQUE
                if(ap->b_pointers[indiceBloqueP] != -1){
                    int res = getBloqueApuntadorLibre(level - 1, inodo, ap->b_pointers[indiceBloqueP], path, bloque, indiceLibre);
                    //RETORNAR EL BLOQUE LIBRE
                    if(res != -1){
                        return res;
                    }
                }else{
                    //ASIGNAR EL BLOQUE ACTUAL COMO EL PADRE
                    int bloquePadre = indiceBloqueActual;
                    //CREAR LOS APUNTADORES
                    int bloqueS = CrearApuntadorInd(level -1, &indiceBloqueActual, bloque, path);
                    if(bloqueS == -1){
                        return ERR_LEVEL_FULL;
                    }
                    //ASIGNAR LOS APUNTADORES CREADOS AL BLOQUE
                    ap->b_pointers[indiceBloqueP] = bloqueS;
                    //ESCRIBIR EN EL DISCO
                    CrearArchivoBloqueApuntadores(ap, path, getBloqueInicial(bloque, bloquePadre));
                    *indiceLibre = 0;
                    return bloqueS;
                }
            }
        }
    }
    return -1;
}


//FUNCION PARA AGREGAR AL SISTEMA LOS BLOQUES DE APUNTADORES
Respuesta AgregarBloqueApuntadores(TablaInodos *inodo, int *indiceInodo, BloquesArchivos *bl, SuperBlock *bloque, char path[]){
    //VERIFICAR EL ESPACIO LIBRE
    if(inodo->i_block[*indiceInodo] != -1){
        int libre = 0;
        int res = getBloqueApuntadorLibre(*indiceInodo, inodo, inodo->i_block[*indiceInodo], path, bloque, &libre);
        if(res == -1){
            return ERR_LEVEL_FULL;
        }
        //LEER EL BLOQUE DE APUNTADORES
        BloquesApuntadores *point = ReadBloquesApuntadores(path, getBloqueInicial(bloque, res));
        point->b_pointers[libre] = bloque->s_first_blo;
        //ESCRIBIR LA INFORMACION EN EL DISCO
        CrearArchivoBloqueApuntadores(point, path, getBloqueInicial(bloque, res));
        GuardarBloqueArchivos(bl, bloque, path);
    }else{
        //CREAR UN NUEVO BLOQUE
        int newIndice;
        int block = CrearApuntadorInd(*indiceInodo, &newIndice, bloque, path);
        //VALIDAR LA CREACION DEL BLOQUE
        if(block == -1){
            return ERR_LEVEL_FULL;
        }
        inodo->i_block[*indiceInodo] = block;
        BloquesApuntadores *point = ReadBloquesApuntadores(path, getBloqueInicial(bloque, newIndice));
        //ESCRIBIR UN NUEVO BLOQUE
        GuardarBloqueArchivos(bl, bloque, path);
    }
    return CORRECTO;
}

//------------------------BLOQUE DE CARPETAS-------------------------

//FUNCION PARA INICIALIZAR UN BLOQUE DE CARPETAS
BloquesCarpetas *CrearBloqueCarpetas(char name[], int indiceDir, char namePad[], int indicePad){
    //INICIALIZAR EL ESPACIO DE MEMORIA
    BloquesCarpetas *block = (BloquesCarpetas*)malloc(sizeof(BloquesCarpetas));
    for(int i = 0; i < 4; i++){
        //INGRESAR LOS DATOS AL BLOQUE
        LimpiarArray(block->b_content[i].b_name, 14);
        block->b_content[i].b_inodo = -1;
    }
    strcpy(block->b_content[0].b_name, name);
    block->b_content[0].b_inodo = indiceDir;
    strcpy(block->b_content[1].b_name, namePad);
    block->b_content[1].b_inodo = indicePad;
    return block;
}

//FUNCION PARA ESCRIBIR LOS DATOS DEL BLOQUE DE CARPETAS EN EL ARCHIVO
void CrearArchivoBloquesCarpetas(BloquesCarpetas *auxsuperb, char path[], int inicio){
    //APUNTADOR AL ARCHIVO DEL DISCO
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL DISCO... \n";
        return;
    }
    //UBICAR EL PUNTERO AL INICIO DEL BLOQUE DE CARPETAS
    fseek(arch, inicio, SEEK_SET);
    //ESCRIBIR EN EL ARCHIVO
    fwrite(auxsuperb, sizeof(BloquesCarpetas), 1, arch);
    fclose(arch);
}

//FUNCION QUE DEVUELVE EL BLOQUE DE CARPETAS
BloquesCarpetas *ReadBloquesCarpetas(char path[], int inicio){
    //APUNTADOR AL DISCO
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL DISCO... \n";
        return NULL;
    }
    //INICIALIZAR EL ESPACIO DE MEMORIA DEL BLOQUE PARA LEER EL ARCHIVO
    BloquesCarpetas *bloque = (BloquesCarpetas*)malloc(sizeof(BloquesCarpetas));
    //UBICAR EL PUNTERO AL INICIO DEL BLOQUE
    fseek(arch, inicio, SEEK_SET);
    //LEER EL ARCHIVO
    fread(bloque, sizeof(BloquesCarpetas), 1, arch);
    fclose(arch);
    //VALIDAR SI EL BLOQUE TIENE CONTENIDO
    if(bloque->b_content[0].b_name[0] == '\0'){
        return NULL;
    }
    for(int i = 0; i < 4; i++){
        if(bloque->b_content[i].b_name[0] == '\0'){
            bloque->b_content[i].b_inodo = -1;
        }
    }
    return bloque;
}

//FUNCION QUE VERIFICA EL INDICE DE LOS ESPACIOS LIBRES EN EL BLOQUE DE DIRECTORIOS
Respuesta getBloqueCarpetasLibre(char nomDir[], char path[], SuperBlock *bloque, int *indiceBloqueActual, int *indiceInodoActual, int *indiceLibre, Tipobloque *type){
    //LEER EL INODO
    TablaInodos *inodo = NULL;
    inodo = ReadInodo(path, getInodoInicial(bloque, *indiceInodoActual));
    //VALIDAR QUE EL DIRECTORIO EXISTA
    if(inodo == NULL){
        return ERR_DIR_NOEX;
    }
    int idPoint = 0;
    bool flag_directo = true;
    BloquesCarpetas *blcarpeta = NULL;
    bool encontrado = false;
    //RECORRER LOS INODOS HASTA ENCONTRAR EL DESEADO
    while(idPoint < TAM_BLOQUES_INODOS && !encontrado){
        if(inodo->i_block[idPoint] != -1){
            if(flag_directo){
                //LEER EL BLOQUE DE CARPETAS
                blcarpeta = ReadBloquesCarpetas(path, getBloqueInicial(bloque, inodo->i_block[idPoint]));
                //VERIFICAR QUE EXISTA EL BLOQUE
                if(strcmp(blcarpeta->b_content[0].b_name, nomDir) == 0){
                    //OBTENER EL INDICE DEL BLOQUE ENCONTRADO
                    *indiceBloqueActual = inodo->i_block[idPoint];
                    int indiceBloque = 2;
                    //RECORRER LOS BLOQUES 
                    while(indiceBloque < 4){
                        //VALIDAR QUE EL ESPACIO ESTE LIBRE
                        if(blcarpeta->b_content[indiceBloque].b_inodo == -1){
                            //ASIGNAR EL VALOR AL PARAMETRO POR REFERENCIA
                            *indiceLibre = indiceBloque;
                            encontrado = true;
                            break;
                        }
                        indiceBloque++;
                    }
                }
            }else{
                //LEER APUNTADOR INDIRECTO
                *type = APUNTADOR;
                *indiceBloqueActual = inodo->i_block[idPoint];
                //OBTENER EL BLOQUE DE APUNTADORES LIBRE
                int bl = getBloqueApuntadorLibre(idPoint, inodo, *indiceBloqueActual, path, bloque, indiceLibre);
                //ESCRIBIR EL INODO EN EL DISCO
                CrearArchivoInodo(inodo, path, getInodoInicial(bloque, *indiceInodoActual));
                //VERIFICAR QUE SE HAYA CREADO EL BLOQUE
                if(bl == -1){
                    idPoint++;
                    continue;
                }
                encontrado = true;
                *indiceBloqueActual = bl;
            }
        }else{
            //VALIDAR SI ES APUNTADOR DIRECTO
            if(flag_directo){
                //CREAR UN NUEVO BLOQUE DE CARPETAS
                BloquesCarpetas *nuevo = CrearBloqueCarpetas(blcarpeta->b_content[0].b_name, blcarpeta->b_content[0].b_inodo,
                blcarpeta->b_content[1].b_name, blcarpeta->b_content[1].b_inodo);
                //APUNTAR AL PRIMER BLOQUE
                inodo->i_block[idPoint] = bloque->s_first_blo;
                //ESCRIBIR EL BLOQUE DE DIRECTORIOS
                CrearArchivoBloquesCarpetas(nuevo, path, getBloqueInicial(bloque, bloque->s_first_blo));
                //ESCRIBIR EL INDODO
                CrearArchivoInodo(inodo, path, getInodoInicial(bloque, *indiceInodoActual));
                //RESTAR UN INODO Y UN BLOQUE DEL SUPER BLOQUE
                *indiceBloqueActual = bloque->s_first_blo;
                *indiceLibre = 2;
                encontrado = true;
                //MARCAR LOS BITMAPS
                bloque->s_first_blo = getBM_index(bloque->s_bm_block_start, bloque->s_blocks_count, path);
                bloque->s_free_blocks_count--;
            }else{
                //CREAR UN NUEVO BLOQUE
                int bl = CrearApuntadorInd(idPoint, indiceBloqueActual, bloque, path);
                //VALIDAR QUE HAYA ESPACIO PARA CREAR EL BLOQUE
                if(bl == -1){
                    return ERR_LEVEL_FULL;
                }
                inodo->i_block[idPoint] = bl;
                //ESCRIBIR EL INODO
                CrearArchivoInodo(inodo, path, getInodoInicial(bloque, *indiceInodoActual));
                *indiceLibre = 0;
                *type = APUNTADOR;
                encontrado = true;
            }

        }
        idPoint++;
        //VALIDAR QUE EL PUNTERO SEA DIRECTO
        if(idPoint > 11){
            flag_directo = false;
        }
    }
    //LIBERAR MEMORIA
    delete inodo;
    delete blcarpeta;
    return CORRECTO;
}

//--------------------------------- BLOQUES DE ARCHIVOS -------------------------

//FUNCION PARA ESCRIBIR EL BLOQUE DE ARCHIVOS EN EL DISCO
void CrearArchivoBloquesArchivos(BloquesArchivos *bloque, char path[], int inicio){
    //APUNTADOR AL DISCO
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL DISCO... \n";
        return;
    }
    //UBICAR EL PUNTERO AL INICIO DEL BLOQUE DE ARCHIVOS PARA SU ESCRITURA
    fseek(arch, inicio, SEEK_SET);
    //ESCRIBIR EN EL DISCO EL BLOQUE DE ARCHIVOS
    fwrite(bloque, sizeof(BloquesArchivos), 1, arch);
    fclose(arch);
}

//FUNCION PARA LEER EL BLOQUE DE ARCHIVOS
BloquesArchivos *ReadBloquesArchivos(char path[], int inicio){
    //APUNTADOR AL DISCO
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL DISCO... \n";
        return NULL;
    }
    //INICIALIZAR EL ESPACIO DE MEMORIA PARA LA LECTURA DEL BLOQUE EN EL DISCO
    BloquesArchivos *bloque = (BloquesArchivos*)malloc(sizeof(BloquesArchivos));
    //UBICAR EL PUNTERO EN EL INICIO DEL BLOQUE DE ARCHIVOS
    fseek(arch, inicio, SEEK_SET);
    //LEER EL ARCHIVO
    fread(bloque, sizeof(BloquesArchivos), 1, arch);
    fclose(arch);
    return bloque;
}

//FUNCION PARA INICIALIZAR UN NUEVO BLOQUE DE ARCHIVOS
BloquesArchivos *CrearBloqueArchivos(){
    //INICIALIZAR EL ESPACIO DE MEMORIA PARA EL BLOQUE Y LIMPIAR EL CONTENIDO
    BloquesArchivos *bloque = (BloquesArchivos*)malloc(sizeof(BloquesArchivos));
    LimpiarArray(bloque->b_content, 64);
    return bloque;
}

//FUNCION PARA GUARDAR LA INFORMACION DEL BLOQUE DE ARCHIVOS
void GuardarBloqueArchivos(BloquesArchivos *bloqueA, SuperBlock *bloqueS, char path[]){
    //ESCRIBIR EL BLOQUE DE ARCHIVOS EN EL DISCO
    CrearArchivoBloquesArchivos(bloqueA, path, getBloqueInicial(bloqueS, bloqueS->s_first_blo));
    //OBTENER LA DIRECCION DEL PRIMER BLOQUE EN LOS BITMAPS
    bloqueS->s_first_blo = getBM_index(bloqueS->s_bm_block_start, bloqueS->s_blocks_count, path);
    //RESTAR EL ESPACIO DISPONIBLE EN LOS BLOQUES
    bloqueS->s_free_blocks_count--;
}

//---------------------------- APUNTADORES INDIRECTOS -------------------------------

//FUNCION PARA CREAR LOS APUNTADORES INDIRECTOS, RETORNA EL INDICE DEL APUNTADOR CREADO
int CrearApuntadorInd(int idPoint, int *idBloqueActual, SuperBlock *bloque, char path[]){
    //VALIDAR QUE EL APUNTADOR SEA INDIRECTO
    if(idPoint -11 == 1){
        //OBTENER EL BLOQUE DE APUNTADORES
        BloquesApuntadores *aux = CrearBloqueApuntadores();
        //OBTENER EL ID
        int idBloque = bloque->s_first_blo;
        //ESCRIBIR EL BLOQUE EN EL DISCO
        CrearArchivoBloqueApuntadores(aux, path, getBloqueInicial(bloque, bloque->s_first_blo));
        //MARCAR EL BITMAP
        bloque->s_first_blo = getBM_index(bloque->s_bm_block_start, bloque->s_blocks_count, path);
        //RESTAR EL CONTADOR DE BITMAP 
        bloque->s_free_blocks_count--;
        //ASIGNAR EL ID
        *idBloqueActual = idBloque;
        return idBloque;
    }else{
        //SI NO HAY BLOQUE DE APUNTADORES SENALADO SE GENERA UNO NUEVO
        //CREAR APUNTADORES RECURSIVAMENTE
        int res = CrearApuntadorInd(idPoint -1, idBloqueActual, bloque, path);
        //CREAR BLOQUE
        BloquesApuntadores *aux = CrearBloqueApuntadores();
        //ASIGNAR EL APUNTADOR CREADO
        aux->b_pointers[0] = res;
        //ASIGNAR EL BLOQUE AL INICIO
        res = bloque->s_first_blo;
        //ESCRIBIR EL BLOQUE DE APUNTADORES EN EL DISCO
        CrearArchivoBloqueApuntadores(aux, path, getBloqueInicial(bloque, bloque->s_first_blo));
        //MARCAR EL BITMAP
        bloque->s_first_blo = getBM_index(bloque->s_bm_block_start, bloque->s_blocks_count, path);
        //RESTAR CONTADOR DEL BITMAP DE BLOQUES
        bloque->s_free_blocks_count--;
        //RETORNAR EL ID DEL PRIMER BLOQUE
        return res;
    }
    return -1;
}



//---------------------------- CARPETAS ---------------------------------------------

//FUNCION QUE CREA UN DIRECTORIO Y DEVUELVE SU INDICE
int CrearDirectorio(SuperBlock *bloque, char path[], char nomDir[], char nomPad[], int indicePad){
    //CREAR EL INODO DE LA NUEVA CARPETA
    TablaInodos *aux = CrearInodo(IN_DIRECTORY, 777, -1);
    int indiceI = bloque->s_first_ino;
    //CREAR EL BLOQUE DE DIRECTORIOS
    BloquesCarpetas *b2 = CrearBloqueCarpetas(nomDir, indiceI, nomPad, indicePad);
    //ASIGNAR EL BLOQUE A LA CARPETA CREADA
    aux->i_block[0] = bloque->s_first_blo;
    //ESCRIBIR EL INODO
    CrearArchivoInodo(aux, path, getInodoInicial(bloque, indiceI));
    //ESCRIBIR EL BLOQUE DE DIRECTORIOS
    CrearArchivoBloquesCarpetas(b2, path, getBloqueInicial(bloque, bloque->s_first_blo));
    //LIBERAR MEMORIA UTILIZADA
    delete aux;
    delete b2;
    //MARCAR LOS BITMAPS
    bloque->s_first_ino = getBM_index(bloque->s_bm_inode_start, bloque->s_inodes_count, path);
    bloque->s_first_blo = getBM_index(bloque->s_bm_block_start, bloque->s_blocks_count, path);
    //RESTAR CONTADORES DE ESPACIOS LIBRES PARA LOS BLOQUES DE CARPETAS Y LOS INDODOS CREADOS
    bloque->s_free_blocks_count--;
    bloque->s_free_inodes_count--;
    return indiceI;
}


//FUNCION PARA CREAR UN NODO CARPETA
Respuesta CrearNodoCarpeta(char dirPad[], char dirName[], char path[], SuperBlock *bloque, int *indiceInodoPadre, int *indiceBloqueActual){
    int indiceLibre = -1;
    Tipobloque type = DIRECTORIO;
    //CREAR DIRECTORIO EN EL ESPACIO LIBRE
    Respuesta res = getBloqueCarpetasLibre(dirPad, path, bloque, indiceBloqueActual, indiceInodoPadre, &indiceLibre, &type);
    //VALIDAR
    if(res != CORRECTO){
        return res;
    }
    if(indiceLibre == -1){
        return ERR_LEVEL_FULL;
    }
    //ESCRIBIR UN DIRECTORIO
    int newIndice = CrearDirectorio(bloque, path, dirName, dirPad, *indiceInodoPadre);
    //VALIDAR QUE SEA UN DIRECTORIO PARA ESCRIBIRLO
    if(type == DIRECTORIO){
        //LEER EL BLOQUE
        BloquesCarpetas *bl = ReadBloquesCarpetas(path, getBloqueInicial(bloque, *indiceBloqueActual));
        bl->b_content[indiceLibre].b_inodo = newIndice;
        strcpy(bl->b_content[indiceLibre].b_name, dirName);
        //ESCRIBIR EL BLOQUE DE DIRECTORIOS
        CrearArchivoBloquesCarpetas(bl, path, getBloqueInicial(bloque, *indiceBloqueActual));
        //LIBERAR LA MEMORIA
        delete bl;
    }else if(type == APUNTADOR){
        //LEER EL BLOQUE DE APUNTADORES
        BloquesApuntadores *pointbl = ReadBloquesApuntadores(path, getBloqueInicial(bloque, *indiceBloqueActual));
        pointbl->b_pointers[indiceLibre] = newIndice;
        //ESCRIBIR EL BLOQUE DE APUNTADORES
        CrearArchivoBloqueApuntadores(pointbl, path, getBloqueInicial(bloque, *indiceBloqueActual));
    }
    *indiceInodoPadre = newIndice;
    return CORRECTO;
}


//FUNCION QUE RETORNA EL INDICE DEL DIRECTORIO CREADO EN UN BLOQUE DE APUNTADORES
int BuscarCarpetaBloqueApuntadores(int level, int indiceBloque, int *indiceInodoActual, char nameDir[], SuperBlock *bloque, char path[]){
    //VALIDAR EL NIVEL DEL APUNTADOR
    if(level == 1){
        //LEER EL BLOQUE DE APUNTADORES
        BloquesApuntadores *pointers = ReadBloquesApuntadores(path, getBloqueInicial(bloque, indiceBloque));
        int indiceApuntador;
        for(indiceApuntador = 0; indiceApuntador < 14; indiceApuntador++){
            if(pointers->b_pointers[indiceApuntador] != -1){
                //BUSCAR EL INODO
                TablaInodos *inodo = ReadInodo(path, getInodoInicial(bloque, pointers->b_pointers[indiceApuntador]));
                if(inodo == NULL){
                    return -1;
                }
                int indiceBloque;
                BloquesCarpetas *bl;
                for(indiceBloque = 0; indiceBloque < 12; indiceBloque++){
                    if(inodo->i_block[indiceBloque] != -1){
                        if(inodo->i_type == IN_DIRECTORY){
                            bl = ReadBloquesCarpetas(path, getBloqueInicial(bloque, inodo->i_block[indiceBloque]));
                            if(bl == NULL){
                                return -1;
                            }
                            int i = 0;
                            if(bl->b_content[i].b_inodo != -1){
                                if(strcmp(bl->b_content[i].b_name, nameDir) == 0){
                                    *indiceInodoActual = bl->b_content[0].b_inodo;
                                    return inodo->i_block[indiceBloque];
                                }
                            }
                        }
                    }
                }
            }
        }
    }else{
        BloquesApuntadores *point = ReadBloquesApuntadores(path, getBloqueInicial(bloque, indiceBloque));
        int indexF;
        for(indexF = 0; indexF < 14; indexF++){
            if(point->b_pointers[indexF] != -1){
                int i = BuscarCarpetaBloqueApuntadores(level -1, point->b_pointers[indexF], indiceInodoActual, nameDir, bloque, path);
                if(i != -1){
                    return i;
                }
            }                
        }
    }
    return -1;
}


//FUNCION QUE RETORNA EL INDICE DEL DIRECTORIO CREADO EN UN BLOQUE DE DIRECTORIOS
int BuscarCarpeta(char nameDir[], char path[], int *indiceInodoActual, SuperBlock *bloque){
    //LEER EL INODO
    TablaInodos *inodo = ReadInodo(path, getInodoInicial(bloque, *indiceInodoActual));
    if(inodo == NULL){
        return -1;
    }
    int indexBlock;
    BloquesCarpetas *bl;
    for(indexBlock = 0; indexBlock < 12; indexBlock++){
        if(inodo->i_block[indexBlock] != -1){
            if(inodo->i_type == IN_DIRECTORY){
                bl = ReadBloquesCarpetas(path, getBloqueInicial(bloque, inodo->i_block[indexBlock]));
                if(bl == NULL){
                    return -1;
                }
                int i;
                for(i = 2; i < 4; i++){
                    if(bl->b_content[i].b_inodo != -1){
                        if(strcmp(bl->b_content[i].b_name, nameDir) == 0){
                            *indiceInodoActual = bl->b_content[i].b_inodo;
                            inodo = ReadInodo(path, getInodoInicial(bloque, *indiceInodoActual));
                            if(inodo == NULL){
                                return -1;
                            }
                            return inodo->i_block[0];
                        }
                    }
                }
            }
        }
    }
    for(indexBlock = 12; indexBlock < 14; indexBlock++){
        int index = BuscarCarpetaBloqueApuntadores(indexBlock - 11, inodo->i_block[indexBlock], indiceInodoActual, nameDir, bloque, path);
        if(index != -1){
            return index;
        }
    }
    return -1;
}

//----------------------------ARCHIVOS---------------------------------

//FUNCION PARA CREAR UN NODO ARCHIVO
Respuesta CrearNodoArchivo(int size, char *text, char path[], char dirpad[], char name[], SuperBlock *bloque, int indiceBloqueActual, int indiceInodoPadre){
    int indiceLibre = -1;
    Tipobloque type = DIRECTORIO;
    //OBTENER EL BLOQUE DE CARPETAS LIBRE
    Respuesta res = getBloqueCarpetasLibre(dirpad, path, bloque, &indiceBloqueActual, &indiceInodoPadre, &indiceLibre, &type);
    //VALIDAR QUE SE HAYA ESCRITO
    if(res != CORRECTO){
        return res;
    }
    //CREAR EL INODO DEL ARCHIVO
    TablaInodos *inodo = CrearInodo(IN_FILE, 664, size);
    //CREAR EL BLOQUE DE ARCHIVO
    BloquesArchivos *bl = CrearBloqueArchivos();
    int indiceInodo = 0;
    int indiceCar = 0;
    int contCar = 0;
    bool guardado = true;
    //CICLO INFINITO PARA ESCRIBIR EL ARCHIVO
    while(guardado){
        if(contCar >= 64 || indiceCar >= size){
            //VALIDAR LOS APUNTADORES DIRECTOS
            if(indiceInodo < 12){
                inodo->i_block[indiceInodo] = bloque->s_first_blo;
                //ESCRIBIR LA INFORMACION EN EL DISCO
                GuardarBloqueArchivos(bl, bloque, path);
                indiceInodo++;
            }else{
                //AGREAR BLOQUES DE APUNTADORES
                Respuesta resp = AgregarBloqueApuntadores(inodo, &indiceInodo, bl, bloque, path);
                //VERIFICAR QUE HAYA ESPACIO EN EL BLOQUE
                if(resp == ERR_LEVEL_FULL){
                    if(indiceInodo < 14){
                        indiceInodo++;
                        continue;
                    }
                }else if(resp != CORRECTO){
                    return resp;
                }
            }
            //CREAR UN NUEVO BLOQUE DE ARCHIVOS
            bl = CrearBloqueArchivos();
            //REINICIAR EL CONTADOR DE CARACTERES
            contCar = 0;
        }
        //ASIGNAR EL CONTENIDO AL BLOQUE
        bl->b_content[contCar] = text[indiceCar];
        //VERIFICAR QUE EL CONTENIDO SEA ACORDE AL TAMANO
        if(indiceCar >= size){
            break;
        }
        contCar++;
        indiceCar++;
    }
    //ESCRIBIR EL INODO
    CrearArchivoInodo(inodo, path, getInodoInicial(bloque, bloque->s_first_ino));
    //LEER EL BLOQUE DE CARPETAS
    BloquesCarpetas *aux_carpetas = ReadBloquesCarpetas(path, getBloqueInicial(bloque, indiceBloqueActual));
    aux_carpetas->b_content[indiceLibre].b_inodo = bloque->s_first_ino;
    //CREAR UN NUEVO BLOQUE DE CARPETAS
    strcpy(aux_carpetas->b_content[indiceLibre].b_name, name);
    CrearArchivoBloquesCarpetas(aux_carpetas, path, getBloqueInicial(bloque, indiceBloqueActual));
    //MARCAR EL BITMAP
    bloque->s_first_ino = getBM_index(bloque->s_bm_inode_start, bloque->s_inodes_count, path);
    //RESTAR EL CONTADOR DE INODOS
    bloque->s_free_inodes_count--;
    return CORRECTO;
}

//FUNCION PARA CREAR ARCHIVOS DE TEXTO ESCRITOS
Respuesta CrearArchivosEscritos(char newPath[], bool createPath, char text[], int size, char path[], char namePartition[]){
    //VALIDAR QUE HAYA ESPACIO PARA CREAR INODOS Y BLOQUES
    int startsuperb;
    SuperBlock *superb = ReadSuperBlock(path,namePartition,&startsuperb);
    if(superb==NULL){
        return ERR_IRRECONOCIBLE;
    }
    int indexInodoPadre = 0;
    stringstream ss(newPath);
    string token;
    string dirPad="/";
    int indexBloqueActual = 0;
    while (getline(ss, token, '/')) {
        if(token!=""){
            //cout<<"padre: "<<dirPad<<endl;
            //cout<<"archivo/carpeta: "<<token<<endl;
            if (ss.tellg() == -1) {
                Respuesta res = CrearNodoArchivo(size,text,path,&dirPad[0],&token[0],superb,indexBloqueActual,indexInodoPadre);
                if(res != CORRECTO){
                    return res;
                }
            }else{
                int indexBloque = BuscarCarpeta(&token[0],path,&indexInodoPadre,superb);
                if(indexBloque!=-1){
                    indexBloqueActual = indexBloque;
                }else{
                    if(createPath){
                        Respuesta rs = CrearNodoCarpeta(&dirPad[0],&token[0],path,superb,&indexInodoPadre,&indexBloqueActual);;
                        if(rs != CORRECTO){
                            return rs;
                        }
                    }else{
                        return ERR_DIR_NOEX;
                    }
                }
            }
            dirPad = token;
        }
    }
    CrearArchivoSuperBlock(superb,path,startsuperb);
    delete superb;
    return CORRECTO;
}

//FUNCION PARA REEMPLAZAR EL CONTENIDO DE UN ARCHIVO
Respuesta ReemplazarContenido(int indiceInodo, char *contenido, char path[], char nomPart[]){
    int bloqueInicial = 0;
    //LEER EL SUPER BLOQUE
    SuperBlock *bloque = ReadSuperBlock(path, nomPart, &bloqueInicial);
    //VALIDAR
    if(bloque == NULL){
        return ERR_IRRECONOCIBLE;
    }
    //LEER LA TABLA DE INODOS
    TablaInodos *inodo = ReadInodo(path, getInodoInicial(bloque, indiceInodo));
    if(inodo == NULL){
        return ERR_IRRECONOCIBLE;
    }
    //CREAR UN BLOQUE DE ARCHIVO
    BloquesArchivos *bl = CrearBloqueArchivos();
    int indexInodo = 0;
    int contCar = 0;
    int indexCar = 0;
    bool flag = true;
    //CREAR UN NUEVO BLOQUE
    while(flag){
        if(contCar >= 64 || contenido[indexCar] == '\0'){
            if(indexInodo < 12){
                if(inodo->i_block[indexInodo] != -1){
                    CrearArchivoBloquesArchivos(bl, path, getBloqueInicial(bloque, inodo->i_block[indexInodo]));
                    indexInodo++;
                }else{
                    inodo->i_block[indexInodo] = bloque->s_first_blo;
                    GuardarBloqueArchivos(bl, bloque, path);
                    indexInodo++;
                }
            }
            bl = CrearBloqueArchivos();
            contCar = 0;
        }
        //VERIFICAR EL CONTENIDO
        bl->b_content[contCar] = contenido[indexCar];
        if(contenido[indexCar] == '\0'){
            break;
        }
        contCar++;
        indexCar++;
    }
    //ESCRIBIR EL INDODO
    CrearArchivoInodo(inodo, path, getInodoInicial(bloque, indiceInodo));
    return CORRECTO;
}

//FUNCION QUE RETORNA EL INDICE DEL ARCHIVO QUE SE DESEA ENCONTRAR
int BuscarArchivo(char filePath[], char path[], char partition[], char **title){
    //VALIDAR QUE HAYA ESPACIO PARA CREAR INODOS Y BLOQUES
    int startsuperb;
    SuperBlock *superb = ReadSuperBlock(path,partition,&startsuperb);
    if(superb==NULL){
        return ERR_IRRECONOCIBLE;
    }

    int indexInodoPadre = 0;
    stringstream ss(filePath);
    string token;
    string dirPad="/";
    int indexBloqueActual = 0;
    while (getline(ss, token, '/')) {
        if(token!=""){
            //cout<<"padre: "<<dirPad<<endl;
            //cout<<"carpeta: "<<token<<endl;
            if (ss.tellg() == -1) {
                //inodo de directorio
                TablaInodos *inodo = ReadInodo(path,getInodoInicial(superb,indexInodoPadre));
                if(inodo == NULL){
                    return ERR_DIR_NOEX;
                }
                if(inodo->i_type == IN_DIRECTORY){
                    int indexBloqueInodo;
                    for(indexBloqueInodo = 0;indexBloqueInodo<12;indexBloqueInodo++){
                        if(inodo->i_block[indexBloqueInodo]!=-1){
                            BloquesCarpetas *directory = ReadBloquesCarpetas(path,getBloqueInicial(superb,inodo->i_block[indexBloqueInodo]));
                            if(directory == NULL){
                                return ERR_IRRECONOCIBLE;
                            }
                            int indexInodoBloque;
                            for(indexInodoBloque = 2;indexInodoBloque <4;indexInodoBloque++){
                                if(strcmp(directory->b_content[indexInodoBloque].b_name,&token[0])==0){
                                    //encontrado
                                    TablaInodos *file = ReadInodo(path,getInodoInicial(superb,directory->b_content[indexInodoBloque].b_inodo));
                                    if(file!=NULL){
                                        if(file->i_type == IN_FILE){
                                            *title=(char*)malloc(sizeof(directory->b_content[indexInodoBloque].b_name));
                                            strcpy(*title,directory->b_content[indexInodoBloque].b_name);
                                            return directory->b_content[indexInodoBloque].b_inodo;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }else{
                    return -1;
                }
            }else{
                int indexBloque = BuscarCarpeta(&token[0],path,&indexInodoPadre,superb);
                if(indexBloque!=-1){
                    indexBloqueActual = indexBloque;
                }else{
                    getErrorMsj(ERR_DIR_NOEX);
                    return -1;
                }
                dirPad = token;
            }
        }
    }
  return -1;
}


//FUNCION QUE RETORNA EL CONTENIDO DE UN ARCHIVO
string getContenidoArchivo(int indexInodo, char path[], SuperBlock *superb){
    string contenido = "";
    TablaInodos *inodo = ReadInodo(path,getInodoInicial(superb,indexInodo));
    if(inodo == NULL){
        return "";
    }
    if(inodo->i_type == IN_FILE){
        int indexBloque;
        for(indexBloque = 0;indexBloque<12;indexBloque++){
            if(inodo->i_block[indexBloque]!=-1){
                BloquesArchivos *file = ReadBloquesArchivos(path,getBloqueInicial(superb,inodo->i_block[indexBloque]));
                if(file== NULL){
                    return "";
                }
                int index;
                for(index=0;index<64;index++){
                    contenido+=file->b_content[index];
                }

            }
        }
        //APUNTADORES INDIRECTOS
        for(indexBloque = 12;indexBloque<14;indexBloque++){
            if(inodo->i_block[indexBloque]!=-1){
                contenido+=getContenidoArchivoApuntador(indexBloque-11,inodo->i_block[indexBloque],path,superb);
            }
        }
    }
    return contenido;
}

//FUNCION QUE RETORNA EL CONTENIDO DE UN ARCHIVO DESDE LOS BLOQUES DE APUNTADORES
string getContenidoArchivoApuntador(int level, int indexBlock, char path[], SuperBlock *superb){
    BloquesApuntadores *points = ReadBloquesApuntadores(path,getBloqueInicial(superb,indexBlock));
    if(points == NULL){
        return "";
    }
    if(level == 1){
        string contenido = "";
        int indexBloque;
        for(indexBloque = 0;indexBloque<15;indexBloque++){
            if(points->b_pointers[indexBloque]!=-1){
                BloquesArchivos *file = ReadBloquesArchivos(path,getBloqueInicial(superb,points->b_pointers[indexBloque]));
                if(file== NULL){
                    return "";
                }
                int index;
                for(index=0;index<64;index++){
                    contenido+=file->b_content[index];
                }

            }
        }
        return contenido;
    }else{
        string contenido = "";
        int indexBloque;
        for(indexBloque = 0;indexBloque<15;indexBloque++){
            if(points->b_pointers[indexBloque]!=-1){
                contenido+=getContenidoArchivoApuntador(level-1,points->b_pointers[indexBloque],path,superb);
            }
        }
        return contenido;
    }
}

//FUNCION QUE RETORNA EL CONTENIDO DE UN ARCHVIVO EN STRING
string BuscarContenidoArchivo(char filePath[], char path[], char partition[], char **title){
    int indexInode = BuscarArchivo(filePath,path,partition,title);
    if(indexInode==-1){
        return "";
    }
    int startsuperb = -1;
    SuperBlock *superb = ReadSuperBlock(path,partition,&startsuperb);
    if(superb==NULL){

        return "";
    }
    string contentResponse = getContenidoArchivo(indexInode,path,superb);
    delete superb;
    return contentResponse;
}

//----------------------------------------- COMANDO MKFS -------------------------------

//FUNCION PARA FORMATEAR UNA PARTICION COMANDO MKFS
Respuesta Formatear(char path[], char partition[], Tipocapacidad tipoFormateo, Tiposistema sistem,bool flag_recov){
    MasterBootRecord *disco = getDataMBR(path);
    if(disco==NULL){
        return ERR_DISK_NO_EX;
    }
    double sizeN;
    int cantInodos;
    int cantBloques;
    //PRIMERA PARTE DE LA ECUACION TAMANOMBR - TAMANO EN BYTES DEL SUPER BLOQUE
    sizeN= disco->mbr_tamano-sizeof(SuperBlock);
    if(sistem == EXT2){
        //AL DESPEJAR N 
        sizeN/=4+sizeof(TablaInodos)+3*sizeof(BloquesArchivos);
    }else if(sistem == EXT3){
        sizeN/=4+sizeof(TablaInodos)+3*sizeof(BloquesArchivos)+sizeof(Journal);
    }
    //APLICAR FLOOR A LAS ECUACIONES
    cantInodos = floor(sizeN);
    cantBloques = cantInodos*3;
    //crear super bloque
    int initPart = 0;
    Respuesta res = getParticionInicial(disco,partition,&initPart);
    if(res != CORRECTO){
        return res;
    }
    int sizeInodos = sizeof(TablaInodos)*cantInodos;
    //BLOQUES
    SuperBlock *superb = (SuperBlock*)malloc(sizeof(SuperBlock));
    superb->s_filesystem_type = sistem;
    getFecha(superb->s_mtime);
    getFecha(superb->s_umtime);
    superb->s_mnt_count = 0;
    superb->s_magic = 0xEF53;
    superb->s_inode_size = sizeof(TablaInodos);
    superb->s_block_size = sizeof(BloquesArchivos);
    superb->s_first_ino = 0;
    superb->s_first_blo = 0;
    if(sistem == EXT2){
        superb->s_bm_inode_start = initPart+sizeof(SuperBlock);
    }else{
        superb->s_bm_inode_start = initPart+sizeof(SuperBlock)+(sizeof(Journal)*cantInodos);
    }
    superb->s_bm_block_start = superb->s_bm_inode_start+cantInodos;
    superb->s_inode_start = superb->s_bm_block_start + cantBloques;
    superb->s_block_start = superb->s_inode_start + sizeInodos;
    superb->s_free_blocks_count = cantBloques;
    superb->s_free_inodes_count = cantInodos;
    superb->s_blocks_count = cantBloques;
    superb->s_inodes_count = cantInodos;
    CrearArchivoSuperBlock(superb,path,initPart);
    //BITMAP DE INODOS
    CrearBitmapTable(cantInodos,superb->s_bm_inode_start,path);
    //BITMAP DE BLOQUES
    CrearBitmapTable(cantBloques,superb->s_bm_block_start,path);
    //CREAR CARPETA RAIZ
    CrearDirectorio(superb,path,(char*)"/",(char*)"/",0);
    CrearArchivoSuperBlock(superb,path,initPart);
    //CREAR ARCHIVO DE USERS
    char *users = (char*)"1,G,root\n1,U,root,root,123\n";
    CrearArchivosEscritos((char*)"/users.txt",true,users,28,path,partition);    
    if(sistem == EXT3 && !flag_recov){
        EscribirJournal(initPart+sizeof(SuperBlock),cantInodos,path);
    }
    delete disco;
    delete superb;
    return CORRECTO;
}

//----------------------- GRUPOS COMANDO MKGRP Y RMGRP ------------------------------------------

//FUNCION PARA CONTAR LOS GRUPOS
int ContarGrupos(char contentGroups[]){
    int contadortoken;
    stringstream ss(contentGroups);
    string token;
    int contadorGrupos = 0;
    while (getline(ss, token, '\n')) {
        if(token!=""){
            contadortoken = 0;
            stringstream line(token);
            string tokenLine;
            while (getline(line, tokenLine, ',')) {
                if(contadortoken == 0){
                    if(tokenLine == "0"){
                        continue;
                    }
                }else if(contadortoken==1){
                    if(tokenLine == "G"){
                        contadorGrupos++;
                    }else{
                        break;
                    }
                }else{
                    break;
                }
                contadortoken++;
            }
        }
    }
    return contadorGrupos;
}

//FUNCION QUE RETORNA UN GRUPO 
Grupo *getGrupo(char name[], char *contentUsers){
    int contadortoken;
    string nameG(name);
    Grupo *grp = NULL;
    stringstream ss(contentUsers);
    string token;
    while (getline(ss, token, '\n')) {
        grp = new Grupo();
        contadortoken = 0;
        stringstream line(token);
        string tokenLine;
        while (getline(line, tokenLine, ',')) {
            if(contadortoken == 0){
                if(tokenLine == "0"){
                    continue;
                }else{
                    grp->id = tokenLine;
                }
            }else if(contadortoken==1){
                if(tokenLine != "G"){
                    grp = NULL;
                    break;
                }
            }else if(contadortoken == 2){
                if(tokenLine == nameG ){
                    grp->name = tokenLine;
                }else{
                    grp = NULL;
                    break;
                }
            }else{
                break;
            }
            contadortoken++;
        }
        if(grp!=NULL)return grp;
    }
    return grp;
}

//FUNCION QUE RETORNA EL GRUPO QUE SE BUSCA POR ID
Grupo *getGrupoId(char name[], char path[], char namePartition[]){
    char *title;
    char *filePath = (char*)"/users.txt";
    string res = BuscarContenidoArchivo(filePath,path,namePartition,&title);
    int contadortoken;
    string nameG(name);
    Grupo *grp = NULL;
    stringstream ss(res);
    string token;
    bool found = false;
    while (getline(ss, token, '\n')) {
        grp = new Grupo();
        contadortoken = 0;
        stringstream line(token);
        string tokenLine;
        while (getline(line, tokenLine, ',')) {
            if(contadortoken == 0){
                if(tokenLine == "0"){
                    continue;
                }else{
                    grp->id = tokenLine;
                    if(tokenLine == nameG){
                        found = true;
                    }
                }
            }else if(contadortoken==1){
                if(tokenLine != "G"){
                    grp = NULL;
                    break;
                }
            }else if(contadortoken == 2){
                    grp->name = tokenLine;
            }else{
                break;
            }
            contadortoken++;
        }
        if(grp!=NULL && found){
            return grp;
        }
    }
    if(!found) return NULL;
    return grp;
}


//FUNCION PARA CREAR UN GRUPO
Respuesta CrearGrupo(char *path, char *partition, char grp[], bool flag_recov){
    char *title;
    char *filePath=(char*)"/users.txt";
    int indexInode = BuscarArchivo(filePath,path,partition,&title);
    if(indexInode==-1){
        return ERR_IRRECONOCIBLE;
    }
    int startsuperb = -1;
    SuperBlock *superb = ReadSuperBlock(path,partition,&startsuperb);
    if(superb==NULL){
        return ERR_IRRECONOCIBLE;
    }
    string resContent = getContenidoArchivo(indexInode,path,superb);
    char *content = &resContent[0];
    int contadorGrupos=ContarGrupos(content);
    Grupo *grpp=getGrupo(grp,content);
    if(grpp != NULL){
        return ERR_GRP_EX;
    }
    string newContent = "";
    int contador = 0;
    while(resContent[contador]!='\0'){
        newContent+=resContent[contador];
        contador++;
    }
    newContent+= to_string(contadorGrupos+1);
    newContent+=",G,";
    newContent+=grp;
    newContent+="\n";
    Respuesta r = ReemplazarContenido(indexInode,&newContent[0],path,partition);
    if(r == CORRECTO && !flag_recov){
        //AGREGAR A JOURNAL
        Journal *newj = new Journal();
        newj->j_operation = ADDGRUPO;
        newj->j_group =grp;
        getFecha(newj->j_date);
        CrearArchivoJournal(superb,startsuperb,path,newj);
    }
    delete superb;
    return r;
}

//FUNCION PARA ELIMINAR UN GRUPO
Respuesta BorrarGrupo(char path[], char partition[], char name[], bool flag_recov){
    char *title;
    char *filePath=(char*)"/users.txt";
    int indexInode = BuscarArchivo(filePath,path,partition,&title);
    if(indexInode==-1){
        return ERR_IRRECONOCIBLE;
    }
    int startsuperb = -1;
    SuperBlock *superb = ReadSuperBlock(path,partition,&startsuperb);
    if(superb==NULL){
        return ERR_IRRECONOCIBLE;
    }
    string content = getContenidoArchivo(indexInode,path,superb);
    stringstream ss(content);
    string token;
    string newContent="";
    int contadorToken = 0;
    bool found = false;
    bool save = false;
    while (getline(ss, token, '\n')) {
        if(!found){
            stringstream ss2(token);
            string tokenLine;
            string newline="";
            contadorToken = 0;
            while (getline(ss2, tokenLine, ',')) {
                if(token!=""){
                    if(contadorToken == 0){
                        if(tokenLine != "0"){
                            newline +="0,";
                        }else{
                            newline+=tokenLine;
                            newline+=",";
                        }
                    }else if(contadorToken == 1){
                        if(tokenLine != "G"){
                            break;
                        }else{
                            newline+="G,";
                        }
                    }else if(contadorToken == 2){
                        newline+=tokenLine;
                        newline+="\n";
                        if(name == tokenLine){
                            save = true;
                            found = true;
                        }else{
                            break;
                        }
                    }
                }
                contadorToken++;
            }
            if(save){
                newContent+=newline;
                newContent+="\n";
            }else{
                newContent+=token;
                newContent+="\n";
            }
        }else{
            newContent+=token;
            newContent+="\n";
        }
    }
    char *my_argument = const_cast<char*> (newContent.c_str());
    Respuesta r = ReemplazarContenido(indexInode,my_argument,path,partition);
    if(r == CORRECTO && !flag_recov){
        //AGREGAR A JOURNAL
        Journal *newj = new Journal();
        newj->j_operation = DELGRUPO;
        newj->j_group =name;
        getFecha(newj->j_date);
        CrearArchivoJournal(superb,startsuperb,path,newj);
    }
    delete superb;
    return r;
}

//----------------------------- USUARIOS COMANDOS MKUSR Y RMUSR ------------------------

//FUNCION PARA DEVOLVER EL NUMERO DE USUARIOS CREADOS
int ContarUsuarios(char contentUsers[]){
    int contadortoken;
    stringstream ss(contentUsers);
    string token;
    int contadorUsuarios = 0;
    while(getline(ss, token, '\n')) {
        if(token!=""){
            contadortoken = 0;
            stringstream line(token);
            string tokenLine;
            while(getline(line, tokenLine, ',')) {
                if(contadortoken == 0){
                    if(tokenLine == "0"){
                        continue;
                    }
                }else if(contadortoken==1){
                    if(tokenLine == "U"){
                        contadorUsuarios++;
                    }else{
                        break;
                    }
                }else{
                    break;
                }
                contadortoken++;
            }
        }
    }
    return contadorUsuarios;
}

//FUNCION QUE RETORNA EL USUARIO
Usuario *getUsuario(char usr[], char *contentUsers){
    int contadortoken;
    string nameUser(usr);
    Usuario *user = NULL;
    stringstream ss(contentUsers);
    string token;
    while(getline(ss, token, '\n')) {
        if(token!=""){
            user = new Usuario();
            contadortoken = 0;
            stringstream line(token);
            string tokenLine;
            while(getline(line, tokenLine, ',')) {
                if(tokenLine!=""){
                    if(contadortoken == 0){
                        if(tokenLine == "0"){
                            continue;
                        }else{
                            user->id = tokenLine;
                        }
                    }else if(contadortoken==1){
                        if(tokenLine != "U"){
                            user = NULL;
                            break;
                        }
                    }else if(contadortoken == 2){
                        user->group = tokenLine;
                    }else if(contadortoken == 3){
                        if(tokenLine == nameUser ){
                            user->name = tokenLine;
                        }else{
                            user = NULL;
                            break;
                        }
                    }else if(contadortoken == 4){
                        user->pwd = tokenLine;
                    }else{
                        break;
                    }
                    contadortoken++;
                }
            }
            if(user!=NULL){
                Grupo *grp = getGrupo(&user->group[0],contentUsers);
                if(grp!=NULL){
                    user->group = grp->id;
                }
                return user;
            }
        }
    }

    if(user!=NULL){
        Grupo *grp = getGrupo(&user->group[0],contentUsers);
        if(grp!=NULL){
            user->group = grp->id;
        }
    }

    return user;
}

//FUNCION QUE RETORNA EL USUARIO Y LO INSERTA EN EL ARCHIVO
Usuario *getUsuario(char usr[], char path[], char namePartition[]){
    char *title;
    char *filePath=(char*)"/users.txt";
    string res = BuscarContenidoArchivo(filePath,path,namePartition,&title);
    return getUsuario(usr,&res[0]);
}


//FUNCION QUE RETORNA EL USUARIO QUE SE BUSCA POR ID
Usuario *getUsuarioId(char id[], char path[], char namePartition[]){
    char *title;
    char *filePath=(char*)"/users.txt";
    string res = BuscarContenidoArchivo(filePath,path,namePartition,&title);
    int contadortoken;
    string idUser(id);
    Usuario *user = NULL;
    stringstream ss(res);
    string token;
    bool found = false;
    while(getline(ss, token, '\n')) {
        if(token!=""){
            user = new Usuario();
            contadortoken = 0;
            stringstream line(token);
            string tokenLine;
            while (std::getline(line, tokenLine, ',')) {
                if(tokenLine!=""){
                    if(contadortoken == 0){
                        if(tokenLine == "0"){
                            continue;
                        }else{
                            user->id = tokenLine;
                            if(tokenLine == idUser ){
                                found = true;
                            }
                        }
                    }else if(contadortoken==1){
                        if(tokenLine != "U"){
                            user = NULL;
                            break;
                        }
                    }else if(contadortoken == 2){
                        user->group = tokenLine;
                    }else if(contadortoken == 3){
                        user->name = tokenLine;
                    }else if(contadortoken == 4){
                        user->pwd = tokenLine;
                    }else{
                        break;
                    }
                    contadortoken++;
                }
            }
            if(user!=NULL && found){
                return user;
            }
        }
    }
    if(!found) return NULL;
    return user;
}

//FUNCION PARA CREAR UN USUARIO
Respuesta CrearUsuario(char *path, char *partition, char usr[], char pwd[], char grp[], bool flag_recov){
    char *title;
    char *filePath= (char*)"/users.txt";
    int indexInode = BuscarArchivo(filePath,path,partition,&title);
    if(indexInode==-1){
        return ERR_IRRECONOCIBLE;
    }
    int startsuperb = -1;
    SuperBlock *superb = ReadSuperBlock(path,partition,&startsuperb);
    if(superb==NULL){
        return ERR_IRRECONOCIBLE;
    }
    string resContent = getContenidoArchivo(indexInode,path,superb);
    char *content = &resContent[0];
    Grupo *grpp = getGrupo(grp,content);
    if(grpp == NULL){
        return ERR_GRP_NOEX;
    }
    int contadorUsuarios = ContarUsuarios(content);
    Usuario *user = getUsuario(usr,content);
    if(user != NULL){
        return ERR_USR_EX;
    }
    string newContent = "";
    int contador = 0;
    while(resContent[contador]!='\0'){
        newContent+=resContent[contador];
        contador++;
    }
    newContent+= to_string(contadorUsuarios+1);
    newContent+=",U,";
    newContent+=usr;
    newContent+=",";
    newContent+=grp;
    newContent+=",";
    newContent+=pwd;
    newContent+="\n";
    Respuesta r = ReemplazarContenido(indexInode,&newContent[0],path,partition);
    if(r == CORRECTO && !flag_recov){
        //AGREGAR A JOURNAL
        Journal *newj = new Journal();
        newj->j_operation = ADDUSUARIO;
        newj->j_user =usr;
        newj->j_group = grp;
        newj->j_content = pwd;
        getFecha(newj->j_date);
        CrearArchivoJournal(superb,startsuperb,path,newj);
    }
    delete superb;
    return r;
}

//FUNCION PARA BORRAR UN USUARIO
Respuesta BorrarUsuario(char path[], char partition[], char name[], bool flag_recov){
    char *title;
    char *filePath=(char*)"/users.txt";
    int indexInode = BuscarArchivo(filePath,path,partition,&title);
    if(indexInode == -1){
        return ERR_IRRECONOCIBLE;
    }
    int startsuperb = -1;
    SuperBlock *superb = ReadSuperBlock(path,partition,&startsuperb);
    if(superb==NULL){
        return ERR_IRRECONOCIBLE;
    }
    string content = getContenidoArchivo(indexInode,path,superb);
    //if(content!=NULL)return ERROR_UNHANDLED;
    stringstream ss(content);
    string token;
    string newContent="";
    int contadorToken = 0;
    bool found = false;
    bool save=false;
    while(getline(ss, token, '\n')) {
        if(!found){
            stringstream ss2(token);
            string tokenLine;
            string newline="";
            contadorToken = 0;
            while(getline(ss2, tokenLine, ',')) {
                if(token!=""){
                    if(contadorToken == 0){
                        if(tokenLine != "0"){
                            newline +="0,";
                        }else{
                            newline+=tokenLine;
                            newline+=",";
                        }
                    }else if(contadorToken == 1){
                        if(tokenLine != "U"){
                            break;
                        }else{
                            newline+="U,";
                        }
                    }else if(contadorToken == 2){
                        newline+=tokenLine;
                        newline+=",";
                        if(name == tokenLine){
                            save = true;
                            found = true;
                        }else{
                            break;
                        }
                    }else if(contadorToken == 3){
                        newline+=tokenLine;
                        newline+=",";
                    }else{
                        newline+=tokenLine;
                        newline+="\n";
                    }
                }
                contadorToken++;
            }
            if(save){
                newContent+=newline;
                newContent+="\n";
            }else{
                newContent+=token;
                newContent+="\n";
            }
        }else{
            newContent+=token;
            newContent+="\n";
        }
    }
    char *my_argument = const_cast<char*> (newContent.c_str());
    Respuesta r = ReemplazarContenido(indexInode,my_argument,path,partition);
    if(r == CORRECTO && !flag_recov){
        //AGREGAR A JOURNAL
        Journal *newj = new Journal();
        newj->j_operation = DELUSUARIO;
        newj->j_user =name;
        getFecha(newj->j_date);
        CrearArchivoJournal(superb,startsuperb,path,newj);
    }
    delete superb;
    return r;
}


//------------------------------ COMANDO MKDIR -------------------
//FUNCION PARA CREAR DIRECTORIOS
Respuesta CrearCarpeta(bool recursivo, char id[], char path[], bool flag_recov){
    Discos_Montados *disco = getDiscoMontado(id);
    if(disco == NULL){
        return ERR_IRRECONOCIBLE;
    }
    Particiones_Montadas *part = getParticionMontada(id);
    if(part == NULL){
        return ERR_IRRECONOCIBLE;
    }
    //VERIFICAR ESPACIO PARA CREAR INODOS Y BLOQUES
    int startsuperb;
    SuperBlock *superb = ReadSuperBlock(disco->path, part->name, &startsuperb);
    if(superb == NULL){
        return ERR_IRRECONOCIBLE;
    }
    int indexPadre = 0;
    int indexBloqueActual = 0;
    stringstream ss(path);
    string token;
    string dirPad = "/";
    while(getline(ss, token, '/')){
        if(token != ""){
            if(ss.tellg() == -1){
                Respuesta res = CrearNodoCarpeta(&dirPad[0], &token[0], disco->path, superb, &indexPadre, &indexBloqueActual);
                if(res != CORRECTO)return res;
            }else{
                int indexBloque = BuscarCarpeta(&token[0], disco->path, &indexPadre, superb);
                if(indexBloque != -1){
                    indexBloqueActual = indexBloque;
                }else{
                    if(recursivo){
                        Respuesta res = CrearNodoCarpeta(&dirPad[0], &token[0], disco->path, superb, &indexPadre, &indexBloqueActual);
                        if(res != CORRECTO){
                            return res;
                        }
                    }else{
                        return ERR_DIR_NOEX;
                    }
                }
            }
            dirPad = token;
        }
    }
    //ESCRIBIR EN EL SUPER BLOQUE
    CrearArchivoSuperBlock(superb, disco->path, startsuperb);
    if(!flag_recov){
        //AGREGAR AL JOURNAL
        Journal *newj = new Journal();
        newj->j_operation = MAKEDIR;
        newj->j_path = path;
        newj->j_boolean = recursivo;
        newj->j_group = login_activo->id_grupo;
        newj->j_user = login_activo->id_usuario;
        newj->j_perms = 777;
        getFecha(newj->j_date);
        CrearArchivoJournal(superb, startsuperb, disco->path, newj);
    }
    return CORRECTO;
}
//---------------------------------------------------------------

//-------------------- COMANDO MKFILE ---------------------------
//FUNCION PARA CREAR ARCHIVOS
Respuesta CrearArchivo(char newPath[], bool createPath, int size, char path[], char namePartition[], bool flag_recov){
    //generar texto
    char *txt = (char*)malloc(sizeof(char)*size);
    int i;
    char caracter = '0';
    for(i=0;i<size;i++){
        txt[i] =caracter;
        caracter++;
        if(caracter>'9'){
            caracter = '0';
        }
    }
    Respuesta res = CrearArchivosEscritos(newPath,createPath,txt,size,path,namePartition);
    if(res == CORRECTO && !flag_recov){
        //AGREGAR A JOURNAL
        Journal *newj = new Journal();
        newj->j_operation = MAKEFILE_SIZE;
        newj->j_path = newPath;
        newj->j_group = login_activo->id_grupo;
        newj->j_user = login_activo->id_usuario;
        newj->j_size = size;
        newj->j_perms = 664;
        newj->j_boolean = createPath;
        getFecha(newj->j_date);

        int startsuperb;
        SuperBlock *superb = ReadSuperBlock(path,namePartition,&startsuperb);
        if(superb==NULL){
            return ERR_IRRECONOCIBLE;
        }
        CrearArchivoJournal(superb,startsuperb,path,newj);
        delete superb;
    }
    return res;
}

//FUNCION PARA CREAR ARCHIVOS CON PARAMETRO CONT
Respuesta CrearArchivo(char newPath[], bool createPath, char pathFile[], char path[], char namePartition[], bool flag_recov){
    FILE *fileText;
    fileText = fopen(pathFile,"r+");
    if(fileText==NULL){
        cout<<"ERROR AL ABRIR EL ARCHIVO EN LA RUTA:  \""<<pathFile<<"\"\n";
        return ERR_IRRECONOCIBLE;
    }
    fseek(fileText, 0L, SEEK_END);
    int file_size = ftell(fileText);
    char txt[file_size];
    fseek(fileText,0L,SEEK_SET);
    fread(txt,file_size,1,fileText);
    fclose(fileText);
    Respuesta res = CrearArchivosEscritos(newPath,createPath,txt,file_size,path,namePartition);
    if(res == CORRECTO && !flag_recov){
        //AGREGAR A JOURNAL
        Journal *newj = new Journal();
        newj->j_operation = MAKEFILE_PATH;
        newj->j_path = newPath;
        newj->j_group = login_activo->id_grupo;
        newj->j_user = login_activo->id_usuario;
        newj->j_content = pathFile;
        newj->j_boolean = createPath;
        newj->j_perms = 664;
        getFecha(newj->j_date);
        int startsuperb;
        SuperBlock *superb = ReadSuperBlock(path,namePartition,&startsuperb);
        if(superb==NULL){
            return ERR_IRRECONOCIBLE;
        }
        CrearArchivoJournal(superb,startsuperb,path,newj);
        delete superb;
    }
    return res;
}

//--------------------------- COMANDO CAT --------------------------------

//FUNCION PARA EL COMANDO CAT
Respuesta Cat(char filePath[], char path[], char partition[]){
    char *title;
    string res = BuscarContenidoArchivo(filePath,path,partition,&title);
    cout<<res<<endl;
    return CORRECTO;
}

//-------------------------- COMANDO EDIT --------------------------------

//FUNCION PARA EL COMANDO EDIT
Respuesta Edit(char pathFile[], char newCont[], char path[], char namePart[], bool flag_recov){
    char *title;
    int indexInode = BuscarArchivo(pathFile,path,namePart,&title);
    if(indexInode==-1){
        return ERR_IRRECONOCIBLE;
    }
    int startsuperb = -1;
    SuperBlock *superb = ReadSuperBlock(path,namePart,&startsuperb);
    if(superb==NULL){
        return ERR_IRRECONOCIBLE;
    }
    string content  = getContenidoArchivo(indexInode,path,superb);
    string newContent = "";
    int contador = 0;
    while(content[contador]!='\0'){
        newContent+=content[contador];
        contador++;
    }
    newContent+=newCont;
    Respuesta r = ReemplazarContenido(indexInode,&newContent[0],path,namePart);
    if(r == CORRECTO && !flag_recov){
        //AGREGAR A JOURNAL
        Journal *newj = new Journal();
        newj->j_operation = EDITFILE;
        newj->j_user = login_activo->id_usuario;
        newj->j_group = login_activo->id_usuario;
        newj->j_content = newCont;
        newj->j_path = pathFile;
        getFecha(newj->j_date);
        CrearArchivoJournal(superb,startsuperb,path,newj);
    }
    delete superb;
    return r;
}

//--------------------- COMANDO LOSS ---------------------------------

//FUNCION PARA EL COMANDO LOSS
Respuesta Loss(char path[], char name[]){
    int startsuperb;
    SuperBlock *superb = ReadSuperBlock(path,name,&startsuperb);
    if(superb==NULL){
        return ERR_IRRECONOCIBLE;
    }
    if(superb->s_filesystem_type == EXT2){
        return ERR_FILESYSTEM;
    }
    //limpiando bitmaps
    int contador;
    FILE * arch;
    arch = fopen (path,"rb+");
    if (arch==NULL)
    {
        cout<<"ERROR AL ABRIR EL DISCO... \n";
        return ERR_IRRECONOCIBLE;
    }
    //LIMPIAR BITMAP DE INODOS
    fseek(arch, superb->s_bm_inode_start, SEEK_SET);
    contador=0;
    while(contador<superb->s_inodes_count){
        fwrite("\0", sizeof(char), 1, arch);
        contador++;
    }
    //LIMPIAR BITMAP DE BLOQUES
    fseek(arch, superb->s_bm_block_start, SEEK_SET);
    contador=0;
    while(contador<superb->s_blocks_count){
        fwrite("\0", sizeof(char), 1, arch);
        contador++;
    }
    //LIMPIAR BITMAP DE INODOS
    fseek(arch, superb->s_bm_inode_start, SEEK_SET);
    contador=0;
    while(contador<superb->s_blocks_count){
        fwrite("\0", sizeof(char), 1, arch);
        contador++;
    }
    //LIMPIAR INODOS
    fseek(arch, superb->s_inode_start, SEEK_SET);
    contador=0;
    while(contador<(superb->s_inodes_count*superb->s_inode_size)){
        fwrite("\0", sizeof(char), 1, arch);
        contador++;
    }
    //LIMPIAR BLOQUES
    fseek(arch, superb->s_block_start, SEEK_SET);
    contador=0;
    while(contador<(superb->s_blocks_count*superb->s_block_size)){
        fwrite("\0", sizeof(char), 1, arch);
        contador++;
    }
    //cerrando stream
    fclose (arch);
    return CORRECTO;
}

//----------------- COMANDO RECOVERY ----------------------------

//FUNCION PARA EL COMANDO RECOVERY
Respuesta Recovery(SuperBlock *superb, int startsuperb, char path[], char namePartition[], char id[]){
    int startOperations = startsuperb+sizeof(SuperBlock);
    Formatear(path,namePartition, FULL, EXT3, true);
    FILE * arch;
    int contador = 0;
    arch = fopen (path,"rb+");
    if (arch==NULL)
    {
        cout<<"ERROR AL ABRIR EL DISCO... \n";
        return ERR_IRRECONOCIBLE;
    }
    Journal *journal = (Journal*)malloc(sizeof(Journal));
    fseek(arch, startOperations, SEEK_SET);
    while(contador<superb->s_inodes_count){
        fread(journal,sizeof(Journal),1,arch);
        if(journal == NULL){
            return ERR_RECOVERY;
        }
        if(journal->j_operation == VACIO){
            return CORRECTO;
        }
        switch (journal->j_operation) {
            case MAKEDIR:
                CrearCarpeta(journal->j_boolean,id,journal->j_path,true);
                break;
            case MAKEFILE_PATH:
                CrearArchivo(journal->j_path,journal->j_boolean,journal->j_content,path,namePartition,true);
                break;
            case MAKEFILE_SIZE:
                CrearArchivo(journal->j_path,journal->j_boolean,journal->j_size,path,namePartition,true);
                break;
            case ADDGRUPO:
                CrearGrupo(path,namePartition,journal->j_group,true);
                break;
            case RMGRP:
                BorrarGrupo(path,namePartition,journal->j_group,true);
                break;
            case ADDUSUARIO:
                CrearUsuario(path,namePartition,journal->j_user,journal->j_content,journal->j_group,true);
                break;
            case DELUSUARIO:
                BorrarUsuario(path,namePartition,journal->j_user,true);
                break;
            case EDITFILE:
                Edit(journal->j_path,journal->j_content,path,namePartition,true);
                break;
            default:
                break;
        }

        contador++;
    }
  fclose (arch);
  return CORRECTO;
}