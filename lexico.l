%{

#include "sintactico.h"
#include <iostream>

int columna = 0;    
    
%}

%option noyywrap
%option caseless

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
touch           "TOUCH"
cat             "CAT"
rm              "RM"
edit            "EDIT"
ren             "REN"
mkdir           "MKDIR"
cp              "CP"
mv              "MV"
find            "FIND"
chown           "CHOWN"
chgrp           "CHGRP"
recovery        "RECOVERY"
loss            "LOSS"
exec            "EXEC"
pause           "PAUSE"
size            "-size"
path            "-path"
name            "-name"
id              "-id"
usr             "-usr"
pwd             "-pwd"
grp             "-grp"
ugo             "-ugo"
filen           "-file"[0-9]+
cont            "-cont"
stdin           "-stdin"
dest            "-dest"
f               "-f"
u               "-u"
type            "-type"
delete          "-delete"
add             "-add"
fs              "-fs"
r               "-r"
p               "-p"
identificador   [0-9]{3}[Aa-zZ]
numero          [0-9]+
ajuste          "BF"|"FF"|"WF"
unidades        "B"|"K"|"M"
cadena          [\"][^\"\n]*[\"]
ruta            {cadena}|([/][^\n\" ]+)+
tipo            "P"|"E"|"L"
capacidad       "FAST"|"FULL"
sistema         "2FS"|"3FS"
nombre          [\*\?a-zA-Z0-9._-]{1,10}
igual           [=]



%%

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
{stdin}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_STDIN;}
{mkgrp}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_MKGRP;}
{rmgrp}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_RMGRP;}
{mkusr}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_MKUSR;}
{mkdir}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_MKDIR;}
{rmusr}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_RMUSR;}
{chmod}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_CHMOD;}
{touch}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_TOUCH;}
{cat}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_CAT;}
{rm}                    {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_RM;}
{edit}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_EDIT;}
{ren}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_REN;}
{cp}                    {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_CP;}
{mv}                    {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_MV;}
{find}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_FIND;}
{chown}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_CHOWN;}
{chgrp}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_CHGRP;}
{recovery}              {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_RECOVERY;}
{loss}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_LOSS;}
{exec}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_EXEC;}
{size}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_SIZE;}
{path}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_PATH;}
{name}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_NAME;}
{id}                    {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_ID;}
{usr}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_USR;}
{pwd}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_PWD;}
{grp}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_GRP;}
{ugo}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_UGO;}
{filen}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_FILEN;}
{cont}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_CONT;}
{dest}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_DEST;}
{f}                     {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_F;}
{u}                     {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_U;}
{type}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_TYPE;}
{delete}                {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_DELETE;}
{add}                   {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_ADD;}
{fs}                    {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_FS;}
{r}                     {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_R;}
{p}                     {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_P;}
{ajuste}                {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_AJUSTE;}
{unidades}              {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_UNIDADES;}
{ruta}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_RUTA;}
{tipo}                  {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_TIPO;}
{capacidad}             {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_CAPACIDAD;}
{sistema}               {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_SISTEMA;}
{igual}                 {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_IGUAL;}
{nombre}                {columna = columna + strlen(yylval.entrada); strcpy(yylval.entrada, yytext); return TOK_NOMBRE;}
[[:blank:]]             ;
.                       {std::cout<<yytext<<"ERROR LEXICO"<< std::ends;}

%%