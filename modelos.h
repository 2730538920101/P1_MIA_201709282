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

//---------------------------------------SISTEMA DE ARCHIVOS------------------------

struct SuperBlock{
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    char s_mtime[16];
    char s_umtime[16];
    int s_mnt_count;
    int s_magic; 
    int s_inode_size;
    int s_block_size;
    int s_first_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
};

struct TablaInodos{
    int i_uid;
    int i_gid;
    int i_size;
    char i_atime[16];
    char i_ctime[16];
    char i_mtime[16];
    int i_block[15];
    Tipoinodo i_type;
    int i_perm;
};

struct Content{
    char b_name[12];
    int b_inodo;
};

struct BloquesCarpetas{
    Content b_content[4];
};

struct BloquesArchivos{
    char b_content[64];
};

struct BloquesApuntadores{
    int b_pointers[16];
};


#endif //MODELOS_H