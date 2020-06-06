%{
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
  pair<char,string>('%', "mod")
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

%}

%code requires {
	#include <vector>
	#include <string>
	#include "Label.h"
	using namespace std;
}

%start METHOD_BODY

%union{

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
}

%token <ival> NUM
%token <fval> F_NUM
%token INT FLOAT BOOLEAN IF_WORD ELSE FOR_WORD WHILE_WORD SYSTEM_OUT
%token <val>  REL_OP BOOL_OP BOOL ID
%token SEMI_COLON LEFT_BRACKET RIGHT_BRACKET LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET EQUALS OTHER NOT
%token <cval> ADD_OP MUL_OP

 /* %type */
%type <block> METHOD_BODY
%type <block> STATEMENT_LIST
%type <block> STATEMENT
%type <block> SYSTEM_PRINT
%type <block> IF
%type <block> WHILE
%type <block> FOR
%type <block> DECLARATION
%type <block> ASSIGNMENT
%type <block> BLOCK
%type <block> BOOLEAN_CONDITION
%type <pt> PRIMITIVE_TYPE
%type <exp> EXPRESSION
//%type <exp> SIMPLE_BOOLEAN_EXPRESSION
//%type <exp> BOOLEAN_TERM
%type <exp> SIMPLE_EXPRESSION
%type <factor> TERM
%type <factor> FACTOR

%%

METHOD_BODY:
    STATEMENT_LIST {
        $$.code = $1.code;
		perform_label_adding($$.code, &$1.next);
		clear_scope(1);
        // print
		print_code($$.code);
    };
STATEMENT_LIST:
    STATEMENT {
        $$.code = $1.code;
        $$.next = $1.next;
		
    }
    | STATEMENT_LIST STATEMENT{
        $$.code = new vector<string *>();
		$$.next = $2.next;
        $$.code->insert($$.code->end(), $1.code->begin(), $1.code->end());
		perform_label_adding($$.code, &$1.next);
        $$.code->insert($$.code->end(), $2.code->begin(), $2.code->end());
    };
BLOCK : 
	{$<block>$.l_id = sym_num;}
	LEFT_CURLY_BRACKET
	STATEMENT_LIST
	RIGHT_CURLY_BRACKET
	{
		//clear scope
		clear_scope($$.l_id);
        $$.code = $3.code;
        $$.next = $3.next;
		
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
    } | SYSTEM_PRINT{
        $$.code = $1.code;
        $$.next = $1.next;	
	};
SYSTEM_PRINT:
	SYSTEM_OUT LEFT_BRACKET EXPRESSION RIGHT_BRACKET SEMI_COLON {
		if($3.type != ERROR_T){
			$$.code = new vector<string*>();
			$$.next = new vector<string*>();
			$$.code->push_back(new string("getstatic java/lang/System/out Ljava/io/PrintStream;"));
			$$.code->insert($$.code->end(), $3.code->begin(), $3.code->end());
			perform_label_adding($$.code, &$3.next);
			$$.code->push_back(new string(string("invokevirtual   java/io/PrintStream/println(") 
				+ ($3.type ==  FLOAT_T ? "F" : "I")
			 	+")V"));
		}else{
			$$.code = nullptr;
			$$.next = nullptr;
		}
	};
DECLARATION :
    PRIMITIVE_TYPE ID SEMI_COLON {
		string id($2);
        if (symbol_table.find(id) != symbol_table.end()){
            $$.code = nullptr;
            yyerror(("ERROR EXIST BEFORE!! --> "+id).c_str());
        } else {
            // add in symbol table int/float
			string t1 = type_map[$1];
            pair<int, int> element (make_pair(sym_num, $1));
            symbol_table.insert({id, element});
			memory_table.insert({sym_num, id});
            vector<string *> *currentcode = new vector<string *>();
            currentcode->push_back(new string(t1 + "const_0"));
            currentcode->push_back(new string(t1 + "store " + to_string(sym_num)));
            sym_num++;
            $$.code = currentcode;
        }
        $$.next = nullptr;
    } | PRIMITIVE_TYPE ID EQUALS EXPRESSION SEMI_COLON {
		
		string id($2);
        if (symbol_table.find(id) != symbol_table.end()){
            $$.code = nullptr;
            yyerror(("ERROR EXIST BEFORE!! --> "+id).c_str());
        } else {
            // add in symbol table int/float
			int id_type = $1;
			bool casting = ($4.type == INT_T) && (id_type == FLOAT_T);
			bool can_assign = ($4.type == id_type) || casting;
			if(can_assign){
				$$.code = new vector <string*>();
				$$.code->insert($$.code->end(), $4.code->begin(), $4.code->end());
				perform_label_adding($$.code, &$4.next);
				if(casting){
					$$.code->push_back(new string("i2f"));
				}
				$$.code->push_back(new string(type_map[id_type] + "store " + to_string(sym_num)));
				pair<int, int> element (make_pair(sym_num, id_type));
				symbol_table.insert({id, element});
				memory_table.insert({sym_num, id});	
				sym_num++;
				$$.next = nullptr;
			}else{
				$$.code = nullptr;
				$$.next = nullptr;
				yyerror(("ERROR CAN'T CASTING!! --> "+id).c_str());					
			}
        }
        $$.next = nullptr;
		
	};
PRIMITIVE_TYPE :
    INT {
        $$ = INT_T;
    }| FLOAT{
        $$ = FLOAT_T;
    } | BOOLEAN {
		$$ = BOOL_T;
	};
IF :
	IF_WORD LEFT_BRACKET BOOLEAN_CONDITION RIGHT_BRACKET
    BLOCK {
		$$.code = new vector<string*>();
		$$.next = new vector<string*>();
		Label Btrue;
		back_patching(&$3.next, Btrue.getName());
		$$.next->insert($$.next->end(), $5.next->begin(), $5.next->end());
		
		$$.code->insert($$.code->end(), $3.code->begin(), $3.code->end());
		$$.code->insert($$.code->end(), $5.code->begin(), $5.code->end());

		add_label_to_code($$.code, Btrue);
	} | 
	IF_WORD LEFT_BRACKET BOOLEAN_CONDITION RIGHT_BRACKET
    BLOCK
    ELSE BLOCK {
		
		$$.code = new vector<string*>();
		$$.next = new vector<string*>();
		Label Bfalse;
		back_patching(&$3.next, Bfalse.getName());
		string * gotoW = new string("goto ");
		$$.next->insert($$.next->end(), $5.next->begin(), $5.next->end());
		$$.next->insert($$.next->end(), $7.next->begin(), $7.next->end());
		$$.next->push_back(gotoW);
				
		$$.code->insert($$.code->end(), $3.code->begin(), $3.code->end());
		$$.code->insert($$.code->end(), $5.code->begin(), $5.code->end());
		$$.code->push_back(gotoW);
		add_label_to_code($$.code, Bfalse);
		$$.code->insert($$.code->end(), $7.code->begin(), $7.code->end());
    };
WHILE :
    WHILE_WORD LEFT_BRACKET BOOLEAN_CONDITION RIGHT_BRACKET
    BLOCK
    {
        $$.code = new vector<string*>();
        $$.next = $3.next;
        Label Begin;
        back_patching(&$5.next, Begin.getName());
        add_label_to_code($$.code, Begin);
        $$.code->insert($$.code->end(), $3.code->begin(), $3.code->end());
        $$.code->insert($$.code->end(), $5.code->begin(), $5.code->end());
        $$.code->push_back(new string("goto " + Begin.getName()));
    };
FOR :
    FOR_WORD LEFT_BRACKET STATEMENT SEMI_COLON BOOLEAN_CONDITION SEMI_COLON STATEMENT RIGHT_BRACKET
    BLOCK
    {
        $$.code = new vector<string*>();
        $$.next = $5.next;
        Label Begin;
        //Label $8.next;
        back_patching($8.next, Begin.getName());
        add_label_to_code($$.code, Begin);
        $$.code->insert($$.code->end(), $3.code->begin(), $3.code->end());
        $$.code->insert($$.code->end(), $5.code->begin(), $5.code->end());
        $$.code->insert($$.code->end(), $9.code->begin(), $9.code->end());
        //add_label_to_code($$.code, $8.next);
        $$.code->insert($$.code->end(), $7.code->begin(), $7.code->end());
        $$.code->push_back(new string("goto " + Begin.getName()));
    };

ASSIGNMENT : ID EQUALS EXPRESSION SEMI_COLON {
	
		string id($1);
		if(symbol_table.find(id) != symbol_table.end()){
			if($3.type != ERROR_T){
				pair<unsigned, int> p= symbol_table[id];
				int id_type  = p.second;
				unsigned id_num = p.first;
				
				bool casting = ($3.type == INT_T) && (id_type == FLOAT_T);
				bool can_assign = ($3.type == id_type) || casting;
				
				if(can_assign){
					$$.code = new vector <string*>();
					$$.code->insert($$.code->end(), $3.code->begin(), $3.code->end());
					perform_label_adding($$.code, &$3.next);
					
					if(casting){
						$$.code->push_back(new string("i2f"));
					}
					
					$$.code->push_back(new string(type_map[id_type] + "store " + to_string(id_num)));
					$$.next = nullptr;
				}else{
					$$.code = nullptr;
					$$.next = nullptr;
					yyerror(("ERROR CAN'T CASTING!! --> "+id).c_str());					
				}
				
			}
		}else{
			$$.code = nullptr;
			$$.next = nullptr;
			yyerror(("ERROR WASN'T DECLARED!! --> "+id).c_str());
		}
		
    };
	
BOOLEAN_CONDITION:
  EXPRESSION
  {
    if ($1.type != ERROR_T) {
      if ($1.type != BOOL_T) {
        $$.code = nullptr;
        $$.next = nullptr;
        yyerror("Condition doesn't evaluate to boolean");
      } else {
        $$.next = new vector<string*>();
        $$.code = new vector<string*>();
		string * ifeq = new string("ifeq ");
        $$.next->push_back(ifeq);
        $$.code->insert($$.code->end(), $1.code->begin(), $1.code->end());
        perform_label_adding($$.code, &$1.next);
        $$.code->push_back(ifeq);
      }
    } else {
      $$.code = nullptr;
      $$.next = nullptr;
    }
  };
EXPRESSION : SIMPLE_EXPRESSION {
        $$.type = $1.type;
        $$.code = $1.code;
        $$.next = nullptr;
		perform_label_adding($$.code, &$1.next);
    }| SIMPLE_EXPRESSION REL_OP SIMPLE_EXPRESSION {
		string rel_op($2);
		if ($1.type != ERROR_T && $3.type != ERROR_T) {                                          // != == (bool, int, float)      >= ... (int, float)
			// if two operants are booleans.
			if($1.type == BOOL_T || $3.type == BOOL_T){
				if($1.type != $3.type){
					$$.type = ERROR_T;
					$$.code = nullptr;
					yyerror("Can't do this operation < "+ rel_op +" > for two diffrent types");					
				}else if(rel_op == "==" || rel_op == "!="){
					$$.type = BOOL_T;
					$$.code = new vector<string*>();
					$$.code->insert($$.code->begin(), $1.code->begin(), $1.code->end());
					$$.code->insert($$.code->end(), $3.code->begin(), $3.code->end());
					Label Btrue, next;
					$$.code->push_back(new string ("if_icmp" + real_ops[rel_op] + " " + Btrue.getName()));
					$$.code->push_back(new string ("iconst_0"));
					$$.code->push_back(new string ("goto " + next.getName()));
					add_label_to_code($$.code, Btrue);
					$$.code->push_back(new string ("iconst_1"));
					add_label_to_code($$.code, next);
				}else{
					$$.type = ERROR_T;
					$$.code = nullptr;
					yyerror("Can't do this operation < "+ rel_op +" > between booleans");					
				}
			}else {
				// if two operants are int or float.
				bool casting = ($1.type != $3.type);
				$$.type = BOOL_T;
				$$.code = new vector<string*>();
				$$.code->insert($$.code->begin(), $1.code->begin(), $1.code->end());
				if (casting && $1.type == INT_T){
					$$.code->push_back(new string ("i2f"));
				}
				$$.code->insert($$.code->end(), $3.code->begin(), $3.code->end());
				if (casting && $3.type == INT_T){
					$$.code->push_back(new string ("i2f"));
				}
				Label Btrue, next;
				if(!casting && $1.type == INT_T){
					$$.code->push_back(new string ("if_icmp" + real_ops[rel_op] + " " + Btrue.getName()));
					
				}else {
					$$.code->push_back(new string ("fcmpl"));
					$$.code->push_back(new string ("if" + real_ops[rel_op] + " " + Btrue.getName()));
				}
				$$.code->push_back(new string ("iconst_0"));
				$$.code->push_back(new string ("goto " + next.getName()));
				add_label_to_code($$.code, Btrue);
				$$.code->push_back(new string ("iconst_1"));
				add_label_to_code($$.code, next);
				
			}
						
		} else {
				$$.type = ERROR_T;
				$$.code = nullptr;
				yyerror("Can't do this operation for two diffrent types");
			}
	};
SIMPLE_EXPRESSION :
    TERM {
        $$.type = $1.type;
        $$.code = $1.code;
		$$.next = nullptr;
    }| ADD_OP TERM {
        if ($2.type != BOOL_T){
            $$.type = $2.type;
			$$.code = $2.code;
            if ($1 == '-'){
                $$.code->push_back(new string(type_map[$2.type] + "neg"));
            }
        } else {
            $$.type = ERROR_T;
            yyerror("Can't add sign for types nether int nor float");
        }
    }| SIMPLE_EXPRESSION ADD_OP TERM {
        if ($1.type == $3.type && ($3.type == INT_T || $3.type == FLOAT_T)){
            $$.type = $3.type;
			$$.code = new vector<string *>();
		    $$.code->insert($$.code->begin(), $1.code->begin(), $1.code->end());
		    $$.code->insert($$.code->end(), $3.code->begin(), $3.code->end());
			$$.code->push_back(new string(type_map[$1.type] + op_map[$2]));
        } else {
            $$.type = ERROR_T;
			$$.code = nullptr;
            yyerror("Can't add two diffrent types nether int nor float");
        }
    };
TERM : FACTOR {
        $$.code = $1.code;
        $$.type = $1.type;
    }| TERM MUL_OP FACTOR {
        if ($1.type == $3.type && ($3.type == INT_T || $3.type == FLOAT_T)){
            $$.type = $3.type;
			$$.code = new vector<string *>();
		    $$.code->insert($$.code->begin(), $1.code->begin(), $1.code->end());
		    $$.code->insert($$.code->end(), $3.code->begin(), $3.code->end());
			$$.code->push_back(new string(type_map[$1.type] + op_map[$2]));

        } else {
            $$.type = ERROR_T;
			$$.code = nullptr;
            yyerror("Can't add two diffrent types nether int nor float");
        }
    };
FACTOR : ID {
        unordered_map<string, pair<unsigned, int>>::iterator it;
        it = symbol_table.find($1);
        if (it != symbol_table.end()){
			int id_type = it->second.second;
			int id_num = it->second.first;
            $$.type = id_type;
            $$.code = new vector<string *>();
            $$.code->push_back(new string(type_map[id_type] + "load " + to_string(id_num)));
            
        } else {
			$$.type = ERROR_T;
			$$.code = nullptr;
					string str($1);
					string msg = "\n ERROR";
					msg +=" WASN'T DECLARED!! -->";
					msg += str;
            yyerror((msg).c_str());
        }
    }| NUM {
        $$.code = new vector<string *>();
        $$.type = INT_T;
        $$.code->push_back(new string("ldc " + to_string($1)));
    }| F_NUM {
		$$.code = new vector<string *>();
		$$.type = FLOAT_T;
		$$.code->push_back(new string("ldc " + to_string($1)));
    } | BOOL {
		$$.code = new vector<string *>();
		$$.type = BOOL_T;
		string str ($1);
		if(str == "true"){
			$$.code->push_back(new string("iconst_1"));
		}else{
			$$.code->push_back(new string("iconst_0"));
		}
	} | LEFT_BRACKET EXPRESSION RIGHT_BRACKET {
        $$.type = $2.type;
        $$.code = $2.code;
		perform_label_adding($$.code, &$2.next);
    };
%%
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
