#ifndef MODELOS_H
#define MODELOS_H
#include "tipos.h"
#include <iostream>

//-----------------------------------------MANEJO DE DISCOS---------------------------------
//DEFINIR UN STRUCT PARA LAS PARTICIONES
struct Partition{
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    long part_size;
    char part_name[16];
};

//DEFINIR UN STRUCT PARA EL MBR
struct MasterBootRecord{
    long mbr_tamano;
    char mbr_fecha_creacion[16];
    int mbr_disk_signature;
    char disk_fit;
    //SOLO PUEDE TENER 4 PARTICIONES 
    Partition particiones[4];
};

//DEFINIR UN STRUCT PARA EL EBR
struct ExtendedBootRecord{
    char part_status;
    char part_fit;
    int part_start;
    long part_size;
    int part_next;
    char part_name[16];
};
//-----------------------------------------------------------------------------


#endif //MODELOS_H