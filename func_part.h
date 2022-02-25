#ifndef FUNC_PART_H
#define FUNC_PART_H

#include "tipos.h"
#include "modelos.h"
#include "retorno.h"
#include "func_disk.h"
#include "globales.h"
#include "virtual_disk.h"
#include "func_sys.h"
#include <iostream>

using namespace std;

//FUNCION PARA CREAR LAS PARTICIONES, INSTANCIAR EL OBJETO
Respuesta CrearParticion(int, Tipounit, char[], char[],Tipoparticion, Tipofit, char[]);

//FUNCION PARA INSTANCIAR UN OBJETO SEGUN EL TIPO DE PARTICION QUE DESEA, PRIMARIA, LOGICA, EXTENDIDA
Respuesta genParticion(int, Tipounit, char[], Tipoparticion, Tipofit, char[]);

//FUNCION PARA INSTANCIAR UN OBJETO DE TIPO PARTICION PRIMARIA
Respuesta genPrimaria(long, Tipofit, char[], MasterBootRecord*, char[]);

//FUNCION PARA INSTANCIAR UN OBJETO DE TIPO PARTICION LOGICA
Respuesta genLogica(long, Tipofit, char[], MasterBootRecord*, char[]);

//FUNCION PARA INSTANCIAR UN OBJETO DE TIPO PARTICION EXTENDIDA
Respuesta genExtendida(long, Tipofit, char[], MasterBootRecord*, char[]);

//Funcion para crear una particion extendida
void genEBR(Partition*, char[]);

//FUNCION PARA ESCRIBIR EL ARCHIVO DEL DISCO EL EBR
void CrearArchivoEBR(ExtendedBootRecord*, char[], int);

//FUNCION QUE SETEA LA DIRECCION DONDE ESTA EL ESPACIO DISPONIBLE EN EL DISCO
//VERIFICA LA MEMORIA VIRTUAL
Respuesta getDireccionInicio(MasterBootRecord*, Tipofit, long, int*);

//FUNCION QUE MODIFICA EL ESPACIO VIRTUAL DE LA PARTICION
Respuesta PartMod(int, Tipounit, char[], char[]);

//FUNCION PARA AGREGAR LOS CAMBIOS EN EL MBR
Respuesta AddSizePart(char[], char[], char[], int, Tipounit);

//FUNCION PARA ELIMINAR UNA PARTICION LOGICA DEL EBR
Respuesta DelLogica(char[], MasterBootRecord*, char[]);

//FUNCION PARA ELIMINAR UNA PARTICION PRIMARIA DEL MBR
Respuesta DelPrimaria(MasterBootRecord*, char[], Tipocapacidad, char[]);

//FUNCION PARA ELIMINAR UNA PARTICION, ENVIA LOS DATOS ESCRITOS EN EL DISCO
Respuesta  DelPartition(char[], char[], Tipoparticion, Tipocapacidad);

//FUNCION PARA ELIMINAR UNA PARTICION, ENVIA LOS DATOS A LA FUNCION DELPARTITION
Respuesta DeletePart(char[], char[], char[], Tipoparticion, Tipocapacidad);

#endif //FUNC_PART_H