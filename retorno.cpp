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
    int posf = nom.find(".");
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
        default:
        {
            cout<<"ERROR NO IDENTIFICADO... \n";
        }break;
    }
}
