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
    TOK_FIRST = 259,
    TOK_WORST = 260,
    TOK_BEST = 261,
    TOK_RUTA_R = 262,
    TOK_KB = 263,
    TOK_MB = 264,
    TOK_BYTES = 265,
    TOK_PRIMARIA = 266,
    TOK_LOGICA = 267,
    TOK_EXTENDIDA = 268,
    TOK_NOMBRE = 269,
    TOK_FAST = 270,
    TOK_FULL = 271,
    TOK_EXT2 = 272,
    TOK_EXT3 = 273,
    TOK_IDENTIFICADOR = 274,
    TOK_REPORTES = 275,
    TOK_CADENA = 276,
    TOK_MKDISK = 277,
    TOK_RMDISK = 278,
    TOK_FDISK = 279,
    TOK_MOUNT = 280,
    TOK_UNMOUNT = 281,
    TOK_MKFS = 282,
    TOK_LOGIN = 283,
    TOK_LOGOUT = 284,
    TOK_MKGRP = 285,
    TOK_RMGRP = 286,
    TOK_MKUSR = 287,
    TOK_RMUSR = 288,
    TOK_CHMOD = 289,
    TOK_MKFILE = 290,
    TOK_MKDIR = 291,
    TOK_REMOVE = 292,
    TOK_EDIT = 293,
    TOK_RENAME = 294,
    TOK_COPY = 295,
    TOK_MOVE = 296,
    TOK_FIND = 297,
    TOK_CHOWN = 298,
    TOK_CHGRP = 299,
    TOK_RECOVERY = 300,
    TOK_LOSS = 301,
    TOK_EXEC = 302,
    TOK_PAUSE = 303,
    TOK_REP = 304,
    TOK_SIZE = 305,
    TOK_PATH = 306,
    TOK_NAME = 307,
    TOK_ID = 308,
    TOK_USUARIO = 309,
    TOK_PASSWORD = 310,
    TOK_PWD = 311,
    TOK_GRP = 312,
    TOK_UGO = 313,
    TOK_CAT = 314,
    TOK_FILEN = 315,
    TOK_CONTENIDO = 316,
    TOK_CONT = 317,
    TOK_DESTINO = 318,
    TOK_FIT = 319,
    TOK_UNIT = 320,
    TOK_TYPE = 321,
    TOK_DELETE = 322,
    TOK_ADD = 323,
    TOK_FS = 324,
    TOK_R = 325,
    TOK_P = 326,
    TOK_IGUAL = 327,
    TOK_RUTA = 328
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

#line 148 "sintactico.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SINTACTICO_H_INCLUDED  */
