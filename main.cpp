#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "lexico.h"
#include "sintactico.h"
#include "clases_comandos.h"
#include "func_disk.h"
#include "func_part.h"
#include "func_sys.h"
#include "func_reportes.h"

using namespace std;

int main(){
    string comando_entrada;
    cout<<"BIENVENIDO AL SISTEMA DE ARCHIVOS, PROYECTO 1 MIA 1S2022\n";
    cout<<"CARLOS JAVIER MARTINEZ POLANCO 201709282\n\n";
    while(true){
        cout<< "\nIngresa un comando: ";
        getline(cin, comando_entrada);
        if(strcmp(comando_entrada.c_str(), "exit")==0){
            break;
        }else if(strcmp(comando_entrada.c_str(), "cls")==0){
            system("clear");
            continue;
        }else if(strcmp(comando_entrada.c_str(), "showm")==0){
            showMounts();
            continue;
        }else if(strcmp(comando_entrada.c_str(), "clm")==0){
            for(int i = 0; i < 27; i++){
                discos_montados[i] = NULL;
            }
            cout<<"SE HAN DESMONTADO TODOS LOS DISCOS... \n";
            continue;
        }else if(comando_entrada != "" && comando_entrada != "\n" && comando_entrada != " "){
            Escribir_Comando(comando_entrada,false);
            Leer_Comando(false);
            continue;
        }
    }
    return 0;
}