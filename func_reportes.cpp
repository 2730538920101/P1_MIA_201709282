#include "func_reportes.h"
#include <iostream>

using namespace std;

//FUNCION PARA ESCRIBIR EL REPORTE DEL MBR
void ReporteMasterBootRecord(char path[], char path_rep[]){
    //obtener los datos del MBR
    MasterBootRecord *disco = getDataMBR(path);
    if(disco == NULL){
        cout<<"ERROR AL CREAR EL REPORTE... \n";
        return;
    }
    //CREAR UN ARCHIVO .DOT PARA ESCRIBIR EL REPORTE
    FILE *arch = fopen("MasterBootRecord_report.dot", "w+");
    if(arch == NULL){
        cout<<"ERROR AL CREAR EL ARCHIVO DOT... \n";
        return;
    }
    //UBICAR EL PUNTERO AL INICIO DEL ARCHIVO
    fseek(arch, 0, SEEK_SET);
    fputs("digraph {\ntbl[\nshape=plaintext\n label =<\n",arch);
    fputs("<table border='0' cellborder='1' cellspacing='0'>\n",arch);
    fputs("<tr><td colspan=\"3\">DISCO DURO</td></tr>\n",arch);
    fputs("<th><td>NOMBRE</td><td>VALOR</td></th>\n",arch);
     //DATOS DEL MBR
     //TAMAÑO
    fputs("<tr><td bgcolor=\"lightblue\">mbr_tamaño</td><td bgcolor=\"lightblue\">",arch);
    fputs(&to_string(disco->mbr_tamano)[0],arch);
    fputs("</td></tr>\n",arch);
    //FECHA
    fputs("<tr><td bgcolor=\"lightblue\">mbr_Fecha_creación</td><td bgcolor=\"lightblue\">",arch);
    fputs(disco->mbr_fecha_creacion,arch);
    fputs("</td></tr>\n",arch);
    //SIGNATURE
    fputs("<tr><td bgcolor=\"lightblue\">mbr_disk_signature</td><td bgcolor=\"lightblue\">",arch);
    fprintf(arch, "%d", disco->mbr_disk_signature);
    fputs("</td></tr>\n",arch);
    //FIT
    fputs("<tr><td bgcolor=\"lightblue\">mbr_disk_fit</td><td bgcolor=\"lightblue\">",arch);
    fprintf(arch, "%c", disco->disk_fit);
    fputs("</td></tr>\n",arch);
    int i;
    Partition part;
    //SETEAR COLORES PARA LAS TABLAS
    char colors[4][10];
    LimpiarArray(colors[0],10);
    strcat(colors[0],"#bcf7c1");
    LimpiarArray(colors[1],10);
    strcat(colors[1],"#f8fc92");
    LimpiarArray(colors[2],10);
    strcat(colors[2],"#fcc292");
    LimpiarArray(colors[3],10);
    strcat(colors[3],"#dfbcf7");


    for(i=0;i<4;i++){
       part = disco->particiones[i];
       if(part.part_status == INACTIVO) continue;
       //PART NAME
       fputs("<tr><td colspan=\"2\" bgcolor=\"",arch);
       fputs(colors[i],arch);
       fputs("\">",arch);
       fputs(part.part_name,arch);
       fputs("</td></tr>\n",arch);
       //PART STATUS
       fputs("<tr><td bgcolor=\"",arch);
       fputs(colors[i],arch);
       fputs("\">part_status</td><td bgcolor=\"",arch);
       fputs(colors[i],arch);
       fputs("\">",arch);
       fprintf(arch, "%c", char(part.part_status));
       fputs("</td></tr>\n",arch);
       //PART TYPE
       fputs("<tr><td bgcolor=\"",arch);
       fputs(colors[i],arch);
       fputs("\">part_type</td><td bgcolor=\"",arch);
       fputs(colors[i],arch);
       fputs("\">",arch);
       fprintf(arch, "%c", part.part_type);
       fputs("</td></tr>\n",arch);
       //PART FIT
       fputs("<tr><td bgcolor=\"",arch);
       fputs(colors[i],arch);
       fputs("\">part_fit</td><td bgcolor=\"",arch);
       fputs(colors[i],arch);
       fputs("\">",arch);
       fprintf(arch, "%c", part.part_fit);
       fputs("</td></tr>\n",arch);
       //PART START
       fputs("<tr><td bgcolor=\"",arch);
       fputs(colors[i],arch);
       fputs("\">part_start</td><td bgcolor=\"",arch);
       fputs(colors[i],arch);
       fputs("\">",arch);
       fprintf(arch, "%d", part.part_start);
       fputs("</td></tr>\n",arch);
       //PART SIZE
       fputs("<tr><td bgcolor=\"",arch);
       fputs(colors[i],arch);
       fputs("\">part_size</td><td bgcolor=\"",arch);
       fputs(colors[i],arch);
       fputs("\">",arch);
       fputs(&to_string(part.part_size)[0],arch);
       fputs("</td></tr>\n",arch);
    }

    fputs("</table>\n",arch);
    fputs(">];\n\n", arch);

    //REPORTE DE EBR'S

    i = 0;
    ExtendedBootRecord *ebr = getPrimerEBR(disco,path);

    while(ebr!=NULL){//existenExtendidas
        ReporteExtendedBootRecord(ebr,arch,i);
        if(ebr->part_next!=-1){
            ebr = getDataEBR(ebr->part_next,path);
        }else{
           ebr = NULL;
        }
        i++;
    }

    fputs("}\n",arch);
    //cerrando stream
    fclose (arch);
    string command = "dot -Tpng MasterBootRecord_report.dot -o  MasterBootRecord_report.png";
    system(command.c_str());
    cout<<"REPORTE MASTER BOOT RECORD CREADO EXITOSAMENTE...\n";
}

//FUNCION PARA ESCRIBIR EL REPORTE DEL EBR
void ReporteExtendedBootRecord(ExtendedBootRecord *ebr, FILE *arch, int index){
    string nombreNodo = "tbl"+to_string(index+1);
    fputs(nombreNodo.c_str(),arch);
    fputs(" [\nshape=plaintext\n label=<\n", arch);
    fputs("<table border='0' cellborder='1' cellspacing='0'>\n",arch);
    fputs("<tr><td colspan=\"3\">",arch);
    fputs(ebr->part_name,arch);
    fputs("</td></tr>\n",arch);
    fputs("<th><td>NOMBRE</td><td>VALOR</td></th>\n",arch);
    //PART STATUS
    fputs("<tr><td bgcolor=\"#fcc8c8\">part_status</td><td bgcolor=\"#fcc8c8\">",arch);
    fprintf(arch, "%d", ebr->part_status);
    fputs("</td></tr>\n",arch);
    //PART FIT
    fputs("<tr><td bgcolor=\"#fcc8c8\">part_fit</td><td bgcolor=\"#fcc8c8\">",arch);
    fprintf(arch, "%c", ebr->part_fit);
    fputs("</td></tr>\n",arch);
    //PART START
    fputs("<tr><td bgcolor=\"#fcc8c8\">part_start</td><td bgcolor=\"#fcc8c8\">",arch);
    fprintf(arch, "%d", ebr->part_start);
    fputs("</td></tr>\n",arch);
    //PART SIZE
    fputs("<tr><td bgcolor=\"#fcc8c8\">part_size</td><td bgcolor=\"#fcc8c8\">",arch);
    fputs(&to_string(ebr->part_size)[0],arch);
    fputs("</td></tr>\n",arch);
    //PART NEXT
    fputs("<tr><td bgcolor=\"#fcc8c8\">part_next</td><td bgcolor=\"#fcc8c8\">",arch);
    fprintf(arch, "%d", ebr->part_next);
    fputs("</td></tr>\n",arch);
    fputs("</table>\n",arch);
    fputs(">];\n", arch);
}


//FUNCION PARA ESCRIBIR EL REPORTE DEL DISCO
void ReporteDisco(char path[], char path_report[]){
    MasterBootRecord* disco = getDataMBR(path);
    if(disco==NULL){
        cout<<"ERROR AL CREAR REPORTE DISK... \n";
        return;
    }

    FILE *arch;
     arch =  fopen("Disk_report.dot","w+");
     if (arch==NULL)
     {
         cout<<"ERROR AL CREAR EL ARCHIVO... \n";
         return;
     }
    fseek(arch, 0, SEEK_SET);
    fputs("digraph G {\n", arch);
    fputs("parent [\n", arch);
    fputs("shape=plaintext\n", arch);
    fputs("label=<\n", arch);
    fputs("<table border='1' cellborder='1'>\n", arch);
    fputs("<tr>\n", arch);

    //MBR
    fputs("<td rowspan=\"2\" bgcolor =\"#dd8703\" >MBR</td>\n", arch);

    int i;
    int inicio = sizeof(MasterBootRecord);
    int fin = sizeof(MasterBootRecord)-1;

    for(i=0;i<4;i++){
        if(disco->particiones[i].part_status == ACTIVO){
        switch(disco->particiones[i].part_type){
        case P:
            fin = disco->particiones[i].part_start;
            if(fin-inicio > 0){
                //ESPACIO LIBRE
                fputs("<td rowspan=\"2\" bgcolor = \"#3ac9da\">LIBRE<br/>", arch);
                fprintf(arch, "%.2f",(getDecimalCast((float)((fin-inicio)*100)/disco->mbr_tamano)));
                fputs("%</td>\n", arch);
            }
            inicio = disco->particiones[i].part_start+disco->particiones[i].part_size;
            //PARTICION PRIMARIA
            fputs("<td rowspan=\"2\" bgcolor =\"#50b104\" >PRIMARIA <br/>",arch);
            fprintf(arch, "%.2f",getDecimalCast((float)(disco->particiones[i].part_size*100)/disco->mbr_tamano));
            fputs("%</td>\n", arch);
            break;
        case E:
            fin = disco->particiones[i].part_start;
            if(fin-inicio > 0){
                //ESPACIO LIBRE
                fputs("<td rowspan=\"2\" bgcolor = \"#3ac9da\">LIBRE<br/>\n", arch);
                fprintf(arch, "%.2f",getDecimalCast((float)((fin-inicio)*100)/disco->mbr_tamano));
                fputs("%</td>\n", arch);
            }
            inicio = disco->particiones[i].part_start+disco->particiones[i].part_size;
            //PARTICION EXTENDIDA
            fputs("<td>\n", arch);
            ReporteExtendidas(arch,disco,path);
            fputs("</td>\n", arch);
            break;
        }
       }
    }
    if(disco->mbr_tamano-inicio > 0){
        //ESPACIO LIBRE
        fputs("<td rowspan=\"2\" bgcolor = \"#3ac9da\">LIBRE<br/>\n", arch);
        fprintf(arch, "%.2f", getDecimalCast((float)((disco->mbr_tamano-inicio)*100)/disco->mbr_tamano));

        fputs("%</td>\n", arch);
    }

    fputs("</tr>\n", arch);
    fputs("</table>\n", arch);
    fputs(">];\n", arch);
    fputs("}\n",arch);
    //cerrando stream
    fclose (arch);
    string command = "dot -Tpng Disk_report.dot -o Disk_report.png";
    system(command.c_str());
    cout<<"REPORTE DISK CREADO EXITOSAMENTE...\n";
}

//FUNCION PARA ESCRIBIR EL REPORTE DE LAS PARTICIONES EXTENDIDAS DEL DISCO
void ReporteExtendidas(FILE *arch, MasterBootRecord *disco, char path[]){
    ExtendedBootRecord *first = getPrimerEBR(disco,path);
    if(first == NULL){
        return;
    }
    int i;
    Partition *extended = NULL;
    for(i=0;i<4;i++){
        if(disco->particiones[i].part_status == ACTIVO && disco->particiones[i].part_type == E){
            extended = &disco->particiones[i];
            break;
        }
    }
        if(extended==NULL){
            return;
        }
    fputs("<table border = \"1\" cellborder=\"1\" bgcolor=\"#da3a85\">\n", arch);
    
    fputs("<tr>\n", arch);
    bool flag = true;
    int inicio = extended->part_start;
    int fin = 0;
    while(flag){
        fin = first->part_start-sizeof(ExtendedBootRecord);
        if(fin-inicio > 0){
            //ESPACIO LIBRE
            fputs("<td rowspan=\"2\" bgcolor = \"#3ac9da\">\n", arch);
            fprintf(arch, "%.2f",getDecimalCast((float)((fin-inicio)*100)/disco->mbr_tamano));
            fputs("%</td>\n", arch);
        }
        inicio = first->part_start+first->part_size;
        if(first->part_status == ACTIVO){
            fputs("<td bgcolor=\"#eeeeee\">EBR</td>\n", arch);
        }
        fputs("<td bgcolor=\"#eeeeee\">", arch);
        if(first->part_status == INACTIVO){
            fputs("LIBRE <br/>",arch);
        }else{
            fputs("LOGICA <br/>",arch);
        }
        fprintf(arch, "%.2f",getDecimalCast((float)(first->part_size*100)/disco->mbr_tamano));
        fputs("%</td>\n",arch);
        if(first->part_next!=-1){
           first = getDataEBR(first->part_next,path);
       }else{
           flag = false;
       }
    }
    if(disco->mbr_tamano-inicio > 0){
        //ESPACIO LIBRE
        fputs("<td rowspan=\"2\" bgcolor = \"#3ac9da\">LIBRE<br/>\n", arch);
        fprintf(arch, "%.2f",getDecimalCast((float)(((extended->part_start+extended->part_size)-inicio)*100)/disco->mbr_tamano));
        fputs("%</td>\n", arch);
    }
    fputs("</tr>\n", arch);
    fputs("</table>\n", arch);
}

