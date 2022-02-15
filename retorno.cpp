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
char * getFecha(){
    char *date;
    //obtener el tiempo del sistema
    time_t t;
    //struct auxiliar para dar formato
    struct tm *local;
    t = time(NULL);
    local = localtime(&t);
    //formato en string
    strftime(date, 16, "%d/%m/%Y %H:%M:%S", local);
    return date;
}

