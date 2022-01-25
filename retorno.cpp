#include "retorno.h"

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