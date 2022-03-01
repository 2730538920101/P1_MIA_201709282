#ifndef FUNC_DISK_H
#define FUNC_DISK_H

#include "tipos.h"
#include "modelos.h"
#include "retorno.h"
#include "func_part.h"
#include "virtual_disk.h"
#include "func_sys.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "globales.h"

using namespace std;

//FUNCION QUE DEVUELVE UN NUMERO RANDOM QUE IDENTIFICARA EL DISCO
int getSignature();

//FUNCION QUE DEVUELVE UN MARCADOR BOOLEANO QUE ES TRUE CUANDO SE CREA Y ESCRIBE EL ARCHIVO MBR
bool CrearArchivoMBR(MasterBootRecord*,char[], char[]);

//FUNCION QUE DEVUELVE UNA RESPUESTA DE ERROR O DE SUCCESS AL CREAR UN NUEVO DISCO
Respuesta CrearDisk(int, Tipofit, Tipounit, char[], char[]);

//FUNCION PARA DAR LECTURA A UN ARCHIVO BINARIO
void ReadDisk(char []);

//FUNCION PARA ELIMINAR UN DISCO "RMDISK"
void RemoveDisk(char[]);

//FUNCION PARA OBTENER LOS DATOS DEL MBR
MasterBootRecord* getDataMBR(char []);

//FUNCION PARA VERIFICAR SI UN DISCO YA FUE CREADO
bool DiskExist(char []);

//FUNCION PARA VERIFICAR QUE LA PARTICION EXTENDIDA HA SIDO CREADA
bool ExtPartExist(char[], char[]);

//FUNCION PARA REEMPLAZAR EL ARCHIVO DEL MBR
void ReemplazarMBR(MasterBootRecord*, char[]);

//FUNCION PARA DEVOLVER LA PRIMERA PARTICION EXTENDIDA
ExtendedBootRecord* getPrimerEBR(MasterBootRecord*, char[]);

//FUNCION PARA OBTENER LOS DATOS DEL EBR
ExtendedBootRecord* getDataEBR(int, char[]);

//FUNCION PARA OBTENER DATOS DE LA PARTICION EXTENDIDA
Partition* getExtPart(char[], MasterBootRecord*);





#endif //FUNC_DISK_H