%{

#include "sintactico.h"
#include <iostream>

int columna = 0;    
    
%}

%option noyywrap
%option caseless

coment          (#.*\n?)
mkdisk          "MKDISK"
rmdisk          "RMDISK"
fdisk           "FDISK"
mount           "MOUNT"
unmount         "UNMOUNT"
mkfs            "MKFS"
login           "LOGIN"
logout          "LOGOUT"
mkgrp           "MKGRP"
rmgrp           "RMGRP"
mkusr           "MKUSR"
rmusr           "RMUSR"
chmod           "CHMOD"
mkfile          "MKFILE"
cat             "CAT"
remove          "REMOVE"
edit            "EDIT"
rename          "RENAME"
mkdir           "MKDIR"
copy            "COPY"
move            "MOVE"
find            "FIND"
chown           "CHOWN"
chgrp           "CHGRP"
recovery        "RECOVERY"
loss            "LOSS"
exec            "EXEC"
pause           "PAUSE"
rep             "REP"
size            "-size"
path            "-path"
name            "-name"
id              "-id"
usuario         "-usuario"
pwd             "-pwd"
password        "-password"
grp             "-grp"
ugo             "-ugo"
filen           "-file"[0-9]+
cont            "-cont"
contenido       "-contenido"
destino         "-destino"
unit            "-unit"
type            "-type"
delete          "-delete"
add             "-add"
fs              "-fs"
r               "-r"
p               "-p"
fit             "-fit"
ruta            "-ruta"
identificador   [0-9]{3}[Aa-zZ]
numero          [0-9]+
cadena          [\"][^\"\n]*[\"]
ruta_r          ([/][^\n\" ]+?)+
nombre          [\*\?a-zA-Z0-9._-]+
igual           [=]



%%
{coment}                { }
{cadena}                {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_CADENA;}
{numero}                {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_NUMERO;}
{identificador}         {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_IDENTIFICADOR;}
{pause}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_PAUSE;}
{mkdisk}                {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_MKDISK;}
{rmdisk}                {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_RMDISK;}
{fdisk}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_FDISK;}
{mount}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_MOUNT;}
{unmount}               {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_UNMOUNT;}
{mkfs}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_MKFS;}
{login}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_LOGIN;}
{logout}                {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_LOGOUT;}
{mkgrp}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_MKGRP;}
{rmgrp}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_RMGRP;}
{mkusr}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_MKUSR;}
{mkdir}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_MKDIR;}
{rmusr}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_RMUSR;}
{chmod}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_CHMOD;}
{mkfile}                {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_MKFILE;}
{cat}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_CAT;}
{remove}                {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_REMOVE;}
{edit}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_EDIT;}
{rename}                {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_RENAME;}
{copy}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_COPY;}
{move}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_MOVE;}
{find}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_FIND;}
{chown}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_CHOWN;}
{chgrp}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_CHGRP;}
{recovery}              {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_RECOVERY;}
{loss}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_LOSS;}
{exec}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_EXEC;}
{rep}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_REP;}
{size}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_SIZE;}
{path}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_PATH;}
{name}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_NAME;}
{id}                    {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_ID;}
{usuario}               {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_USUARIO;}
{password}              {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_PASSWORD;}
{pwd}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_PWD;}
{grp}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_GRP;}
{ugo}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_UGO;}
{filen}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_FILEN;}
{contenido}             {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_CONTENIDO;}
{cont}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_CONT;}
{destino}               {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_DESTINO;}
{unit}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_UNIT;}
{type}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_TYPE;}
{delete}                {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_DELETE;}
{add}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_ADD;}
{fs}                    {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_FS;}
{fit}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_FIT;}
{r}                     {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_R;}
{p}                     {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_P;}
{ruta}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_RUTA;}
"FF"                    {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_FIRST;}
"WF"                    {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_WORST;}
"BF"                    {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_BEST;}
"K"                     {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_KB;}
"M"                     {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_MB;}
"B"                     {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_BYTES;}
{ruta_r}                {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_RUTA_R;}
"P"                     {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_PRIMARIA;}
"E"                     {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_EXTENDIDA;}
"L"                     {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_LOGICA;}
"FAST"                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_FAST;}
"FULL"                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_FULL;}
"2FS"                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_EXT2;}
"3FS"                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_EXT3;}
{igual}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_IGUAL;}
{nombre}                {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_NOMBRE;}
"\n"			 { }
[[:blank:]]		 { }
.                       {std::cout<<yytext<<"ERROR LEXICO"<< std::endl;}

%%
