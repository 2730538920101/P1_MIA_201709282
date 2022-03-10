#ifndef RETORNO_H
#define RETORNO_H
#include <string.h>
#include "tipos.h"
#include <iostream>
#include <math.h>
#include "clases_comandos.h"
#include "lexico.h"
#include "retorno.h"
#include "sintactico.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include "modelos.h"
#include "func_disk.h"
#include "virtual_disk.h"
#include "func_sys.h"


using namespace std;

//FUNCION QUE DEVUELVE EL VALOR DE UN NUMERO EN STRING A ENTRERO
int getNumero(string);

//FUNCION QUE ELIMINA LAS COMILLAS DE UNA CADENA
string getCadenaSinComillas(char path_original[]);

//FUNCION QUE DEVUELVE EL NOMBRE DE UN ARCHIVO DESDE EL PATH RECIBIDO
string getNameFromPath(char *path, int *position);

//FUNCION QUE DEVUELVE EL PATH SIN EL NOMBRE INCLUIDO EN EL STRING
string getPathSinNombre(char *path, int tamNombre);

//FUNCION QUE DEVUELVE EL VALOR DEL TAMANO QUE SE INGRESA
long getSize(int, Tipounit);

//FUNCION QUE DEVUELVE LA FECHA ACTUAL EN EL SISTEMA
void getFecha(char[]);

//FUNCION PARA CREAR CARPETAS
void CrearCarpeta(string path);

//FUNCION PARA LIMPIAR UN ARRAY
void LimpiarArray(char[], int);

//FUNCION QUE VERIFICA EL PATH DEL DISCO
void getPathOfDisk(char [], char [], char []);

//FUNCION QUE DEVUELVE UN MENSAJE DE ERROR SEGUN EL ERROR QUE ENCUENTRE
void getErrorMsj(Respuesta);

//FUNCION PARA ESCRIBIR CEROS EN UN ARCHIVO
void LlenarCeros(char[], int, int);

//FUNCION QUE CUENTA LOS DISCOS
Respuesta getContDisk(int *contador, char *id);

//FUNCION QUE RETORNA UN ID PARA LAS PARTICIONES CREADAS CON LOS ULTIMOS DIGITOS DE MI CARNET COMO BASE
//82
char *getPartitionId(char, int);

//FUNCION QUE RETORNA UN NUMERO DECIMAL CONVERTIDO A FLOAT PARA ESCRIBIR LOS RESPORTES
float getDecimalCast(float);

//FUNCION QUE VERIFICA QUE LA SESION DEL LOGIN ESTE INICIADA
bool LoginActivo();

#endif //RETORNO_H