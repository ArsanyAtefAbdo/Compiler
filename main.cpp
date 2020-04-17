#include <iostream>
#include "Components/ReadLexicalRulesFile.h"
#include "Components/Node.h"
#include "Components/DFA.h"
#include "Builder/Builder.h"
#include "Converter/Converter.h"
#include "Components/Minimizer.h"
#include "Components/Scanner.h"
#include "Parser_Generator/Components/ProductionRule.h"
#include "Parser_Generator/LL(1) Converter/LL1Converter.h"
#include "Parser_Generator/Parsing Table Constructor/ParsingTable.h"

using namespace std;

int main() {

// //----------------- parsing file and build -----------
//    map<string, int> priorities{};
//    vector<LexicalRule*>rules = ReadLexicalRulesFile::getInstance()->read_from_file("test.txt", &priorities);
//    NFA* nfa = Builder::getInstance()->buildNFAFromLexicalRules(rules, priorities);
//
//    //--------------convert NFA to DFA----------------
//
//    DFA* dfa = Converter::getInstance()->convert(nfa, Builder::getInstance()->getAlphabet());
//    map<Node *, map<char, Node *>> ans = dfa->getDTable();
//
//    //--------------Minimize the DFA Table and save it----------------
//    Minimizer::getInstance()->DFAMinimize(dfa);
//    ans = dfa->getDTable();
//
//    ReadLexicalRulesFile::getInstance()->printTable("table", ans, Builder::getInstance()->getAlphabet());
//
//
//    //----------------Scanning the input program--------------
//    vector<pair<string, string>> tokens = Scanner::getInstance()->scanProgramFile("prog.txt",  dfa);
//    for(const pair<string, string>&token : tokens){
//        cout << token.second << endl;
//    }


//  testing LL1 converter problem 2)a sheet 4 :D

    auto* P = new SyntacticTerm("P");
    auto* Def = new SyntacticTerm("Def");
    auto* E = new SyntacticTerm("E");

    auto* id = new ProductionTerm("id", Terminal);
    auto* num = new ProductionTerm("num", Terminal);
    auto* close = new ProductionTerm(")", Terminal);
    auto* open = new ProductionTerm("(", Terminal);
    auto* plus = new ProductionTerm("+", Terminal);
    auto* comma = new ProductionTerm(",", Terminal);
    auto* openS = new ProductionTerm("[", Terminal);
    auto* closeS = new ProductionTerm("]", Terminal);
    auto* semi = new ProductionTerm(";", Terminal);
    auto* equal = new ProductionTerm("=", Terminal);
    //auto* Eps = new ProductionTerm("", Terminal);


    auto* prS1 = new ProductionRule(P);
    prS1->addProductionTerm(P);
    prS1->addProductionTerm(semi);
    prS1->addProductionTerm(Def);
    auto* prS2 = new ProductionRule(P);
    prS2->addProductionTerm(Def);


    auto* prA1 = new ProductionRule(Def);
    prA1->addProductionTerm(id);
    prA1->addProductionTerm(open);
    prA1->addProductionTerm(id);
    prA1->addProductionTerm(close);
    prA1->addProductionTerm(equal);
    prA1->addProductionTerm(E);


    auto* production1 = new ProductionRule(E);
    production1->addProductionTerm(id);

    auto* production2 = new ProductionRule(E);
    production2->addProductionTerm(num);

    auto* production3 = new ProductionRule(E);
    production3->addProductionTerm(open);
    production3->addProductionTerm(E);
    production3->addProductionTerm(E);
    production3->addProductionTerm(close);

    auto* production4 = new ProductionRule(E);
    production4->addProductionTerm(open);
    production4->addProductionTerm(E);
    production4->addProductionTerm(plus);
    production4->addProductionTerm(E);
    production4->addProductionTerm(close);

    auto* production5 = new ProductionRule(E);
    production5->addProductionTerm(openS);
    production5->addProductionTerm(E);
    production5->addProductionTerm(comma);
    production5->addProductionTerm(E);
    production5->addProductionTerm(closeS);

    cout << P->toString() << endl;
    cout << Def->toString() << endl;
    cout << E->toString() << endl;
    cout << "-------- after converting -------" << endl;
    vector<SyntacticTerm*>v{P,Def, E};
    vector<SyntacticTerm*> answer = LL1Converter::getInstance()->convertToLL1(v);
    for(SyntacticTerm* t :answer ){
        cout << t->toString() << endl;
    }
    cout << "# of productions" <<answer.size() << endl;
    ParsingTable* ptable = new ParsingTable();
    cout << "-------- table -------" << endl;
    map<SyntacticTerm*, map<string, ProductionRule>> table = ptable->getTable(answer);
    for (auto i:table){
        cout << " first element " << i.first->toString()<< " end " << endl;
        for (auto j:i.second){
            cout << "char "<<j.first << " rule: " << j.second.toString() << endl;
        }
    }
    return 0;
}
