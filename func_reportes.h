#ifndef FUNC_REPORTES_H
#define FUNC_REPORTES_H
#include "tipos.h"
#include "modelos.h"
#include "func_disk.h"
#include "func_part.h"
#include "retorno.h"
#include "func_sys.h"
#include "virtual_disk.h"
#include <iostream>

using namespace std;


//FUNCION PARA ESCRIBIR EL REPORTE DEL MBR
void ReporteMasterBootRecord(char[], char[]);

//FUNCION PARA ESCRIBIR EL REPORTE DEL EBR
void ReporteExtendedBootRecord(ExtendedBootRecord*, FILE*, int);

//FUNCION PARA ESCRIBIR EL REPORTE DEL DISCO
void ReporteDisco(char[], char[]);

//FUNCION PARA ESCRIBIR EL REPORTE DE LAS PARTICIONES EXTENDIDAS DEL DISCO
void ReporteExtendidas(FILE*, MasterBootRecord*, char[]);

//FUNCION PARA ESCRIBIR EL REPORTE DE INODOS
Respuesta ReporteInodos(char[], char[], char[]);

//FUNCION PARA GRAFICAR EL INODO
void graphInodo(TablaInodos*, int, FILE*, char[], SuperBlock*);

//FUNCION PARA GRAFICAR LOS BLOQUES DE APUNTADORES
void graphBlockPointer(int level,int indexPadre,int indexBlock,FILE *fileReport,char path[],SuperBlock *superb,
                       bool graphConnection,Tipoinodo type);

//FUNCION PARA GRAFICAR LA CONEXION DEL INODO AL BLOQUE
void graphConnectionInodoBloque(int indexnodo,int indexBloque,int indexPuerto,FILE *arch);

//FUNCION PARA GRAFICAR LA CONEXION DEL BLOQUE AL INODO
void graphConnectionBloqueInodo(int indexnodo,int indexBloque,int indexPuerto,FILE *arch);

//FUNCION PARA GRAFICAR LA CONEXION DE UN BLOQUE CON BLOQUE
void graphConnectionBloqueBLoque(int indexB1,int indexB2,int indexPuerto,FILE *arch);

//FUNCION PARA GRAFICAR UN BLOQUE DE CARPETA
void graphBlockDirectory(BloquesCarpetas *block,int initBlock, FILE *arch,int indexInodo,SuperBlock *superb,char path[],bool graphConnection);

//FUNCION PARA GRAFICAR LOS BLOQUES DE ARCHIVOS
void graphBlockFile(BloquesArchivos *block,int initBlock, FILE *arch,int indexInodo);

//FUNCION PARA EL REPORTE BLOCKS
Respuesta ReporteBlocks(char path[], char name[], char path_report[]);

//FUNCION PARA EL REPORTE JOURNAL
Respuesta ReporteJournal(char path[], char namePart[],char reportPath[]);

//FUNCION PARA LOS REPORTES BM_BLOCK y BM_INODE
Respuesta ReporteBitmap(int rep, char path[], char name[],char path_rep[]);

//FUNCION PARA EL REPORTE TREE
void ReporteTree(char path_report[], char id[]);

//FUNCION PARA EL REPORTE SB
void ReporteSb(char[], char[], char[]);

#endif //FUNC_REPORTES_H