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



