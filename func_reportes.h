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




#endif //FUNC_REPORTES_H