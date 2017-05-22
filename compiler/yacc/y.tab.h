/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    CLASS = 258,
    MAIN = 259,
    THIS = 260,
    IF = 261,
    ELSE = 262,
    SWITCH = 263,
    CASE = 264,
    DEFAULT = 265,
    FOR = 266,
    DO = 267,
    WHILE = 268,
    CONTINUE = 269,
    BREAK = 270,
    TRY = 271,
    CATCH = 272,
    TRUE = 273,
    FALSE = 274,
    VOID = 275,
    INT = 276,
    FLOAT = 277,
    DOUBEL = 278,
    CHAR = 279,
    BOOLEAN = 280,
    STRING = 281,
    NEW = 282,
    CONST = 283,
    FINAL = 284,
    STATIC = 285,
    PRINT = 286,
    READ = 287,
    PUBLIC = 288,
    PROTECTED = 289,
    PRIVATE = 290,
    EXTENDS = 291,
    FINALLY = 292,
    IMPLEMENTS = 293,
    RETURN = 294,
    EXCEPTION = 295,
    DOUBLE_OPERATOR = 296,
    COMPARE_BOOL = 297,
    CONNECT_BOOL = 298,
    EQUAL = 299,
    REAL_DATA = 300,
    INT_DATA = 301,
    STRING_DATA = 302,
    ID = 303
  };
#endif
/* Tokens.  */
#define CLASS 258
#define MAIN 259
#define THIS 260
#define IF 261
#define ELSE 262
#define SWITCH 263
#define CASE 264
#define DEFAULT 265
#define FOR 266
#define DO 267
#define WHILE 268
#define CONTINUE 269
#define BREAK 270
#define TRY 271
#define CATCH 272
#define TRUE 273
#define FALSE 274
#define VOID 275
#define INT 276
#define FLOAT 277
#define DOUBEL 278
#define CHAR 279
#define BOOLEAN 280
#define STRING 281
#define NEW 282
#define CONST 283
#define FINAL 284
#define STATIC 285
#define PRINT 286
#define READ 287
#define PUBLIC 288
#define PROTECTED 289
#define PRIVATE 290
#define EXTENDS 291
#define FINALLY 292
#define IMPLEMENTS 293
#define RETURN 294
#define EXCEPTION 295
#define DOUBLE_OPERATOR 296
#define COMPARE_BOOL 297
#define CONNECT_BOOL 298
#define EQUAL 299
#define REAL_DATA 300
#define INT_DATA 301
#define STRING_DATA 302
#define ID 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
