#ifndef FUNC_SYS_H
#define FUNC_SYS_H


#include "func_disk.h"
#include "modelos.h"
#include "tipos.h"
#include "func_part.h"
#include "retorno.h"
#include "virtual_disk.h"
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

//FUNCION QUE VERIFICA QUE LA PARTICION ESTE ACTIVA
Respuesta getParticionInicial(MasterBootRecord*, char[], int*);

//FUNCION PARA ESCRIBIR EL SUPER BLOQUE
void CrearArchivoSuperBlock(SuperBlock *sb, char path[], int init);

//FUNCION QUE LEE EL SUPER BLOQUE
SuperBlock* ReadSuperBlock(char[], char[], int*);
SuperBlock *ReadSuperBlock(char[], char[]);


//FUNCION QUE RETORNA EL INDICE DONDE SE ENCUENTRA EL BIT SELECCIONADO EN EL BITMAP
int getBM_index(int primerBM, int ultimoBM, char path[]);

//FUNCION QUE ESCRIBE LA TABLA DE BITMAPS
void CrearBitmapTable(int numInodos, int primero, char path[]);


//FUNCION PARA ESCRIBIR EL JOURNAL INICIALMENTE
void EscribirJournal(int inicio, int cant, char path[]);

//FUNCION PARA AGREGAR EL JOURNAL AL ARCHIVO
void CrearArchivoJournal(SuperBlock*, int, char[], Journal*);

//FUNCION PARA INICIALIZAR UN BLOQUE DE CARPETAS
BloquesCarpetas *CrearBloqueCarpetas(char [], int, char[], int);

//FUNCION PARA ESCRIBIR LOS DATOS DEL BLOQUE DE CARPETAS EN EL ARCHIVO
void CrearArchivoBloquesCarpetas(BloquesCarpetas*, char[], int);

//FUNCION QUE DEVUELVE EL BLOQUE DE CARPETAS
BloquesCarpetas *ReadBloquesCarpetas(char[], int);

//FUNCION QUE DEVUELVE LA POSICION DEL PRIMER INODO
int getInodoInicial(SuperBlock*, int);

//FUNCION PARA ESCRIBIR EL INODO EN EL ARCHIVO
void CrearArchivoInodo(TablaInodos*, char[], int);

//FUNCION QUE LEE EL INODO 
TablaInodos *ReadInodo(char[], int);

//FUNCION QUE INICIALIZA LOS VALORES DEL INODO
TablaInodos *CrearInodo(Tipoinodo, int, int);

//FUNCION PARA LIMPIAR LOS APUNTADORES DE UN INODO
void LimpiarInodo(TablaInodos*);

//FUNCION PARA ESCRIBIR EL BLOQUE DE ARCHIVOS EN EL DISCO
void CrearArchivoBloquesArchivos(BloquesArchivos*, char[], int);

//FUNCION PARA LEER EL BLOQUE DE ARCHIVOS
BloquesArchivos *ReadBloquesArchivos(char[], int);

//FUNCION PARA INICIALIZAR UN NUEVO BLOQUE DE ARCHIVOS
BloquesArchivos *CrearBloqueArchivos();

//FUNCION PARA GUARDAR LA INFORMACION DEL BLOQUE DE ARCHIVOS
void GuardarBloqueArchivos(BloquesArchivos*, SuperBlock*, char[]);

//FUNCION QUE RETORNA EL BLOQUE INICIAL
int getBloqueInicial(SuperBlock*, int);

//FUNCION PARA INICIALIZAR UN BLOQUE DE APUNTADORES
BloquesApuntadores *CrearBloqueApuntadores();

//FUNCION PARA ESCRIBIR EN EL SUPERBLOCK UN BLOQUE DE APUNTADORES
void CrearArchivoBloqueApuntadores(BloquesApuntadores*, char[], int);

//FUNCION PARA LEER LA INFORMACION DEL BLOQUE DE APUNTADORES
BloquesApuntadores *ReadBloquesApuntadores(char[], int);

//FUNCION PARA AGREGAR AL SISTEMA LOS BLOQUES DE APUNTADORES
Respuesta AgregarBloqueApuntadores(TablaInodos *inodo, int *indiceInodo, BloquesArchivos *bl, SuperBlock *bloque, char path[]);

//FUNCION PARA CREAR LOS APUNTADORES INDIRECTOS, RETORNA EL INDICE DEL APUNTADOR CREADO
int CrearApuntadorInd(int, int*, SuperBlock*, char[]);

//FUNCION QUE DEVUELVE EL INDICE DE UN ESPACIO LIBRE EN LOS BLOQUES DE APUNTADORES
int getBloqueApuntadorLibre(int, TablaInodos*, int, char[], SuperBlock*, int*);

//FUNCION QUE CREA UN DIRECTORIO Y DEVUELVE SU INDICE
int CrearDirectorio(SuperBlock*, char[], char[], char[], int);

//FUNCION QUE VERIFICA EL INDICE DE LOS ESPACIOS LIBRES EN EL BLOQUE DE DIRECTORIOS
Respuesta getBloqueCarpetasLibre(char[], char[], SuperBlock*, int*, int*, int*, Tipobloque*);

//FUNCION PARA CREAR UN NODO ARCHIVO
Respuesta CrearNodoArchivo(int, char*, char[], char[], char[], SuperBlock*, int, int);

//FUNCION PARA CREAR UN NODO CARPETA
Respuesta CrearNodoCarpeta(char[], char[], char[], SuperBlock*, int*, int*);

//FUNCION QUE RETORNA EL INDICE DEL DIRECTORIO CREADO EN UN BLOQUE DE APUNTADORES
int BuscarCarpetaBloqueApuntadores(int, int, int*, char[], SuperBlock*, char[]);

//FUNCION QUE RETORNA EL INDICE DEL DIRECTORIO CREADO EN UN BLOQUE DE DIRECTORIOS
int BuscarCarpeta(char[], char[], int*, SuperBlock*);

//FUNCION PARA CREAR ARCHIVOS DE TEXTO ESCRITOS
Respuesta CrearArchivosEscritos(char[], bool, char[], int, char[], char[]);

//FUNCION PARA FORMATEAR UNA PARTICION COMANDO MKFS
Respuesta Formatear(char[], char[], Tipocapacidad, Tiposistema, bool);


#endif //FUNC_SYS_H