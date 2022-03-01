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
    int aux = 0;
    string nom;
    nom = getNameFromPath(path, &aux);
    char *aux2 = &nom[0];
    string aux3 = getPathSinNombre(path, strlen(aux2)+aux);
    Respuesta resultado = CrearDisk(size, fit, unit, &aux3[0], aux2);
    if(resultado == CORRECTO){
        cout<<"EL DISCO FUE CREADO EXITOSAMENTE... \n";
    }else{
        getErrorMsj(resultado);
    }
}

//CREAR RMDISK
C_rmdisk::C_rmdisk(char path[]){
    //parametros obligatorios
    this->path = path;
}

//FUNCION EJECUTAR RMDISK
void C_rmdisk::Ejecutar(){
    cout<<"Ejecutando comando RMDISK... \n ";
    RemoveDisk(path);
}

//CREAR FDISK
C_fdisk::C_fdisk(int size, char path[], char name[]){
    //parametros obligatorios
    this->size = size;
    this->path = path;
    this->name = name;
    //patrametros opcionales con valor por defecto
    this->unit = K;
    this->tipo = P;
    this->fit = WF;
    this->capacidad = CAPACIDAD_ERROR;    
}

//FUNCION EJECUTAR FDISK
void C_fdisk::Ejecutar(){
    cout<<"Ejecutando comando FDISK... \n ";
    int inicio = 0;
    string str;
    str = getNameFromPath(path, &inicio);
    char *word = &str[0];
    string finalstr = getPathSinNombre(path, strlen(word) + inicio);
    Respuesta res = CrearParticion(size, unit, &finalstr[0], word, this->tipo, fit, name);
    if(res == CORRECTO){
        switch(this->tipo){
            case P:
            {
                cout<<"SE HA CREADO UNA PARTICION PRIMARIA... "<<endl;
            }break;
            case E:
            {
                cout<<"SE HA CREADO UNA PARTICION EXTENDIDA... "<<endl;
            }break;
            case L:
            {
                cout<<"SE HA CREADO UNA PARTICION LOGICA... "<<endl;
            }break;
            default:
            {
                break;
            }
        }
    }else{
        getErrorMsj(res);
    }
}

//CLASE AUXILIAR PARA EJECUTAR EL PARAMETRO ADD EN EL COMANDO FDISK
C_add::C_add(char name[], char path[], int size){
    //parametros obligatorios
    this->size = size;
    this->name = name;
    this->path = path;
    //parametros opcionales con valor por defecto
    this->unit = K;
}

//funcion ejecutar comando FDISK con parametro add
void C_add::Ejecutar(){
    cout<<"Ejecutando comando FDISK con parametro ADD... \n ";
    int inicio = 0;
    string str;
    str = getNameFromPath(path, &inicio);
    char *word = &str[0];
    string finalstr = getPathSinNombre(path, strlen(word) + inicio);
    Respuesta res = AddSizePart(&finalstr[0], word, name, this->size, unit);
    if(res == CORRECTO){
        cout<<"LA PARTICION SE HA MODIFICADO EXITOSAMENTE... "<<endl;
    }else{
        getErrorMsj(res);
    }
}

//Clase auxiliar para ejecutar el parametro DELETE en el comando FDISK
C_delete::C_delete(char name[], char path[], Tipocapacidad capacidad, Tipoparticion tipo){
    //parametros obligatorios
    this->name = name;
    this->path = path;
    this->capacidad = capacidad;
    this->tipo = tipo;
}

//funcion ejecutar FDISK con parametro delete
void C_delete::Ejecutar(){
    cout<<"Ejecutando comando FDISK con parametro DELETE... \n ";
    int inicio = 0;
    string str;
    str = getNameFromPath(path, &inicio);
    char *word = &str[0];
    string finalstr = getPathSinNombre(path, strlen(word) + inicio);
    Respuesta res = DeletePart(&finalstr[0], word, name, this->tipo, this->capacidad);
    if(res == CORRECTO){
        cout<<"LA PARTICION HA SIDO ELIMINADA EXITOSAMENTE... "<<endl;
    }else{
        getErrorMsj(res);
    }

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
    Respuesta res = MontarParticion(path, name);
    if(res != CORRECTO){
        getErrorMsj(res);
        return;
    }else{
        cout<<"SE HA MONTADO UNA PARTICION EXITOSAMENTE... \n";
    }
}

//CREAR UNMOUNT
C_unmount::C_unmount(char id[]){
    //parametros obligatorios
    this->id = id;
}

//FUNCION EJECUTAR UNMOUNT
void C_unmount::Ejecutar(){
    cout<<"Ejecutando comando UNMOUNT... \n ";
    Respuesta res = UnmountP(id);
    if(res != CORRECTO){
        getErrorMsj(res);
        return;
    }else{
        showMounts();
        cout<<"PARTICION DESMONTADA EXITOSAMENTE... \n";
    }
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
C_login::C_login(char usuario[], char password[], char id[]){
    //parametros obligatorios
    this->usuario = usuario;
    this->password = password;
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
C_mkusr::C_mkusr(char usuario[], char pwd[], char grp[]){
    //parametros obligatorios
    this->usuario = usuario;
    this->pwd = pwd;
    this->grp = grp;
}

//FUNCION EJECUTAR MKUSR
void C_mkusr::Ejecutar(){
    cout<<"Ejecutando comando MKUSR... \n ";
}

//CREAR RMUSR
C_rmusr::C_rmusr(char usuario[]){
    //parametros obligatorios
    this->usuario = usuario;
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

//CREAR MKFILE
C_mkfile::C_mkfile(char path[]){
    //paramtros obligatorios
    this->path = path;
    //parametros opcionales con valor por defecto
    this->r_flag = false;
    this->size = 0;
    this->cont = NULL;
}

//FUNCION EJECUTAR MKFILE
void C_mkfile::Ejecutar(){
    cout<<"Ejecutando comando MKFILE... \n ";
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

//CREAR REMOVE
C_remove::C_remove(char path[]){
    //parametros obligatorios
    this->path = path;
}

//FUNCION EJECUTAR REMOVE
void C_remove::Ejecutar(){
    cout<<"Ejecutando comando REMOVE... \n ";
}

//CREAR EDIT
C_edit::C_edit(char path[], char contenido[]){
    //parametros obligatorios
    this->path = path;
    this->contenido = contenido;
}

//FUNCION EJECUTAR EDIT
void C_edit::Ejecutar(){
    cout<<"Ejecutando comando EDIT... \n ";
}

//CREAR RENAME
C_rename::C_rename(char path[], char name[]){
    //parametros obligatorios
    this->path = path;
    this->name = name;
}

//FUNCION EJECUTAR RENAME
void C_rename::Ejecutar(){
    cout<<"Ejecutando comando RENAME... \n ";
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

//CREAR COPY
C_copy::C_copy(char path[], char destino[]){
    //parametros obligatorios
    this->path = path;
    this->destino = destino;
}

//FUNCION EJECUTAR COPY
void C_copy::Ejecutar(){
    cout<<"Ejecutando comando COPY... \n ";
}

//CREAR MOVE
C_move::C_move(char path[], char dest[]){
    //parametros obligatorios
    this->path = path;
    this->destino = destino;
}

//FUNCION EJECUTAR MOVE
void C_move::Ejecutar(){
    cout<<"Ejecutando comando MOVE... \n ";
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
C_chown::C_chown(char path[], char usuario[]){
    //parametros obligatorios
    this->path = path;
    this->usuario = usuario;
    //parametros opcionales con valor por defecto
    this->r_flag = false;
}

//FUNCION EJECUTAR CHOWN
void C_chown::Ejecutar(){
    cout<<"Ejecutando comando CHOWN... \n ";
}


//CREAR CHGRP
C_chgrp::C_chgrp(char usuario[], char grp[]){
    //parametros obligatorios
    this->usuario = usuario;
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
    FILE *archaux = fopen(path, "r");
    if(archaux == NULL){
        cout<<"ERROR AL INTENTAR ABIR EL SCRIPT... "<<endl;
        return;
    }
    //se crea un buffer para la lectura 
    char Buffer[1024];
    while(fgets(Buffer, 1024, archaux)){
        cout<<Buffer<<endl;
        Escribir_Comando(Buffer,true);
        Leer_Comando(true);
    }
    fclose(archaux);
}

//CREAR REP
C_rep::C_rep(Tiporeporte reporte, char path[], char id[]){
    //parametros obligatorios
    this->reporte = reporte;
    this->path = path;
    this->id = id;
    //parametros opcionales con valor por defecto
    this->ruta = NULL;
}

//FUNCION EJECUTAR REP
void C_rep::Ejecutar(){
    showMounts();
    cout<<"Ejecutando comando REP... \n";
    Discos_Montados *disk = getDiscoMontado(this->id);
    if(disk == NULL){
        cout<<"NO HAY DISCOS MONTADOS... \n";
        return;
    }
    Particiones_Montadas *part = getParticionMontada(this->id);
    if(part == NULL){
        cout<<"LA PARTICION NO HA SIDO MONTADA... \n";
        return;
    }
    int ext = 0;
    string msj;
    msj = getNameFromPath(this->path, &ext);
    char *aux = &msj[0];
    string aux2 = getPathSinNombre(this->path, strlen(aux) + ext);
    CrearCarpeta(aux2);
    switch(this->reporte){
        case MBR:
        {
            cout<<"REPORTE MBR... "<<endl;
            ReadDisk(this->path);
            ReporteMasterBootRecord(disk->path, this->path);
        }break;
        case DISK:
        {
            cout<<"REPORTE DISK... "<<endl;
            ReporteDisco(disk->path, this->path);
        }break;
        case INODE:
        {
            cout<<"REPORTE INODE... "<<endl;
        }break;
        case BLOCK:
        {
            cout<<"REPORTE BLOCK... "<<endl;
        }break;
        case JOURNALING:
        {
            cout<<"REPORTE JOURNALING... "<<endl;
        }break;
        case BM_BLOCK:
        {
            cout<<"REPORTE BM_BLOCK... "<<endl;
        }break;
        case BM_INODE:
        {
            cout<<"REPORTE BM_INODE... "<<endl;
        }break;
        case TREE:
        {
            cout<<"REPORTE TREE... "<<endl;
        }break;
        case SB:
        {
            cout<<"REPORTE SB... "<<endl;
        }break;
        case FILE_REP:
        {
            cout<<"REPORTE FILE... "<<endl;
        }break;
        case LS:
        {
            cout<<"REPORTE LS... "<<endl;
        }break;
        default:
        {
            cout<<"EL REPORTE SOLICITADO ES INCORRECTO... "<<endl;
        }break;
    }
}

//FUNCION EJECUTAR LOGOUT
void C_logout::Ejecutar(){
    cout<<"Ejecutando comando LOGOUT... \n ";
}

//FUNCION EJECUTAR PAUSE
void C_pause::Ejecutar(){
    cout<<"Ejecutando comando PAUSE... \n ";
    system("read -r -p \"PARA CONTINUAR PRESIONA CUALQUIER TECLA...\" key");
}


//FUNCION ValidarParametros HACE UN ANALISIS SEMANTICO VALIDANDO LOS PARAMETROS QUE VIENEN EN CADA COMANDO
bool ValidarParametros(char *name, char *path, char *id, char *usuario, char *password, char *pwd, char *grp, 
                        char *cont, char *contenido, char *filen, char *destino, char *ruta, Tipofit fit,
                        Tipounit unit, Tipoparticion type, Tipocapacidad capacidad, Tiposistema sistema,
                        bool sizeEx, bool addEx, bool ugoEx, bool r_flag, bool p_flag, TipoComando commandtype){
                            //VALIDA QUE VENGAN UNICAMENTE LOS PARAMETREOS ACEPTADOS POR CADA COMANDO
                            switch(commandtype){
                                case MKDISK:
                                    {//Parametros permitidos: size, path , fit, unit
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            contenido != NULL||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            addEx ||
                                            ugoEx 
                                        );
                                    }break;
                                case RMDISK:
                                    {//Parametros permitidos: path 
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case FDISK:
                                    {//Parametros permitidos: path, size, name, unit, type, fit, delete, add 
                                        return!(
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            ugoEx 
                                        );                   
                                    }break;
                                case MOUNT:
                                    {//Parametros permitidos: path, name 
                                        return!(
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case UNMOUNT:
                                    {//Parametros permitidos: id 
                                        return!(
                                            name != NULL ||
                                            path != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case MKFS:
                                    {//Parametros permitidos: id, type, fs
                                        return!(
                                            name != NULL ||
                                            path != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            p_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case LOGIN:
                                    {//Parametros permitidos: usuario, password, id 
                                        return!(
                                            name != NULL ||
                                            path != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case MKGRP:
                                    {//Parametros permitidos: name 
                                        return!(
                                            path != NULL ||
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case RMGRP:
                                    {//Parametros permitidos: name 
                                        return!(
                                            path != NULL ||
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case MKUSR:
                                    {//Parametros permitidos: usuario, pwd, grp 
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            path != NULL ||
                                            password != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case RMUSR:
                                    {//Parametros permitidos: usuario 
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            path != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case CHMOD:
                                    {//Parametros permitidos: path, ugo, r 
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            p_flag ||
                                            addEx ||
                                            sizeEx
                                        );
                                    }break;
                                case MKFILE:
                                    {//Parametros permitidos: path, r, size, cont
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case REMOVE:
                                    {//Parametros permitidos: path 
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case EDIT:
                                    {//Parametros permitidos: path, contenido 
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case RENAME:
                                    {//Parametros permitidos: path, name 
                                        return!(
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case MKDIR:
                                    {//Parametros permitidos: path, p
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            r_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case COPY:
                                    {//Parametros permitidos: path, destino 
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
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
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case MOVE:
                                    {//Parametros permitidos: path, destino 
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
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
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case FIND:
                                    {//Parametros permitidos: path, name
                                        return!(
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case CHOWN:
                                    {//Parametros permitidos: path, usuario, r
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
                                            fit != FIT_ERROR ||
                                            unit != UNIT_ERROR ||
                                            type != TIPO_ERROR ||
                                            capacidad != CAPACIDAD_ERROR ||
                                            sistema != FS_EXT_ERROR ||
                                            //banderas para verificar el tipo de dato
                                            p_flag ||
                                            addEx ||
                                            ugoEx ||
                                            sizeEx
                                        );
                                    }break;
                                case CHGRP:
                                    {//Parametros permitidos: usuario, grp
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            path != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case RECOVERY:
                                    {//Parametros permitidos: id 
                                        return!(
                                            name != NULL ||
                                            path != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case LOSS:
                                    {//Parametros permitidos: id 
                                        return!(
                                            name != NULL ||
                                            path != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case EXEC:
                                    {//Parametros permitidos: path
                                        return!(
                                            name != NULL ||
                                            id != NULL ||
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            ruta != NULL ||
                                            destino != NULL ||
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
                                case REP:
                                    {//Parametros permitidos: path, name, id , ruta
                                        return!(
                                            usuario != NULL ||
                                            password != NULL ||
                                            pwd != NULL ||
                                            grp != NULL ||
                                            cont != NULL ||
                                            contenido != NULL ||
                                            filen != NULL ||
                                            destino != NULL ||
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
    char *usuario = NULL;
    char *password = NULL;
    char *pwd = NULL;
    char *grp = NULL;
    char *cont = NULL;
    char *contenido = NULL;
    char *filen = NULL;
    char *destino = NULL;
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
    int size = -1;
    int ugo = -1;
    int add = -1;

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
            case FIT:
                {
                    fit = auxparam->fit;
                }break;
            case UNIT:
                {
                    unit = auxparam->unit;
                }break;
            case TYPE:
                {
                    type = auxparam->type;
                }break;
            case DELETE:
            case FORMATO:
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
            case USUARIO:
                {
                    usuario = auxparam->text;
                }break;
            case PASSWORD:
                {
                    password = auxparam->text;
                }break;
            case PWD:
                {
                    pwd = auxparam->text;
                }break;
            case R:
                {
                    r_flag = auxparam->r_flag;
                }break;
            case CONTENIDO:
                {
                    contenido = auxparam->text;
                }break;
            case CONT:
                {
                    cont = auxparam->text;
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
            case DESTINO:
                {
                    destino = auxparam->text;
                }break;
            case RUTA:
                {
                    ruta = auxparam->text;
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
    if(!ValidarParametros(name, path, id, usuario, password, pwd, grp, 
                        cont, contenido, filen, destino, ruta, fit,
                        unit, type, capacidad, sistema, sizeEx, addEx,
                        ugoEx, r_flag, p_flag, commandtype)){
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
                if(!sizeEx && type == -1){
                    cout<<"El parametro size es obligatorio en este comando FDISK \n";
                    return NULL;
                }
                if(name == NULL){
                    cout<<"El parametro name es obligatorio en este comando FDISK \n";
                    return NULL;
                }
                if(capacidad != CAPACIDAD_ERROR){
                    //Eliminar la particion
                    C_delete *del = new C_delete(name, path, capacidad, P);
                    //verificar que tenga parametro tipo de particion
                    if(type != TIPO_ERROR){
                        del->tipo = type;
                    }
                    return del;
                }
                if(addEx){
                    //agregar tamano
                    C_add *addp = new C_add(name, path, size);
                    //verificar que tenga el parametro unit
                    if(unit != UNIT_ERROR){
                        addp->unit = unit;
                    }
                    return addp;
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
                if(usuario == NULL){
                    cout<<"El parametro usuario es obligatorio en esta comando LOGIN \n";
                    return NULL;
                }
                if(password == NULL){
                    cout<<"El parametro password es obligatorio en este comando LOGIN \n";
                    return NULL;
                }
                if(id == NULL){
                    cout<<"El parametro id es obligatorio en este comando LOGIN \n";
                    return NULL;
                }
                //crear objeto auxiliar de la clase C_login
                C_login *aux_login = new C_login(usuario,password,id);
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
                if(usuario == NULL){
                    cout<<"El parametro usuario es obligatorio en esta comando MKUSR \n";
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
                C_mkusr *aux_mkusr = new C_mkusr(usuario,pwd,grp);
                //retornar el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_mkusr;
            }break;
        case RMUSR:
            {
                //verificar que vengan los parametros obligatorios, si no viene el valor retorna NULL
                if(usuario == NULL){
                    cout<<"El parametro usuario es obligatorio en este comando RMUSR \n";
                    return NULL;
                }
                //se crea un objeto auxiliar de la clase C_rmusr
                C_rmusr *aux_rmusr = new C_rmusr(usuario);
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
        case MKFILE:
            {
                //verificar parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando MKFILE \n";
                    return NULL;
                }
                //crear objeto auxiliar
                C_mkfile *aux_mkfile = new C_mkfile(path);
                //verificar parametros opcionales
                if(r_flag == true){
                    aux_mkfile->r_flag = r_flag;
                }
                if(sizeEx){
                    aux_mkfile->size = size;
                }
                if(cont != NULL){
                    aux_mkfile->cont = cont;
                }
                //retornar el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_mkfile;
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
        case REMOVE:
            {
                //verificar parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando REMOVE \n";
                    return NULL;
                }
                //crear objeto auxiliar
                C_remove *aux_remove = new C_remove(path);
                //retornar objeto auxliar casteado a la clase Comando
                return (Comando*)aux_remove;
            }break;
        case EDIT:
            {
                //verificar parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando EDIT \n";
                    return NULL;
                }
                if(contenido == NULL){
                    cout<<"El paramtro contenido es obligatorio en este comando EDIT \n";
                    return NULL;
                }
                //crear el objeto auxiliar
                C_edit *aux_edit = new C_edit(path, contenido);
                //retornar el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_edit;
            }break;
        case RENAME:
            {
                 //verificar que vengan los parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando RENAME \n";
                }
                if(name == NULL){
                    cout<<"El parametro name es obligatorio en este comando RENAME \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_rename
                C_rename *aux_rename = new C_rename(path, name);
                //se retorna el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_rename;
            }break;
        case MKDIR:
            {
                 //verificar que vengan los parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando MKDIR \n";
                }
                //crear el objeto auxiliar de la clase C_mkdir
                C_mkdir *aux_mkdir = new C_mkdir(path);
                //verificar parametros obligarorios
                if(p_flag == true){
                    aux_mkdir->p_flag = p_flag;
                }
                //retornar objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_mkdir;
            }break;
        case COPY:
            {
                 //verificar que vengan los parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando COPY \n";
                }
                if(destino == NULL){
                    cout<<"El parametro destino es obligatorio en este comando COPY \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_copy
                C_copy *aux_copy = new C_copy(path, destino);
                //se retorna el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_copy;
            }break;
        case MOVE:
            {
                 //verificar que vengan los parametros obligatorios
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando MOVE \n";
                }
                if(destino == NULL){
                    cout<<"El parametro dest es obligatorio en este comando MOVE \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_move
                C_move *aux_move = new C_move(path, destino);
                //se retorna el objeto auxiliar casteado a la clase Comando
                return (Comando*)aux_move;

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
                if(usuario == NULL){
                    cout<<"El parametro usuario es obligatorio en este comando CHOWN \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_ren
                C_chown *aux_chown = new C_chown(path, usuario);
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
                if(usuario == NULL){
                    cout<<"El parametro usuario es obligatorio en este comando CHGRP \n";
                }
                if(grp == NULL){
                    cout<<"El parametro grp es obligatorio en este comando CHGRP \n";
                    return NULL;
                }
                //crear el objeto auxiliar de la clase C_chgrp
                C_chgrp *aux_chgrp = new C_chgrp(usuario, grp);
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
        case REP:
            {
                 //verificar parametros obligatorios
                if(name == NULL){
                    cout<<"El parametro name es obligatorio en este comando REP \n";
                    return NULL;
                }
                if(path == NULL){
                    cout<<"El parametro path es obligatorio en este comando REP \n";
                    return NULL;
                }
                if(id == NULL){
                    cout<<"El parametro id es obligatorio en este comando REP \n";
                    return NULL;
                }
                //verificar tipo de reporte
                Tiporeporte reporte;
                if(strcasecmp(name,"MBR")==0){
                    reporte = MBR;
                }else if(strcasecmp(name,"DISK")==0){
                    reporte = DISK;
                }else if(strcasecmp(name,"INODE")==0){
                    reporte = INODE;
                }else if(strcasecmp(name,"JOURNALING")==0){
                    reporte = JOURNALING;
                }else if(strcasecmp(name,"BLOCK")==0){
                    reporte = BLOCK;
                }else if(strcasecmp(name,"BM_INODE")==0){
                    reporte = BM_INODE;
                }else if(strcasecmp(name,"BM_BLOCK")==0){
                    reporte = BM_BLOCK;
                }else if(strcasecmp(name,"TREE")==0){
                    reporte = TREE;
                }else if(strcasecmp(name,"SB")==0){
                    reporte = SB;
                }else if(strcasecmp(name,"FILE")==0){
                    reporte = FILE_REP;
                }else if(strcasecmp(name,"LS")==0){
                    reporte = LS;
                }else{
                    cout<<"EL TIPO DE REPORTE NO EXISTE... "<<endl;
                    return NULL;
                }
                //crear objeto auxiliar
                C_rep *aux_rep = new C_rep(reporte, path, id);
                //verificar parametros opcionales
                if(reporte == LS || reporte == FILE_REP){
                    if(ruta == NULL){
                        cout<<"AL SOLICITAR ESTE TIPO DE REPORTE DEBE INGRESAR EL PARAMETRO -ruta... "<<endl;
                        return NULL;
                    }else{
                        aux_rep->ruta = ruta;
                    }
                }
                //retornar objeto auxliar casteado a la clase Comando
                return (Comando*)aux_rep;
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
        arch = fopen("comandos.script", "w+");
    }else{
        arch = fopen("definidos.script", "w+");
    }
    fwrite(comando.c_str(), sizeof(char), strlen(comando.c_str()), arch);
    fclose(arch);
}

//Funcion que permite la lectura de los archivos donde se escribiran los comandos y ejecuta el analizador
void Leer_Comando(bool bandera){
    FILE *arch;
    if(!bandera){
        arch = fopen("comandos.script", "r");
    }else{
        arch = fopen("definidos.script", "r");
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
