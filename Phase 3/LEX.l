%{
/* flex LEX.l
  bison -dy SYN.y
g++ -Wno-write-strings -std=gnu++11 lex.yy.c y.tab.c */
/* C stuff */
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include <string.h>
    #include "y.tab.h"
     extern "C" int yyparse (void);
    void yyerror(const char*);
     void showError();
%}
 /* Regular Expressions */
letter   [a-zA-Z]
digit    [0-9]
id       {letter}({letter}|{digit})*
digits   {digit}+
num      "-"?{digits}
fnum     "-"?{digits}.{digits}("E"{digits}+)?
relop    "=="|"!="|">"|">="|"<"|"<="
assign   "="
boolop   "&&"|"||"
addop    "+"|"-"
mulop    "*"|"/"|"%"
bool     "true"|"false"
%%
 /* Token Specifications */
"int"	                {return INT;}
"float"             	{return FLOAT;}
"boolean"               {return BOOLEAN;}
"if"                	{return IF_WORD;}
"else"              	{return ELSE;}
"for"	                {return FOR_WORD;}
"while"	                {return WHILE_WORD;}
"System.out.println"	{return SYSTEM_OUT;}
";"                     {return SEMI_COLON;}
"("                     {return LEFT_BRACKET;}
")"                     {return RIGHT_BRACKET;}
"{"                     {return LEFT_CURLY_BRACKET;}
"}"                     {return RIGHT_CURLY_BRACKET;}
{fnum}                  {yylval.fval = atof(yytext); return F_NUM;}
{relop}                 {yylval.val = yytext;return REL_OP;}
{boolop}                {yylval.val = yytext;return BOOL_OP;}
{bool}                  {yylval.val = yytext;return BOOL;}
{id}                    {yylval.val = strdup(yytext);return ID;}
{addop}                 {yylval.val = yytext;return ADD_OP;}
{mulop}                 {yylval.val = yytext;return MUL_OP;}
{num}                   {yylval.ival = atoi(yytext); return NUM;}
{assign}                {return EQUALS;}
\n                      {;}
%%
 /* C functions */
/* int main(void)
{
yyparse();
return 0;
} */

int yywrap(void)
{
return 1;
}


void showError()
{
printf("Error: invalid input\n");
}
