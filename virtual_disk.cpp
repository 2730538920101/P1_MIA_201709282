#include "virtual_disk.h"

#include <iostream>

using namespace std;

//INICIALIZAR EL ESPACIO VIRTUAL DE DISCO
Espacio_v::Espacio_v(){
    this->siguiente = NULL;
}

//INICIALIZAR EL ESPACIO VIRTUAL DE DISCO CON PARAMETROS
Espacio_v::Espacio_v(long tam, int inicio, Tipostatusblock status){
    this->size = tam;
    this->inicio = inicio;
    this->status = status;
}


