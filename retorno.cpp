#include "retorno.h"
#include <iostream>

using namespace std;

//FUNCION QUE DEVUELVE EL VALOR DE UN NUMERO EN ENTERO
int getNumero(string num){
    try{
        //PRUEBA DEVOLVER EL VALOR DEL NUMERO EN ENTERO
        int i = stoi(num);
        return i;
    }catch(invalid_argument const &e){
        cout<<"El valor ingresado es invalido"<<"\n";
        return -123456789;
    }catch(out_of_range const &e){
        cout<<"El numero es muy extenso"<<"\n";
        return -123456789;
    }
}

//FUNCION QUE ME DEVUELVE LAS CADENAS SIN COMILLAS
string getCadenaSinComillas(char path_original[]){
    string str(path_original);
    str = str.substr(1, strlen(path_original)-2);
    return &str[0];
}


//FUNCION QUE DEVUELVE EL NOMBRE DE UN ARCHIVO DESDE EL PATH RECIBIDO
string getNameFromPath(char *path, int *position){
    //casting de char a string
    string nom(path);
    //definir el delimitador de las rutas
    string delimitador = "/";
    //inicializar el tamano del string
    size_t pos = 0;
    //string auxiliar
    string token;
    //extraer el string que hay dentro del delimitador
    while((pos = nom.find(delimitador)) != std::string::npos){
        token = nom.substr(0,pos);
        nom.erase(0, pos + delimitador.length());
    }
    //marcar el final del string para ubicar el nombre
    int posf = -1;
    posf = nom.find(".");
    if(posf > 0){
        //obtener el tamano completo del nombre
        int sizecomp = strlen(nom.c_str());
        nom = nom.substr(0, posf);
        *position = sizecomp - posf;
    }
    return nom;
}

//FUNCION QUE DEVUELVE EL PATH SIN EL NOMBRE INCLUIDO EN EL STRING
string getPathSinNombre(char *path, int tamNombre){
    //Castear el path a string
    string rut(path);
    //Obtener el tamano
    int tam = strlen(path);
    //borrar el nombre del archivo del path
    if(tam - tamNombre -1 < tam && tam - tamNombre -1 > 0){
        return rut.substr(0, tam - tamNombre -1);
    }
    return rut;
}




//FUNCION QUE DEVUELVE EL VALOR DEL TAMANO QUE SE INGRESA
long getSize(int size, Tipounit unidad){
    //fijar el tamano
    size_t finaltam;
    switch(unidad){
        //devuelve cantidad en bytes
        case B:
        {
            finaltam = size;
        }break;
        //devuelve cantidad en mega bytes
        case M:
        {
            finaltam = size * 1024;
            finaltam = finaltam * 1024;
        }break;
        //devuelve cantidad en kilo bytes
        case K:
        {
            finaltam = size * 1024;
        }break;
        //devuelve cantidad en kilo bytes por defecto
        default:
        {
            finaltam = size * 1024;
        }break;
    }
    return finaltam;
}

//FUNCION QUE DEVUELVE LA FECHA ACTUAL EN EL SISTEMA
void getFecha(char *date){
    
    //obtener el tiempo del sistema
    time_t t;
    //struct auxiliar para dar formato
    struct tm *local;
    t = time(NULL);
    local = localtime(&t);
    //formato en string
    strftime(date, 16, "%d/%m/%y %H:%M", local);
}

//FUNCION PARA CREAR CARPETAS
void CrearCarpeta(string path){
    //inicializar una variable para copiar el string
    char auxpath[150];
    strcpy(auxpath, &path[0]);
    //contador para la posicion en el string
    int pos = 0;
    //buscar la ruta en el string
    for(int i = 0; i < strlen(auxpath); i++){
        if(auxpath[i] == '/'){
            pos = i;
        }
    }
    auxpath[pos] = '\0';
    //INSTANCIAR UN DIRECTORIO
    DIR* carpeta = opendir(auxpath);
    //verificar que la carpeta esta creada
    if(carpeta == 0){
        //iniciar un buffer
        char com[1024] = "";
        //iniciar un string para ingresar comandos al sistema otorgando permisos 777 al directorio creado
        strcat(com, "sudo mkdir -p -m 777 \"");
        strcat(com, auxpath);
        strcat(com, "\"");
        com[strlen(com)+1] = '\0';
        system(com);
    }
}


//FUNCION PARA LIMPIAR UN ARRAY
void LimpiarArray(char array[], int tam){
    for(int i = 0; i < tam; i++){
        array[i] = 0;
    }
}

//FUNCION QUE VERIFICA EL PATH DEL DISCO
void getPathOfDisk(char path[], char name[], char path_comp[]){
    strcat(path_comp, path);
    strcat(path_comp, "/");
    strcat(path_comp, name);
    strcat(path_comp, ".dk");
}



//FUNCION QUE DEVUELVE UN MENSAJE DE ERROR SEGUN EL ERROR QUE ENCUENTRE
void getErrorMsj(Respuesta res){
    switch(res){
        case ERR_DISK_NO_EX:
        {
            cout<<"EL DISCO NO EXISTE... \n";
        }break;
        case ERR_ID_INCORRECT:
        {
            cout<<"EL ID ES INCORRECTO... \n";
        }break;
        case ERR_DISK_UNMOUNTED:
        {
            cout<<"EL DISCO NO ESTA MONTADO... \n";
        }break;
        case ERR_ESPACIO_INS:
        {
            cout<<"EL DISCO NO TIENE SUFICIENTE ESPACIO... \n";
        }break;
        case ERR_PART_EX:
        {
            cout<<"LA PARTICION YA EXISTE EN EL DISCO... \n";
        }break;
        case ERR_PP_LLENA:
        {
            cout<<"EL DISCO NO PUEDE CREAR UNA PARTICION PRIMARIA, SOLO PERMITE 4... \n";
        }break;
        case ERR_PE_EX:
        {
            cout<<"EL DISCO YA TIENE UNA PARTICION EXTENDIDA... \n";
        }break;
        case ERR_PE_NOEX:
        {
            cout<<"ERROR AL OPERAR LA PARTICION LOGICA, NO EXISTE UNA PARTICION EXTENDIDA EN EL DISCO... \n";
        }break;
        case ERR_IRRECONOCIBLE:
        {
            cout<<"ERROR NO MANEJABLE... \n";
        }break;
        case ERR_TAM_MIN:
        {
            cout<<"EL TAMANO DEBE SER MAYOR A CERO... \n";
        }break;
        case ERR_PART_NOEX:
        {
            cout<<"LA PARTICION NO EXISTE... \n";
        }break;
        case ERR_NO_ADD_ESPACIO:
        {
            cout<<"NO SE PUEDE AGREGAR ESPACIO A LA PARTICION, YA NO HAY ESPACIO LIBRE... \n";
        }break;
        case ERR_PART_UNMOUNTED:
        {
            cout<<"LA PARTICION NO HA SIDO MONTADA... \n";
        }break;
        case ERR_PART_MOUNTED:
        {
            cout<<"LA PARTICION YA HA SIDO MONTADA... \n";
        }break;
        case ERR_DIR_NOEX:
        {
            cout<<"EL DIRECTORIO NO EXISTE... \n";
        }break;
        case ERR_LEVEL_FULL:
        {
            cout<<"NO SE PUEDEN CREAR MAS CARPETAS O ARCHIVOS, NO HAY ESPACIO SUFICIENTE... \n";
        }break;
        case ERR_GRP_EX:
        {
            cout<<"ERROR, EL GRUPO YA EXISTE... \n";
        }break;
        case ERR_GRP_NOEX:
        {
            cout<<"ERROR, EL GRUPO NO EXISTE... \n";
        }break;
        case ERR_USR_EX:
        {
            cout<<"ERROR, EL USUARIO YA EXISTE... \n";
        }break;
        case ERR_USR_NOEX:
        {
            cout<<"ERROR, EL USUARIO NO EXISTE... \n";
        }break;
        case ERR_INCORRECT_PWD:
        {
            cout<<"ERROR, EL PASSWORD ES INCORRECTO... \n";
        }break;
        case ERR_FILESYSTEM:
        {
            cout<<"ERROR, EL SISTEMA DE ARCHIVOS NO PUEDE EJECUTAR EL COMANDO... \n";
        }break;
        case ERR_RECOVERY:
        {
            cout<<"ERROR, EL SISTEMA DE ARCHIVOS NO SE PUDO RESTAURAR COMPLETAMENTE... \n";
        }break;
        default:
        {
            cout<<"ERROR NO IDENTIFICADO... \n";
        }break;
    }
}

//FUNCION PARA ESCRIBIR CEROS EN UN ARCHIVO
void LlenarCeros(char path[], int pos, int tam){
    //INICIALIZAR UN PUNTERO A UN ARCHIVO UBICADO EN LA RUTA QUE RECIBE COMO PARAMETRO
    FILE *arch;
    arch = fopen(path, "rb+");
    //VERIFICAR QUE EXISTA O SE HAYA CREADO EL ARCHIVO
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL ARCHIVO... \n";
        return;
    }
    //ubicar el puntero en la posicion que recibe como parametro
    fseek(arch, pos, SEEK_SET);
    //FTELL DA EL VALOR DE LA POSICION SENALADA POR EL PUNTERO REUBICADO POR FSEEK
    //FTELL DEVUELVE -1 SI NO SE CUMPLE 
    while(ftell(arch) < tam && ftell(arch) !=-1){
        //escribir ceros
        fwrite("\0",sizeof(char), 1, arch);
    }
    //CERRAR EL STREAM
    fclose(arch);
}


//FUNCION QUE CUENTA LOS DISCOS
Respuesta getContDisk(int *contador, char *id){
    //casting a string del id
    string word(id);
    //verificar la longitud del id
    if(strlen(id) < 4){
        return ERR_ID_INCORRECT;
    }
    char letra = word.at(2);
    //BUSCAR LA LETRA
    *contador = 0;
    //bandera para verificar si existe el disco
    bool flag = false;
    while(discos_montados[*contador] != NULL){
        //validar la existencia
        if(discos_montados[*contador]->letra == letra){
            flag = true;
            break;
        }
        (*contador)++;
    }
    //validar error de disco montado
    if(!flag){
        return ERR_DISK_UNMOUNTED;
    }
    //devolver respuesta de exito
    return CORRECTO;
}


//FUNCION QUE RETORNA UN ID PARA LAS PARTICIONES CREADAS CON LOS ULTIMOS DIGITOS DE MI CARNET COMO BASE
//82
char *getPartitionId(char letra, int numero){
    string str("82");
    str+=to_string(numero);
    str+=letra;
    return &str[0];
}

//FUNCION QUE RETORNA UN NUMERO DECIMAL CONVERTIDO A FLOAT PARA ESCRIBIR LOS RESPORTES
float getDecimalCast(float val){
    return roundf(val * 100) / 100;
}

//FUNCION QUE VERIFICA QUE LA SESION DEL LOGIN ESTE INICIADA
bool LoginActivo(){
    //VALIDAR QUE EXISTA UN USUARIO LOGEADO Y TENGA TODOS SUS ATRIBUTOS SETEADOS
    if(login_activo->user != NULL){
        return true;
    }
    if(login_activo->path != NULL){
        return true;
    }
    if(login_activo->nomPart != NULL){
        return true;
    }
    if(login_activo->id != NULL){
        return true;
    }
    return false;
}

