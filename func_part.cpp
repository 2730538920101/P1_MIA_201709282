#include "func_part.h"
#include "globales.h"
#include <iostream>

using namespace std;

//-------------------------------FDISK -------------------------------------------------------------------

//FUNCION PARA CREAR LAS PARTICIONES, INSTANCIAR EL OBJETO
Respuesta CrearParticion(int tam, Tipounit unit, char path[], char nomDisco[],Tipoparticion tipo, Tipofit fit, char name[]){
    //BUFFER
    char path_comp[200];
    LimpiarArray(path_comp, sizeof(path_comp));
    getPathOfDisk(path, nomDisco, path_comp);
    //ESCRIBIR EN EL DISCO
    Respuesta res = genParticion(tam, unit, path_comp, tipo, fit, name);
    //SI EL PROCESO FUE EXITOSO ESCRIBIR EN EL RAID
    if(res == CORRECTO){
        char nameRaid[50];
        LimpiarArray(nameRaid, 50);
        strcat(nameRaid, nomDisco);
        strcat(nameRaid,"_Error");
        LimpiarArray(path_comp, sizeof(path_comp));
        getPathOfDisk(path, nameRaid, path_comp);
        //ESCRIBIR ARCHIVO
        genParticion(tam, unit, path_comp, tipo, fit, name);
    }
    return res;
}

//FUNCION PARA INSTANCIAR UN OBJETO SEGUN EL TIPO DE PARTICION QUE DESEA, PRIMARIA, LOGICA, EXTENDIDA
Respuesta genParticion(int tam, Tipounit unit, char path[], Tipoparticion tipo, Tipofit fit, char name[]){
    //OBTENER LOS DATOS DEL MBR
    MasterBootRecord *disco = getDataMBR(path);
    if(disco == NULL){
        return ERR_IRRECONOCIBLE;
    }
    //DEFINIR EL TAMANO DE LA PARTICION
    long tam_final = getSize(tam, unit);
    //VALIDAR QUE EL ESPACIO SEA MAYOR QUE CERO
    if(tam_final <= 0){
        return ERR_TAM_MIN;
    }
    //GENERAR LA PARTICION SEGUN EL TIPO
    switch (tipo){
        case P:
        {
            return genPrimaria(tam_final, fit, name, disco, path);
        }
        case E:
        {
            return genExtendida(tam_final, fit, name, disco, path);
        }
        case L:
        {
            return genLogica(tam_final, fit, name, disco, path);
        } 
    }
    //LIBERAR LA MEMORIA
    delete disco;
    return CORRECTO;
}


//FUNCION PARA INSTANCIAR UN OBJETO DE TIPO PARTICION PRIMARIA
Respuesta genPrimaria(long tam, Tipofit fit, char name[], MasterBootRecord *disco, char path[]){
    int i;
    int inicio;
    //UBICAR LA DIRECCION DE INICIO DE ESCRITURA PARA LA PARTICION
    Respuesta res = getDireccionInicio(disco, (Tipofit)disco->disk_fit, tam, &inicio);
    cout<<inicio<<endl;
    if(res != CORRECTO){
        return res;
    }
    //BUSCAR SI LA PARTICION EXISTE
    Partition *part;
    bool flag_esp = false;
    for(i = 0; i < 4; i++){
        part = &disco->particiones[i];
        if(part->part_status == INACTIVO){
            flag_esp = true;
            break;
        }else{
            if(strcmp(part->part_name, name) == 0){
                return ERR_PART_EX;
            }
        }
    }
    //SI EXISTE ESPACIO INGRESSAR LOS DATOS Y REESCRIBIR EL MBR
    if(flag_esp){
        part = &disco->particiones[i];
        part->part_fit = fit;
        strcpy(part->part_name, name);
        part->part_size = tam;
        part->part_start = inicio;
        part->part_type = P;
        part->part_status = ACTIVO;
        ReemplazarMBR(disco, path);
        return CORRECTO;
    }else{
        return ERR_PP_LLENA;
    }
}

//FUNCION PARA INSTANCIAR UN OBJETO DE TIPO PARTICION LOGICA
Respuesta genLogica(long tam, Tipofit fit, char name[], MasterBootRecord *disco, char path[]){
    //OBTENER EL PRIMER EBR
    ExtendedBootRecord *primero = getPrimerEBR(disco, path);
    int nueva_pos = 0;
    //VALIDAR SI EL EBR EXISTE
    if(primero == NULL){
        return ERR_PE_NOEX;
    }
    //ESPACIO DE MEMORIA AUXILIAR PARA LOS DATOS DEL EBR
    ExtendedBootRecord *ebr_aux = (ExtendedBootRecord*)malloc(sizeof(ExtendedBootRecord));
    //ASIGNAR DATOS A LA VARIABLE AUX
    ebr_aux->part_fit = fit;
    strcpy(ebr_aux->part_name, name);
    ebr_aux->part_next = -1;
    ebr_aux->part_size = tam;
    ebr_aux->part_status = ACTIVO;
    //VALIDAR SI EL PRIMER EBR ES EL UNICO QUE EXISTE Y REEMPLAZARLO
    if(primero->part_next == -1 && primero->part_status == INACTIVO){
        //UBICAR LA DIRECCION DE ESCRITURA DEL EBR
        ebr_aux->part_start = primero->part_start;
        //VALIDAR EL ESPACIO EN EL DISCO
        if(tam > primero->part_size){
            return ERR_ESPACIO_INS;
        }
        //ESCRIBIR EL ARCHIVO
        CrearArchivoEBR(ebr_aux, path, primero->part_start - sizeof(ExtendedBootRecord));
    }else{
        //SI EXISTEN MAS PARTICIONES AGREGAR AL FINAL DE LA LISTA
        bool flag = true;
        //RECORRER LAS EXTENDIDAS
        while(flag){
            if(primero->part_next != -1){
                //LEER EL STRUCT
                primero = getDataEBR(primero->part_next, path);
            }else{
                flag = false;
            }
        }
        //UBICAR LA NUEVA POSICION DEL EBR
        nueva_pos = primero->part_start + primero->part_size;
        primero->part_next = nueva_pos;
        //ESCRIBIR EL EBR
        CrearArchivoEBR(primero, path,  primero->part_start - sizeof(ExtendedBootRecord));
        ebr_aux->part_start = nueva_pos + sizeof(ExtendedBootRecord);
        CrearArchivoEBR(ebr_aux, path, nueva_pos);
    }
    return CORRECTO;
}

//FUNCION PARA INSTANCIAR UN OBJETO DE TIPO PARTICION EXTENDIDA
Respuesta genExtendida(long tam, Tipofit fit, char name[], MasterBootRecord *disco, char path[]){
    //Auxiliar para almacenar el punto de inicio donde se debe escribir la particion
    int inicio;
    int i;
    //OBTENER LA DIRECCION DE INICIO DE ESCRITURA DE LA PARTICION
    Respuesta res = getDireccionInicio(disco, (Tipofit)disco->disk_fit, tam, &inicio);
    //VERIFICAR SI SE REALIZO ADECUADAMENTE EL PROCESO Y RETORNAR LA RESPUESTA
    if(res != CORRECTO){
        return res;
    }
    //BUSCAR LA PARTICION
    Partition *part;
    //bandera si existe particion extendida
    bool flag_ext = true;
    //bandira si hay espacio en el disco
    bool flag_esp = false;
    //validar si hay particiones extendidas
    for(i = 0; i < 4; i++){
        part = &disco->particiones[i];
        //validacion
        if(part->part_type == E){
            flag_ext = false;
            break;
        }
    }
    //Si la particion extendida verificar si hay espacio
    if(flag_ext){
        for(i = 0; i < 4; i++){
            part = &disco->particiones[i];
            //validar el espacio
            if(part->part_status == INACTIVO){
                flag_esp = true;
                break;
            }else{
                //validar que exista la particion
                if(strcmp(part->part_name, name) == 0){
                    return ERR_PART_EX;
                }
            }
        }
    }
    //Si hay espacio y hay una particion extendida escribir en el archivo
    if(flag_ext){
        if(flag_esp){
            part = &disco->particiones[i];
            part->part_fit = fit;
            strcpy(part->part_name, name);
            part->part_size = tam;
            part->part_start = inicio;
            part->part_type = E;
            part->part_status = ACTIVO;
            //REEMPLAZAR LOS DATOS DEL DISCO
            ReemplazarMBR(disco, path);
            //NUEVOS DATOS EBR
            genEBR(part, path);
            //LLENAR ESPACIO ADICIONAL CON CEROS
            LlenarCeros(path, part->part_start + sizeof(ExtendedBootRecord), tam);
            return CORRECTO;
        }else{
            return ERR_PP_LLENA;
        }
    }else{
        return ERR_PE_EX;
    }
    return CORRECTO;
}

//Funcion para crear una particion extendida
void genEBR(Partition *particion, char path[]){
    //INICIALIZAR ESPACIO DE MEMORIA PARA COPIAR DATOS DE LA PARTICION EXTENDIDA
    ExtendedBootRecord *part_ext = (ExtendedBootRecord*)malloc(sizeof(ExtendedBootRecord));
    //OBTENER DATOS DE LA PARTICION
    part_ext->part_fit = particion->part_fit;
    strcpy(part_ext->part_name, particion->part_name);
    part_ext->part_next = -1;
    part_ext->part_size = particion->part_size;
    part_ext->part_start = particion->part_start + sizeof(ExtendedBootRecord);
    part_ext->part_status = INACTIVO;
    //Escribir informacion de la particion extendida en un archivo
    CrearArchivoEBR(part_ext, path, particion->part_start);
}

//FUNCION PARA ESCRIBIR EL ARCHIVO DEL DISCO EL EBR
void CrearArchivoEBR(ExtendedBootRecord *part_ext, char path[], int inicio){
    //iniciar el puntero al archivo
    FILE *arch;
    //dar permisos de lectura y escritura al archivo binario
    arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL ARCHIVO... "<<endl;
        return;
    }
    //Ubicar el puntero en donde se debe escribir el EBR
    fseek(arch, inicio, SEEK_SET);
    fwrite(part_ext, sizeof(ExtendedBootRecord), 1, arch);
    fclose(arch);
}

//FUNCION QUE SETEA LA DIRECCION DONDE ESTA EL ESPACIO DISPONIBLE EN EL DISCO
//VERIFICA LA MEMORIA VIRTUAL
Respuesta getDireccionInicio(MasterBootRecord *disco, Tipofit fit, long tam, int *inicio){
    //Inicializar el punto de inicio en -1
    *inicio = -1;
    int i;
    int contPart = 0;
    //virtualizar las particiones
    Espacio_v *parts[4];
    bool empty =  true;
    //inicializar el espacio virtual que ya esta utilizado por el MBR
    for(i = 0; i < 4; i++){
        if(disco->particiones[i].part_status == ACTIVO){
            parts[contPart] = new Espacio_v(disco->particiones[i].part_size, disco->particiones[i].part_start, OCUPADO);
            empty = false;
            contPart++;
        }
    }
    //SI EL DISCO ESTA VACIO LA PRIMERA PARTICION SE ESCRIBE DESPUES DE LA INFORMACION DEL MBR
    if(empty){
        if(disco->mbr_tamano >= tam){
            *inicio = sizeof(MasterBootRecord);
        }
    }else{
        //ORDENAR SECUENCIALMENTE LAS PARTICIONES 
        Espacio_v *aux;
        for(int i = 0; i < contPart; i++){
            for(int j = 0; j < contPart -1; j++){
                if(parts[j]->inicio > parts[j+1]->inicio){
                    aux = parts[j];
                    parts[j] = parts[j+1];
                    parts[j+1] = aux;
                }
            }
        }
        //DIRECCION DE INICIO Y DE FIN DEL MBR ESCRITO
        int init = sizeof(MasterBootRecord);
        int fin = sizeof(MasterBootRecord)-1;
        //INICIAR ESPACIOS LIBRES EN LA MEMORIA
        Espacio_v *libres[5];
        int contEsp = 0;
        //CREAR ESPACIOS LIBRES EN LA ESTRUCTURA
        for(i = 0; i < contPart; i++){
            fin = parts[i]->inicio;
            if(fin - init > 0){
                libres[contEsp] = new Espacio_v(fin - init, init, LIBRE);
                contEsp++;
            }
            init = parts[i]->inicio + parts[i]->size;
        }
        libres[contEsp] = new Espacio_v(disco->mbr_tamano - init + sizeof(MasterBootRecord), init, LIBRE);
        contEsp++;
        //ORDENAR SECUENCIALMENTE LOS ESPACIOS LIBRES SEGUN EL TAMANO
        for(int i = 0; i < contEsp; i++){
            for(int j = 0; j < contEsp - 1; j++){
                if(libres[j]->size > libres[j+1]->size){
                    aux = libres[j];
                    libres[j] = libres[j+1];
                    libres[j+1] = aux;
                }
            }
        }
        //MANDAR LA DIRECCION DE INICIO SEGUN EL AJUSTE SELECCIONADO
        switch (fit){
        case FF:
        //EL PRIMER AJUSTE CREA LA PARTICION EN EL PRIMER ESPACIO LIBRE CON SUFICIENTE ESPACIO PARA CREARLA
            for(i = 0; i < contEsp; i++){
                if(tam <= libres[i]->size){
                    *inicio = libres[i]->inicio;
                    break;
                }
            }
            break;
        case WF:
        //EL PEOR AJUSTE CREA LA PARTICION EN EL ESPACIO LIBRE DE MAYOR TAMANO
            if(tam <= libres[contEsp -1]->size){
                *inicio = libres[contEsp -1]->inicio;
            }
            break;
        case BF:
        //EL MEJOR AJUSTE CREA LA PARTICION EN EL ESPACIO LIBRE QUE TENGA SUFICIENTE ESPACIO PARA CREARLA
            int tams[contEsp];
            for(i = 0; i < contEsp; i++){
                tams[i] = libres[i]->size - tam;
            }
            int best = 0;
            for(i = 0; i < contEsp; i++){
                if(tams[i] < tams[best]){
                    best = i;
                }
            }
            if(best == -1){
                return ERR_ESPACIO_INS;
            }
            *inicio = libres[best]->inicio;
            break;
        }
    }
    //MENSAJE DE ESPACIO INSUFICIENTE EN EL DISCO    
    if(*inicio == -1){
        return ERR_ESPACIO_INS;
    }
    return CORRECTO;   
}


//-------------------------PARAMETRO ADD COMANDO FDISK--------------------------------------------
//FUNCION QUE MODIFICA EL ESPACIO VIRTUAL DE LA PARTICION
Respuesta PartMod(int tam, Tipounit unit, char path[], char name[]){
    //OBTENER DATOS DEL MBR
    MasterBootRecord *disco = getDataMBR(path);
    //verificar si existe el disco
    if(disco == NULL){
        return ERR_IRRECONOCIBLE;
    }
    //OBTENER EL TAMANO A AGREGAR
    long tam_final = getSize(tam, unit);
    //DEFINIR EL ESPACIO VIRTUALIZADO
    Espacio_v *parts[4];
    //CONTADORES
    int contPart = 0;
    int i;
    //RECORRER LAS PARTICIONES
    for(i = 0; i < 4; i++){
        //VALIDAR EL STATUS DE LA PARTICION
        if(disco->particiones[i].part_status == ACTIVO){
            //INICIALIZAR EL ESPACIO VIRTUAL
            parts[contPart] = new Espacio_v(disco->particiones[i].part_size, disco->particiones[i].part_start, OCUPADO);
            contPart++;
        }
    }
    //ORDENAR SECUENCIALMENTE LAS PARTICIONES VIRTUALIZADAS
    Espacio_v *virtual_aux;
    //ORDENAMIENTO
    for(int i = 0; i < contPart; i++){
        for(int j = 0; j < contPart -1; j++){
            //VALIDAR LOS TAMANOS DE LAS PARTICIONES
            if(parts[j]->inicio > parts[j+1]->inicio){
                virtual_aux = parts[j];
                parts[j] = parts[j+1];
                parts[j+1] = virtual_aux;
            }
        }
    }
    //BUSCAR EL SIGUIENTE ESPACIO ANTES DE TERMINAR DE LEER EL DISCO
    Partition *part = NULL;
    int index = 0;
    //recorrer particioned y validar que exista espacio
    for(i = 0; i < 4; i++){
        if(disco->particiones[i].part_status == ACTIVO){
            if(strcmp(disco->particiones[i].part_name, name) == 0){
                part = &disco->particiones[i];
                break;
            }
            index++;
        }
    }

    //VALIDACIONES Y AGREGAR EL TAMANO
    if(part == NULL){
        return ERR_PART_NOEX;
    }else{
        //MODIFICAR EL TAMANO
        if(part->part_size + tam_final <= 0){
            return ERR_TAM_MIN;
        }
        if(index == contPart -1){
            int auxt = part->part_start + part->part_size + tam_final;
            if(disco->mbr_tamano < auxt){
                return ERR_NO_ADD_ESPACIO;
            }
        }else{
            int auxt2 = part->part_start + part->part_size + tam_final;
            if(parts[index + 1]->inicio < auxt2){
                return ERR_NO_ADD_ESPACIO;
            }
        }
        //REESCRIBIR MBR Y ASIGNAR EL NUEVO VALOR AL ESPACIO VIRTUAL
        part->part_size = part->part_size + tam_final;
        ReemplazarMBR(disco, path);
    }
    return CORRECTO;
}



//FUNCION PARA AGREGAR LOS CAMBIOS EN EL MBR
Respuesta AddSizePart(char path[], char nomDisco[], char nomParticion[], int modtam, Tipounit unit){
    //OBTENER LA RUTA DEL DISCO
    char path_comp[200];
    LimpiarArray(path_comp, sizeof(path_comp));
    getPathOfDisk(path, nomDisco, path_comp);
    //ESCRIBIR EL ARCHIVO
    Respuesta res = PartMod(modtam, unit, path_comp, nomParticion);
    if(res == CORRECTO){
        //ESCRIBIR EL RAID
        char nameErr[50];
        LimpiarArray(nameErr, 50);
        strcat(nameErr, nomDisco);
        strcat(nameErr, "_Error");
        LimpiarArray(path_comp, sizeof(path_comp));
        getPathOfDisk(path, nameErr, path_comp);
        PartMod(modtam, unit, path_comp, nomParticion);
    }
    return res;
}

//-------------------------PARAMETRO DELETE COMANDO FDISK-------------------------------------

//FUNCION PARA ELIMINAR UNA PARTICION, ENVIA LOS DATOS A LA FUNCION DELPARTITION
Respuesta DeletePart(char path[], char nomDisco[], char name[], Tipoparticion tipo, Tipocapacidad capacidad){
    //Buffer
    char path_comp[200];
    LimpiarArray(path_comp, sizeof(path_comp));
    getPathOfDisk(path, nomDisco, path_comp);
    //ESCRIBIR EL ARCHIVO
    Respuesta res = DelPartition(path_comp, name, tipo, capacidad);
    if(res == CORRECTO){
        //ESCRIBIR EL RAID
        char nameErr[50];
        LimpiarArray(nameErr, 50);
        strcat(nameErr, nomDisco);
        strcat(nameErr, "_Error");
        LimpiarArray(path_comp, sizeof(path_comp));
        getPathOfDisk(path, nameErr, path_comp);
        //ESCRIBIR ARCHIVO
        DelPartition(path_comp, name, tipo, capacidad);
    }
    return CORRECTO;
}

//FUNCION PARA ELIMINAR UNA PARTICION, ENVIA LOS DATOS ESCRITOS EN EL DISCO
Respuesta  DelPartition(char path[], char name[], Tipoparticion tipo, Tipocapacidad capacidad){
    //OBTENER DATOS DEL MBR
    MasterBootRecord *disco = getDataMBR(path);
    if(disco == NULL){
        return ERR_IRRECONOCIBLE;
    }
    //VALIDAR EL TIPO DE PARTICION A ELIMINAR Y LLAMAR AL METODO RESPECTIVO
    switch(tipo){
        case P:
        case E:
        {
            return DelPrimaria(disco, name, capacidad, path);
        }
        case L:
        {
            return DelLogica(name, disco, path);
        }
    }
    return CORRECTO;
}

//FUNCION PARA ELIMINAR UNA PARTICION PRIMARIA DEL MBR
Respuesta DelPrimaria(MasterBootRecord *disco, char name[], Tipocapacidad capacidad, char path[]){
    //RECORRER LAS PARTICIONES
    for(int i = 0; i < 4; i++){
        //VALIDAR EL ESTADO DE LA PARTICION
        if(disco->particiones[i].part_status == ACTIVO){
            if(strcmp(disco->particiones[i].part_name, name) == 0){
                //ELIMINAR LA PARTICION PRIMARIA
                disco->particiones[i].part_status = INACTIVO;
                LimpiarArray(disco->particiones[i].part_name, 16);
                //delete = full
                if(capacidad == FULL){
                    //si el tipo de borrado es full se llena con ceros el archivo
                    LlenarCeros(path, disco->particiones[i].part_start, disco->particiones[0].part_size);
                }
                //inicializar valores
                disco->particiones[i].part_size = 0;
                disco->particiones[i].part_start = 0;
                ReemplazarMBR(disco, path);
                return CORRECTO;
            }
        }
    }
    return ERR_PART_NOEX;
}

//FUNCION PARA ELIMINAR UNA PARTICION LOGICA DEL EBR
Respuesta DelLogica(char name[], MasterBootRecord *disco, char path[]){
    //OBTENER EL EBR DE LAS PARTICIONES
    ExtendedBootRecord *primero = getPrimerEBR(disco, path);
    //OBTENER LA PARTICION EXTENDIDA
    Partition *extendida = getExtPart(name, disco);
    //VALIDAR EXISTENCIAS
    if(extendida == NULL){
        return ERR_PE_NOEX;
    }
    if(primero == NULL){
        return ERR_PE_NOEX;
    }
    //BANDERAS
    ExtendedBootRecord *anterior = NULL;
    bool flag = true;
    //RECORRER PARTICIONES
    while(flag){
        if(strcmp(primero->part_name, name) == 0){
            //SI ENCUENTRA LA PARTICION ELIMINAR
            if(anterior != NULL){
                anterior->part_next = primero->part_next;
                //ESCRIBIR LOS DATOS EN EL ANTERIOR
                CrearArchivoEBR(anterior, path, anterior->part_start);
            }
        }
        anterior = primero;
        primero = getDataEBR(primero->part_next, path);
        if(primero == NULL){
            flag = false;
        }
    }
    return CORRECTO;
}

//--------------------------------------------------------------------------------------------------------------

//-----------------------------------------------MOUNT----------------------------------------------------------

