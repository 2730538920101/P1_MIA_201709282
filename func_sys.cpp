#include "func_sys.h"
#include <iostream>
 
using namespace std;

//FUNCION QUE VERIFICA QUE LA PARTICION ESTE ACTIVA
Respuesta getParticionInicial(MasterBootRecord *disco, char name[], int *init){
    int i;
    for(i = 0; i < 4; i++){
        //RECORRER LAS PARTICIONES DEL DISCO Y VERIFICAR EL STATUS
        if(disco->particiones[i].part_status == ACTIVO){
            //VALIDAR EL NOMBRE 
            if(strcmp(disco->particiones[i].part_name, name) == 0){
                //asignar el valor de inicio de la particion 
                *init = disco->particiones[i].part_start;
                return CORRECTO;
            }
        }
    }
    return ERR_PART_NOEX;
}

//FUNCION PARA ESCRIBIR EL SUPER BLOQUE
void CrearArchivoSuperBlock(SuperBlock *sb, char path[], int init){
    //UBICAR EL PUNTERO AL INICIO DEL SUPER BLOQUE DEL DISCO
    FILE *arch;
    arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL ARCHIVO... "<<endl;
        return;
    }
    fseek(arch, init, SEEK_SET);
    //ESCRIBIR EL SUPER BLOQUE
    fwrite(sb, sizeof(SuperBlock),1,arch);
    fclose(arch);
}

//FUNCION QUE LEE EL SUPER BLOQUE
SuperBlock *ReadSuperBlock(char path[], char name[]){
    //OBTENER LOS DATOS DEL MBR
    MasterBootRecord *disco = getDataMBR(path);
    if(disco == NULL){
        cout<<"ERROR AL ABRIR EL ARCHIVO... "<<endl;
        return NULL;
    }
    int init;
    //OBTENER LA PARTICION 
    Respuesta res = getParticionInicial(disco, name, &init);
    if(res != CORRECTO){
        return NULL;
    }
    //LIMPIAR LA MEMORIA
    delete disco;
    FILE *arch = fopen(path, "rb+");
    if(arch == NULL){
        cout<<"ERROR AL ABRIR EL ARCHIVO... "<<endl;
        return NULL;
    }
    //INICIALIZAR EL SUPER BLOQUE
    SuperBlock *sb = (SuperBlock*)malloc(sizeof(SuperBlock));
    //UBICAR EL PUNTERO EN EL INICIO DE LA ESCRITURA DEL SUPER BLOQUE
    fseek(arch, init, SEEK_SET);
    //LEER INFORMACION ESCRITA EN EL SUPER BLOQUE
    fread(sb, sizeof(SuperBlock), 1, arch);
    fclose(arch);
    return sb;
}

