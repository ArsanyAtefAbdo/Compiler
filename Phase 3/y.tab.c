
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "SYN.y"

/* C stuff */
#include "Label.h"
#include <stdio.h>
#include <string>
#include <tuple>
#include <unordered_map>
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
extern int yylex();
extern "C" int yyparse (void);
extern  FILE *yyin;
void yyerror(string);
void print_code(vector<string *> * code);
// -------------Michael Said----------------
	
unsigned Label::label_num = 0;
char Label::label_char = 'a';
// adding new label to the code.
void add_label_to_code(vector<string *> *code, Label label);
// adding a label to the code if the list next needs backpatching, then backpatches next with that label.
void perform_label_adding(vector<string *> *code, vector<string *> **next);
// patching all strings in list by adding the string label_name to their end.
void back_patching(vector<string *> **list, string label_name);

void clear_scope(unsigned l_id);

//------------------------------------------
ofstream fileOut("out.j");
unsigned sym_num = 1;
///           name          num  type
unordered_map<string, pair<unsigned, int>> symbol_table;
unordered_map<unsigned, string> memory_table;
typedef enum {INT_T, FLOAT_T, BOOL_T, ERROR_T} type_enum;

unordered_map<char, string> op_map = {
  pair<char,string>('+', "add"),
  pair<char,string>('-', "sub"),
  pair<char,string>('*', "mul"),
  pair<char,string>('/', "div"),
  pair<char,string>('%', "rem")
};

unordered_map<string, string> real_ops = {
  pair<string,string>("==", "eq"),
  pair<string,string>(">=", "ge"),
  pair<string,string>(">", "gt"),
  pair<string,string>("<=", "le"),
  pair<string,string>("<", "lt"),
  pair<string,string>("!=", "ne")
};

unordered_map<int, string> type_map = {
  pair<int, string>(INT_T, "i"), pair<int, string>(BOOL_T, "i"), pair<int, string>(FLOAT_T, "f")
};



/* Line 189 of yacc.c  */
#line 133 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
#line 60 "SYN.y"

	#include <vector>
	#include <string>
	#include "Label.h"
	using namespace std;



/* Line 209 of yacc.c  */
#line 166 "y.tab.c"

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
     REL_OP = 268,
     BOOL = 269,
     ID = 270,
     SEMI_COLON = 271,
     LEFT_BRACKET = 272,
     RIGHT_BRACKET = 273,
     LEFT_CURLY_BRACKET = 274,
     RIGHT_CURLY_BRACKET = 275,
     EQUALS = 276,
     OTHER = 277,
     NOT = 278,
     OR = 279,
     AND = 280,
     ADD_OP = 281,
     MUL_OP = 282
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
#define REL_OP 268
#define BOOL 269
#define ID 270
#define SEMI_COLON 271
#define LEFT_BRACKET 272
#define RIGHT_BRACKET 273
#define LEFT_CURLY_BRACKET 274
#define RIGHT_CURLY_BRACKET 275
#define EQUALS 276
#define OTHER 277
#define NOT 278
#define OR 279
#define AND 280
#define ADD_OP 281
#define MUL_OP 282




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 69 "SYN.y"


  int ival;     // int
  float fval;   // float
  char cval;   // value
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
			unsigned l_id; // id of block before it
			vector<string *> *code;
			vector<string *> *next;
	} block;
	int pt;



/* Line 214 of yacc.c  */
#line 263 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 275 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   92

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  48
/* YYNRULES -- Number of states.  */
#define YYNSTATES  89

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   282

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    11,    16,    19,    21,
      23,    25,    28,    30,    36,    39,    44,    45,    47,    49,
      51,    53,    55,    61,    69,    75,    85,    89,    90,    92,
      94,    96,   100,   102,   106,   108,   111,   115,   117,   121,
     123,   126,   130,   132,   136,   138,   140,   142,   144
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      29,     0,    -1,    30,    -1,    33,    -1,    30,    33,    -1,
      -1,    32,    19,    30,    20,    -1,    35,    16,    -1,    38,
      -1,    39,    -1,    40,    -1,    41,    16,    -1,    34,    -1,
      12,    17,    44,    18,    16,    -1,    37,    15,    -1,    37,
      15,    21,    44,    -1,    -1,    35,    -1,    41,    -1,     5,
      -1,     6,    -1,     7,    -1,     8,    17,    43,    18,    31,
      -1,     8,    17,    43,    18,    31,     9,    31,    -1,    11,
      17,    43,    18,    31,    -1,    10,    17,    36,    16,    43,
      16,    42,    18,    31,    -1,    15,    21,    44,    -1,    -1,
      41,    -1,    44,    -1,    45,    -1,    44,    25,    45,    -1,
      46,    -1,    45,    24,    46,    -1,    47,    -1,    23,    46,
      -1,    17,    44,    18,    -1,    48,    -1,    48,    13,    48,
      -1,    49,    -1,    26,    49,    -1,    48,    26,    49,    -1,
      50,    -1,    49,    27,    50,    -1,    15,    -1,     3,    -1,
       4,    -1,    14,    -1,    17,    47,    18,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   128,   128,   136,   141,   150,   150,   162,   165,   168,
     171,   174,   177,   182,   198,   216,   250,   253,   256,   261,
     263,   265,   269,   282,   302,   315,   336,   374,   377,   383,
     405,   410,   447,   451,   487,   491,   513,   518,   523,   585,
     589,   600,   613,   616,   630,   649,   653,   657,   666
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "F_NUM", "INT", "FLOAT",
  "BOOLEAN", "IF_WORD", "ELSE", "FOR_WORD", "WHILE_WORD", "SYSTEM_OUT",
  "REL_OP", "BOOL", "ID", "SEMI_COLON", "LEFT_BRACKET", "RIGHT_BRACKET",
  "LEFT_CURLY_BRACKET", "RIGHT_CURLY_BRACKET", "EQUALS", "OTHER", "NOT",
  "OR", "AND", "ADD_OP", "MUL_OP", "$accept", "METHOD_BODY",
  "STATEMENT_LIST", "BLOCK", "@1", "STATEMENT", "SYSTEM_PRINT",
  "DECLARATION", "OPTIONAL_DECLARATION", "PRIMITIVE_TYPE", "IF", "WHILE",
  "FOR", "ASSIGNMENT", "OPTIONAL_ASSIGNMENT", "BOOLEAN_CONDITION",
  "BOOLEAN_EXPRESSION", "SIMPLE_BOOLEAN_EXPRESSION", "BOOLEAN_TERM",
  "EXPRESSION", "SIMPLE_EXPRESSION", "TERM", "FACTOR", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    28,    29,    30,    30,    32,    31,    33,    33,    33,
      33,    33,    33,    34,    35,    35,    36,    36,    36,    37,
      37,    37,    38,    38,    39,    40,    41,    42,    42,    43,
      44,    44,    45,    45,    46,    46,    46,    47,    47,    48,
      48,    48,    49,    49,    50,    50,    50,    50,    50
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     0,     4,     2,     1,     1,
       1,     2,     1,     5,     2,     4,     0,     1,     1,     1,
       1,     1,     5,     7,     5,     9,     3,     0,     1,     1,
       1,     3,     1,     3,     1,     2,     3,     1,     3,     1,
       2,     3,     1,     3,     1,     1,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    19,    20,    21,     0,     0,     0,     0,     0,     0,
       2,     3,    12,     0,     0,     8,     9,    10,     0,     0,
      16,     0,     0,     0,     1,     4,     7,    14,    11,    45,
      46,    47,    44,     0,     0,     0,     0,    29,    30,    32,
      34,    37,    39,    42,    17,     0,    18,     0,     0,    26,
       0,     0,    34,    35,     0,    40,     5,     0,     0,     0,
       0,     0,     0,     5,     0,    15,    36,    48,     0,    22,
       0,    31,    33,    38,    41,    43,     0,    24,    13,     5,
       0,    27,    23,     0,    28,     0,     6,     5,    25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     9,    10,    69,    70,    11,    12,    13,    45,    14,
      15,    16,    17,    18,    85,    36,    37,    38,    39,    40,
      41,    42,    43
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -60
static const yytype_int8 yypact[] =
{
      59,   -60,   -60,   -60,    17,    19,    20,    22,    -7,    47,
      59,   -60,   -60,    44,    27,   -60,   -60,   -60,    45,     9,
       4,     9,     9,     9,   -60,   -60,   -60,    51,   -60,   -60,
     -60,   -60,   -60,     9,     9,    42,    50,    52,    54,   -60,
     -60,    -5,    48,   -60,   -60,    60,   -60,    61,    -3,    52,
       9,     0,    62,   -60,    26,    48,   -60,     9,     9,    26,
      42,    42,     9,   -60,    65,    52,   -60,   -60,    62,    73,
      64,    54,   -60,    58,    48,   -60,    69,   -60,   -60,   -60,
      59,    71,   -60,    43,   -60,    70,   -60,   -60,   -60
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -60,   -60,     7,   -59,   -60,   -10,   -60,    72,   -60,   -60,
     -60,   -60,   -60,   -19,   -60,   -18,   -17,    32,   -27,   -16,
      31,   -33,    30
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      25,    46,    55,    47,    77,    48,    49,    53,    59,     1,
       2,     3,    29,    30,    23,    64,    51,    52,    66,     8,
      82,    60,    57,    31,    32,    57,    33,    74,    88,    29,
      30,    72,    34,    65,    19,    35,    20,    21,    68,    22,
      31,    32,    27,    54,    76,    29,    30,    24,     1,     2,
       3,     4,    35,     5,     6,     7,    31,    32,     8,    54,
      26,    28,    84,    86,     1,     2,     3,     4,    56,     5,
       6,     7,    50,    25,     8,    61,    62,    57,    58,    63,
      67,    78,    79,    80,    60,    81,     8,    83,    87,    71,
      73,    75,    44
};

static const yytype_uint8 yycheck[] =
{
      10,    20,    35,    21,    63,    22,    23,    34,    13,     5,
       6,     7,     3,     4,    21,    18,    33,    33,    18,    15,
      79,    26,    25,    14,    15,    25,    17,    60,    87,     3,
       4,    58,    23,    50,    17,    26,    17,    17,    54,    17,
      14,    15,    15,    17,    62,     3,     4,     0,     5,     6,
       7,     8,    26,    10,    11,    12,    14,    15,    15,    17,
      16,    16,    81,    20,     5,     6,     7,     8,    18,    10,
      11,    12,    21,    83,    15,    27,    16,    25,    24,    18,
      18,    16,     9,    19,    26,    16,    15,    80,    18,    57,
      59,    61,    20
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,     7,     8,    10,    11,    12,    15,    29,
      30,    33,    34,    35,    37,    38,    39,    40,    41,    17,
      17,    17,    17,    21,     0,    33,    16,    15,    16,     3,
       4,    14,    15,    17,    23,    26,    43,    44,    45,    46,
      47,    48,    49,    50,    35,    36,    41,    43,    44,    44,
      21,    44,    47,    46,    17,    49,    18,    25,    24,    13,
      26,    27,    16,    18,    18,    44,    18,    18,    47,    31,
      32,    45,    46,    48,    49,    50,    43,    31,    16,     9,
      19,    16,    31,    30,    41,    42,    20,    18,    31
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 128 "SYN.y"
    {
        (yyval.block).code = (yyvsp[(1) - (1)].block).code;
		perform_label_adding((yyval.block).code, &(yyvsp[(1) - (1)].block).next);
		clear_scope(1);
        // print
		print_code((yyval.block).code);
    }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 136 "SYN.y"
    {
        (yyval.block).code = (yyvsp[(1) - (1)].block).code;
        (yyval.block).next = (yyvsp[(1) - (1)].block).next;

    }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 141 "SYN.y"
    {

        (yyval.block).code = new vector<string *>();
		(yyval.block).next = (yyvsp[(2) - (2)].block).next;
        (yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(1) - (2)].block).code->begin(), (yyvsp[(1) - (2)].block).code->end());
		perform_label_adding((yyval.block).code, &(yyvsp[(1) - (2)].block).next);
        (yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(2) - (2)].block).code->begin(), (yyvsp[(2) - (2)].block).code->end());
    }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 150 "SYN.y"
    {(yyval.block).l_id = sym_num;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 154 "SYN.y"
    {
		//clear scope
		clear_scope((yyval.block).l_id);
        (yyval.block).code = (yyvsp[(3) - (4)].block).code;
        (yyval.block).next = (yyvsp[(3) - (4)].block).next;

	}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 162 "SYN.y"
    {
        (yyval.block).code = (yyvsp[(1) - (2)].block).code;
        (yyval.block).next = (yyvsp[(1) - (2)].block).next;
    }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 165 "SYN.y"
    {
        (yyval.block).code = (yyvsp[(1) - (1)].block).code;
        (yyval.block).next = (yyvsp[(1) - (1)].block).next;
    }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 168 "SYN.y"
    {
        (yyval.block).code = (yyvsp[(1) - (1)].block).code;
        (yyval.block).next = (yyvsp[(1) - (1)].block).next;
    }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 171 "SYN.y"
    {
		(yyval.block).code = (yyvsp[(1) - (1)].block).code;
        (yyval.block).next = (yyvsp[(1) - (1)].block).next;
	}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 174 "SYN.y"
    {
        (yyval.block).code = (yyvsp[(1) - (2)].block).code;
        (yyval.block).next = (yyvsp[(1) - (2)].block).next;
    }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 177 "SYN.y"
    {
        (yyval.block).code = (yyvsp[(1) - (1)].block).code;
        (yyval.block).next = (yyvsp[(1) - (1)].block).next;
	}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 182 "SYN.y"
    {
		if((yyvsp[(3) - (5)].exp).type != ERROR_T){
			(yyval.block).code = new vector<string*>();
			(yyval.block).next = new vector<string*>();
			(yyval.block).code->push_back(new string("getstatic java/lang/System/out Ljava/io/PrintStream;"));
			(yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(3) - (5)].exp).code->begin(), (yyvsp[(3) - (5)].exp).code->end());
			perform_label_adding((yyval.block).code, &(yyvsp[(3) - (5)].exp).next);
			(yyval.block).code->push_back(new string(string("invokevirtual   java/io/PrintStream/println(")
				+ ((yyvsp[(3) - (5)].exp).type ==  FLOAT_T ? "F" : "I")
			 	+")V"));
		}else{
			(yyval.block).code = nullptr;
			(yyval.block).next = nullptr;
		}
	}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 198 "SYN.y"
    {
		string id((yyvsp[(2) - (2)].val));
        if (symbol_table.find(id) != symbol_table.end()){
            (yyval.block).code = nullptr;
            yyerror(("ERROR EXIST BEFORE!! --> "+id).c_str());
        } else {
            // add in symbol table int/float
			string t1 = type_map[(yyvsp[(1) - (2)].pt)];
            pair<int, int> element (make_pair(sym_num, (yyvsp[(1) - (2)].pt)));
            symbol_table.insert({id, element});
			memory_table.insert({sym_num, id});
            vector<string *> *currentcode = new vector<string *>();
            currentcode->push_back(new string(t1 + "const_0"));
            currentcode->push_back(new string(t1 + "store " + to_string(sym_num)));
            sym_num++;
            (yyval.block).code = currentcode;
        }
        (yyval.block).next = nullptr;
    }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 216 "SYN.y"
    {

		string id((yyvsp[(2) - (4)].val));
        if (symbol_table.find(id) != symbol_table.end()){
            (yyval.block).code = nullptr;
            yyerror(("ERROR EXIST BEFORE!! --> "+id).c_str());
        } else {
            // add in symbol table int/float
			int id_type = (yyvsp[(1) - (4)].pt);
			bool casting = ((yyvsp[(4) - (4)].exp).type == INT_T) && (id_type == FLOAT_T);
			bool can_assign = ((yyvsp[(4) - (4)].exp).type == id_type) || casting;
			if(can_assign){
				(yyval.block).code = new vector <string*>();
				(yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(4) - (4)].exp).code->begin(), (yyvsp[(4) - (4)].exp).code->end());
				perform_label_adding((yyval.block).code, &(yyvsp[(4) - (4)].exp).next);
				if(casting){
					(yyval.block).code->push_back(new string("i2f"));
				}
				(yyval.block).code->push_back(new string(type_map[id_type] + "store " + to_string(sym_num)));
				pair<int, int> element (make_pair(sym_num, id_type));
				symbol_table.insert({id, element});
				memory_table.insert({sym_num, id});
				sym_num++;
				(yyval.block).next = nullptr;
			}else{
				(yyval.block).code = nullptr;
				(yyval.block).next = nullptr;
				yyerror(("ERROR CAN'T CASTING!! --> "+id).c_str());
			}
        }
        (yyval.block).next = nullptr;

	}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 250 "SYN.y"
    {
	(yyval.block).code = nullptr;
	(yyval.block).next = nullptr;
}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 253 "SYN.y"
    {
	(yyval.block).code = (yyvsp[(1) - (1)].block).code;
    (yyval.block).next = (yyvsp[(1) - (1)].block).next;
}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 256 "SYN.y"
    {
	(yyval.block).code = (yyvsp[(1) - (1)].block).code;
    (yyval.block).next = (yyvsp[(1) - (1)].block).next;
}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 261 "SYN.y"
    {
        (yyval.pt) = INT_T;
    }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 263 "SYN.y"
    {
        (yyval.pt) = FLOAT_T;
    }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 265 "SYN.y"
    {
		(yyval.pt) = BOOL_T;
	}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 270 "SYN.y"
    {
		(yyval.block).code = new vector<string*>();
		(yyval.block).next = new vector<string*>();
		Label Btrue;
		back_patching(&(yyvsp[(3) - (5)].block).next, Btrue.getName());
		(yyval.block).next->insert((yyval.block).next->end(), (yyvsp[(5) - (5)].block).next->begin(), (yyvsp[(5) - (5)].block).next->end());

		(yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(3) - (5)].block).code->begin(), (yyvsp[(3) - (5)].block).code->end());
		(yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(5) - (5)].block).code->begin(), (yyvsp[(5) - (5)].block).code->end());

		add_label_to_code((yyval.block).code, Btrue);
	}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 284 "SYN.y"
    {

		(yyval.block).code = new vector<string*>();
		(yyval.block).next = new vector<string*>();
		Label Bfalse;
		back_patching(&(yyvsp[(3) - (7)].block).next, Bfalse.getName());
		string * gotoW = new string("goto ");
		(yyval.block).next->insert((yyval.block).next->end(), (yyvsp[(5) - (7)].block).next->begin(), (yyvsp[(5) - (7)].block).next->end());
		(yyval.block).next->insert((yyval.block).next->end(), (yyvsp[(7) - (7)].block).next->begin(), (yyvsp[(7) - (7)].block).next->end());
		(yyval.block).next->push_back(gotoW);

		(yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(3) - (7)].block).code->begin(), (yyvsp[(3) - (7)].block).code->end());
		(yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(5) - (7)].block).code->begin(), (yyvsp[(5) - (7)].block).code->end());
		(yyval.block).code->push_back(gotoW);
		add_label_to_code((yyval.block).code, Bfalse);
		(yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(7) - (7)].block).code->begin(), (yyvsp[(7) - (7)].block).code->end());
    }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 304 "SYN.y"
    {
        (yyval.block).code = new vector<string*>();
        (yyval.block).next = (yyvsp[(3) - (5)].block).next;
        Label Begin;
        back_patching(&(yyvsp[(5) - (5)].block).next, Begin.getName());
        add_label_to_code((yyval.block).code, Begin);
        (yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(3) - (5)].block).code->begin(), (yyvsp[(3) - (5)].block).code->end());
        (yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(5) - (5)].block).code->begin(), (yyvsp[(5) - (5)].block).code->end());
        (yyval.block).code->push_back(new string("goto " + Begin.getName()));
    }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 317 "SYN.y"
    {
        (yyval.block).code = new vector<string*>();
        (yyval.block).next = (yyvsp[(5) - (9)].block).next;
        Label Begin;
        //Label $8.next;
        //back_patching($8.next, Begin.getName());
		if ((yyvsp[(3) - (9)].block).code != nullptr){
			(yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(3) - (9)].block).code->begin(), (yyvsp[(3) - (9)].block).code->end());
		}
        add_label_to_code((yyval.block).code, Begin);
        (yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(5) - (9)].block).code->begin(), (yyvsp[(5) - (9)].block).code->end());
        (yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(9) - (9)].block).code->begin(), (yyvsp[(9) - (9)].block).code->end());
        perform_label_adding((yyval.block).code, &(yyvsp[(9) - (9)].block).next);
		if ((yyvsp[(7) - (9)].block).code != nullptr){
			(yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(7) - (9)].block).code->begin(), (yyvsp[(7) - (9)].block).code->end());
		}
        (yyval.block).code->push_back(new string("goto " + Begin.getName()));
    }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 336 "SYN.y"
    {

		string id((yyvsp[(1) - (3)].val));
		if(symbol_table.find(id) != symbol_table.end()){
			if((yyvsp[(3) - (3)].exp).type != ERROR_T){
				pair<unsigned, int> p= symbol_table[id];
				int id_type  = p.second;
				unsigned id_num = p.first;

				bool casting = ((yyvsp[(3) - (3)].exp).type == INT_T) && (id_type == FLOAT_T);
				bool can_assign = ((yyvsp[(3) - (3)].exp).type == id_type) || casting;

				if(can_assign){
					(yyval.block).code = new vector <string*>();
					(yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(3) - (3)].exp).code->begin(), (yyvsp[(3) - (3)].exp).code->end());
					perform_label_adding((yyval.block).code, &(yyvsp[(3) - (3)].exp).next);

					if(casting){
						(yyval.block).code->push_back(new string("i2f"));
					}

					(yyval.block).code->push_back(new string(type_map[id_type] + "store " + to_string(id_num)));
					(yyval.block).next = nullptr;
				}else{
					(yyval.block).code = nullptr;
					(yyval.block).next = nullptr;
					yyerror(("ERROR CAN'T CASTING!! --> "+id).c_str());
				}

			}
		}else{
			(yyval.block).code = nullptr;
			(yyval.block).next = nullptr;
			yyerror(("ERROR WASN'T DECLARED!! --> "+id).c_str());
		}

    }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 374 "SYN.y"
    {
	(yyval.block).code = nullptr;
	(yyval.block).next = nullptr;
}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 377 "SYN.y"
    {
	(yyval.block).code = (yyvsp[(1) - (1)].block).code;
    (yyval.block).next = (yyvsp[(1) - (1)].block).next;
}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 384 "SYN.y"
    {
    if ((yyvsp[(1) - (1)].exp).type != ERROR_T) {
      if ((yyvsp[(1) - (1)].exp).type != BOOL_T) {
        (yyval.block).code = nullptr;
        (yyval.block).next = nullptr;
        yyerror("Condition doesn't evaluate to boolean ");
      } else {
        (yyval.block).next = new vector<string*>();
        (yyval.block).code = new vector<string*>();
		string * ifeq = new string("ifeq ");
        (yyval.block).next->push_back(ifeq);
        (yyval.block).code->insert((yyval.block).code->end(), (yyvsp[(1) - (1)].exp).code->begin(), (yyvsp[(1) - (1)].exp).code->end());
        perform_label_adding((yyval.block).code, &(yyvsp[(1) - (1)].exp).next);
        (yyval.block).code->push_back(ifeq);
      }
    } else {
      (yyval.block).code = nullptr;
      (yyval.block).next = nullptr;
    }
  }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 405 "SYN.y"
    {
	(yyval.exp).code = (yyvsp[(1) - (1)].exp).code;
	(yyval.exp).type = (yyvsp[(1) - (1)].exp).type;
	(yyval.exp).next = nullptr;
	perform_label_adding((yyval.exp).code, &(yyvsp[(1) - (1)].exp).next);
}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 410 "SYN.y"
    {
	if((yyvsp[(1) - (3)].exp).type == (yyvsp[(3) - (3)].exp).type && (yyvsp[(1) - (3)].exp).type == BOOL_T){

		(yyval.exp).type = BOOL_T;
		Label BFalse;
		(yyval.exp).code = new vector<string*>();
		(yyval.exp).next = new vector<string*>();
		string * gotoW = new string("goto ");

		if((yyvsp[(1) - (3)].exp).next != nullptr){
			(yyval.exp).next->insert((yyval.exp).next->end(), (yyvsp[(1) - (3)].exp).next->begin(), (yyvsp[(1) - (3)].exp).next->end());
		}
		(yyval.exp).next->push_back(gotoW);

		(yyval.exp).code->insert((yyval.exp).code->end(), (yyvsp[(1) - (3)].exp).code->begin(), (yyvsp[(1) - (3)].exp).code->end());
		(yyval.exp).code->push_back(new string("ifne " + BFalse.getName())); // not equal zero
		(yyval.exp).code->push_back(new string("iconst_0"));

		(yyval.exp).code->push_back(gotoW);
		add_label_to_code((yyval.exp).code, BFalse);
		(yyval.exp).code->insert((yyval.exp).code->end(), (yyvsp[(3) - (3)].exp).code->begin(), (yyvsp[(3) - (3)].exp).code->end());
		perform_label_adding((yyval.exp).code, &(yyvsp[(3) - (3)].exp).next);

	}else if ((yyvsp[(1) - (3)].exp).type == (yyvsp[(3) - (3)].exp).type && (yyvsp[(1) - (3)].exp).type != ERROR_T){

		(yyval.exp).type = ERROR_T;
		(yyval.exp).code = nullptr;
		(yyval.exp).next = nullptr;
		yyerror("Invalid logical not on operands");

	}else {
		(yyval.exp).type = ERROR_T;
		(yyval.exp).code = nullptr;
		(yyval.exp).next = nullptr;
	}

}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 447 "SYN.y"
    {
	(yyval.exp).code = (yyvsp[(1) - (1)].factor).code;
	(yyval.exp).type = (yyvsp[(1) - (1)].factor).type;
	(yyval.exp).next = nullptr;
}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 451 "SYN.y"
    {

	if((yyvsp[(1) - (3)].exp).type == (yyvsp[(3) - (3)].factor).type && (yyvsp[(1) - (3)].exp).type == BOOL_T){

		(yyval.exp).type = BOOL_T;
		Label BFalse;
		(yyval.exp).code = new vector<string*>();
		(yyval.exp).next = new vector<string*>();
		string * gotoW = new string("goto ");

		if((yyvsp[(1) - (3)].exp).next != nullptr){
			(yyval.exp).next->insert((yyval.exp).next->end(), (yyvsp[(1) - (3)].exp).next->begin(), (yyvsp[(1) - (3)].exp).next->end());

		}
		(yyval.exp).next->push_back(gotoW);

		(yyval.exp).code->insert((yyval.exp).code->end(), (yyvsp[(1) - (3)].exp).code->begin(), (yyvsp[(1) - (3)].exp).code->end());
		(yyval.exp).code->push_back(new string("ifeq " + BFalse.getName())); // equal zero
		(yyval.exp).code->push_back(new string("iconst_1"));
		(yyval.exp).code->push_back(gotoW);
		add_label_to_code((yyval.exp).code, BFalse);
		(yyval.exp).code->insert((yyval.exp).code->end(), (yyvsp[(3) - (3)].factor).code->begin(), (yyvsp[(3) - (3)].factor).code->end());

	}else if ((yyvsp[(1) - (3)].exp).type == (yyvsp[(3) - (3)].factor).type && (yyvsp[(1) - (3)].exp).type != ERROR_T){

		(yyval.exp).type = ERROR_T;
		(yyval.exp).code = nullptr;
		(yyval.exp).next = nullptr;
		yyerror("Invalid logical not on operands");

	}else {
		(yyval.exp).type = ERROR_T;
		(yyval.exp).code = nullptr;
		(yyval.exp).next = nullptr;
	}
}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 487 "SYN.y"
    {
	(yyval.factor).code = (yyvsp[(1) - (1)].exp).code;
	(yyval.factor).type = (yyvsp[(1) - (1)].exp).type;

}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 491 "SYN.y"
    {
	if ((yyvsp[(2) - (2)].factor).type != ERROR_T){
		if ((yyvsp[(2) - (2)].factor).type != BOOL_T){
			(yyval.factor).type = ERROR_T;
			(yyval.factor).code = nullptr;
			yyerror("Invalid logical not on operands");
		}else {
			(yyval.factor).type = BOOL_T;
			(yyval.factor).code = (yyvsp[(2) - (2)].factor).code;
			Label BTrue, BFalse;
			(yyval.factor).code->push_back(new string("ifeq " + BTrue.getName())); // equal zero
			(yyval.factor).code->push_back(new string("iconst_0"));
			(yyval.factor).code->push_back(new string("goto " + BFalse.getName()));
			add_label_to_code((yyval.factor).code, BTrue);
			(yyval.factor).code->push_back(new string("iconst_1"));
			add_label_to_code((yyval.factor).code, BFalse);
		}
	}else {

		(yyval.factor).type = ERROR_T;
		(yyval.factor).code = nullptr;
	}
}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 513 "SYN.y"
    {
        (yyval.factor).type = (yyvsp[(2) - (3)].exp).type;
        (yyval.factor).code = (yyvsp[(2) - (3)].exp).code;
		perform_label_adding((yyval.factor).code, &(yyvsp[(2) - (3)].exp).next);
}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 518 "SYN.y"
    {
        (yyval.exp).type = (yyvsp[(1) - (1)].exp).type;
        (yyval.exp).code = (yyvsp[(1) - (1)].exp).code;
        (yyval.exp).next = nullptr;
		perform_label_adding((yyval.exp).code, &(yyvsp[(1) - (1)].exp).next);
    }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 523 "SYN.y"
    {
		string rel_op((yyvsp[(2) - (3)].val));
		if ((yyvsp[(1) - (3)].exp).type != ERROR_T && (yyvsp[(3) - (3)].exp).type != ERROR_T) {                                          // != == (bool, int, float)      >= ... (int, float)
			// if two operants are booleans.
			if((yyvsp[(1) - (3)].exp).type == BOOL_T || (yyvsp[(3) - (3)].exp).type == BOOL_T){
				if((yyvsp[(1) - (3)].exp).type != (yyvsp[(3) - (3)].exp).type){
					(yyval.exp).type = ERROR_T;
					(yyval.exp).code = nullptr;
					yyerror("Can't do this operation < "+ rel_op +" > for two diffrent types");					
				}else if(rel_op == "==" || rel_op == "!="){
					(yyval.exp).type = BOOL_T;
					(yyval.exp).code = new vector<string*>();
					(yyval.exp).code->insert((yyval.exp).code->begin(), (yyvsp[(1) - (3)].exp).code->begin(), (yyvsp[(1) - (3)].exp).code->end());
					(yyval.exp).code->insert((yyval.exp).code->end(), (yyvsp[(3) - (3)].exp).code->begin(), (yyvsp[(3) - (3)].exp).code->end());
					Label Btrue, next;
					(yyval.exp).code->push_back(new string ("if_icmp" + real_ops[rel_op] + " " + Btrue.getName()));
					(yyval.exp).code->push_back(new string ("iconst_0"));
					(yyval.exp).code->push_back(new string ("goto " + next.getName()));
					add_label_to_code((yyval.exp).code, Btrue);
					(yyval.exp).code->push_back(new string ("iconst_1"));
					add_label_to_code((yyval.exp).code, next);
				}else{
					(yyval.exp).type = ERROR_T;
					(yyval.exp).code = nullptr;
					yyerror("Can't do this operation < "+ rel_op +" > between booleans");					
				}
			}else {
				// if two operants are int or float.
				bool casting = ((yyvsp[(1) - (3)].exp).type != (yyvsp[(3) - (3)].exp).type);
				(yyval.exp).type = BOOL_T;
				(yyval.exp).code = new vector<string*>();
				(yyval.exp).code->insert((yyval.exp).code->begin(), (yyvsp[(1) - (3)].exp).code->begin(), (yyvsp[(1) - (3)].exp).code->end());
				if (casting && (yyvsp[(1) - (3)].exp).type == INT_T){
					(yyval.exp).code->push_back(new string ("i2f"));
				}
				(yyval.exp).code->insert((yyval.exp).code->end(), (yyvsp[(3) - (3)].exp).code->begin(), (yyvsp[(3) - (3)].exp).code->end());
				if (casting && (yyvsp[(3) - (3)].exp).type == INT_T){
					(yyval.exp).code->push_back(new string ("i2f"));
				}
				Label Btrue, next;
				if(!casting && (yyvsp[(1) - (3)].exp).type == INT_T){
					(yyval.exp).code->push_back(new string ("if_icmp" + real_ops[rel_op] + " " + Btrue.getName()));
					
				}else {
					(yyval.exp).code->push_back(new string ("fcmpl"));
					(yyval.exp).code->push_back(new string ("if" + real_ops[rel_op] + " " + Btrue.getName()));
				}
				(yyval.exp).code->push_back(new string ("iconst_0"));
				(yyval.exp).code->push_back(new string ("goto " + next.getName()));
				add_label_to_code((yyval.exp).code, Btrue);
				(yyval.exp).code->push_back(new string ("iconst_1"));
				add_label_to_code((yyval.exp).code, next);
				
			}
						
		} else {
				(yyval.exp).type = ERROR_T;
				(yyval.exp).code = nullptr;
				yyerror("Can't do this operation for two diffrent types");
			}
	}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 585 "SYN.y"
    {
        (yyval.exp).type = (yyvsp[(1) - (1)].factor).type;
        (yyval.exp).code = (yyvsp[(1) - (1)].factor).code;
		(yyval.exp).next = nullptr;
    }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 589 "SYN.y"
    {
        if ((yyvsp[(2) - (2)].factor).type != BOOL_T){
            (yyval.exp).type = (yyvsp[(2) - (2)].factor).type;
			(yyval.exp).code = (yyvsp[(2) - (2)].factor).code;
            if ((yyvsp[(1) - (2)].cval) == '-'){
                (yyval.exp).code->push_back(new string(type_map[(yyvsp[(2) - (2)].factor).type] + "neg"));
            }
        } else {
            (yyval.exp).type = ERROR_T;
            yyerror("Can't add sign for types nether int nor float");
        }
    }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 600 "SYN.y"
    {
        if ((yyvsp[(1) - (3)].exp).type == (yyvsp[(3) - (3)].factor).type && ((yyvsp[(3) - (3)].factor).type == INT_T || (yyvsp[(3) - (3)].factor).type == FLOAT_T)){
            (yyval.exp).type = (yyvsp[(3) - (3)].factor).type;
			(yyval.exp).code = new vector<string *>();
		    (yyval.exp).code->insert((yyval.exp).code->begin(), (yyvsp[(1) - (3)].exp).code->begin(), (yyvsp[(1) - (3)].exp).code->end());
		    (yyval.exp).code->insert((yyval.exp).code->end(), (yyvsp[(3) - (3)].factor).code->begin(), (yyvsp[(3) - (3)].factor).code->end());
			(yyval.exp).code->push_back(new string(type_map[(yyvsp[(1) - (3)].exp).type] + op_map[(yyvsp[(2) - (3)].cval)]));
        } else {
            (yyval.exp).type = ERROR_T;
			(yyval.exp).code = nullptr;
            yyerror("Can't add two diffrent types nether int nor float");
        }
    }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 613 "SYN.y"
    {
        (yyval.factor).code = (yyvsp[(1) - (1)].factor).code;
        (yyval.factor).type = (yyvsp[(1) - (1)].factor).type;
    }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 616 "SYN.y"
    {
        if ((yyvsp[(1) - (3)].factor).type == (yyvsp[(3) - (3)].factor).type && ((yyvsp[(3) - (3)].factor).type == INT_T || (yyvsp[(3) - (3)].factor).type == FLOAT_T)){
            (yyval.factor).type = (yyvsp[(3) - (3)].factor).type;
			(yyval.factor).code = new vector<string *>();
		    (yyval.factor).code->insert((yyval.factor).code->begin(), (yyvsp[(1) - (3)].factor).code->begin(), (yyvsp[(1) - (3)].factor).code->end());
		    (yyval.factor).code->insert((yyval.factor).code->end(), (yyvsp[(3) - (3)].factor).code->begin(), (yyvsp[(3) - (3)].factor).code->end());
			(yyval.factor).code->push_back(new string(type_map[(yyvsp[(1) - (3)].factor).type] + op_map[(yyvsp[(2) - (3)].cval)]));

        } else {
            (yyval.factor).type = ERROR_T;
			(yyval.factor).code = nullptr;
            yyerror("Can't add two diffrent types nether int nor float");
        }
    }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 630 "SYN.y"
    {
        unordered_map<string, pair<unsigned, int>>::iterator it;
        it = symbol_table.find((yyvsp[(1) - (1)].val));
        if (it != symbol_table.end()){
			int id_type = it->second.second;
			int id_num = it->second.first;
            (yyval.factor).type = id_type;
            (yyval.factor).code = new vector<string *>();
            (yyval.factor).code->push_back(new string(type_map[id_type] + "load " + to_string(id_num)));
            
        } else {
			(yyval.factor).type = ERROR_T;
			(yyval.factor).code = nullptr;
					string str((yyvsp[(1) - (1)].val));
					string msg = "\n ERROR";
					msg +=" WASN'T DECLARED!! -->";
					msg += str;
            yyerror((msg).c_str());
        }
    }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 649 "SYN.y"
    {
        (yyval.factor).code = new vector<string *>();
        (yyval.factor).type = INT_T;
        (yyval.factor).code->push_back(new string("ldc " + to_string((yyvsp[(1) - (1)].ival))));
    }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 653 "SYN.y"
    {
		(yyval.factor).code = new vector<string *>();
		(yyval.factor).type = FLOAT_T;
		(yyval.factor).code->push_back(new string("ldc " + to_string((yyvsp[(1) - (1)].fval))));
    }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 657 "SYN.y"
    {
		(yyval.factor).code = new vector<string *>();
		(yyval.factor).type = BOOL_T;
		string str ((yyvsp[(1) - (1)].val));
		if(str == "true"){
			(yyval.factor).code->push_back(new string("iconst_1"));
		}else{
			(yyval.factor).code->push_back(new string("iconst_0"));
		}
	}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 666 "SYN.y"
    {
        (yyval.factor).type = (yyvsp[(2) - (3)].exp).type;
        (yyval.factor).code = (yyvsp[(2) - (3)].exp).code;
		perform_label_adding((yyval.factor).code, &(yyvsp[(2) - (3)].exp).next);
    }
    break;



/* Line 1455 of yacc.c  */
#line 2362 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 671 "SYN.y"

/* MAIN */
main ()
{
	FILE *myfile;
		myfile = fopen("try.txt", "r");
	if (!myfile) {
		printf("Code file does not exist!\n");
		char path[200];
		if (!getcwd(path, sizeof(path)))
		     {
		     return -1;
		     }
		printf("%s\n",path);
		getchar();
		return -1;
	}
	{ fileOut << ".class public " + string("out") + "\n.super java/lang/Object\n"
    + ".method public <init>()V\naload_0"
    + "\ninvokespecial java/lang/Object/<init>()V\nreturn\n.end"
    + " method\n.method public static main([Ljava/lang/String;)V\n.limit locals 1000\n.limit stack 1000" << endl;
	}
	yyin = myfile;
    yyparse();
	
	fileOut << "return\n.end method" << endl;
	
	system("java -jar jasmin.jar out.j");
	system("java out");
	system("pause");
}

void yyerror(string s)
{
printf(s.c_str());
fileOut << s << endl;
}

void print_code(vector<string *> * code) {
  if (code == nullptr) {
    return;
  } else {
    for (int i = 0; i < code->size(); i++) {
			fileOut<<(*((*code)[i]))<<endl;
    }
  }
}

// -------------Michael Said----------------
void add_label_to_code(vector<string *> *code, Label label){
	string *s = new string(label.getName() + ":");
	code->push_back(s);
}

void perform_label_adding(vector<string *> *code, vector<string *> **next){
	
	if (*next != nullptr && !(*next)->empty()){
		Label label;
		back_patching(next, label.getName());
		add_label_to_code(code, label);
	}
}

void back_patching(vector<string *> **list, string label_name){
	if(*list != nullptr){
		for (unsigned i=0; i < (*list)->size(); i++){
			(*((*(*list))[i])) += label_name;
		}
		// free memory
		delete *list;
		*list = nullptr;
	}
}

void clear_scope(unsigned l_id){
	while(sym_num > l_id){
		sym_num--;
		//remove from tables
		string s = memory_table[sym_num];
		symbol_table.erase(symbol_table.find(s));
		memory_table.erase(memory_table.find(sym_num));
	}
}

//------------------------------------------
