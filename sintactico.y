%{

#include "lexico.h"
#include <iostream>
#include <string.h>
#include "tipos.h"
#include "clases_comandos.h"
#include "retorno.h"
#include "modelos.h"

extern int yylineno;
extern int columna;
extern char *yytext;

void yyerror(const char* msj){    
    std::cout<<"ERROR SINTACTICO EN: "<<msj<<" "<<yytext<< std::endl;
}

%}

/* directiva bison permite enviar mensajes de error diferentes a syntax error */
%define parse.error verbose


%union{
#include "tipos.h"

char entrada [256];
Tipofit fit;
Tipoparticion tipo;
Tipounit unit;
Tipocapacidad capacidad;
Tiposistema sistema;
TipoComando tipocomando;
Tiporeporte tiporeporte;
Tipoparametro parametro;
struct Parametro *PARAM;
class Comando *COMMAND;
int INT;
}

%token <entrada> TOK_NUMERO
%token <entrada> TOK_FIRST
%token <entrada> TOK_WORST
%token <entrada> TOK_BEST
%token <entrada> TOK_RUTA_R
%token <entrada> TOK_KB
%token <entrada> TOK_MB
%token <entrada> TOK_BYTES
%token <entrada> TOK_PRIMARIA
%token <entrada> TOK_LOGICA
%token <entrada> TOK_EXTENDIDA
%token <entrada> TOK_NOMBRE
%token <entrada> TOK_FAST
%token <entrada> TOK_FULL
%token <entrada> TOK_EXT2
%token <entrada> TOK_EXT3
%token <entrada> TOK_IDENTIFICADOR
%token <entrada> TOK_REPORTES
%token <entrada> TOK_CADENA

%token <entrada> TOK_MKDISK
%token <entrada> TOK_RMDISK
%token <entrada> TOK_FDISK
%token <entrada> TOK_MOUNT
%token <entrada> TOK_UNMOUNT
%token <entrada> TOK_MKFS
%token <entrada> TOK_LOGIN
%token <entrada> TOK_LOGOUT
%token <entrada> TOK_MKGRP
%token <entrada> TOK_RMGRP
%token <entrada> TOK_MKUSR
%token <entrada> TOK_RMUSR
%token <entrada> TOK_CHMOD
%token <entrada> TOK_MKFILE
%token <entrada> TOK_MKDIR
%token <entrada> TOK_REMOVE
%token <entrada> TOK_EDIT
%token <entrada> TOK_RENAME
%token <entrada> TOK_COPY
%token <entrada> TOK_MOVE
%token <entrada> TOK_FIND
%token <entrada> TOK_CHOWN
%token <entrada> TOK_CHGRP
%token <entrada> TOK_RECOVERY
%token <entrada> TOK_LOSS
%token <entrada> TOK_EXEC
%token <entrada> TOK_PAUSE
%token <entrada> TOK_REP
%token <entrada> TOK_SIZE
%token <entrada> TOK_PATH
%token <entrada> TOK_NAME
%token <entrada> TOK_ID
%token <entrada> TOK_USUARIO
%token <entrada> TOK_PASSWORD
%token <entrada> TOK_PWD
%token <entrada> TOK_GRP
%token <entrada> TOK_UGO
%token <entrada> TOK_CAT
%token <entrada> TOK_FILEN
%token <entrada> TOK_CONTENIDO
%token <entrada> TOK_CONT
%token <entrada> TOK_DESTINO
%token <entrada> TOK_FIT
%token <entrada> TOK_UNIT
%token <entrada> TOK_TYPE
%token <entrada> TOK_DELETE
%token <entrada> TOK_ADD
%token <entrada> TOK_FS
%token <entrada> TOK_R
%token <entrada> TOK_P
%token <entrada> TOK_IGUAL
%token <entrada> TOK_RUTA




%type <entrada> inicio
%type <tipocomando> comando_estado
%type <COMMAND> comand_list
%type <COMMAND> comando

%type <PARAM> params_list
%type <PARAM> param

%type <fit> ajustes
%type <capacidad> capacidades
%type <unit> unidades
%type <tipo> tipos
%type <sistema> sistemas

%start inicio  

%%

inicio:                 comand_list{
                            ListarComando($1, true);
                        }
;

comand_list:            comand_list comando{
                            if($1 != NULL){
                                if($2 != NULL){
                                    Comando *primero = $1;
                                    while(primero->siguiente != NULL){
                                        primero = primero->siguiente;
                                    }
                                    primero->siguiente = $2;
                                }
                                $$ = $1;
                            }else{
                                if($2 != NULL){
                                    $$ = $2;
                                }else{
                                    $$ = NULL;
                                }
                            }
                        }
                        |comando{
                            $$ = $1;
                        }           
;

comando:                comando_estado params_list{
                            Comando *aux_comando = getComando($1, $2);
                            $$ = aux_comando;
                        }
                        |TOK_PAUSE{
                            $$ = new C_pause();
                        }
                        |TOK_LOGOUT{
                            $$ = new C_logout();
                        }
;

comando_estado:         TOK_MKDISK{
                            $$=MKDISK;
                        }
                        |TOK_RMDISK{
                            $$=RMDISK;
                        }
                        |TOK_FDISK{
                            $$=FDISK;
                        }
                        |TOK_MOUNT{
                            $$=MOUNT;
                        }  
                        |TOK_UNMOUNT{
                            $$=UNMOUNT;
                        }
                        |TOK_MKFS{
                            $$=MKFS;
                        }
                        |TOK_LOGIN{
                            $$=LOGIN;
                        }
                        |TOK_MKGRP{
                            $$=MKGRP;
                        }
                        |TOK_RMGRP{
                            $$=RMGRP;
                        }
                        |TOK_MKUSR{
                            $$=MKUSR;
                        }
                        |TOK_RMUSR{
                            $$=RMUSR;
                        }
                        |TOK_CHMOD{
                            $$=CHMOD;
                        }
                        |TOK_MKFILE{
                            $$=MKFILE;
                        }
                        |TOK_CAT{
                            $$=CAT;
                        }
                        |TOK_MKDIR{
                            $$=MKDIR;
                        }
                        |TOK_REMOVE{
                            $$=REMOVE;
                        }
                        |TOK_EDIT{
                            $$=EDIT;
                        }
                        |TOK_RENAME{
                            $$=RENAME;
                        }
                        |TOK_COPY{
                            $$=COPY;
                        }
                        |TOK_MOVE{
                            $$=MOVE;
                        }
                        |TOK_FIND{
                            $$=FIND;
                        }
                        |TOK_CHOWN{
                            $$=CHOWN;
                        }
                        |TOK_CHGRP{
                            $$=CHGRP;
                        }
                        |TOK_RECOVERY{
                            $$=RECOVERY;
                        }
                        |TOK_LOSS{
                            $$=LOSS;
                        }
                        |TOK_EXEC{
                            $$=EXEC;
                        }
                        |TOK_REP{
                            $$=REP;
                        }
;

params_list:            params_list param{
                            Parametro *aux_param = $1;
                            while(aux_param->siguiente != NULL){
                                aux_param = aux_param->siguiente;
                            }
                            aux_param->siguiente = $2;
                            $$ = $1;
                        }
                        |param{
                            $$ = $1;
                        }
;

param:                  TOK_PATH TOK_IGUAL TOK_RUTA_R{
                            $$ = new Parametro(PATH);
                            strcpy($$->text, $3);
                        }
                        |TOK_PATH TOK_IGUAL TOK_CADENA{
                            $$ = new Parametro(PATH);
                            strcpy($$->text, getCadenaSinComillas($3).c_str());
                        }
                        |TOK_SIZE TOK_IGUAL TOK_NUMERO{
                            $$ = new Parametro(SIZE);
                            $$->num = getNumero($3);
                        }
                        |TOK_UNIT TOK_IGUAL unidades{
                            $$ = new Parametro(UNIT);    
                            $$->unit = $3;
                            
                        }
                        |TOK_FIT TOK_IGUAL ajustes{
                            $$ = new Parametro(FIT);
                            $$->fit = $3;
                            
                        }
                        |TOK_NAME TOK_IGUAL TOK_NOMBRE{
                            $$ = new Parametro(NAME);
                            strcpy($$->text, $3);
                        }
                        |TOK_NAME TOK_IGUAL TOK_CADENA{
                            $$ = new Parametro(NAME);
                            strcpy($$->text, getCadenaSinComillas($3).c_str());
                        }
                        |TOK_TYPE TOK_IGUAL tipos{
                            $$ = new Parametro(TYPE);
                            $$->type = $3;
                            
                        }
                        |TOK_DELETE TOK_IGUAL capacidades{
                            $$ = new Parametro(DELETE);
                            $$->capacidad = $3;
                            
                        }
                        |TOK_ADD TOK_IGUAL TOK_NUMERO{
                            $$ = new Parametro(ADD);
                            $$->num = getNumero($3);
                        }
                        |TOK_ID TOK_IGUAL TOK_IDENTIFICADOR{
                            $$ = new Parametro(ID);
                            strcpy($$->text, $3);
                        }
                        |TOK_TYPE TOK_IGUAL capacidades{
                            $$ = new Parametro(FORMATO);
                            $$->capacidad = $3;
                        }
                        |TOK_FS TOK_IGUAL sistemas{
                            $$ = new Parametro(FS);
                            $$->sistema = FS_EXT_ERROR;
                        }
                        |TOK_USUARIO TOK_IGUAL TOK_NOMBRE{
                            $$ = new Parametro(USUARIO);
                            strcpy($$->text, $3);
                        }
                        |TOK_USUARIO TOK_IGUAL TOK_CADENA{
                            $$ = new Parametro(USUARIO);
                            strcpy($$->text, getCadenaSinComillas($3).c_str());
                        }
                        |TOK_PASSWORD TOK_IGUAL TOK_NOMBRE{
                            $$ = new Parametro(PASSWORD);
                            strcpy($$->text, $3);
                        }
                        |TOK_PASSWORD TOK_IGUAL TOK_NUMERO{
                            $$ = new Parametro(PASSWORD);
                            strcpy($$->text, $3);
                        }
                        |TOK_PWD TOK_IGUAL TOK_NOMBRE{
                            $$ = new Parametro(PWD);
                            strcpy($$->text, $3);
                        }
                        |TOK_PWD TOK_IGUAL TOK_NUMERO{
                            $$ = new Parametro(PWD);
                            strcpy($$->text, $3);
                        }      
                        |TOK_GRP TOK_IGUAL TOK_NOMBRE{
                            $$ = new Parametro(GRP);
                            strcpy($$->text, $3);
                        }
                        |TOK_GRP TOK_IGUAL TOK_CADENA{
                            $$ = new Parametro(GRP);
                            strcpy($$->text, getCadenaSinComillas($3).c_str());
                        }
                        |TOK_UGO TOK_IGUAL TOK_NUMERO{
                            $$ = new Parametro(UGO);
                            $$->num = getNumero($3);
                        }
                        |TOK_R{
                            $$ = new Parametro(R);
                            $$->r_flag = true;
                        }
                        |TOK_P{
                            $$ = new Parametro(PP);
                            $$->p_flag = true;
                        }
                        |TOK_CONT TOK_IGUAL TOK_RUTA_R{
                            $$ = new Parametro(CONT);
                            strcpy($$->text, $3);
                        }
                        |TOK_CONTENIDO TOK_IGUAL TOK_RUTA_R{
                            $$ = new Parametro(CONTENIDO);
                            strcpy($$->text, $3);
                        }
                        |TOK_CONTENIDO TOK_IGUAL TOK_CADENA{
                            $$ = new Parametro(CONTENIDO);
                            strcpy($$->text, getCadenaSinComillas($3).c_str());
                        }
                        |TOK_CONT TOK_IGUAL TOK_CADENA{
                            $$ = new Parametro(CONT);
                            strcpy($$->text, getCadenaSinComillas($3).c_str());
                        }
                        |TOK_DESTINO TOK_IGUAL TOK_RUTA_R{
                            $$ = new Parametro(DESTINO);
                            strcpy($$->text, $3);
                        }
                        |TOK_DESTINO TOK_IGUAL TOK_CADENA{
                            $$ = new Parametro(DESTINO);
                            strcpy($$->text, getCadenaSinComillas($3).c_str());
                        }
                        |TOK_FILEN TOK_IGUAL TOK_RUTA_R{
                            $$ = new Parametro(FILEN);
                            strcpy($$->text, $3);
                        }
                        |TOK_FILEN TOK_IGUAL TOK_CADENA{
                            $$ = new Parametro(FILEN);
                            strcpy($$->text, getCadenaSinComillas($3).c_str());
                        }
                        |TOK_RUTA TOK_IGUAL TOK_CADENA{
                            $$ = new Parametro(RUTA);
                            strcpy($$->text, getCadenaSinComillas($3).c_str());
                        }
                        |TOK_RUTA TOK_IGUAL TOK_RUTA_R{
                            $$ = new Parametro(RUTA);
                            strcpy($$->text, $3);
                        }                                           
;

unidades:               TOK_KB{
                            $$ = K;
                        }
                        |TOK_MB{
                            $$ = M;
                        }
                        |TOK_BYTES{
                            $$ = B;
                        }
;

tipos:                  TOK_PRIMARIA{
                            $$ = P;
                        }
                        |TOK_EXTENDIDA{
                            $$ = E;
                        }
                        |TOK_LOGICA{
                            $$ = L;
                        }
;

capacidades:            TOK_FAST{
                            $$ = FAST;
                        }
                        |TOK_FULL{
                            $$ = FULL;
                        }
;

sistemas:               TOK_EXT2{
                            $$ = EXT2;
                        }
                        |TOK_EXT3{
                            $$ = EXT3;
                        }
;

ajustes:                TOK_FIRST{
                            $$ = FF;
                        }
                        |TOK_WORST{
                            $$ = WF;
                        }
                        |TOK_BEST{        
                            $$ = BF;
                        }
;

%%
