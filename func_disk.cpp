#include "func_disk.h"
#include "globales.h"
#include <iostream>
using namespace std;

//FUNCION QUE DEVUELVE UN NUMERO RANDOM QUE IDENTIFICARA EL DISCO
int getSignature(){
    //pasar el tiempo actual a la funcion srand para inicializar la semilla
    srand(time(NULL));
    //guardar el numero random en una variable
    int ran = rand();
    //agregar mas probabilidad de aleatorizacion al random generado como identificador entre 1 y 1000000
    ran = 1 + rand() % (1000);
    return ran;
}

//FUNCION QUE DEVUELVE UN MARCADOR BOOLEANO QUE ES TRUE CUANDO SE CREA Y ESCRIBE EL ARCHIVO MBR
bool CrearArchivoMBR(MasterBootRecord *disk, char path[], char path_comp[]){
    //CREAR UN DIRECTORIO CON EL PATH INGRESADO
    CrearCarpeta(path_comp);
    FILE *arch;
    arch = fopen(path_comp, "wb+");
    //verificar si el archivo se creo correctamente 
    if(arch == NULL){
        cout<<"Error al crear el archivo del MBR... \n";
        return false;
    }else{
        //inicializar con ceros el archivo
        fseek(arch, disk->mbr_tamano, SEEK_SET);
        fwrite("\0", sizeof(char), 1, arch);
        //escribir el MBR en el disco
        fseek(arch, 0, SEEK_SET);
        fwrite(disk, sizeof(MasterBootRecord), 1, arch);
        //cerrar el archivo
        fclose(arch);
        return true;
    }
}

//FUNCION QUE DEVUELVE UNA RESPUESTA DE ERROR O DE SUCCESS AL CREAR UN NUEVO DISCO
Respuesta CrearDisk(int size, Tipofit fit, Tipounit unit, char path[], char name[]){
    //VERIFICAR EL TAMANO
    long tam = getSize(size, unit);
    //INICIALIZAR EL MASTER BOOT RECORD
    MasterBootRecord *disk = (MasterBootRecord*)malloc(sizeof(MasterBootRecord));
    //INGRESAR DATA AL STRUCT
    getFecha(disk->mbr_fecha_creacion);
    disk->disk_fit = fit;
    disk->mbr_disk_signature = getSignature();
    disk->mbr_tamano = tam;
    //INGRESAR PARTICIONES
    for(int i = 0; i < 4; i++){
        disk->particiones[i].part_fit = fit;
        string nombre = "Part_"+to_string(i+1);
        LimpiarArray(disk->particiones[i].part_name, 16);
        strcpy(disk->particiones[i].part_name, nombre.c_str());
        disk->particiones[i].part_size = 0;
        disk->particiones[i].part_start = 0;
        disk->particiones[i].part_status = INACTIVO;
        disk->particiones[i].part_type = P;
    }
    //CREAR LA RUTA DEL DISCO
    char path_comp[200];
    LimpiarArray(path_comp, sizeof(path_comp));
    getPathOfDisk(path, name, path_comp);
    //ESCRIBIR EL MBR
    bool flag = CrearArchivoMBR(disk, path, path_comp);
    if(!flag){
        return ERR_DISK_NO_EX;
    } 
    //ESCRIBIR RAID
    char tipoErr[50];
    LimpiarArray(tipoErr, 50);
    strcat(tipoErr, name);
    strcat(tipoErr, "_Error");
    LimpiarArray(path_comp, sizeof(path_comp));
    getPathOfDisk(path, tipoErr, path_comp);
    CrearArchivoMBR(disk, path, path_comp);
    //liberar memoria
    delete disk;
    return CORRECTO;
}

//FUNCION PARA DAR LECTURA A UN ARCHIVO BINARIO
void ReadDisk(char path[]){
    MasterBootRecord data;
    FILE *arch = fopen(path, "rb+");
    if(arch != NULL){
        fseek(arch, 0, SEEK_SET);
        fread(&data, sizeof(MasterBootRecord), 1, arch);
        cout<<"----DATOS DEL MBR----"<<endl;
        cout<<"MBR SIZE: "<<sizeof(MasterBootRecord)<<endl;
        cout<<"FECHA DE CREACION: "<<data.mbr_fecha_creacion<<endl;
        cout<<"FIT: "<<data.disk_fit<<endl;
        cout<<"SIGNATURE: "<<data.mbr_disk_signature<<endl;
        cout<<"SIZE: "<<data.mbr_tamano<<endl;
        cout<<"----PARTICIONES----"<<endl;
        for(int i =0; i < 4; i++){
            cout<<"PARTICION "<<i+1<<endl;
            cout<<"NAME: "<<data.particiones[i].part_name<<endl;
            cout<<"SIZE: "<<data.particiones[i].part_size<<endl;
            switch(data.particiones[i].part_fit){
                case BF:
                {
                    cout<<"FIT: BF"<<endl;
                }break;
                case FF:
                {
                    cout<<"FIT: FF"<<endl;
                }break;
                case WF:
                {
                    cout<<"FIT: WF"<<endl;
                }break;
                default:
                    cout<<"FIT: ... \n";
            }
            
            switch(data.particiones[i].part_type){
                case P:
                {
                    cout<<"TYPE: P"<<endl;
                }break;
                case E:
                {
                    cout<<"TYPE: E"<<endl;
                }break;
                case L:
                {
                    cout<<"TYPE: L"<<endl;
                }break;
                default:
                    cout<<"TYPE: ... \n";
            }
            
            cout<<"START: "<<data.particiones[i].part_start<<endl;

            switch(data.particiones[i].part_status){
                case ACTIVO:
                {
                    cout<<"STATUS: ACTIVO"<<endl;
                }break;
                case INACTIVO:
                {
                    cout<<"STATUS: INACTIVO"<<endl;
                }break;
                default:
                    cout<<"STATUS: ... \n";
            }
            
            cout<<"------------------------------------"<<endl;
        }
    }else{
        cout<<"EL DISCO NO HA SIDO CREADO EN ESA RUTA... "<<endl;
    }
    fclose(arch);
}


//FUNCION PARA ELIMINAR UN DISCO "RMDISK"
void RemoveDisk(char path[]){
    //Mensaje de advertencia
    cout<<"ADVERTENCIA!!! \n"
    <<"ESTA SEGURO QUE DESEA ELIMINAR EL DISCO? \n"
    <<"INGRESA (S) o (s) PARA CONTINUAR Y (N) o (n) PARA CANCELAR "<<endl;
    //Ingresar el valor
    char res;
    cin>>res;
    //Verificar que el valor ingresado sea correcto
    if(res == 83 || res == 115){
        //ELIMINAR DISCO
        if(DiskExist(path)){
            if(remove(path) != 0){
                cout<<"ERROR AL ELIMINAR EL DISCO... \n";
            }else{
                cout<<"EL DISCO SE HA ELIMINADO EXITOSAMENTE... \n";
            }
        }else{
            cout<<"ERROR AL ELIMINAR EL DISCO, TIENE PARTICIONES MONTADAS EN EL SISTEMA... \n";
        }
    }else if(res == 78 || res == 110){
        cout<<"CANCELANDO LA OPERACION... \n";
    
    }else{
        cout<<"VALOR INGRESADO INCORRECTO... \n";
    }
}

//FUNCION PARA OBTENER LOS DATOS DEL MBR
MasterBootRecord* getDataMBR(char path[]){
    //INICIALIZAR UNA VARIABLE PARA ALMACENAR LOS DATOS
    MasterBootRecord *data;
    data = (MasterBootRecord*)malloc(sizeof(MasterBootRecord));
    //ABRIR ARCHIVO CON PERMISO DE LECTURA
    FILE *arch = fopen(path, "rb+");
    //VERIFICAR QUE NO HAYA ERROR EN EL ARCHIVO
    if(arch == NULL){
        cout<<"EL DISCO NO EXISTE... "<<endl;
        return NULL;
    }
    //UBICAR EL PUNTERO AL PRINCIPIO DEL ARCHIVO
    fseek(arch, 0, SEEK_SET);
    //LEER LOS DATOS DEL ARCHIVO
    fread(data, sizeof(MasterBootRecord), 1, arch);
    //CERRAR EL STREAM
    fclose(arch);
    //RETORNAR EL STRUCT
    return data;
}

//FUNCION PARA VERIFICAR SI UN DISCO YA FUE CREADO
bool DiskExist(char path[]){
    //inicializar un contador para recorrer los discos montados en el sistema
    int diskcont = 0;
    //bandera que indica coincidencia en la busqueda
    bool flag = false;
    //recorrer la lista de discos montados
    while(discos_montados[diskcont] != NULL){
        //compara los nombres de los discos contra el dato ingresado
        if(strcmp(discos_montados[diskcont]->path, path)==0){
            flag = true;
            //salir del ciclo
            break;
        }
        //aumentar el contador
        diskcont++;
    }
    //Retornar un true
    return !flag;
}

//FUNCION PARA VERIFICAR QUE LA PARTICION EXTENDIDA HA SIDO CREADA
bool ExtPartExist(char path[], char name[]){
    //BANDERAS
    int contDisk = 0;
    bool existe = false;
    //RECORRER LAS PARTICIONES MONTADAS DEL DISCO MONTADO
    while(discos_montados[contDisk] != NULL){
        //validar existencia
        if(strcmp(discos_montados[contDisk]->path, path) == 0){
            existe = true;
            break;
        }
        contDisk++;
    }
    //SI LA PARTICION NO ESTA MONTADA, SE TIENE QUE MONTAR
    //BANDERAS
    bool existePart = false;
    //MONTAR PARTICION
    Discos_Montados *montado = discos_montados[contDisk];
    int cont = 0;
    //Validar que la particion este montada
    if(montado != NULL){
        //RECORRER LAS PARTICIONES
        while(montado->parts_mounted[cont] != NULL){
            //VALIDAR SI LA PARTICION EXISTE
            if(strcmp(montado->parts_mounted[cont]->name, name) == 0){
                existePart = true;
            }
            cont++;
        }
    }
    return !false;
}

//FUNCION PARA REEMPLAZAR EL ARCHIVO DEL MBR
void ReemplazarMBR(MasterBootRecord *disco, char path[]){
    //INICIAR PUNTERO AL ARCHIVO
    FILE *arch;
    arch = fopen(path, "rb+");
    //validar que el archivo este correcto
    if(arch == NULL){
        cout<<"EL DISCO NO EXISTE... "<<endl;
        return;
    }
    //UBICAR EL PUNTERO AL INICIO DEL ARCHIVO PARA ESCRIBIR TODO EL DISCO
    fseek(arch, 0, SEEK_SET);
    //Escribir en el disco
    fwrite(disco, sizeof(MasterBootRecord), 1, arch);
    //Cerrar el stream
    fclose(arch);
}

//FUNCION PARA DEVOLVER LA PRIMERA PARTICION EXTENDIDA
ExtendedBootRecord* getPrimerEBR(MasterBootRecord *disco, char path[]){
    //particion auxiliar para almacenar los datos del EBR
    Partition *ext = NULL;
    for(int i = 0; i< 4; i++){
        //vallidar que la particion sea extendida y que su estado sea de activo
        if(disco->particiones[i].part_status == ACTIVO && disco->particiones[i].part_type == E){
            //ASIGNAR EL VALOR DE LA PARTICION A LA PARTICION AUXILIAR
            ext = &disco->particiones[i];
            break;
        }
    }
    if(ext != NULL){
        return getDataEBR(ext->part_start, path);
    }
    return NULL;
}

//FUNCION PARA OBTENER LOS DATOS DEL EBR
ExtendedBootRecord* getDataEBR(int inicio, char path[]){
    //INICIAR EL PUNTERO AL ARCHIVO
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL ARCHIVO... "<<endl;
        return NULL;
    }
    //MEMORIA AUXILIAR PARA LOS DATOS DEL EBR
    ExtendedBootRecord *ebr_aux = (ExtendedBootRecord*)malloc(sizeof(ExtendedBootRecord));
    //UBICAR EL PUNTERO EN DONDE SE COMIENZA A LEER EL EBR
    fseek(arch, inicio, SEEK_SET);
    //LEER EL STRUCT EN EL ARCHIVO
    fread(ebr_aux, sizeof(ExtendedBootRecord), 1, arch);
    //CERRAR EL STREAM
    fclose(arch); 
    //RETORNAR EL EBR AUXILIAR
    return ebr_aux;
}


//FUNCION PARA OBTENER DATOS DE LA PARTICION EXTENDIDA
Partition* getExtPart(char name[], MasterBootRecord *disco){
    //recorrer las particiones
    for(int i = 0; i < 4; i++){
        //validar que las particiones sean extendidas y esten activas
        if(disco->particiones[i].part_status == ACTIVO && disco->particiones[i].part_type == E){
            //validar que el nombre de la particion sea el mismo
            if(strcmp(disco->particiones[i].part_name, name) == 0){
                return &disco->particiones[i];
            }
        }
    }
    return NULL;
}

