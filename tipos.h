#ifndef TIPOS_H
#define TIPOS_H

enum Tipofit {BF, FF, WF, FIT_ERROR};
enum Tipounit {K, M, B, UNIT_ERROR};
enum Tipoparticion {P, E, L, TIPO_ERROR};
enum Tipocapacidad {FAST, FULL, CAPACIDAD_ERROR};
enum Tiposistema {EXT2, EXT3, FS_EXT_ERROR};
enum Respuesta { 
    CORRECTO
};

enum TipoComando{
    MKDISK,
    RMDISK,
    FDISK,
    MOUNT,
    UNMOUNT,
    MKFS,
    LOGIN,
    LOGOUT,
    MKGRP,
    RMGRP,
    MKUSR,
    RMUSR,
    CHMOD,
    TOUCH,
    CAT,
    RM,
    EDIT,
    REN,
    MKDIR,
    CP,
    MV,
    FIND,
    CHOWN,
    CHGRP,
    RECOVERY,
    LOSS,
    EXEC,
    PAUSE
};

enum Tipoparametro{
    SIZE,
    PATH,
    ID,
    F,
    U,
    TYPE,
    DELETE,
    ADD,
    NAME,
    FS,
    USR,
    PWD,
    R,
    CONT, 
    STDIN,
    GRP, 
    UGO, 
    FILEN, 
    PP,
    DEST

};


#endif //TIPOS_H