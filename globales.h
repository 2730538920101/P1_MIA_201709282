#ifndef GLOBALES_H
#define GLOBALES_H
#include "virtual_disk.h"
#include "modelos.h"

//DEFINIR UNA PLANTILLA GLOBAL PARA VER LOS DISCOS MONTADOS EN EL SISTEMA
extern Discos_Montados *discos_montados[27];

//DEFINIR EL TAMANO DE LOS APUNTADORES DE LOS INODOS
extern int TAM_BLOQUES_INODOS;

//CREAR UN LOGIN DE FORMA GLOBAL PARA VERIFICAR LA SESION INICIADA
extern Login_Sesion *login_activo;

#endif //GLOBALES_H