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
SuperBlock *ReadSuperBlock(char[], char[]);




#endif //FUNC_SYS_H