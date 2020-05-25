%{
**** C stuff ****
#include <stdio.h>
#include <bits/stdc++.h>
#include "y.tab.h"
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
{fnum}                  {yylval.val = yytext;yylval.fval = atof(yytext); return F_NUM;}
{relop}                 {yylval.val = yytext;yylval.type = "REL_OP"; return REL_OP;}
{boolop}                {yylval.val = yytext;yylval.type = "BOOL_OP"; return BOOL_OP;}
{bool}                  {yylval.val = yytext;yylval.type = "BOOL"; return BOOL;}
{id}                    {yylval.val = yytext;yylval.type = "ID";return ID;}
{addop}                 {yylval.val = yytext;yylval.type = "ADD_OP"; return ADD_OP;}
{mulop}                 {yylval.val = yytext;yylval.type = "MUL_OP"; return MUL_OP;}
{num}                   {yylval.val = yytext;yylval.ival = atoi(yytext); return NUM;}
{assign}                {return EQUALS;}
.                       {showError(); return (OTHER);}
%%
**** C functions ****
int main(void)
{
yyparse();
return 0;
}

void showError()
{
printf("Error: invalid input");
}