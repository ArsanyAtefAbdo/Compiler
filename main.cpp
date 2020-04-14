#include <iostream>
#include "Components/ReadLexicalRulesFile.h"
#include "Components/Node.h"
#include "Components/DFA.h"
#include "Builder/Builder.h"
#include "Converter/Converter.h"
#include "Components/Minimizer.h"
#include "Components/Scanner.h"
#include "Parser_Generator/Components/ProductionRule.h"
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

    auto* E = new SyntacticTerm("E");

    auto* id = new ProductionTerm("id", Terminal);
    auto* close = new ProductionTerm(")", Terminal);
    auto* open = new ProductionTerm("(", Terminal);
    auto* plus = new ProductionTerm("+", Terminal);
    auto* mins = new ProductionTerm("-", Terminal);
    auto* times = new ProductionTerm("*", Terminal);
    auto* div = new ProductionTerm("/", Terminal);
    auto* Eps = new ProductionTerm("", Terminal);

    auto* production1 = new ProductionRule(E);
    production1->addProductionTerm(E);
    production1->addProductionTerm(plus);
    production1->addProductionTerm(E);
    auto* production2 = new ProductionRule(E);
    production2->addProductionTerm(E);
    production2->addProductionTerm(mins);
    production2->addProductionTerm(E);
    auto* production3 = new ProductionRule(E);
    production3->addProductionTerm(E);
    production3->addProductionTerm(times);
    production3->addProductionTerm(E);
    auto* production4 = new ProductionRule(E);
    production4->addProductionTerm(E);
    production4->addProductionTerm(div);
    production4->addProductionTerm(E);
    auto* production5 = new ProductionRule(E);
    production5->addProductionTerm(open);
    production5->addProductionTerm(E);
    production5->addProductionTerm(close);
    auto* production6 = new ProductionRule(E);
    production6->addProductionTerm(mins);
    production6->addProductionTerm(E);
    auto* production7 = new ProductionRule(E);
    production7->addProductionTerm(id);
    auto* production8 = new ProductionRule(E);
    production8->addProductionTerm(Eps);

    E->addProduction(production1);
    E->addProduction(production2);
    E->addProduction(production3);
    E->addProduction(production4);
    E->addProduction(production5);
    E->addProduction(production6);
    E->addProduction(production7);
    E->addProduction(production8);

    cout << E->toString();

    return 0;
}
