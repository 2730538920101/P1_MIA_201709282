#ifndef TIPOS_H
#define TIPOS_H

enum Tipofit {BF, FF, WF, FIT_ERROR};
enum Tipounit {K, M, B, UNIT_ERROR};
enum Tipoparticion {P, E, L, TIPO_ERROR};
enum Tipocapacidad {FAST, FULL, CAPACIDAD_ERROR};
enum Tiposistema {EXT2, EXT3, FS_EXT_ERROR};

enum Tipostatus {ACTIVO = 1, INACTIVO = 0};

enum Tiporeporte {
    MBR,
    DISK,
    INODE,
    JOURNALING,
    BLOCK,
    BM_INODE,
    BM_BLOCK,
    TREE,
    SB,
    FILE_REP,
    LS,
    REPORTE_ERROR
};

enum Respuesta { 
    CORRECTO,
    ERR_DISK_NO_EX
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
    MKFILE,
    CAT,
    REMOVE,
    EDIT,
    RENAME,
    MKDIR,
    COPY,
    MOVE,
    FIND,
    CHOWN,
    CHGRP,
    RECOVERY,
    LOSS,
    EXEC,
    PAUSE,
    REP
};

enum Tipoparametro{
    SIZE,
    PATH,
    ID,
    FIT,
    UNIT,
    TYPE,
    DELETE,
    ADD,
    NAME,
    FS,
    USUARIO,
    PASSWORD,
    PWD,
    R,
    CONT, 
    CONTENIDO,
    GRP, 
    UGO, 
    FILEN, 
    PP,
    DESTINO,
    RUTA
};


#endif //TIPOS_H