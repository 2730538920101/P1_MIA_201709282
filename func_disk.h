#ifndef FUNC_DISK_H
#define FUNC_DISK_H

#include "tipos.h"
#include "modelos.h"
#include "retorno.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

//FUNCION QUE DEVUELVE UN NUMERO RANDOM QUE IDENTIFICARA EL DISCO
int getSignature();

//FUNCION QUE DEVUELVE UN MARCADOR BOOLEANO QUE ES TRUE CUANDO SE CREA Y ESCRIBE EL ARCHIVO MBR
bool CrearArchivoMBR(MasterBootRecord*,char[], char[]);

//FUNCION QUE DEVUELVE UNA RESPUESTA DE ERROR O DE SUCCESS AL CREAR UN NUEVO DISCO
Respuesta CrearDisk(int, Tipofit, Tipounit, char[], char[]);




#endif //FUNC_DISK_H