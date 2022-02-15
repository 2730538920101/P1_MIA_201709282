/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_SINTACTICO_H_INCLUDED
# define YY_YY_SINTACTICO_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_NUMERO = 258,
    TOK_AJUSTE = 259,
    TOK_RUTA_R = 260,
    TOK_UNIDADES = 261,
    TOK_TIPO = 262,
    TOK_NOMBRE = 263,
    TOK_CAPACIDAD = 264,
    TOK_SISTEMA = 265,
    TOK_IDENTIFICADOR = 266,
    TOK_REPORTES = 267,
    TOK_CADENA = 268,
    TOK_MKDISK = 269,
    TOK_RMDISK = 270,
    TOK_FDISK = 271,
    TOK_MOUNT = 272,
    TOK_UNMOUNT = 273,
    TOK_MKFS = 274,
    TOK_LOGIN = 275,
    TOK_LOGOUT = 276,
    TOK_MKGRP = 277,
    TOK_RMGRP = 278,
    TOK_MKUSR = 279,
    TOK_RMUSR = 280,
    TOK_CHMOD = 281,
    TOK_MKFILE = 282,
    TOK_MKDIR = 283,
    TOK_REMOVE = 284,
    TOK_EDIT = 285,
    TOK_RENAME = 286,
    TOK_COPY = 287,
    TOK_MOVE = 288,
    TOK_FIND = 289,
    TOK_CHOWN = 290,
    TOK_CHGRP = 291,
    TOK_RECOVERY = 292,
    TOK_LOSS = 293,
    TOK_EXEC = 294,
    TOK_PAUSE = 295,
    TOK_REP = 296,
    TOK_SIZE = 297,
    TOK_PATH = 298,
    TOK_NAME = 299,
    TOK_ID = 300,
    TOK_USUARIO = 301,
    TOK_PASSWORD = 302,
    TOK_PWD = 303,
    TOK_GRP = 304,
    TOK_UGO = 305,
    TOK_CAT = 306,
    TOK_FILEN = 307,
    TOK_CONTENIDO = 308,
    TOK_CONT = 309,
    TOK_DESTINO = 310,
    TOK_FIT = 311,
    TOK_UNIT = 312,
    TOK_TYPE = 313,
    TOK_DELETE = 314,
    TOK_ADD = 315,
    TOK_FS = 316,
    TOK_R = 317,
    TOK_P = 318,
    TOK_IGUAL = 319,
    TOK_RUTA = 320
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 25 "sintactico.y"

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

#line 140 "sintactico.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SINTACTICO_H_INCLUDED  */
