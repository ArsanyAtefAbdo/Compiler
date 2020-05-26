%{
/* C stuff */
#include <stdio.h>
#include <string>
extern int yylex();
void yyerror(const char*);
extern "C" int yyparse (void);
%}

%code requires {
	#include <vector>
	using namespace std;
}

%union{

    int ival;     // int
	float fval;   // float
	char * val;   // value
    char * type;  // type --> ADD_OP MUL_OP NUM F_NUM REL_OP BOOL_OP BOOL ID
    struct {
        vector<string *> *code;
        vector<string *> *next;
  } Basic_nt;
}

%token <ival> NUM
%token <fval> F_NUM 
%token INT FLOAT BOOLEAN IF_WORD ELSE FOR_WORD WHILE_WORD SYSTEM_OUT
%token <val> ADD_OP MUL_OP REL_OP BOOL_OP BOOL ID
%token SEMI_COLON LEFT_BRACKET RIGHT_BRACKET LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET EQUALS OTHER

 /* %type */
%type <Basic_nt> STATEMENT_LIST
%type <Basic_nt> STATEMENT
%type <Basic_nt> DECLARATION
%type <Basic_nt> ASSIGNMENT
 /* %type PRIMITIVE_TYPE %type EXPRESSION %type SIMPLE_EXPRESSION %type TERM %type FACTOR %type SIGN */

%%

METHOD_BODY:
    STATEMENT_LIST
    ;
STATEMENT_LIST:
    STATEMENT | STATEMENT_LIST STATEMENT
    ;
STATEMENT :
    DECLARATION | IF_WORD | WHILE_WORD | ASSIGNMENT
    ; 
DECLARATION :
    PRIMITIVE_TYPE ID
    ; 
PRIMITIVE_TYPE :
    INT | FLOAT
    ;
IF :
    IF_WORD LEFT_BRACKET EXPRESSION RIGHT_BRACKET 
    LEFT_CURLY_BRACKET STATEMENT RIGHT_CURLY_BRACKET
    ELSE LEFT_CURLY_BRACKET STATEMENT RIGHT_CURLY_BRACKET 
    ;
WHILE :
    WHILE_WORD LEFT_BRACKET EXPRESSION RIGHT_BRACKET 
    LEFT_CURLY_BRACKET STATEMENT RIGHT_CURLY_BRACKET 
    ;
ASSIGNMENT :
    ID EQUALS EXPRESSION
    ; 
EXPRESSION : SIMPLE_EXPRESSION  | SIMPLE_EXPRESSION REL_OP SIMPLE_EXPRESSION
    { printf("EXP\n"); return 0;}
    ;
SIMPLE_EXPRESSION : TERM | SIGN TERM | SIMPLE_EXPRESSION ADD_OP TERM  
    { printf("S_EXP\n"); return 0;}
    ;
TERM : FACTOR | TERM MUL_OP FACTOR
    { printf("TERM\n"); return 0;}
    ;
FACTOR : ID | NUM | LEFT_BRACKET EXPRESSION RIGHT_BRACKET
    { printf("FACTOR\n"); return 0;}
    ;
SIGN : ADD_OP 
    { printf("SIGN\n"); return 0;}
    ; 
%%
/* MAIN */
void yyerror(const char *s)
{
printf("Error\n");
exit(1);
}