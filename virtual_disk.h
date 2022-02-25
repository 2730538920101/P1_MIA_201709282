#ifndef VIRTUAL_DISK_H
#define VIRTUAL_DISK_H

#include <iostream>
#include "modelos.h"

using namespace std;

//DEFINIR UNA CLASE DE TIPO LISTA PARA VIRTUALIZAR EL ESPACIO DEL DISCO
class Espacio_v{
    public:
        long size;
        int inicio;
        //Variable que indica si esta libre o esta ocupado el espacio
        Tipostatusblock status;
        //Puntero al siguiente nodo
        Espacio_v *siguiente;
        //constructor vacio
        Espacio_v();
        //constructor con datos iniciales
        Espacio_v(long, int, Tipostatusblock);
};

//CLASE QUE ALMACENA LA INFORMACION DE LAS PARTICIONES MONTADAS EN EL DISCO
class Particiones_Montadas{
    public:
        char name[75];
        char id[10];
        int inicio;
};

//CLASE QUE ALMACENA LA INFORMACION DE LOS DISCOS MONTADOS
class Discos_Montados{
    public:
        //path donde se encuentra el disco
        char path[100];
        //letra que identifica al disco
        char letra;
        //Lista de particiones montadas
        Particiones_Montadas *parts_mounted[60];
        //constructor que inicializa las particiones montadas en NULL
        Discos_Montados(){
            for(int i = 0; i < 60; i++){
                parts_mounted[i] = NULL;
            }
        }
};


#endif