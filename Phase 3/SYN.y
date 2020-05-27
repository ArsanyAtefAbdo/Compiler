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
unordered_map<string, tuple<int, float, int>> symbol_table;
typedef enum {INT_T, FLOAT_T, BOOL_T, ERROR_T} type_enum;
#define maxid 20
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
}

%token <ival> NUM
%token <fval> F_NUM
%token INT FLOAT BOOLEAN IF_WORD ELSE FOR_WORD WHILE_WORD SYSTEM_OUT
%token <val> ADD_OP MUL_OP REL_OP BOOL_OP BOOL ID
%token SEMI_COLON LEFT_BRACKET RIGHT_BRACKET LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET EQUALS OTHER

 /* %type */
%type <block> METHOD_BODY
%type <block> STATEMENT_LIST
%type <block> STATEMENT
%type <block> IF
%type <block> WHILE
%type <block> DECLARATION
%type <block> ASSIGNMENT
%type <pt> PRIMITIVE_TYPE
%type <exp> EXPRESSION
%type <exp> SIMPLE_EXPRESSION
%type <factor> TERM
%type <factor> FACTOR
%type <val> SIGN

%%

METHOD_BODY:
    STATEMENT_LIST {
        $$.code = $1.code;
        // print
    };
STATEMENT_LIST:
    STATEMENT {
        $$.code = $1.code;
        $$.next = $1.next;
        //print
    }
    | STATEMENT_LIST STATEMENT{
        vector<string *> *currentcode = new vector<string *>();
        currentcode->insert(currentcode->begin(), $1.code->begin(), $1.code->end());
        currentcode->insert(currentcode->end(), $2.code->begin(), $2.code->end());
        $$.code = currentcode;
        $$.next = $2.next;
        // print
    };
STATEMENT :
    DECLARATION {
        $$.code = $1.code;
        $$.next = $1.next;
    } | IF {
        $$.code = $1.code;
        $$.next = $1.next;
    } | WHILE {
        $$.code = $1.code;
        $$.next = $1.next;
    } | ASSIGNMENT{
        $$.code = $1.code;
        $$.next = $1.next;
    };
DECLARATION :
    PRIMITIVE_TYPE ID SEMI_COLON {
        unordered_map<string, tuple<int, float, int>>::iterator it;
        it = symbol_table.find($2);
        if (it != symbol_table.end()){
            $$.code = nullptr;
						string str($2, $2 + maxid);
            yyerror((str + " EXIST BEFORE!!").c_str());
        } else {
            // add in symbol table int/float
						string str($2, $2 + maxid);
            string key = str;
						string t1;
						if ($1 == INT_T){
							 t1.push_back('i');
						} else if ($1 == FLOAT_T){
					  	 t1.push_back('f');
			  		} else if ($1 == BOOL_T){
					  	 t1.push_back('b');
						}
            tuple<int, float, int> element (make_tuple(sym_num, 0, $1));
            symbol_table.insert({key, element});
            vector<string *> *currentcode = new vector<string *>();
            currentcode->push_back(new string(t1 + "const_0"));
            currentcode->push_back(new string(t1 + "store" + to_string(sym_num)));
            sym_num++;
            $$.code = currentcode;
        }
        $$.next = nullptr;
    };
PRIMITIVE_TYPE :
    INT {
        $$ = INT_T;
    }| FLOAT{
        $$ = FLOAT_T;
    };
IF :
    IF_WORD LEFT_BRACKET EXPRESSION RIGHT_BRACKET
    LEFT_CURLY_BRACKET STATEMENT RIGHT_CURLY_BRACKET
    ELSE LEFT_CURLY_BRACKET STATEMENT RIGHT_CURLY_BRACKET {
        if ($3.type == BOOL_T){
					/// if true add its code
                $$.code = $6.code;
                $$.next = $6.next;
					/// if false
                $$.code = $10.code;
                $$.next = $10.next;
        } else {
            yyerror("Expression incorrect");
        }
    };
WHILE :
    WHILE_WORD LEFT_BRACKET EXPRESSION RIGHT_BRACKET
    LEFT_CURLY_BRACKET STATEMENT RIGHT_CURLY_BRACKET
    {
        // optional
    };
ASSIGNMENT : ID EQUALS EXPRESSION SEMI_COLON {
        unordered_map<string, tuple<int, float, int>>::iterator it;
        it = symbol_table.find($1);
        if (it != symbol_table.end()){
            // bytecode of assignment
        } else {
					string str($1, $1 + maxid);
            yyerror((str + " WASN'T DECLARED!!").c_str());
        }
    };
EXPRESSION : SIMPLE_EXPRESSION {
        $$.type = $1.type;
        $$.code = $1.code;
        $$.next = $$.next;
    }| SIMPLE_EXPRESSION REL_OP SIMPLE_EXPRESSION {
    if ($1.type == $3.type) {
        $$.type = BOOL_T;
				string t1;
				if ($1.type == INT_T){
					 t1.push_back('i');
				} else if ($1.type == FLOAT_T){
					 t1.push_back('f');
				} else if ($1.type == BOOL_T){
					 t1.push_back('b');
				}
				$$.code->push_back(new string(t1 + "load_1")); // EXPRESSION MEM_NUMBER?
				$$.code->push_back(new string(t1 + "load_2"));
				string str($2, $2 + 2);
        if(str == "==") {
              $$.code->push_back(new string ("if_" + t1 + "cmpe"));
						} else if (str == "!="){
              $$.code->push_back(new string ("if_" + t1 + "cmpne"));
						} else if (str == ">="){
              $$.code->push_back(new string ("if_" + t1 + "cmpge"));
          	} else if (str == "<="){
              $$.code->push_back(new string ("if_" + t1 + "cmple"));
          	} else if (str == ">"){
              $$.code->push_back(new string ("if_" + t1 + "cmpg"));
          	} else if (str == "<"){
              $$.code->push_back(new string ("if_" + t1 + "cmpl"));
						}
        	} else {
            $$.type = ERROR_T;
            yyerror("Can't do this operation for two diffrent types");
        }
    };
SIMPLE_EXPRESSION :
    TERM {
        $$.type = $1.type;
        $$.code = $1.code;
    }| SIGN TERM {
        if ($2.type == INT_T || $2.type == FLOAT_T){
            $$.type = $2.type;
            if ($1 == "-"){
                $$.code = $2.code; /// is there a change in bytecode?!
            } else {
                $$.code = $2.code;
            }
        } else {
            $$.type = ERROR_T;
            yyerror("Can't add sign for types nether int nor float");
        }
    }| SIMPLE_EXPRESSION ADD_OP TERM {
        if ($1.type == $3.type && ($3.type == INT_T || $3.type == FLOAT_T)){
            $$.type = $3.type;
						vector<string *> *currentcode = new vector<string *>();
		        currentcode->insert(currentcode->begin(), $1.code->begin(), $1.code->end());
		        currentcode->insert(currentcode->end(), $3.code->begin(), $3.code->end());
						string t1;
						if ($1.type == INT_T){
							 t1.push_back('i');
						} else if ($1.type == FLOAT_T){
							 t1.push_back('f');
						} else if ($1.type == BOOL_T){
							 t1.push_back('b');
						}
            if ($2 = "-"){
                currentcode->push_back(new string(t1 + "sub"));
            } else {
                currentcode->push_back(new string(t1 + "add"));
            }
						$$.code = currentcode;
        } else {
            $$.type = ERROR_T;
            yyerror("Can't add two diffrent types nether int nor float");
        }
    };
TERM : FACTOR {
        $$.code = $1.code;
        $$.type = $1.type;
    }| TERM MUL_OP FACTOR {
        if ($1.type == $3.type && ($3.type == INT_T || $3.type == FLOAT_T)){
            $$.type = $3.type;
						vector<string *> *currentcode = new vector<string *>();
		        currentcode->insert(currentcode->begin(), $1.code->begin(), $1.code->end());
		        currentcode->insert(currentcode->end(), $3.code->begin(), $3.code->end());
						string t1;
						if ($1.type == INT_T){
							 t1.push_back('i');
						} else if ($1.type == FLOAT_T){
							 t1.push_back('f');
						} else if ($1.type == BOOL_T){
							 t1.push_back('b');
						}
            if ($2 = "*"){
                currentcode->push_back(new string(t1 + "mul"));
            } else if ($2 = "/"){
                currentcode->push_back(new string(t1 + "div"));
            } else {
                currentcode->push_back(new string(t1 + "mod"));
            }
						$$.code = currentcode;
        } else {
            $$.type = ERROR_T;
            yyerror("Can't add two diffrent types nether int nor float");
        }
    };
FACTOR : ID {
        unordered_map<string, tuple<int, float, int>>::iterator it;
        it = symbol_table.find($1);
        if (it != symbol_table.end()){
					int t = std::get<2>(it->second);
					string t1;
					if (t == INT_T){
						 t1.push_back('i');
					} else if (t == FLOAT_T){
						 t1.push_back('f');
					} else if (t == BOOL_T){
						 t1.push_back('b');
					}
            $$.type = INT_T; /// change it to right type
            vector<string *> *currentcode = new vector<string *>();
						string str($1, $1 + maxid);
            currentcode->push_back(new string($$.type + "load_" + str));
            $$.code = currentcode;
        } else {
					string str($1, $1 + maxid);
            yyerror((str + " WASN'T DECLARED!!").c_str());
        }
    }| NUM {
        $$.code = new vector<string *>();
        $$.type = INT_T;
				string str($1, $1 + maxid);
        $$.code->push_back(new string("ldc " + str));
    }| F_NUM {
			$$.code = new vector<string *>();
			$$.type = FLOAT_T;
			string str($1, $1 + maxid);
			$$.code->push_back(new string("ldc " + str));
    }| LEFT_BRACKET EXPRESSION RIGHT_BRACKET {
        $$.type = $2.type;
        $$.code = $2.code;
    };
 SIGN : ADD_OP {
	    char * v = $1;
	 		$$ = v;
    };
%%
/* MAIN */
void yyerror(const char *s)
{
printf("Error\n");
exit(1);
}
