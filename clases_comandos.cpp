#include "clases_comandos.h"
//INICIALIZAR OBJETOS PARA GENERAR LOS COMANDOS

//CREAR MKDISK
C_mkdisk::C_mkdisk(int size, char path[]){
    //parametros obligatorios
    this->size = size;
    this->path = path;
    //parametros opcionales con valor por defecto
    this->fit = FF;
    this->unit = M;
}

//FUNCION EJECUTAR MKDISK
void C_mkdisk::Ejecutar(){
    cout<<"Ejecutando comando MKDISK... \n ";
}

//CREAR RMDISK
C_rmdisk::C_rmdisk(char path[]){
    //parametros obligatorios
    this->path = path;
}

//FUNCION EJECUTAR RMDISK
void C_rmdisk::Ejecutar(){
    cout<<"Ejecutando comando RMDISK... \n ";
}

//CREAR FDISK
C_fdisk::C_fdisk(int size, char path[], char name[]){
    //parametros obligatorios
    this->size = size;
    this->path = path;
    this->name = name;
    //parametros opcionales con valor por defecto
    this->unit = K;
    this->fit = WF;
}

//FUNCION EJECUTAR FDISK
void C_fdisk::Ejecutar(){
    cout<<"Ejecutando comando FDISK... \n ";
}

//CREAR MOUNT
C_mount::C_mount(char path[], char name[]){
    //parametros obligatorios
    this->path = path;
    this->name = name;
}

//FUNCION EJECUTAR MOUNT
void C_mount::Ejecutar(){
    cout<<"Ejecutando comando MOUNT... \n ";
}

//CREAR UNMOUNT
C_unmount::C_unmount(char id[]){
    //parametros obligatorios
    this->id = id;
}

//FUNCION EJECUTAR UNMOUNT
void C_unmount::Ejecutar(){
    cout<<"Ejecutando comando UNMOUNT... \n ";
}

//CREAR MKFS
C_mkfs::C_mkfs(char id[]){
    //parametros obligatorios
    this->id = id;
    //parametros opcionales con valor por defecto
    this->capacidad = FULL;
    this->sistema = EXT2;
}

//FUNCION EJECUTAR MKFS
void C_mkfs::Ejecutar(){
    cout<<"Ejecutando comando MKFS... \n ";
}

//CREAR LOGIN
C_login::C_login(char usr[], char pwd[], char id[]){
    //parametros obligatorios
    this->usr = usr;
    this->pwd = pwd;
    this->id = id;
}

//FUNCION EJECUTAR LOGIN
void C_login::Ejecutar(){
    cout<<"Ejecutando comando LOGIN... \n ";
}

//CREAR MKGRP
C_mkgrp::C_mkgrp(char name[]){
    //parametros obligatorios
    this->name = name;
}

//FUNCION EJECUTAR MKGRP
void C_mkgrp::Ejecutar(){
    cout<<"Ejecutando comando MKGRP... \n ";
}

//CREAR RMGRP
C_rmgrp::C_rmgrp(char name[]){
    //parametros obligatorios
    this->name = name;
}

//FUNCION EJECUTAR RMGRP
void C_rmgrp::Ejecutar(){
    cout<<"Ejecutando comando RMGRP... \n ";
}

//CREAR MKUSER
C_mkusr::C_mkusr(char usr[], char pwd[], char grp[]){
    //parametros obligatorios
    this->usr = usr;
    this->pwd = pwd;
    this->grp = grp;
}

//FUNCION EJECUTAR MKUSR
void C_mkusr::Ejecutar(){
    cout<<"Ejecutando comando MKUSR... \n ";
}

//CREAR RMUSR
C_rmusr::C_rmusr(char usr[]){
    //parametros obligatorios
    this->usr = usr;
}

//FUNCION EJECUTAR RMUSR
void C_rmusr::Ejecutar(){
    cout<<"Ejecutando comando RMUSR... \n ";
}

//CREAR CHMOD
C_chmod::C_chmod(char path[], int ugo){
    //parametros obligatorios
    this->path = path;
    this->ugo = ugo;
    //parametros opcionales con valor por defecto
    this->r_flag = false;
}

//FUNCION EJECUTAR CHMOD
void C_chmod::Ejecutar(){
    cout<<"Ejecutando comando CHMOD... \n ";
}

//CREAR TOUCH
C_touch::C_touch(char path[]){
    //paramtros obligatorios
    this->path = path;
    //parametros opcionales con valor por defecto
    this->r_flag = false;
    this->size = 0;
    this->cont = NULL;
    this->stdin_flag = false;
}

//FUNCION EJECUTAR TOUCH
void C_touch::Ejecutar(){
    cout<<"Ejecutando comando TOUCH... \n ";
}

//CREAR CAT
C_cat::C_cat(char filen[]){
    //parametros obligatorios
    this->filen = filen;
}

//FUNCION EJECUTAR CAT
void C_cat::Ejecutar(){
    cout<<"Ejecutando comando CAT... \n ";
}

//CREAR RM
C_rm::C_rm(char path[]){
    //parametros obligatorios
    this->path = path;
}

//FUNCION EJECUTAR RM
void C_rm::Ejecutar(){
    cout<<"Ejecutando comando RM... \n ";
}

//CREAR EDIT
C_edit::C_edit(char path[], char cont[]){
    //parametros obligatorios
    this->path = path;
    this->cont = cont;
    //parametros opcionales con su valor por defecto
    this->stdin_flag = false;
}

//FUNCION EJECUTAR EDIT
void C_edit::Ejecutar(){
    cout<<"Ejecutando comando EDIT... \n ";
}

//CREAR REN
C_ren::C_ren(char path[], char name[]){
    //parametros obligatorios
    this->path = path;
    this->name = name;
}

//FUNCION EJECUTAR REN
void C_ren::Ejecutar(){
    cout<<"Ejecutando comando REN... \n ";
}

//CREAR MKDIR
C_mkdir::C_mkdir(char path[]){
    //parametros obligatorios
    this->path = path;
    //parametros obligatorios con valor por defecto
    this->p_flag = false;
}

//FUNCION EJECUTAR MKDIR
void C_mkdir::Ejecutar(){
    cout<<"Ejecutando comando MKDIR... \n ";
}

//CREAR CP
C_cp::C_cp(char path[], char dest[]){
    //parametros obligatorios
    this->path = path;
    this->dest = dest;
}

//FUNCION EJECUTAR CP
void C_cp::Ejecutar(){
    cout<<"Ejecutando comando CP... \n ";
}

//CREAR MV
C_mv::C_mv(char path[], char dest[]){
    //parametros obligatorios
    this->path = path;
    this->dest = dest;
}

//FUNCION EJECUTAR MV
void C_mv::Ejecutar(){
    cout<<"Ejecutando comando MV... \n ";
}


//CREAR FIND
C_find::C_find(char path[], char name[]){
    //parametros obligatorios
    this->path = path;
    this->name = name;
}

//FUNCION EJECUTAR FIND
void C_find::Ejecutar(){
    cout<<"Ejecutando comando FIND... \n ";
}


//CREAR CHOWN
C_chown::C_chown(char path[], char usr[]){
    //parametros obligatorios
    this->path = path;
    this->usr = usr;
    //parametros opcionales con valor por defecto
    this->r_flag = false;
}

//FUNCION EJECUTAR CHOWN
void C_chown::Ejecutar(){
    cout<<"Ejecutando comando CHOWN... \n ";
}


//CREAR CHGRP
C_chgrp::C_chgrp(char usr[], char grp[]){
    //parametros obligatorios
    this->usr = usr;
    this->grp = grp;
}

//FUNCION EJECUTAR CHGRP
void C_chgrp::Ejecutar(){
    cout<<"Ejecutando comando CHGRP... \n ";
}

//CREAR RECOVERY
C_recovery::C_recovery(char id[]){
    //parametros obligatorios
    this->id = id;
}

//FUNCION EJECUTAR RECOVERY
void C_recovery::Ejecutar(){
    cout<<"Ejecutando comando RECOVERY... \n ";
}

//CREAR LOSS
C_loss::C_loss(char id[]){
    //parametros obligatorios
    this->id = id;
}

//FUNCION EJECUTAR LOSS
void C_loss::Ejecutar(){
    cout<<"Ejecutando comando LOSS... \n ";
}


//CREAR EXEC
C_exec::C_exec(char path[]){
    //parametros obligatorios
    this->path = path;
}

//FUNCION EJECUTAR EXEC
void C_exec::Ejecutar(){
    cout<<"Ejecutando comando EXEC... \n ";
}

//FUNCION EJECUTAR LOGOUT
void C_logout::Ejecutar(){
    cout<<"Ejecutando comando LOGOUT... \n ";
}

//FUNCION EJECUTAR PAUSE
void C_pause::Ejecutar(){
    cout<<"Ejecutando comando PAUSE... \n ";
}


//FUNCION ValidarParametros HACE UN ANALISIS SEMANTICO VALIDANDO LOS PARAMETROS QUE VIENEN EN CADA COMANDO
bool ValidarParametros(char *name, char *path, char *id, char *usr, char *pwd, char *grp, 
                        char *cont, char *filen, char *dest, char *ruta, Tipofit fit,
                        Tipounit unit, Tipoparticion type, Tipocapacidad capacidad, Tiposistema sistema,
                        bool sizeEx, bool addEx, bool ugoEx, bool r_flag, bool p_flag, bool stdin_flag,
                        TipoComando commandtype){
                            //VALIDA QUE VENGAN UNICAMENTE LOS PARAMETREOS ACEPTADOS POR CADA COMANDO
                            switch(commandtype){
                                case MKDISK:
                                    {//Parametros permitidos: size, path , f, u
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx 
                                        );
                                    }break;
                                case RMDISK:
                                    {//Parametros permitidos: path 
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );                      
                                    }break;
                                case FDISK:
                                    {//Parametros permitidos: path, size, name, u, type, f, delete, add 
                                        return!(
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            ugoEx 
                                        );                   
                                    }break;
                                case MOUNT:
                                    {//Parametros permitidos: path, name 
                                        return!(
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case UNMOUNT:
                                    {//Parametros permitidos: id 
                                        return!(
                                            name != NULL ||
                                            path != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case MKFS:
                                    {//Parametros permitidos: id, type, fs
                                        return!(
                                            name != NULL ||
                                            path != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case LOGIN:
                                    {//Parametros permitidos: usr, pwd, id 
                                        return!(
                                            name != NULL ||
                                            path != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;                 
                                case MKGRP:
                                    {//Parametros permitidos: name 
                                        return!(
                                            path != NULL ||
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case RMGRP:
                                    {//Parametros permitidos: name 
                                        return!(
                                            path != NULL ||
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case MKUSR:
                                    {//Parametros permitidos: usr, pwd, grp 
                                        return!(
                                            name != NULL ||
                                            path != NULL ||
                                            id != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case RMUSR:
                                    {//Parametros permitidos: usr 
                                        return!(
                                            name != NULL ||
                                            path != NULL ||
                                            id != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case CHMOD:
                                    {//Parametros permitidos: path, ugo, r 
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            sizeEx
                                        );
                                    }break;
                                case TOUCH:
                                    {//Parametros permitidos: path, r, size, cont, stdin
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            p_flag ||
                                            addEx ||
                                            ugoEx 
                                        );
                                    }break;
                                case CAT:
                                    {//Parametros permitidos: filen
                                        return!(
                                            name != NULL ||
                                            path != NULL ||
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case RM:
                                    {//Parametros permitidos: path 
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case EDIT:
                                    {//Parametros permitidos: path, cont, stdin 
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case REN:
                                    {//Parametros permitidos: path, name 
                                        return!(
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case MKDIR:
                                    {//Parametros permitidos: path, p
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case CP:
                                    {//Parametros permitidos: path, dest 
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case MV:
                                    {//Parametros permitidos: path, dest 
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case FIND:
                                    {//Parametros permitidos: path, name
                                        return!(
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case CHOWN:
                                    {//Parametros permitidos: path, usr, r
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case CHGRP:
                                    {//Parametros permitidos: usr, grp
                                        return!(
                                            name != NULL ||
                                            path != NULL ||
                                            id != NULL ||
                                            pwd != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case RECOVERY:
                                    {//Parametros permitidos: id 
                                        return!(
                                            name != NULL ||
                                            path != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case LOSS:
                                    {//Parametros permitidos: id 
                                        return!(
                                            name != NULL ||
                                            path != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case EXEC:
                                    {//Parametros permitidos: path
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usr != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            dest != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            stdin_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                default:
                                    {
                                        return false;
                                    }
                            }
                        }

//Funcion de la clase comando que permite formar los comandos correctos
Comando* getComando(TipoComando commandtype, Parametro *param){
    //INICIALIZAR UN PARAMETRO AUXILIAR PARA RECORRER LA LISTA
    Parametro *auxparam = param;

    //INICIAR TODOS LOS PARAMETROS QUE RECIBIRA LA FUNCION PARA VALIDAR SU PRESENCIA DENTRO DEL COMANDO
    char *name = NULL;
    char *path = NULL;
    char *id = NULL;
    char *usr = NULL;
    char *pwd = NULL;
    char *grp = NULL;
    char *cont = NULL;
    char *filen = NULL;
    char *dest = NULL;
    char *ruta = NULL;
    Tipofit fit = FIT_ERROR;
    Tipounit unit = UNIT_ERROR;
    Tipoparticion type = TIPO_ERROR;
    Tipocapacidad capacidad = CAPACIDAD_ERROR;
    Tiposistema sistema = FS_EXT_ERROR;
    bool sizeEx = false;
    bool addEx = false;
    bool ugoEx = false;
    bool r_flag = false;
    bool p_flag = false;
    bool stdin_flag = false;
    int size = -1;
    int ugo = -1;

    //CICLO WHILE QUE RECORRE LOS PARAMETROS Y DEVUELVE SU VALOR DE RETORNO
    while(auxparam != NULL){
        //ASIGNAR A LAS VARIABLES EL VALOR DE RETORNO SEGUN EL PARAMETRO QUE RECIBE
        switch(auxparam->paramtype){
            case SIZE:
                {
                    size = auxparam->num;
                    sizeEx = true;
                }break;
            case PATH:
                {
                    path = auxparam->text;
                }break;
            case ID:
                {
                    id = auxparam->text;
                }break;
            case F:
                {
                    fit = auxparam->fit;
                }break;
            case U:
                {
                    unit = auxparam->unit;
                }break;
            case TYPE:
                {
                    type = auxparam->type;
                }break;
            case DELETE:
                {
                    capacidad = auxparam->capacidad;
                }break;
            case ADD:
                {
                    size = auxparam->num;
                    addEx = true;
                }break;
            case NAME:
                {
                    name = auxparam->text;
                }break;
            case FS:
                {
                    sistema = auxparam->sistema;
                }break;
            case USR:
                {
                    usr = auxparam->text;
                }break;
            case PWD:
                {
                    pwd = auxparam->text;
                }break;
            case R:
                {
                    r_flag = auxparam->r_flag;
                }break;
            case CONT:
                {
                    cont = auxparam->text;
                }break;
            case STDIN:
                {
                    stdin_flag = auxparam->stdin_flag;
                }break;
            case GRP:
                {
                    grp = auxparam->text;
                }break;
            case UGO:
                {
                    ugo = auxparam->num;
                    ugoEx = true;
                }break; 
            case FILEN:
                {
                    filen = auxparam->text;
                }break; 
            case PP:
                {
                    p_flag = auxparam->p_flag;
                }break;
            case DEST:
                {
                    dest = auxparam->text;
                }break;
            default:
                {
                    cout<<"El parametro ingresado es invalido. \n";
                }break;
        }
        //ANALIZAR EL SIGUIENTE PARAMETRO EN LA LISTA
        auxparam = auxparam->siguiente;
    }
    //SE VALIDA QUE LOS PARAMETROS INGRESADOS PERTENEZCAN AL COMANDO 
    if(!ValidarParametros(name,path,id,usr,pwd,grp,cont,filen,dest,ruta,fit,unit,type,capacidad,sistema,
                        sizeEx,addEx,ugoEx,r_flag,p_flag,stdin_flag,commandtype)){
                            cout<<"El comando ingresado tiene parametros no permitidos \n";
                            return NULL;
                        }
    //se valida que los comandos traigan sus parametros obligatorios y que el valor ingresado sea correcto
    //se crean los objetos de cada comando y se asignan los valores de los parametros ingresados en sus atributos
    //debe retornar un objeto (POR COMANDO) que hereda de la clase Comando
    switch(commandtype){
        case MKDISK:
            {
                //verificar que vengan los parametros obligatorios, si no viene el valor retorna NULL
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando MKDISK \n";
                    return NULL;
                }
                if(!sizeEx){
                    cout<<"El parametro size es obligatorio en este comando MKDISK \n";
                    return NULL;
                }
                //crear un objeto de la clase C_mkdisk
                C_mkdisk *aux_mkdisk = new C_mkdisk(size, path);
                //modificamos los parametros auxiliares si traen algun valor
                if(fit != FIT_ERROR){
                    aux_mkdisk->fit = fit;
                }
                if(unit != UNIT_ERROR){
                    aux_mkdisk->unit = unit;
                }
                //Retornar el objeto C_mkdisk casteado a objeto Comando
                return (Comando*)aux_mkdisk;
            }break;
        case RMDISK:
            {
                //verificar que vengan los parametros obligatorios, si no viene el valor retorna NULL
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando RMDISK \n";
                    return NULL;
                }
                //se crea un objeto auxiliar de la clase C_rmdisk
                C_rmdisk *aux_rmdisk = new C_rmdisk(path);
                //retornar un objeto C_rmdisk casteado a la clase Comando
                return (Comando*)aux_rmdisk;
            }break;
        case FDISK:
            {
                 //verificar que vengan los parametros obligatorios, si no viene el valor retorna NULL
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando FDISK \n";
                    return NULL;
                }
                if(!sizeEx){
                    cout<<"El parametro size es obligatorio en este comando FDISK \n";
                    return NULL;
                }
                if(name == NULL){
                    cout<<"El parametro name es obligatorio en este comando FDISK \n";
                    return NULL;
                }
                // crear un objeto de la clase C_fdisk
                C_fdisk *aux_fdisk = new C_fdisk(size, path, name);
                //se validan los parametros auxiliares y se les asigna un valor a los parametros del objeto de retorno
                if(unit != UNIT_ERROR){
                    aux_fdisk->unit = unit;
                }
                if(type != TIPO_ERROR){
                    aux_fdisk->tipo = type;
                }
                if(fit != FIT_ERROR){
                    aux_fdisk->fit = fit;
                }
                //retornar el objeto de la clase C_fdisk y castearlo a la clase Comando
                return (Comando*)aux_fdisk;
            }break;
        case MOUNT:
            {
                //verificar que vengan los parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando MOUNT \n";
                }
                if(name == NULL){
                    cout<<"El parametro name es obligatorio en este comando MOUNT \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_mount
                C_mount *aux_mount = new C_mount(path, name);
                //se retorna el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_mount;
            }break;
        case UNMOUNT:
            {
                //verificar los parametros obligatorios
                if(id == NULL){
                    cout<<"El parametro id es obligatorio en este comando UNMOUNT \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_unmount
                C_unmount *aux_unmount = new C_unmount(id);
                //se retorna el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_unmount;
            }break;
        case MKFS:
            {
                //verificar los parametros obligatorios
                if(id == NULL){
                    cout<<"El parametro id es obligatorio en este comando MKFS \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_mkfs
                C_mkfs *aux_mkfs = new C_mkfs(id);
                //se verifican los parametros auxiliares
                if(capacidad != CAPACIDAD_ERROR){
                    aux_mkfs->capacidad = capacidad;
                }
                if(sistema != FS_EXT_ERROR){
                    aux_mkfs->sistema = sistema;
                }
                //se retorna el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_mkfs;
            }break;
        case LOGIN:
            {
                //verificar los parametros obligatorios
                if(usr == NULL){
                    cout<<"El parametro usr es obligatorio en esta comando LOGIN \n";
                    return NULL;
                }
                if(pwd == NULL){
                    cout<<"El parametro pwd es obligatorio en este comando LOGIN \n";
                    return NULL;
                }
                if(id == NULL){
                    cout<<"El parametro id es obligatorio en este comando LOGIN \n";
                    return NULL;
                }
                //crear objeto auxiliar de la clase C_login
                C_login *aux_login = new C_login(usr,pwd,id);
                //retornar el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_login;
            }break;
        case MKGRP:
            {
                //verificar que vengan los parametros obligatorios, si no viene el valor retorna NULL
                if(name == NULL){
                    cout<<"El parametro name es obligatorio en este comando MKGRP \n";
                    return NULL;
                }
                //se crea un objeto auxiliar de la clase C_rmdisk
                C_mkgrp *aux_mkgrp = new C_mkgrp(name);
                //retornar un objeto C_mkgrp casteado a la clase Comando
                return (Comando*)aux_mkgrp;
            }break;
        case RMGRP:
            {
                //verificar que vengan los parametros obligatorios, si no viene el valor retorna NULL
                if(name == NULL){
                    cout<<"El parametro name es obligatorio en este comando RMGRP \n";
                    return NULL;
                }
                //se crea un objeto auxiliar de la clase C_rmgrp
                C_rmgrp *aux_rmgrp = new C_rmgrp(name);
                //retornar un objeto C_rmgrp casteado a la clase Comando
                return (Comando*)aux_rmgrp;
            }break;
        case MKUSR:
            {
                 //verificar los parametros obligatorios
                if(usr == NULL){
                    cout<<"El parametro usr es obligatorio en esta comando MKUSR \n";
                    return NULL;
                }
                if(pwd == NULL){
                    cout<<"El parametro pwd es obligatorio en este comando MKUSR \n";
                    return NULL;
                }
                if(grp == NULL){
                    cout<<"El parametro grp es obligatorio en este comando MKUSR \n";
                    return NULL;
                }
                //crear objeto auxiliar de la clase C_mkusr
                C_mkusr *aux_mkusr = new C_mkusr(usr,pwd,grp);
                //retornar el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_mkusr;
            }break;
        case RMUSR:
            {
                //verificar que vengan los parametros obligatorios, si no viene el valor retorna NULL
                if(usr == NULL){
                    cout<<"El parametro usr es obligatorio en este comando RMUSR \n";
                    return NULL;
                }
                //se crea un objeto auxiliar de la clase C_rmusr
                C_rmusr *aux_rmusr = new C_rmusr(usr);
                //retornar un objeto C_rmusr casteado a la clase Comando
                return (Comando*)aux_rmusr;
            }break;
        case CHMOD:
            {
                //verificar que vengan los paramtros obligatorios, si no viene el valor retorna NULL
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando CHMOD \n";
                    return NULL;
                }
                if(!ugoEx){
                    cout<<"El paramtro ugo es obligatorio en este comando CHMOD \n";
                    return NULL;
                }
                //Crear un objeto auxiliar de la clase C_chmod
                C_chmod *aux_chmod = new C_chmod(path, ugo);
                //verificar los parametros opcionales
                if(r_flag == true){
                    aux_chmod->r_flag = r_flag;
                }
                //retornar el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_chmod;
            }break;
        case TOUCH:
            {
                //verificar parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando TOUCH \n";
                    return NULL;
                }
                //crear objeto auxiliar
                C_touch *aux_touch = new C_touch(path);
                //verificar parametros opcionales
                if(r_flag == true){
                    aux_touch->r_flag = r_flag;
                }
                if(sizeEx){
                    aux_touch->size = size;
                }
                if(cont != NULL){
                    aux_touch->cont = cont;
                }
                if(stdin_flag == true){
                    aux_touch->stdin_flag = stdin_flag;
                }
                //retornar el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_touch;
            }break;
        case CAT:
            {
                //verificar parametros obligatorios
                if(filen == NULL){
                    cout<<"El parametro filen es obligatorio en este comando CAT \n";
                    return NULL;
                }
                //crear objeto auxiliar
                C_cat *aux_cat = new C_cat(filen);
                //retornar objeto auxliar casteado a la clase Comando
                return (Comando*)aux_cat;

            }break;
        case RM:
            {
                //verificar parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando RM \n";
                    return NULL;
                }
                //crear objeto auxiliar
                C_rm *aux_rm = new C_rm(path);
                //retornar objeto auxliar casteado a la clase Comando
                return (Comando*)aux_rm;
            }break;
        case EDIT:
            {
                //verificar parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando EDIT \n";
                    return NULL;
                }
                if(cont == NULL){
                    cout<<"El paramtro cont es obligatorio en este comando EDIT \n";
                    return NULL;
                }
                //crear el objeto auxiliar
                C_edit *aux_edit = new C_edit(path, cont);
                //verificar parametros opcionales
                if(stdin_flag == true){
                    aux_edit->stdin_flag = stdin_flag;
                }
                //retornar el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_edit;
            }break;
        case REN:
            {
                 //verificar que vengan los parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando REN \n";
                }
                if(name == NULL){
                    cout<<"El parametro name es obligatorio en este comando REN \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_ren
                C_ren *aux_ren = new C_ren(path, name);
                //se retorna el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_ren;
            }break;
        case MKDIR:
            {
                 //verificar que vengan los parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando MKDIR \n";
                }
                //crear el objeto auxiliar de la clase C_MKDIR
                C_mkdir *aux_mkdir = new C_mkdir(path);
                //verificar parametros obligarorios
                if(p_flag == true){
                    aux_mkdir->p_flag = p_flag;
                }
                //retornar objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_mkdir;
            }break;
        case CP:
            {
                 //verificar que vengan los parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando CP \n";
                }
                if(dest == NULL){
                    cout<<"El parametro dest es obligatorio en este comando CP \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_cp
                C_cp *aux_cp = new C_cp(path, dest);
                //se retorna el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_cp;
            }break;
        case MV:
            {
                 //verificar que vengan los parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando MV \n";
                }
                if(dest == NULL){
                    cout<<"El parametro dest es obligatorio en este comando MV \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_mv
                C_mv *aux_mv = new C_mv(path, dest);
                //se retorna el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_mv;

            }break;
        case FIND:
            {
                 //verificar que vengan los parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando FIND \n";
                }
                if(name == NULL){
                    cout<<"El parametro name es obligatorio en este comando FIND \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_find
                C_find *aux_find = new C_find(path, name);
                //se retorna el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_find;
            }break;
        case CHOWN:
            {
                 //verificar que vengan los parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando CHOWN \n";
                }
                if(usr == NULL){
                    cout<<"El parametro usr es obligatorio en este comando CHOWN \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_ren
                C_chown *aux_chown = new C_chown(path, usr);
                //verificar parametros opcionales
                if(r_flag == true){
                    aux_chown->r_flag = r_flag;
                }
                //se retorna el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_chown;
            }break;
        case CHGRP:
            {
                 //verificar que vengan los parametros obligatorios
                if(usr == NULL){
                    cout<<"El parametro usr es obligatorio en este comando CHGRP \n";
                }
                if(grp == NULL){
                    cout<<"El parametro grp es obligatorio en este comando CHGRP \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_chgrp
                C_chgrp *aux_chgrp = new C_chgrp(usr, grp);
                //se retorna el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_chgrp;
            }break;
        
        case RECOVERY:
            {
                //verificar los parametros obligatorios
                if(id == NULL){
                    cout<<"El parametro id es obligatorio en este comando RECOVERY \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_recovery
                C_recovery *aux_recovery = new C_recovery(id);
                //se retorna el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_recovery;
            }break;
        case LOSS:
            {
                //verificar los parametros obligatorios
                if(id == NULL){
                    cout<<"El parametro id es obligatorio en este comando LOSS \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_loss
                C_loss *aux_loss = new C_loss(id);
                //se retorna el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_loss;
            }break;
        case EXEC:
            {
                 //verificar parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando EXEC \n";
                    return NULL;
                }
                //crear objeto auxiliar
                C_exec *aux_exec = new C_exec(path);
                //retornar objeto auxliar casteado a la clase Comando
                return (Comando*)aux_exec;
            }break;
    }
    //Si el comando tiene algun error retornara NULL
    return NULL;
}

//Funcion de la clase comando que permite listar elementos del comando
Comando* ListarComando(Comando *command, bool flag){
    //crear una variable estatica para la persistencia de datos en la lista
    static Comando *ListaComandos;
    if(flag){
        ListaComandos = command;
    }
    return ListaComandos;
}

//Funcion que permite escribir los comandos ingresados en un archivo
void Escribir_Comando(string comando, bool bandera){
    FILE *arch;
    if(!bandera){
        arch = fopen("comandos.txt", "w+");
    }else{
        arch = fopen("comandos_definidos.txt", "w+");
    }
    fwrite(comando.c_str(), sizeof(char), strlen(comando.c_str()), arch);
    fclose(arch);
}

//Funcion que permite la lectura de los archivos donde se escribiran los comandos y ejecuta el analizador
void Leer_Comando(bool bandera){
    FILE *arch;
    if(!bandera){
        arch = fopen("comandos.txt", "r");
    }else{
        arch = fopen("comandos_definidos.txt", "r");
    }
    if(arch == NULL){
        cout<<"Error en la lectura del archivo... \n \n";
    }
    //LLAMAR AL ANALIZADOR LEXICO PASANDO COMO PARAMETRO EL ARCHIVO QUE SE LEERA
    yyrestart(arch);
    //LLAMAR AL ANALIZADOR SINTACTICO
    int respuesta = yyparse();
    //SI NO SE OBTIENE RESPUESTA, RETORNA UNA LISTA VACIA
    if(respuesta == 0){
        if(ListarComando(NULL, false)!= NULL){
            //SE REALIZA LA EJECUCION DE LOS COMANDOS
            Activador_Ejecutar(ListarComando(NULL, false));
            ListarComando(NULL, true);
        }
    }
    fclose(arch);
}

//Funcion que recorre la lista formada y realiza la Ejecucion del metodo Ejecutar en cada nodo
void Activador_Ejecutar(Comando* comando){
    Comando *primero = comando;
    while(primero != NULL){
        primero->Ejecutar();
        primero = primero->siguiente;
    }
}