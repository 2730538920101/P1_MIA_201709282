#ifndef MODELOS_H
#define MODELOS_H
#include "tipos.h"
#include <iostream>

using namespace std;

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

//-------IMPLEMENTACION DEL JOURNAL SISTEMA EXT3--------------------
class Journal{
    public:
        TipoOperacion j_operation;
        char j_date[16];
        char *j_path;
        char *j_content;
        char *j_user;
        char *j_group;
        int j_size;
        int j_perms;
        bool j_boolean;
        //METODO CONTRUCTOR
        Journal(){
            //INICIALIZAR LOS ATRIBUTOS DEL JOURNAL CON EL CONSTRUCTOR
            this->j_operation = VACIO;
            this->j_path = NULL;
            this->j_content = NULL;
            this->j_group = NULL;
            this->j_user = NULL;
            this->j_size = -1;
            this->j_perms = -1;
            this->j_boolean = false;
        }
};


//---------------------------CLASES SISTEMA DE LOGIN -----------
class Login_Sesion{
    public:
        char *user;
        char *path;
        char *nomPart;
        char *id;
        char *id_usuario;
        char *id_grupo;
        //METODO CONTRUCTOR
        Login_Sesion(){
            //Inicializar los atributos en el constructor
            this->user = NULL;
            this->path = NULL;
            this->nomPart = NULL;
            this->id = NULL;
            this->id_grupo = NULL;
            this->id_usuario = NULL;
        }
        //METODO PARA INICIALIZAR UN VALOR EN CERO
        void LimpiarSesion(){
            user = NULL;
            path = NULL;
            nomPart = NULL;
            id = NULL;
            this->id_grupo = NULL;
            this->id_usuario = NULL;
        }
};

class Usuario{
    public:
        string id;
        char tipo;
        string name;
        string pwd;
        string group;
};

class Grupo{
    public:
        string id;
        string name;
};

#endif //MODELOS_H