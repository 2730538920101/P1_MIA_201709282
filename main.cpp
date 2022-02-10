#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "lexico.h"
#include "sintactico.h"
#include "clases_comandos.h"
#include "retorno.h"

using namespace std;

int main(){
    std::string comando_entrada;
    std::cout<<"BIENVENIDO AL SISTEMA DE ARCHIVOS, PROYECTO 1 MIA 1S2022\n";
    std::cout<<"CARLOS JAVIER MARTINEZ POLANCO 201709282\n\n";
    while(true){
        std::cout<< "Ingresa un comando: ";
        getline(std::cin, comando_entrada);
        if(strcmp(comando_entrada.c_str(), "exit")==0){
            break;
        }else if(strcmp(comando_entrada.c_str(), "cls")==0){
            system("clear");
            continue;
        }
        if(comando_entrada != ""){
            Escribir_Comando(comando_entrada,false);
            Leer_Comando(false);
        }
    }
    
}