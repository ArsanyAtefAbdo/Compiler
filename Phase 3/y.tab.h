
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
#line 20 "SYN.y"

	#include <vector>
	using namespace std;



/* Line 1676 of yacc.c  */
#line 47 "y.tab.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     F_NUM = 259,
     INT = 260,
     FLOAT = 261,
     BOOLEAN = 262,
     IF_WORD = 263,
     ELSE = 264,
     FOR_WORD = 265,
     WHILE_WORD = 266,
     SYSTEM_OUT = 267,
     ADD_OP = 268,
     MUL_OP = 269,
     REL_OP = 270,
     BOOL_OP = 271,
     BOOL = 272,
     ID = 273,
     SEMI_COLON = 274,
     LEFT_BRACKET = 275,
     RIGHT_BRACKET = 276,
     LEFT_CURLY_BRACKET = 277,
     RIGHT_CURLY_BRACKET = 278,
     EQUALS = 279,
     OTHER = 280
   };
#endif
/* Tokens.  */
#define NUM 258
#define F_NUM 259
#define INT 260
#define FLOAT 261
#define BOOLEAN 262
#define IF_WORD 263
#define ELSE 264
#define FOR_WORD 265
#define WHILE_WORD 266
#define SYSTEM_OUT 267
#define ADD_OP 268
#define MUL_OP 269
#define REL_OP 270
#define BOOL_OP 271
#define BOOL 272
#define ID 273
#define SEMI_COLON 274
#define LEFT_BRACKET 275
#define RIGHT_BRACKET 276
#define LEFT_CURLY_BRACKET 277
#define RIGHT_CURLY_BRACKET 278
#define EQUALS 279
#define OTHER 280




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 27 "SYN.y"


  int ival;     // int
	float fval;   // float
	char * val;   // value
  char * type;  // type --> ADD_OP MUL_OP NUM F_NUM REL_OP BOOL_OP BOOL ID
  struct {
        int type;
        vector<string *> *code;
        vector<string *> *next;
  } exp;
	struct {
			int type;
			vector<string *> *code;
	} factor;
	struct {
			vector<string *> *code;
			vector<string *> *next;
	} block;
	int pt;



/* Line 1676 of yacc.c  */
#line 138 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


