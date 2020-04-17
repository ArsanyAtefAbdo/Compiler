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
#include "Parser_Generator/File_Reader/ReadInputFile.h"

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

    vector<SyntacticTerm*>answer = ReadInputFile::getInstance()->read_from_file("test_input_file_phase_2.txt");
    for(SyntacticTerm* t :answer ){
        cout << t->toString() << endl;
    }
    cout << "-------- after converting -------" << endl;

    answer = LL1Converter::getInstance()->convertToLL1(answer);
    for(SyntacticTerm* t :answer ){
        cout << t->toString() << endl;
    }
    auto* ptable = new ParsingTable();
    cout << "-------- table -------" << endl;
    map<SyntacticTerm*, map<string, ProductionRule>> table = ptable->getTable(answer);
    for (const auto& i:table){
        cout << " non-terminal " << i.first->getName() << endl;
        for (auto j:i.second){
            if (j.second.isSync()) {
                cout << j.first << " rule: " << "synch" << endl;
            } else {
                cout << j.first << " rule: " << j.second.toString() << endl;
            }
        }
    }
    return 0;
}