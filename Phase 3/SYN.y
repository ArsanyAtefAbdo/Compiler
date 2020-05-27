%{
/* C stuff */
#include <stdio.h>
#include <string>
#include <tuple>
#include <unordered_map>
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
extern int yylex();
void yyerror(const char*);
extern "C" int yyparse (void);
int sym_num = 1;
///           name          num  value  type
unordered_map<string, tuple<int, float, string>> symbol_table;

%}

%code requires {
	#include <vector>
	using namespace std;
}

%start METHOD_BODY

%union{

    int ival;     // int
	float fval;   // float
	char * val;   // value
    char * type;  // type --> ADD_OP MUL_OP NUM F_NUM REL_OP BOOL_OP BOOL ID
    struct {
        string *type;    // int, float,   bool,    basic
        string *value;   // 5,    1.5,  true|false  null
        vector<string *> *code; // bytecode for this non terminal
        vector<string *> *next;
  } non_terminal;
}

%token <ival> NUM
%token <fval> F_NUM
%token INT FLOAT BOOLEAN IF_WORD ELSE FOR_WORD WHILE_WORD SYSTEM_OUT
%token <val> ADD_OP MUL_OP REL_OP BOOL_OP BOOL ID
%token SEMI_COLON LEFT_BRACKET RIGHT_BRACKET LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET EQUALS OTHER

 /* %type */
%type <non_terminal> METHOD_BODY
%type <non_terminal> STATEMENT_LIST
%type <non_terminal> STATEMENT
%type <non_terminal> IF
%type <non_terminal> WHILE
%type <non_terminal> DECLARATION
%type <non_terminal> ASSIGNMENT
%type <non_terminal> PRIMITIVE_TYPE
%type <non_terminal> EXPRESSION
%type <non_terminal> SIMPLE_EXPRESSION
%type <non_terminal> TERM
%type <non_terminal> FACTOR
%type <non_terminal> SIGN

%%

METHOD_BODY:
    STATEMENT_LIST {
        /* $$.type = "basic";
        $$.code = $1.code;
        // print  */
    };
STATEMENT_LIST:
    STATEMENT {
        /* $$.type = new string("basic");
        $$.code = $1.code;
        $$.next = $1.next;
        //print */
    }
    | STATEMENT_LIST STATEMENT{
        /* $$.type = new string("basic");
        vector<string *> *currentcode = new vector<string *>();
        currentcode->insert(currentcode->begin(), $1.code->begin(), $1.code->end());
        currentcode->insert(currentcode->end(), $2.code->begin(), $2.code->end());
        $$.code = currentcode;
        $$.next = $2.next;
        // print */
    };
STATEMENT :
    DECLARATION {
        /* $$.type = new string("basic");
        $$.code = $1.code;
        $$.next = $1.next; */
    } | IF {
        /* $$.type = new string("basic");
        $$.code = $1.code;
        $$.next = $1.next; */
    } | WHILE {
        /* $$.type = new string("basic");
        $$.code = $1.code;
        $$.next = $1.next; */
    } | ASSIGNMENT{
        /* $$.type = new string("basic");
        $$.code = $1.code;
        $$.next = $1.next; */
    };
DECLARATION :
    PRIMITIVE_TYPE ID SEMI_COLON {
        /* unordered_map<string, tuple<int, float, string>>::iterator it;
        it = symbol_table.find($2.val);
        if (it != symbol_table.end()){
            $$.type = new string("basic");
            $$.code = nullptr;
            yyerror($2.val + " EXIST BEFORE!!");
        } else {
            $$.type = new string("basic");
            // add in symbol table int/float
            string key = $2.val;
            tuple<int, float, string> element (make_tuple(sym_num, 0, $1.type));
            symbol_table.insert({key, element});
            vector<string *> *currentcode = new vector<string *>();
            currentcode->push_back(new string($1.type + "const_0"));
            currentcode->push_back(new string($1.type + "store" + to_string(sym_num)));
            sym_num++;
            $$.code = currentcode;
        }
        $$.next = nullptr; */
    };
PRIMITIVE_TYPE :
    INT {
        $$.type = new string("i");
    }| FLOAT{
        $$.type = new string("f");
    };
IF :
    IF_WORD LEFT_BRACKET EXPRESSION RIGHT_BRACKET
    LEFT_CURLY_BRACKET STATEMENT RIGHT_CURLY_BRACKET
    ELSE LEFT_CURLY_BRACKET STATEMENT RIGHT_CURLY_BRACKET {
        /* if (*$3.type == "bool"){
            $$.type = new string("basic");
            if ($3.val == "true"){ // or 1
                $$.code = $6.code;
                $$.next = $6.next;
            } else if ($3.val == "false"){
                $$.code = $10.code;
                $$.next = $10.next;
            }
        } else {
            yyerror("Expression incorrect");
        } */
    };
WHILE :
    WHILE_WORD LEFT_BRACKET EXPRESSION RIGHT_BRACKET
    LEFT_CURLY_BRACKET STATEMENT RIGHT_CURLY_BRACKET
    {
        // optional
    };
ASSIGNMENT : ID EQUALS EXPRESSION SEMI_COLON {
        /* unordered_map<string, tuple<int, float, string>>::iterator it;
        it = symbol_table.find($1.val);
        if (it != symbol_table.end()){
            std::get<1>(it->second) = $3.value;
        } else {
            yyerror($1.val + " WASN'T DECLARED!!");
        } */
    };
EXPRESSION : SIMPLE_EXPRESSION {
        /* $$.type = $1.type;
        $$.code = $1.code;
        $$.next = $$.next; /// not sure */
    }| SIMPLE_EXPRESSION REL_OP SIMPLE_EXPRESSION {
    /* if (*$1.type == *$2.type) {
        $$.type = new string("bool");
        float v1 = atof(*$1.value);
        float v2 = atof(*$3.value);
        string t1 = *$1.type;
        string t2 = *$3.type;
        switch(REL_OP.val) {
           case "=="  :
              if (v1 == v2){
                $$.value = new string("true");
              } else {
                $$.value = new string("false");
              }
              $$.code->push_back(new string(t1 + "load_1"));
              $$.code->push_back(new string(t2 + "load_2"));
              $$.code->push_back("if_" + t1 + "cmpe");
              break;
           case "!="  :
              if (v1 != v2){
                $$.value = new string("true");
              } else {
                $$.value = new string("false");
              }
              $$.code.push_back(new string(t1 + "load_1"));
              $$.code.push_back(new string(t2 + "load_2"));
              $$.code.push_back("if_" + t1 + "cmpne");
              break;
           case ">="  :
             if (v1 != v2){
                $$.value = new string("true");
              } else {
                $$.value = new string("false");
              }
              $$.code.push_back(new string(t1 + "load_1"));
              $$.code.push_back(new string(t2 + "load_2"));
              $$.code.push_back("if_" + t1 + "cmpge");
              break;
           case "<="  :
              if (v1 <= v2){
                  $$.value = new string("true");
              } else {
                $$.value = new string("false");
              }
              $$.code.push_back(new string(t1 + "load_1"));
              $$.code.push_back(new string(t2 + "load_2"));
              $$.code.push_back("if_" + t1 + "cmple");
              break;
           case ">"  :
              if (v1 > v2){
              	$$.value = new string("true");
              } else {
                $$.value = new string("false");
              }
              $$.code.push_back(new string(t1 + "load_1"));
              $$.code.push_back(new string(t2 + "load_2"));
              $$.code.push_back("if_" + t1 + "cmpg");
              break;
           case "<"  :
              if (v1 < v2){
                $$.value = new string("true");
              } else {
                $$.value = new string("false");
              }
              $$.code.push_back(new string(t1 + "load_1"));
              $$.code.push_back(new string(t2 + "load_2"));
              $$.code.push_back("if_" + t1 + "cmpl");
              break;
            }
        } else {
            $$.type = new string("error");
            yyerror("Can't do this operation for two diffrent types");
        } */
    };
SIMPLE_EXPRESSION :
    TERM {
        /* $$.type = $1.type;
        $$.code = $1.code;
        $$.next = $1.nest; // not sure */
    }| SIGN TERM {
        /* if (*$2.type == "i" || *$2.type == "f"){
            $$.type = $2.type;
            if (*$1.value == "neg"){
                $$.value = (-1) * $1.value;
                $$.code = $1.code; /// is there a change in bytecode?!
            } else {
                $$.value = $1.value;
                $$.code = $1.code;
            }
            $$.next = $1.nest; // not sure
        } else {
            $$.type = "error";
            yyerror("Can't add sign for types nether int nor float");
        } */
    }| SIMPLE_EXPRESSION ADD_OP TERM {
        /* if ($1.type == $3.type && ($3.type == "i" || $3.type == "f")){
            $$.type = $3.type;
            vector<string *> currentcode = new vector<string *>();
            currentcode.push_back($1.code);
            currentcode.push_back($3.code);
            $$.code = currentcode;
            $$.next = $3.next;
            if ($2.val = "-"){
                $$.value = $1.value - $3.value;
                currentcode.push_back(new string($1.type + "sub"));
            } else {
                $$.value = $1.value + $3.value;
                currentcode.push_back(new string($1.type + "add"));
            }
        } else {
            $$.type = "error";
            yyerror("Can't add two diffrent types nether int nor float");
        } */
    };
TERM : FACTOR {
        /* $$.code = $1.code;
        $$.type = $1.type;
        $$.next = $1.next;
        $$.value = $1.value; */
    }| TERM MUL_OP FACTOR {
        /* if ($1.type == $3.type && ($3.type == "i" || $3.type == "f")){
            $$.type = $3.type;
            vector<string *> currentcode = new vector<string *>();
            currentcode.push_back($1.code);
            currentcode.push_back($3.code);
            $$.code = currentcode;
            $$.next = $3.next;
            if ($2.val = "*"){
                $$.value = $1.value * $3.value;
                currentcode.push_back(new string($1.type + "mul"));
            } else if ($2.val = "/"){
                $$.value = $1.value / $3.value;
                currentcode.push_back(new string($1.type + "div"));
            } else {
                $$.value = $1.value % $3.value;
                currentcode.push_back(new string($1.type + "mod"));
            }
        } else {
            $$.type = "error";
            yyerror("Can't add two diffrent types nether int nor float");
        } */
    };
FACTOR : ID {
        /* string t;
        unordered_map<string, tuple<int, float, string>>::iterator it;
        it = symbol_table.find($1.val);
        if (it != symbol_table.end()){
            $$.type = std::get<2>(it->second);
            $$.value = std::get<1>(it->second);
            vector<string *> currentcode = new vector<string *>();
                  string *s = new string($$.type + "load_" + to_string($$.value));
                  currentcode.push_back(s);
                  $$.code = currentcode;
        } else {
            yyerror($1.val + " WASN'T DECLARED!!");
        } */
    }| NUM {
        /* $$.code = new vector<string *>();
        $$.type = "i";
        string *s = new string("ldc " + to_string($1));
        $$.code->push_back(s);
        $$.value = $1.ival; */
    }| F_NUM {
        /* $$.code = new vector<string *>();
        $$.type = "f";
        string *s = new string("ldc " + to_string($1));
        $$.code->push_back(s);
        $$.value = $1.ival; */
    }| LEFT_BRACKET EXPRESSION RIGHT_BRACKET {
        /* $$.type = $2.type;
        $$.code = $2.code;
        $$.value = $2.value; */
    };
 SIGN : ADD_OP {

    };
%%
/* MAIN */
void yyerror(const char *s)
{
printf("Error\n");
exit(1);
}