#ifndef CLASES_COMANDOS_H
#define CLASES_COMANDOS_H
#include <iostream>
#include "tipos.h"
#include <string.h>
#include "clases_comandos.h"
#include "sintactico.h"
#include "lexico.h"
#include "retorno.h"

using namespace std;

//Clase abstracta para comandos
class Comando{
    public:
        //funcion a la cual se le aplicara polimorfismo por medio de la herencia
        virtual void Ejecutar(){}
        //variable apuntador que dara funcion de lista a la clase Comando
        Comando *siguiente = NULL;
};

//Clase para generar comando mkdisk, hereda de la clase Comando
class C_mkdisk:public Comando{
    public:
        int size;
        char *path;
        Tipofit fit;
        Tipounit unit;
        //constructor con los parametros obligatorios
        C_mkdisk(int size, char path[]);
        //funcion ejecutar heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar comando rmdisk, hereda de la clase Comando
class C_rmdisk:public Comando{
    public:
        char *path;
        //constructor con los parametros obligatorios
        C_rmdisk(char path[]);
        //funcion ejecutar heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar comando fdisk, hereda de la clase Comando
class C_fdisk:public Comando{
    public:
        int size;
        char *path;
        char *name;
        Tipounit unit;
        Tipoparticion tipo;
        Tipofit fit;
        Tipocapacidad capacidad;
        int add;
        //constructor con los parametros obligatorios
        C_fdisk(int size, char path[], char name[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando mount, hereda de la clase Comando
class C_mount:public Comando{
    public:
        char *path;
        char *name;
        //constructor con los parametros obligatorios
        C_mount(char path[], char name[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando unmount, hereda de la clase Comando
class C_unmount:public Comando{
    public:
        char *id;
        //constructor con los parametros obligatorios
        C_unmount(char id[]);
        //funcion ejecutar, heredada de la clase abtracta
        void Ejecutar();
};

//Clase para generar el comando mkfs, hereda de la clase Comando
class C_mkfs:public Comando{
    public:
        char *id;
        Tipocapacidad capacidad;
        Tiposistema sistema;
        //constructor con los parametros obligatorios
        C_mkfs(char id[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando login, hereda de la clase Comando
class C_login:public Comando{
    public:
        char *usr;
        char *pwd;
        char *id;
        //constructor con los parametros obligatorios
        C_login(char usr[], char pwd[], char id[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando logout, hereda de la clase Comando
class C_logout:public Comando{
    //funcion que no recibe parametros, unicamente se define el metodo ejecutar heredado de la clase Comando
    void Ejecutar();
};

//Clase para generar el comando pause, hereda de la clase Comando
class C_pause:public Comando{
    //funcion que no recibe parametros, unicamente se define el metodo ejecutar heredado de la clase Comando
    void Ejecutar();
};

//Clase para generar el comando mkgrp, hereda de la clase Comando
class C_mkgrp:public Comando{
    public:
        char *name;
        //constructor con los parametros obligatorios
        C_mkgrp(char name[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando rmgrp, hereda de la clase Comando
class C_rmgrp:public Comando{
    public:
        char *name;
        //constructor con los parametros obligatorios
        C_rmgrp(char name[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando mkusr, hereda de la clase Comando
class C_mkusr:public Comando{
    public:
        char *usr;
        char *pwd;
        char *grp;
        //constructor con los parametros obligatorios
        C_mkusr(char usr[], char pwd[], char gro[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando rmusr, hereda de la clase Comando
class C_rmusr:public Comando{
    public:
        char *usr;
        //constructor con los parametros obligatorios
        C_rmusr(char usr[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando chmod, hereda de la clase Comando
class C_chmod:public Comando{
    public:
        char *path;
        int ugo;
        bool r_flag;
        //constructor con los parametros obligatorios
        C_chmod(char path[], int ugo);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando touch, hereda de la clase Comando
class C_touch:public Comando{
    public:
        char *path;
        int size;
        char *cont;
        bool r_flag;
        bool stdin_flag;
        //constructor con los parametros obligatorios
        C_touch(char path[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando cat, hereda de la clase Comando
class C_cat:public Comando{
    public:
        char *filen;
        //constructor con los parametros obligatorios
        C_cat(char filen[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando rm, hereda de la clase Comando
class C_rm:public Comando{
    public:
        char *path;
        //constructor con los parametros obligatorios
        C_rm(char path[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};


//Clase para generar el comando edit, hereda de la clase Comando
class C_edit:public Comando{
    public:
        char *path;
        char *cont;
        bool stdin_flag;
        //constructor con los parametros obligatorios
        C_edit(char path[], char cont[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando ren, hereda de la clase Comando
class C_ren:public Comando{
    public:
        char *path;
        char *name;
        //constructor con los parametros obligatorios
        C_ren(char path[], char name[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando mkdir, hereda de la clase Comando
class C_mkdir:public Comando{
    public:
        char *path;
        bool p_flag;
        //constructor con los parametros obligatorios
        C_mkdir(char path[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando cp, hereda de la clase Comando
class C_cp:public Comando{
    public:
        char *path;
        char *dest;
        //constructor con los parametros obligatorios
        C_cp(char path[], char dest[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando mv, hereda de la clase Comando
class C_mv:public Comando{
    public:
        char *path;
        char *dest;
        //constructor con los parametros obligatorios
        C_mv(char path[], char dest[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando find, hereda de la clase Comando
class C_find:public Comando{
    public:
        char *path;
        char *name;
        //constructor con los parametros obligatorios
        C_find(char path[], char name[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando chown, hereda de la clase Comando
class C_chown:public Comando{
    public:
        char *path;
        char *usr;
        bool r_flag;
        //constructor con los parametros obligatorios
        C_chown(char path[], char usr[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando chgrp, hereda de la clase Comando
class C_chgrp:public Comando{
    public:
        char *usr;
        char *grp;
        //constructor con los parametros obligatorios
        C_chgrp(char usr[], char grp[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando recovery, hereda de la clase Comando
class C_recovery:public Comando{
    public:
        char *id;
        //constructor con los parametros obligatorios
        C_recovery(char id[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase para generar el comando loss, hereda de la clase Comando
class C_loss:public Comando{
    public:
        char *id;
        //constructor con los parametros obligatorios
        C_loss(char id[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};


//Clase para generar el comando exec, hereda de la clase Comando
class C_exec:public Comando{
    public:
        char *path;
        //constructor con los parametros obligatorios
        C_exec(char path[]);
        //funcion ejecutar, heredada de la clase Comando
        void Ejecutar();
};

//Clase abstracta para formar parametros y enlistarlos
class Parametro{
    public:
        //atributos que reciben la respuesta de los parametros
        Tipoparametro paramtype;
        char text[200];
        int num;
        Tipofit fit;
        Tipounit unit;
        Tipoparticion type;
        Tipocapacidad capacidad;
        Tiposistema sistema;
        //bandera, indicador de presencia de parametros sin retorno
        bool r_flag;
        bool p_flag;
        bool stdin_flag;
        //variable apuntador que dara funcion de lista a la clase Parametro
        Parametro *siguiente;
        //constructor
        Parametro(Tipoparametro param){
            paramtype = param;
            siguiente = NULL;
        }
};

//Funcion que permite escribir los comandos ingresados en un archivo
void Escribir_Comando(string comando, bool bandera);

//Funcion que permite la lectura de los archivos donde se escribiran los comandos y ejecuta el analizador
void Leer_Comando(bool bandera);

//Funcion que recorre la lista formada y realiza la Ejecucion del metodo Ejecutar en cada nodo
void Activador_Ejecutar(Comando* comando);

//Funcion de la clase comando que permite formar los comandos correctos
Comando* getComando(TipoComando commandtype, Parametro *param);

//Funcion de la clase comando que permite listar elementos del comando
Comando* ListarComando(Comando *command, bool flag);

//Funcion booleana que valida que los parametros ingresados sean los permitidos en cada comando
bool ValidarParametros(char *name, char *path, char *id, char *usr, char *pwd, char *grp, 
                        char *cont, char *filen, char *dest, char *ruta, Tipofit fit,
                        Tipounit unit, Tipoparticion type, Tipocapacidad capacidad, Tiposistema sistema,
                        bool sizeEx, bool addEx, bool ugoEx, TipoComando commandtype);

#endif //CLASES_COMANDOS_H