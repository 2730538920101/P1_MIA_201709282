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
    string pathString(path_rep);
    string command = "dot -Tpng MasterBootRecord_report.dot -o \""+ pathString+"\"";
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
    string pathString(path_report);
    string command = "dot -Tpng Disk_report.dot -o \""+pathString+"\"";
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

//FUNCION PARA ESCRIBIR EL REPORTE DE INODOS
Respuesta ReporteInodos(char path[], char name[], char path_report[]){
    SuperBlock *superb = ReadSuperBlock(path,name);
    if(superb == NULL){
        return ERR_IRRECONOCIBLE;
    }
    FILE * arch;
     arch = fopen (path,"rb+");
    if (arch==NULL)
    {
        cout<<"ERROR AL ABRIR EL DISCO... \n";
        return ERR_IRRECONOCIBLE;
    }

    FILE * fileReport;
    fileReport = fopen ("Inodes_report.dot","w+");
    if (fileReport==NULL)
    {
        cout<<"ERROR AL CREAR EL ARCHVIVO DOT... \n";
        return ERR_IRRECONOCIBLE;
    }
    fseek(fileReport, 0, SEEK_SET);
    fputs("digraph {\n", fileReport);
    //reporte de inodos
    char caracter;
    int contador = 0;
    TablaInodos *inodo;
    fseek(arch, superb->s_bm_inode_start, SEEK_SET);
    while(contador<superb->s_inodes_count){
        fread(&caracter, sizeof(char), 1, arch);
        if(caracter == '1'){
            inodo = ReadInodo(path,getInodoInicial(superb,contador));
            if(inodo == NULL){
                break;
            }
            fputs("i_",fileReport);
            fputs(&to_string(contador)[0],fileReport);
            fputs("[ shape=plaintext label=< \n", fileReport);
            fputs("<table border=\"1\" cellborder = \"0\" cellspacing='0'>\n", fileReport);
            fputs("<tr><td colspan=\"3\">Inodo ",fileReport);
            fputs(&to_string(contador)[0],fileReport);
            fputs("</td></tr>\n", fileReport);
            fputs("<tr><td bgcolor=\"#DAF7A6\">i_uid</td><td bgcolor=\"#DAF7A6\">",fileReport);
            fputs(&to_string(inodo->i_uid)[0],fileReport);
            fputs("</td></tr>\n", fileReport);
            fputs("<tr><td bgcolor=\"#DAF7A6\">i_gid</td><td bgcolor=\"#DAF7A6\">",fileReport);
            fputs(&to_string(inodo->i_gid)[0],fileReport);
            fputs("</td></tr>\n", fileReport);
            fputs("<tr><td bgcolor=\"#DAF7A6\">i_size</td><td bgcolor=\"#DAF7A6\">",fileReport);
            fputs(&to_string(inodo->i_size)[0],fileReport);
            fputs("</td></tr>\n", fileReport);
            fputs("<tr><td bgcolor=\"#DAF7A6\">i_atime</td><td bgcolor=\"#DAF7A6\">",fileReport);
            fputs(inodo->i_atime,fileReport);
            fputs("</td></tr>\n", fileReport);
            fputs("<tr><td bgcolor=\"#DAF7A6\">i_ctime</td><td bgcolor=\"#DAF7A6\">",fileReport);
            fputs(inodo->i_ctime,fileReport);
            fputs("</td></tr>\n", fileReport);
            fputs("<tr><td bgcolor=\"#DAF7A6\">i_mtime</td><td bgcolor=\"#DAF7A6\">",fileReport);
            fputs(inodo->i_mtime,fileReport);
            fputs("</td></tr>\n", fileReport);
            fputs("<tr><td bgcolor=\"#DAF7A6\">i_type</td><td bgcolor=\"#DAF7A6\">",fileReport);
            fputs(&to_string(inodo->i_type)[0],fileReport);
            fputs("</td></tr>\n", fileReport);
            fputs("<tr><td bgcolor=\"#DAF7A6\">i_perm</td><td bgcolor=\"#DAF7A6\">",fileReport);
            fputs(&to_string(inodo->i_perm)[0],fileReport);
            fputs("</td></tr>\n", fileReport);
            int i=0;
            //APUNTADORES DIRECTOS
            while(i<12){
                fputs("<tr><td bgcolor=\"#FFC300\">AD", fileReport);
                fputs(&to_string(i+1)[0],fileReport);
                fputs("</td><td ",fileReport);
                fputs(" bgcolor=\"#FFC300\">",fileReport);
                fputs(&to_string(inodo->i_block[i])[0],fileReport);
                fputs("</td></tr>\n", fileReport);
                i++;
            }
            while (i<TAM_BLOQUES_INODOS) {
                fputs("<tr><td bgcolor=\"#FF5733\">AI", fileReport);
                fputs(&to_string(i-11)[0],fileReport);
                fputs("</td><td bgcolor=\"#FF5733\">",fileReport);
                fputs(&to_string(inodo->i_block[i])[0],fileReport);
                fputs("</td></tr>\n", fileReport);
                i++;
            }

            fputs("</table>\n",fileReport);
            fputs(">];\n",fileReport);
        }
        contador++;
    }
    fputs("}\n",fileReport);
    fclose (fileReport);
    fclose (arch);
    string pathString(path_report);
    string command = "dot -Tpng Inodes_report.dot -o \""+pathString+"\"";//+"/report_mbr.png";
    system(command.c_str());
    return CORRECTO;
}

//FUNCION PARA GRAFICAR LOS BLOQUES DE APUNTADORES
void graphBlockPointer(int level,int indexPadre,int indexBlock,FILE *fileReport,char path[],SuperBlock *superb, bool graphConnection,Tipoinodo type){
    BloquesApuntadores *block = ReadBloquesApuntadores(path,getBloqueInicial(superb,indexBlock));
    if(block==NULL) return;
    fputs("b_",fileReport);
    fputs(&to_string(indexBlock)[0],fileReport);
    fputs("[ shape=plaintext label=< \n", fileReport);
    fputs("<table border='0' cellborder='1' cellspacing='0'>\n", fileReport);
    fputs("<tr><td ",fileReport);

    fputs("port=\"",fileReport);
    fputs(&to_string((indexPadre+indexBlock)*sizeof(TablaInodos))[0],fileReport);
    fputs("\"",fileReport);
    fputs(">Bloque ",fileReport);
    fputs(&to_string(indexBlock)[0],fileReport);
    fputs("</td></tr>\n", fileReport);
    int i;
    for(i=0;i<TAM_BLOQUES_INODOS;i++){
        fputs("<tr><td bgcolor = \"#FFA07A\" ",fileReport);
        if(block->b_pointers[i]!=-1){
            if(level == 1 && type == IN_DIRECTORY){
                fputs("port=\"ib",fileReport);
                fputs(&to_string(block->b_pointers[i]*sizeof(TablaInodos))[0],fileReport);
                fputs("\"",fileReport);
            }else{
            fputs("port=\"",fileReport);
            int port = (indexBlock+block->b_pointers[i])*sizeof(TablaInodos);
            fputs(&to_string(port)[0],fileReport);
            fputs("\"",fileReport);
            }
        }
        fputs(">",fileReport);
        fputs(&to_string(block->b_pointers[i])[0],fileReport);
        fputs("</td></tr>\n",fileReport);
    }
    fputs("</table>\n",fileReport);
    fputs(">];\n",fileReport);
    for(i=0;i<TAM_BLOQUES_INODOS;i++){
        if(block->b_pointers[i]!=-1){
            if(level==1){
                if(type==IN_DIRECTORY){
                    TablaInodos *ind = ReadInodo(path,getInodoInicial(superb,block->b_pointers[i]));
                    graphInodo(ind,block->b_pointers[i],fileReport,path,superb);
                    if(graphConnection)
                        graphConnectionBloqueInodo(block->b_pointers[i],indexBlock,block->b_pointers[i]*sizeof(TablaInodos),fileReport);
                    }else{
                        BloquesArchivos *file = ReadBloquesArchivos(path,getBloqueInicial(superb,block->b_pointers[i]));
                        graphBlockFile(file,block->b_pointers[i],fileReport,indexBlock);
                        int port = (indexBlock+block->b_pointers[i])*sizeof(TablaInodos);
                        if(graphConnection)
                        graphConnectionBloqueBLoque(indexBlock,block->b_pointers[i],port,fileReport);
                    }
                }else{
                    graphBlockPointer(level-1,indexBlock,block->b_pointers[i],fileReport,path,superb,graphConnection,type);
                    int port = (indexBlock+block->b_pointers[i])*sizeof(TablaInodos);
                    if(graphConnection)
                        graphConnectionBloqueBLoque(indexBlock,block->b_pointers[i],port,fileReport);
                    }
                }
    }

}


//FUNCION PARA GRAFICAR EL INODO
void graphInodo(TablaInodos *inodo, int indexInodo, FILE *arch, char path[], SuperBlock *superb){
    if(inodo==NULL) return;
    fputs("i_",arch);
    fputs(&to_string(indexInodo)[0],arch);
    fputs("[ shape=plaintext label=< \n", arch);
    fputs("<table border='0' cellborder='1' cellspacing='0'>\n", arch);
    fputs("<tr><td ",arch);
    fputs("port=\"ib",arch);
    fputs(&to_string(indexInodo*sizeof(TablaInodos))[0],arch);
    fputs("\"",arch);
    fputs(" colspan=\"3\">Inodo ",arch);
    fputs(&to_string(indexInodo)[0],arch);
    fputs("</td></tr>\n", arch);
    fputs("<tr><td bgcolor=\"#fbffa8\">i_uid</td><td bgcolor=\"#fbffa8\">",arch);
    fputs(&to_string(inodo->i_uid)[0],arch);
    fputs("</td></tr>\n", arch);
    fputs("<tr><td bgcolor=\"#fbffa8\">i_gid</td><td bgcolor=\"#fbffa8\">",arch);
    fputs(&to_string(inodo->i_gid)[0],arch);
    fputs("</td></tr>\n", arch);
    fputs("<tr><td bgcolor=\"#fbffa8\">i_size</td><td bgcolor=\"#fbffa8\">",arch);
    fputs(&to_string(inodo->i_size)[0],arch);
    fputs("</td></tr>\n", arch);
    fputs("<tr><td bgcolor=\"#fbffa8\">i_atime</td><td bgcolor=\"#fbffa8\">",arch);
    fputs(inodo->i_atime,arch);
    fputs("</td></tr>\n", arch);
    fputs("<tr><td bgcolor=\"#fbffa8\">i_ctime</td><td bgcolor=\"#fbffa8\">",arch);
    fputs(inodo->i_ctime,arch);
    fputs("</td></tr>\n", arch);
    fputs("<tr><td bgcolor=\"#fbffa8\">i_mtime</td><td bgcolor=\"#fbffa8\">",arch);
    fputs(inodo->i_mtime,arch);
    fputs("</td></tr>\n", arch);
    fputs("<tr><td bgcolor=\"#fbffa8\">i_type</td><td bgcolor=\"#fbffa8\">",arch);
    fputs(&to_string(inodo->i_type)[0],arch);
    fputs("</td></tr>\n", arch);
    fputs("<tr><td bgcolor=\"#fbffa8\">i_perm</td><td bgcolor=\"#fbffa8\">",arch);
    fputs(&to_string(inodo->i_perm)[0],arch);
    fputs("</td></tr>\n", arch);
    int i=0;
    //APUNTADORES DIRECTOS
    while(i<12){
        fputs("<tr><td bgcolor=\"#ffd1a8\">AD", arch);
        fputs(&to_string(i+1)[0],arch);
        fputs("</td><td ",arch);
        if(inodo->i_block[i]!=-1){
            fputs("port=\"",arch);
            fputs(&to_string((indexInodo+inodo->i_block[i])*sizeof(TablaInodos))[0],arch);
            fputs("\"",arch);
        }
        fputs(" bgcolor=\"#ffd1a8\">",arch);
        fputs(&to_string(inodo->i_block[i])[0],arch);
        fputs("</td></tr>\n", arch);
        i++;
    }
    while (i<TAM_BLOQUES_INODOS) {
        fputs("<tr><td bgcolor=\"#a8ffdf\">AI", arch);
        fputs(&to_string(i-11)[0],arch);
        fputs("</td><td ",arch);
        if(inodo->i_block[i]!=-1){
            fputs("port=\"",arch);
            fputs(&to_string((indexInodo+inodo->i_block[i])*sizeof(TablaInodos))[0],arch);
            fputs("\"",arch);
        }
        fputs(" bgcolor=\"#a8ffdf\">",arch);
        fputs(&to_string(inodo->i_block[i])[0],arch);
        fputs("</td></tr>\n", arch);
        i++;
    }

    fputs("</table>\n",arch);
    fputs(">];\n",arch);

    //GRAFICAR BLOQUES
    i=0;
    while(i<12){
        if(inodo->i_block[i]!=-1){
            int pos = getBloqueInicial(superb,inodo->i_block[i]);
            if(inodo->i_type == IN_DIRECTORY){
                BloquesCarpetas *dir = ReadBloquesCarpetas(path,pos);
                if(dir!=NULL){
                    graphBlockDirectory(dir,inodo->i_block[i],arch,indexInodo,superb,path,true);
                }
            }else if(inodo->i_type == IN_FILE){
                BloquesArchivos *dir = ReadBloquesArchivos(path,pos);
                if(dir!=NULL){
                    graphBlockFile(dir,inodo->i_block[i],arch,indexInodo);
                }
            }
            graphConnectionInodoBloque(indexInodo,inodo->i_block[i],(indexInodo+inodo->i_block[i])*sizeof(TablaInodos),arch);
        }
        i++;
    }
    while(i<TAM_BLOQUES_INODOS){
        if(inodo->i_block[i]!=-1){
            graphBlockPointer(i-11,indexInodo,inodo->i_block[i],arch,path,superb,true,inodo->i_type);
            graphConnectionInodoBloque(indexInodo,inodo->i_block[i],(indexInodo+inodo->i_block[i])*sizeof(TablaInodos),arch);
        }
        i++;
    }
}

//FUNCION PARA GRAFICAR LA CONEXION DEL BLOQUE CON EL INODO
void graphConnectionInodoBloque(int indexnodo,int indexBloque,int indexPuerto,FILE *arch){
    fputs("i_",arch);
    fputs(&to_string(indexnodo)[0],arch);
    fputs(":",arch);
    fputs(&to_string(indexPuerto)[0],arch);
    fputs("->",arch);
    fputs("b_",arch);
    fputs(&to_string(indexBloque)[0],arch);
    fputs(":",arch);
    fputs(&to_string(indexPuerto)[0],arch);
    fputs(";\n",arch);
}

//FUNCION PARA GRAFICAR LA CONEXION DEL BLOQUE AL INODO
void graphConnectionBloqueInodo(int indexnodo,int indexBloque,int indexPuerto,FILE *arch){
    fputs("b_",arch);
    fputs(&to_string(indexBloque)[0],arch);
    fputs(":",arch);
    fputs("ib",arch);
    fputs(&to_string(indexPuerto)[0],arch);
    fputs("->",arch);
    fputs("i_",arch);
    fputs(&to_string(indexnodo)[0],arch);
    fputs(":",arch);
    fputs("ib",arch);
    fputs(&to_string(indexPuerto)[0],arch);
    fputs(";\n",arch);
}

//FUNCION PARA GRAFICAR LA CONEXION DE UN BLOQUE CON BLOQUE
void graphConnectionBloqueBLoque(int indexB1,int indexB2,int indexPuerto,FILE *arch){
    fputs("b_",arch);
    fputs(&to_string(indexB1)[0],arch);
    fputs(":",arch);
    fputs(&to_string(indexPuerto)[0],arch);
    fputs("->",arch);
    fputs("b_",arch);
    fputs(&to_string(indexB2)[0],arch);
    fputs(":",arch);
    fputs(&to_string(indexPuerto)[0],arch);
    fputs(";\n",arch);
}

//FUNCION PARA GRAFICAR UN BLOQUE DE CARPETA
void graphBlockDirectory(BloquesCarpetas *block,int initBlock, FILE *arch,int indexInodo,SuperBlock *superb,char path[],bool graphConnection){
    fputs("b_",arch);
    fputs(&to_string(initBlock)[0],arch);
    fputs("[ shape=plaintext label=< \n", arch);
    fputs("<table border='0' cellborder='1' cellspacing='0'>\n", arch);
    fputs("<tr><td ",arch);
    fputs("port=\"",arch);
    fputs(&to_string((indexInodo+initBlock)*sizeof(TablaInodos))[0],arch);
    fputs("\"",arch);
    fputs(" colspan=\"3\">Bloque ",arch);
    fputs(&to_string(initBlock)[0],arch);
    fputs("</td></tr>\n", arch);

    char colors[4][10];
    LimpiarArray(colors[0],10);
    strcat(colors[0],"#e5b7ff");
    LimpiarArray(colors[1],10);
    strcat(colors[1],"#c0ffb7");
    LimpiarArray(colors[2],10);
    strcat(colors[2],"#ffb7c0");
    LimpiarArray(colors[3],10);
    strcat(colors[3],"#ffd2b7");
    int i;
    for(i=0;i<4;i++){
        fputs("<tr><td bgcolor=\"",arch);
        fputs(colors[i],arch);
        fputs("\">b_name</td><td bgcolor=\"",arch);
        fputs(colors[i],arch);
        fputs("\" ",arch);
        if(block->b_content[i].b_inodo!=-1 && block->b_content[i].b_inodo!=indexInodo){
            fputs("port=\"ib",arch);
            fputs(&to_string(block->b_content[i].b_inodo*sizeof(TablaInodos))[0],arch);
            fputs("\"",arch);
        }
        fputs(">",arch);
        fputs(block->b_content[i].b_name,arch);
        fputs("</td></tr>\n",arch);
        fputs("<tr><td bgcolor=\"",arch);
        fputs(colors[i],arch);
        fputs("\">b_inodo</td><td bgcolor=\"",arch);
        fputs(colors[i],arch);
        fputs("\">",arch);
        fputs(&to_string(block->b_content[i].b_inodo)[0],arch);
        fputs("</td></tr>\n",arch);
    }
    fputs("</table>\n",arch);
    fputs(">];\n",arch);
    if(graphConnection){
        for(i=2;i<4;i++){
            if(block->b_content[i].b_inodo!=-1){
                TablaInodos *inodo = ReadInodo(path,getInodoInicial(superb,block->b_content[i].b_inodo));
                graphInodo(inodo,block->b_content[i].b_inodo,arch,path,superb);
                graphConnectionBloqueInodo(block->b_content[i].b_inodo,initBlock,block->b_content[i].b_inodo*sizeof(TablaInodos),arch);
            }
        }
    }
}

//FUNCION PARA GRAFICAR LOS BLOQUES DE ARCHIVOS
void graphBlockFile(BloquesArchivos *block,int initBlock, FILE *arch,int indexInodo){
    fputs("b_",arch);
    fputs(&to_string(initBlock)[0],arch);
    fputs("[ shape=plaintext label=< \n", arch);
    fputs("<table border='0' cellborder='1' cellspacing='0'>\n", arch);
    fputs("<tr><td ",arch);
    fputs("port=\"",arch);
    fputs(&to_string((indexInodo+initBlock)*sizeof(TablaInodos))[0],arch);
    fputs("\">Bloque ",arch);
    fputs(&to_string(initBlock)[0],arch);
    fputs("</td></tr>\n", arch);
    fputs("<tr><td>",arch);
    int i;
    for(i=0;i<64;i++){
        if(block->b_content[i]!='\0' && block->b_content[i]>0){
           fprintf(arch,"%c", block->b_content[i]);
           if(i!=0){
               if(i%31 == 0){
                  fputs("<br/>",arch);
               }
           }
        }
    }
    fputs("</td></tr>\n",arch);
    fputs("</table>\n",arch);
    fputs(">];\n",arch);
}


//FUNCION PARA EL REPORTE BLOCKS
Respuesta ReporteBlocks(char path[], char name[], char path_report[]){
    SuperBlock *superb = ReadSuperBlock(path,name);
    if(superb == NULL){
        return ERR_IRRECONOCIBLE;
    }
    FILE * arch;
    arch = fopen (path,"rb+");
    if (arch==NULL){
        cout<<"ERROR AL ABRIR EL DISCO\n";
        return ERR_IRRECONOCIBLE;
    }

    FILE * fileReport;
    fileReport = fopen ("Blocks_report.dot","w");
    if (fileReport==NULL){
        cout<<"ERROR AL CREAR EL ARCHIVO DOT... \n";
        return ERR_IRRECONOCIBLE;
    }
    fseek(fileReport, 0, SEEK_SET);
    fputs("digraph di{\n", fileReport);
    //reporte de inodos
    char caracter;
    int contador = 0;
    TablaInodos *inodo;
    fseek(arch, superb->s_bm_inode_start, SEEK_SET);
    while(contador<superb->s_inodes_count){
        fread(&caracter, sizeof(char), 1, arch);
        if(caracter == '1'){
            inodo = ReadInodo(path,getInodoInicial(superb,contador));
            if(inodo == NULL){
                break;
            }
            int i;
            //apuntadores directos
            for(i=0;i<12;i++){
                if(inodo->i_block[i]!=-1){
                    if(inodo->i_type == IN_DIRECTORY){
                        BloquesCarpetas *block = ReadBloquesCarpetas(path,getBloqueInicial(superb,inodo->i_block[i]));
                        graphBlockDirectory(block,inodo->i_block[i],fileReport,contador,superb,path,false);
                    }else if(inodo->i_type == IN_FILE){
                        BloquesArchivos *block = ReadBloquesArchivos(path,getBloqueInicial(superb,inodo->i_block[i]));
                        graphBlockFile(block,inodo->i_block[i],fileReport,contador);
                    }
                }
            }
            //apuntadores indirectos
            for(i=12;i<15;i++){
                if(inodo->i_block[i]!=-1){
                    graphBlockPointer(i-11,contador,inodo->i_block[i],fileReport,path,superb,false,inodo->i_type);
                }
            }
        }
        contador++;
    }
    fputs("}\n",fileReport);
    fclose (fileReport);
    fclose (arch);
    string pathString(path_report);
    string command = "dot -Tpng Blocks_report.dot -o \""+pathString+"\"";
    return CORRECTO;
}

//FUNCION PARA EL REPORTE JOURNAL
Respuesta ReporteJournal(char path[], char namePart[],char reportPath[]){
    int startsuperb;
    SuperBlock *superb = ReadSuperBlock(path,namePart,&startsuperb);
    if(superb==NULL){
        return ERR_IRRECONOCIBLE;
    }
    FILE * fileReport;
    fileReport = fopen ("Journal_report.dot","w+");
    if (fileReport==NULL){
        cout<<"ERROR AL CREAR EL ARCHIVO DOT...\n";
         return ERR_IRRECONOCIBLE;
    }
    fseek(fileReport, 0, SEEK_SET);
    fputs("digraph di{\n", fileReport);
    fputs("i_3[ shape=plaintext label=<\n",fileReport);
    fputs("<table>\n",fileReport);
    fputs("<tr><td colspan=\"9\" bgcolor=\"#DAF7A6\">Journal</td></tr>\n",fileReport);
    fputs("<tr>\n",fileReport);
    fputs("<td bgcolor=\"#DAF7A6\">Operacion</td>\n",fileReport);
    fputs("<td bgcolor=\"#DAF7A6\">Fecha</td>\n",fileReport);
    fputs("<td bgcolor=\"#DAF7A6\">Ruta</td>\n",fileReport);
    fputs("<td bgcolor=\"#DAF7A6\">Contenido</td>\n",fileReport);
    fputs("<td bgcolor=\"#DAF7A6\">Tamaño</td>\n",fileReport);
    fputs("<td bgcolor=\"#DAF7A6\">Grupo</td>\n",fileReport);
    fputs("<td bgcolor=\"#DAF7A6\">Usuario</td>\n",fileReport);
    fputs("<td bgcolor=\"#DAF7A6\">Permisos</td>\n",fileReport);
    fputs("<td bgcolor=\"#DAF7A6\">Recursivo</td>\n",fileReport);
    fputs("</tr>\n",fileReport);
    int startOperations = startsuperb+sizeof(SuperBlock);
    FILE * arch;
    int contador = 0;
    arch = fopen (path,"rb+");
    if (arch==NULL){
        cout<<"ERROR AL ABRIR EL DISCO...\n";
        return CORRECTO;
    }
    Journal *journal = (Journal*)malloc(sizeof(Journal));
    fseek(arch, startOperations, SEEK_SET);
    while(contador<superb->s_inodes_count){
        fread(journal,sizeof(Journal),1,arch);
        if(journal == NULL){
            return ERR_IRRECONOCIBLE;
        }
        switch (journal->j_operation) {
            case MAKEDIR:
                {
                    fputs("<tr>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">Mkdir</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_date,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_path,fileReport);
                    fputs("</td>\n",fileReport);
                    //contenido
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    //tamaño
                    fputs("<td bgcolor=\"#DAF7A6\">-</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_group,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_user,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(&to_string(journal->j_perms)[0],fileReport);
                    fputs("</td>\n",fileReport);
                    if(journal->j_boolean){
                        fputs("<td bgcolor=\"#DAF7A6\">SI</td>\n",fileReport);

                    }else{
                        fputs("<td bgcolor=\"#DAF7A6\">NO</td>\n",fileReport);
                    }

                    fputs("</tr>\n",fileReport);
                }
                    break;
                case MAKEFILE_PATH:
                {
                    fputs("<tr>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">Mkfile</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_date,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_path,fileReport);
                    fputs("</td>\n",fileReport);
                    //contenido
                    fputs("<td bgcolor=\"#DAF7A6\"> ",fileReport);
                    fputs(journal->j_content,fileReport);
                    fputs(" </td>\n",fileReport);
                    //tamaño
                    fputs("<td bgcolor=\"#DAF7A6\">-</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_group,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_user,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(&to_string(journal->j_perms)[0],fileReport);
                    fputs("</td>\n",fileReport);
                    if(journal->j_boolean){
                        fputs("<td bgcolor=\"#DAF7A6\">SI</td>\n",fileReport);

                    }else{
                        fputs("<td bgcolor=\"#DAF7A6\">NO</td>\n",fileReport);
                    }
                    fputs("</tr>\n",fileReport);
                }
                    break;
                case MAKEFILE_SIZE:
                {
                    fputs("<tr>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">Mkfile</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_date,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_path,fileReport);
                    fputs("</td>\n",fileReport);
                    //contenido
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    //tamaño
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(&to_string(journal->j_size)[0],fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_group,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_user,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(&to_string(journal->j_perms)[0],fileReport);
                    fputs("</td>\n",fileReport);
                    if(journal->j_boolean){
                        fputs("<td bgcolor=\"#DAF7A6\">SI</td>\n",fileReport);

                    }else{
                        fputs("<td bgcolor=\"#DAF7A6\">NO</td>\n",fileReport);
                    }

                    fputs("</tr>\n",fileReport);
                }
                    break;
                case ADDGRUPO:
                {
                    fputs("<tr>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">mkgrp</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_date,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    //contenido
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    //tamaño
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_group,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("</tr>\n",fileReport);
                }
                    break;
                case DELGRUPO:
                {
                    fputs("<tr>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">rmgrp</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_date,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    //contenido
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    //tamaño
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_group,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("</tr>\n",fileReport);
                }
                    break;
                case DELUSUARIO:
                {
                    fputs("<tr>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">rmusr</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_date,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    //contenido
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    //tamaño
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_user,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("</tr>\n",fileReport);
                }
                    break;
                case ADDUSUARIO:
                {
                    fputs("<tr>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">mkusr</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_date,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    //contenido
                    fputs("<td bgcolor=\"#DAF7A6\"> ",fileReport);
                    fputs(journal->j_content,fileReport);
                    fputs(" </td>\n",fileReport);
                    //tamaño
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> ",fileReport);
                    fputs(journal->j_group,fileReport);
                    fputs(" </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> ",fileReport);
                    fputs(journal->j_user,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("</tr>\n",fileReport);
                }
                    break;
                case EDITFILE:
                {
                    fputs("<tr>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">mkusr</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\">",fileReport);
                    fputs(journal->j_date,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> ",fileReport);
                    fputs(journal->j_path,fileReport);
                    fputs(" </td>\n",fileReport);
                    //contenido
                    fputs("<td bgcolor=\"#DAF7A6\"> ",fileReport);
                    fputs(journal->j_content,fileReport);
                    fputs(" </td>\n",fileReport);
                    //tamaño
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> ",fileReport);
                    fputs(journal->j_group,fileReport);
                    fputs(" </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> ",fileReport);
                    fputs(journal->j_user,fileReport);
                    fputs("</td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("<td bgcolor=\"#DAF7A6\"> - </td>\n",fileReport);
                    fputs("</tr>\n",fileReport);
                }
                    break;
                default:
                    contador = superb->s_inodes_count+1;
                    break;
            }
        contador++;
    }

    fclose (arch);
    fputs("</table>\n",fileReport);
    fputs(">];\n",fileReport);
    fputs("}\n",fileReport);
    fclose (fileReport);
    string pathString(reportPath);
    string command = "dot -Tpng Journal_report.dot -o \""+pathString+"\"";
    system(command.c_str());
    return CORRECTO;
}

//FUNCION PARA LOS REPORTES BM_BLOCK y BM_INODE
Respuesta ReporteBitmap(int rep, char path[], char name[],char path_rep[]){
    SuperBlock *superb = ReadSuperBlock(path,name);
    if(superb == NULL){
        return ERR_IRRECONOCIBLE;
    }
    FILE * arch;
    arch = fopen (path,"rb+");
    if (arch==NULL){
        cout<<"ERROR AL ABRIR EL DISCO...\n";
        return ERR_IRRECONOCIBLE;
    }

    FILE * fileReport;
    fileReport = fopen (path_rep,"w+");
    if (fileReport==NULL){
        cout<<"ERROR AL CREAR EL ARCHIVO DOT...\n";
        return ERR_IRRECONOCIBLE;
    }
    fseek(fileReport, 0, SEEK_SET);
    if(rep == 0){
        //reporte de inodos
        char caracter;
        int contador = 0;
        fseek(arch, superb->s_bm_inode_start, SEEK_SET);
        while(contador<superb->s_inodes_count){
            fread(&caracter, sizeof(char), 1, arch);
            fwrite(&caracter, sizeof(char), 1, fileReport);
            if((contador+1)%20==0 && contador!=0){
                fwrite("\n", sizeof(char), 1, fileReport);
            }
            contador++;
        }
    }else{
        //reporte de bloques
        char caracter;
        int contador = 0;
        fseek(arch, superb->s_bm_block_start, SEEK_SET);
        while(contador<superb->s_blocks_count){
            fread(&caracter, sizeof(char), 1, arch);
            fwrite(&caracter, sizeof(char), 1, fileReport);
            if((contador+1)%20==0 && contador!=0){
                fwrite("\n", sizeof(char), 1, fileReport);
            }
            contador++;
        }
    }
    fclose (fileReport);
    fclose (arch);
    delete superb;
    return CORRECTO;
}

//FUNCION PARA EL REPORTE TREE
void ReporteTree(char path_report[], char id[]){
    Discos_Montados *disk = getDiscoMontado(id);
    if(disk == NULL){
        return;
    }
    Particiones_Montadas *partition = getParticionMontada(id);
    if(partition==NULL){
        return;
    }
    SuperBlock *superb = ReadSuperBlock(disk->path,partition->name);
    if(superb==NULL){
        return;
    }
    FILE * arch;
    arch = fopen ("Tree_report.dot","w+");
    if (arch==NULL){
        cout<<"ERROR AL CREAR EL ARCHIVO DOT...\n";
        return;
    }
    fseek(arch, 0, SEEK_SET);
    fputs("digraph G {\n", arch);
    fputs("rankdir =LR;\n", arch);
    //graphAllInodes(superb,arch,disk->path);
    TablaInodos *inodo = ReadInodo(disk->path,getInodoInicial(superb,0));
    if(inodo!=NULL){
        graphInodo(inodo,0,arch,disk->path,superb);
    }
    fputs("}\n",arch);
    //cerrando stream
    fclose (arch);
    string pathString(path_report);
    string command = "dot -Tpng Tree_report.dot -o \""+pathString+"\"";
    system(command.c_str());
}


//FUNCION PARA EL REPORTE superb
void ReporteSb(char path[], char name[], char path_report[]){
    SuperBlock *superb = ReadSuperBlock(path,name);
    if(superb==NULL){
        return;
    }
    FILE * arch;
    arch = fopen ("superb_report.dot","w+");
    if (arch==NULL){
            cout<<"ERROR AL CREAR EL ARCHIVO DOT...\n";
            return;
        }
    fseek(arch, 0, SEEK_SET);
    fputs("digraph {\ntbl [\nshape=plaintext\n label=<\n", arch);
    fputs("<table border='0' cellborder='1' cellspacing='0'>\n",arch);
    fputs("<tr><td colspan=\"3\">",arch);
    fputs(name,arch);
    fputs("</td></tr>\n",arch);
    fputs("<th><td>Nombre</td><td>Valor</td></th>\n",arch);
    //file system
    fputs("<tr><td bgcolor=\"#bcf7c1\">s_filesystem_type</td><td bgcolor=\"#bcf7c1\">",arch);
    fputs(&to_string(superb->s_filesystem_type)[0],arch);
    fputs("</td></tr>\n",arch);
    //count inodes
    fputs("<tr><td bgcolor=\"#b4e0fa\">s_inodes_count</td><td bgcolor=\"#b4e0fa\">",arch);
    fputs(&to_string(superb->s_inodes_count)[0],arch);
    fputs("</td></tr>\n",arch);
    //count blocks
    fputs("<tr><td bgcolor=\"#bcf7c1\">s_blocks_count</td><td bgcolor=\"#bcf7c1\">",arch);
    fputs(&to_string(superb->s_blocks_count)[0],arch);
    fputs("</td></tr>\n",arch);
    //count free inodes
    fputs("<tr><td bgcolor=\"#b4e0fa\">s_free_inodes_count</td><td bgcolor=\"#b4e0fa\">",arch);
    fputs(&to_string(superb->s_free_inodes_count)[0],arch);
    fputs("</td></tr>\n",arch);
    //count free blocks
    fputs("<tr><td bgcolor=\"#bcf7c1\">s_free_blocks_count</td><td bgcolor=\"#bcf7c1\">",arch);
    fprintf(arch, "%d", superb->s_free_blocks_count);
    fputs("</td></tr>\n",arch);
    //date mount
    fputs("<tr><td bgcolor=\"#b4e0fa\">s_mtime</td><td bgcolor=\"#b4e0fa\">",arch);
    fputs(superb->s_mtime,arch);
    fputs("</td></tr>\n",arch);
    //date unmount
    fputs("<tr><td bgcolor=\"#bcf7c1\">s_umtime</td><td bgcolor=\"#bcf7c1\">",arch);
    fputs(superb->s_umtime,arch);
    fputs("</td></tr>\n",arch);
    //count mount
    fputs("<tr><td bgcolor=\"#b4e0fa\">s_mnt_count</td><td bgcolor=\"#b4e0fa\">",arch);
    fputs(&to_string(superb->s_mnt_count)[0],arch);
    fputs("</td></tr>\n",arch);
    //magic
    fputs("<tr><td bgcolor=\"#bcf7c1\">s_magic</td><td bgcolor=\"#bcf7c1\">",arch);
    fputs(&to_string(superb->s_magic)[0],arch);
    fputs("</td></tr>\n",arch);
    //size inode
    fputs("<tr><td bgcolor=\"#b4e0fa\">s_inode_size</td><td bgcolor=\"#b4e0fa\">",arch);
    fputs(&to_string(superb->s_inode_size)[0],arch);
    fputs("</td></tr>\n",arch);
    //size block
    fputs("<tr><td bgcolor=\"#bcf7c1\">s_block_size</td><td bgcolor=\"#bcf7c1\">",arch);
    fputs(&to_string(superb->s_block_size)[0],arch);
    fputs("</td></tr>\n",arch);
    //first free inode
    fputs("<tr><td bgcolor=\"#b4e0fa\">s_firts_ino</td><td bgcolor=\"#b4e0fa\">",arch);
    fputs(&to_string(superb->s_first_ino)[0],arch);
    fputs("</td></tr>\n",arch);
    //first free block
    fputs("<tr><td bgcolor=\"#bcf7c1\">s_first_blo</td><td bgcolor=\"#bcf7c1\">",arch);
    fputs(&to_string(superb->s_first_blo)[0],arch);
    fputs("</td></tr>\n",arch);
    //start bitmap inodes
    fputs("<tr><td bgcolor=\"#b4e0fa\">s_bm_inode_start</td><td bgcolor=\"#b4e0fa\">",arch);
    fputs(&to_string(superb->s_bm_inode_start)[0],arch);
    fputs("</td></tr>\n",arch);
    //start bitmap blocks
    fputs("<tr><td bgcolor=\"#bcf7c1\">s_bm_block_start</td><td bgcolor=\"#bcf7c1\">",arch);
    fputs(&to_string(superb->s_bm_block_start)[0],arch);
    fputs("</td></tr>\n",arch);
    //start inodes
    fputs("<tr><td bgcolor=\"#b4e0fa\">s_inode_start</td><td bgcolor=\"#b4e0fa\">",arch);
    fputs(&to_string(superb->s_inode_start)[0],arch);
    fputs("</td></tr>\n",arch);
    //start blocks
    fputs("<tr><td bgcolor=\"#bcf7c1\">s_block_start</td><td bgcolor=\"#bcf7c1\">",arch);
    fputs(&to_string(superb->s_block_start)[0],arch);
    fputs("</td></tr>\n",arch);
    fputs("</table>\n",arch);
    fputs(">];\n\n", arch);
    fputs("}\n",arch);
    //cerrando stream
    fclose (arch);
    string pathString(path_report);
    string command = "dot -Tpng superb_report.dot -o \""+pathString+"\"";
    system(command.c_str());
}


//FUNCION PARA GRAFICAR UN ARCHIVO
Respuesta graphFile(char *text, char *title,char reportPath[]){
    FILE * fileReport;
    fileReport = fopen ("File_report.dot","w+");
    if (fileReport==NULL){
        cout<<"ERROR AL CREAR EL ARCHIVO DOT...\n";
        return ERR_IRRECONOCIBLE;
    }
    fseek(fileReport, 0, SEEK_SET);
    fputs("digraph di{\n", fileReport);
    fputs("nodo[label=\"",fileReport);
    int index = 0;
        while(text[index]!='\0' && text[index]>0){
        fprintf(fileReport,"%c", text[index]);
        if(index%64 == 0 && index!=0){
            fputs("\n",fileReport);
        }
        index++;
        }
    fputs("\"\n shape=\"note\"];\n",fileReport);
    fputs("labelloc=\"t\";\nlabel=\"",fileReport);
    fputs(title,fileReport);
    fputs("\";",fileReport);
    fputs("}\n",fileReport);
    fclose (fileReport);
    string pathString(reportPath);
    string command = "dot -Tpng File_report.dot -o \""+pathString+"\"";
    system(command.c_str());
    return CORRECTO;
}


//FUNCION PARA EL REPORTE FILE
Respuesta ReporteFile(char filePath[], char path[], char partition[], char reportPath[]){
    char *title=(char*)"";
    string res = BuscarContenidoArchivo(filePath,path,partition,&title);
    return graphFile(&res[0],title,reportPath);
}

//FUNCION PARA GRAFICAR EL INODO EN EL REPORTE LS
void graphInodoForLs(TablaInodos* inodo,FILE *fileReport,char path[],char namePart[],SuperBlock *superb,char name[]){
    if(inodo==NULL) return;
        if(inodo->i_type == IN_DIRECTORY){
            fputs("<tr>\n", fileReport);
            fputs("<td bgcolor=\"#f99c87\">", fileReport);
            //permisos
            fputs(&to_string(inodo->i_perm)[0],fileReport);
            fputs("</td>\n", fileReport);
            fputs("<td bgcolor=\"#f99c87\">", fileReport);
            //usuario
            Usuario *user = getUsuarioId(&to_string(inodo->i_uid)[0],path,namePart);
            if(user!=NULL){
                fputs(&user->name[0], fileReport);
            }
            fputs("</td>\n", fileReport);
            fputs("<td bgcolor=\"#f99c87\">", fileReport);
            //grupo
            Grupo *grupo = getGrupoId(&to_string(inodo->i_gid)[0],path,namePart);
            if(grupo!=NULL){
                fputs(&grupo->name[0], fileReport);
            }
            fputs("</td>\n", fileReport);
            fputs("<td bgcolor=\"#f99c87\">", fileReport);
            //tamaño
            fputs(&to_string(inodo->i_size)[0],fileReport);
            fputs("</td>\n", fileReport);
            fputs("<td bgcolor=\"#f99c87\">", fileReport);
            //fecha y hora
            fputs(inodo->i_ctime,fileReport);
            fputs("</td>\n", fileReport);
            fputs("<td bgcolor=\"#f99c87\">Carpeta</td>\n", fileReport);
            fputs("<td bgcolor=\"#f99c87\">", fileReport);
            //nombre
            fputs(name, fileReport);
            fputs("</td>\n", fileReport);
            fputs("</tr>\n", fileReport);
            int indexInodo;
            for(indexInodo = 0;indexInodo<12;indexInodo++){
                if(inodo->i_block[indexInodo]!=-1){
                    if(inodo->i_type == IN_DIRECTORY){
                        BloquesCarpetas *directory = ReadBloquesCarpetas(path,getBloqueInicial(superb,inodo->i_block[indexInodo]));
                        if(directory!=NULL){
                            int indexBlock;
                            for(indexBlock = 2;indexBlock<4;indexBlock++){
                                if(directory->b_content[indexBlock].b_inodo!=-1){
                                    TablaInodos *inodo2 = ReadInodo(path,getInodoInicial(superb,directory->b_content[indexBlock].b_inodo));
                                    if(inodo2!=NULL){
                                        graphInodoForLs(inodo2,fileReport,path,namePart,superb,directory->b_content[indexBlock].b_name);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            //GRAFICAR INDIRECTOS
            while(indexInodo<TAM_BLOQUES_INODOS){
                if(inodo->i_block[indexInodo]!=-1){
                    graphInodoForLsRec(indexInodo-11,inodo->i_block[indexInodo],fileReport,path,namePart,superb,inodo->i_type);
                }
                indexInodo++;
            }
        }else{
            fputs("<tr>\n", fileReport);
            fputs("<td bgcolor=\"#f99c87\">", fileReport);
            //permisos
            fputs(&to_string(inodo->i_perm)[0],fileReport);
            fputs("</td>\n", fileReport);
            fputs("<td bgcolor=\"#f99c87\">", fileReport);
            //usuario
            Usuario *user = getUsuarioId(&to_string(inodo->i_uid)[0],path,namePart);
            if(user!=NULL){
                fputs(&user->name[0], fileReport);
            }
            fputs("</td>\n", fileReport);
            fputs("<td bgcolor=\"#f99c87\">", fileReport);
            //grupo
            Grupo *grupo = getGrupoId(&to_string(inodo->i_gid)[0],path,namePart);
            if(grupo!=NULL){
                fputs(&grupo->name[0], fileReport);
            }
            fputs("</td>\n", fileReport);fputs("<td bgcolor=\"#f99c87\">", fileReport);
            //tamaño
            fputs(&to_string(inodo->i_size)[0],fileReport);
            fputs("</td>\n", fileReport);
            fputs("<td bgcolor=\"#f99c87\">", fileReport);
            //fecha y hora
            fputs(inodo->i_ctime,fileReport);
            fputs("</td>\n", fileReport);
            fputs("<td bgcolor=\"#f99c87\">Archivo</td>\n", fileReport);
            fputs("<td bgcolor=\"#f99c87\">", fileReport);
            //nombre
            fputs(name, fileReport);
            fputs("</td>\n", fileReport);
            fputs("</tr>\n", fileReport);
        }
}


//FUNCION PARA GRAFICAR EL INODO RECURSIVAMENTE EN EL REPORTE LS
void graphInodoForLsRec(int level,int indexBlock,FILE *fileReport,char path[],char namePart[],SuperBlock *superb,Tipoinodo type){
    BloquesApuntadores *block = ReadBloquesApuntadores(path,getBloqueInicial(superb,indexBlock));
    if(block==NULL) return;
    if(level==1){
        int indexPointer;
        for(indexPointer = 0;indexPointer<15;indexPointer++){
            if(block->b_pointers[indexPointer]!=-1){
                if(type==IN_DIRECTORY){
                    TablaInodos *ind = ReadInodo(path,getInodoInicial(superb,block->b_pointers[indexPointer]));
                    BloquesCarpetas *directory = ReadBloquesCarpetas(path,getBloqueInicial(superb,ind->i_block[0]));
                    if(directory!=NULL){
                        graphInodoForLs(ind,fileReport,path,namePart,superb,directory->b_content[0].b_name);
                    }
                }
            }
        }
    }else{
        int indexPointer;
        for(indexPointer = 0;indexPointer<15;indexPointer++){
           graphInodoForLsRec(level-1,block->b_pointers[indexPointer],fileReport,path,namePart,superb,type);
        }
    }
}

//FUNCION PARA EL REPORTE LS
Respuesta ReporteLs(char path[], char name[], char path_report[]){
    SuperBlock *superb = ReadSuperBlock(path,name);
    if(superb == NULL){
        return ERR_IRRECONOCIBLE;
    }
    FILE * arch;
    arch = fopen (path,"rb+");
    if (arch==NULL){
        cout<<"ERROR AL ABRIR EL DISCO...\n";
        return ERR_IRRECONOCIBLE;
    }
    FILE * fileReport;
    fileReport = fopen ("Ls_report.dot","w+");
    if(fileReport==NULL){
        cout<<"ERROR AL CREAR EL ARCHIVO DOT...\n";
        return ERR_IRRECONOCIBLE;
    }
    fseek(fileReport, 0, SEEK_SET);
    fputs("digraph d{\n", fileReport);
    fputs("i_3[ shape=plaintext label=<\n", fileReport);
    fputs("<table>\n", fileReport);
    fputs("<tr>\n", fileReport);
    fputs("<td bgcolor=\"#f99c87\">Permisos</td>\n", fileReport);
    fputs("<td bgcolor=\"#f99c87\">Usuario Propietario</td>\n", fileReport);
    fputs("<td bgcolor=\"#f99c87\">Grupo</td>\n", fileReport);
    fputs("<td bgcolor=\"#f99c87\">Tamaño</td>\n", fileReport);
    fputs("<td bgcolor=\"#f99c87\">Fecha y Hora</td>\n", fileReport);
    fputs("<td bgcolor=\"#f99c87\">Tipo</td>\n", fileReport);
    fputs("<td bgcolor=\"#f99c87\">Nombre</td>\n", fileReport);
    fputs("</tr>\n", fileReport);
    TablaInodos *inodo = ReadInodo(path,getInodoInicial(superb,0));
    if(inodo!=NULL){
        graphInodoForLs(inodo,fileReport,path,name,superb,(char*)"/");
    }
    fputs("</table>\n>];\n", fileReport);
    fputs("}\n",fileReport);
    fclose (fileReport);
    fclose (arch);
    string pathString(path_report);
    string command = "dot -Tpng Ls_report.dot -o \""+pathString+"\"";
    system(command.c_str());
    return CORRECTO;
}