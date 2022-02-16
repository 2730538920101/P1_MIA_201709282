#include "func_disk.h"
#include <iostream>
using namespace std;

//FUNCION QUE DEVUELVE UN NUMERO RANDOM QUE IDENTIFICARA EL DISCO
int getSignature(){
    //pasar el tiempo actual a la funcion srand para inicializar la semilla
    srand(time(NULL));
    //guardar el numero random en una variable
    int ran = rand();
    //agregar mas probabilidad de aleatorizacion al random generado como identificador entre 1 y 1000000
    ran = 1 + rand() % (1000000);
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
        string nombre = "part_"+to_string(i+1);
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

