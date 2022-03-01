#ifndef TIPOS_H
#define TIPOS_H

enum Tipofit {BF='B', FF='F', WF='W', FIT_ERROR};
enum Tipounit {K='k', M='m', B='b', UNIT_ERROR};
enum Tipoparticion {P='P', E='E', L='L', TIPO_ERROR};
enum Tipocapacidad {FAST, FULL, CAPACIDAD_ERROR};
enum Tiposistema {EXT2='2', EXT3='3', FS_EXT_ERROR};

enum Tipostatus {ACTIVO = '1', INACTIVO = '0'};
enum Tipostatusblock {OCUPADO, LIBRE};

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
    ERR_DISK_NO_EX,
    ERR_ID_INCORRECT,
    ERR_DISK_UNMOUNTED,
    ERR_ESPACIO_INS,
    ERR_PART_EX,
    ERR_PP_LLENA,
    ERR_PE_EX,
    ERR_PE_NOEX,
    ERR_IRRECONOCIBLE,
    ERR_TAM_MIN,
    ERR_PART_NOEX,
    ERR_NO_ADD_ESPACIO,
    ERR_DISCO_NO_MONT,
    ERR_ID_MAL_GEN,
    ERR_PART_UNMOUNTED,
    ERR_PART_MOUNTED
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
    RUTA,
    FORMATO
};

enum Tipoinodo{
    IN_FILE = 0,
    IN_DIRECTORY = 1
};

#endif //TIPOS_H