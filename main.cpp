#include <iostream>
#include "Components/ReadLexicalRulesFile.h"
#include "Components/Node.h"
#include "Components/DFA.h"
#include "Builder/Builder.h"
#include "Converter/Converter.h"
#include "Components/Minimizer.h"
#include "Components/Scanner.h"
using namespace std;

int main() {

 //----------------- parsing file and build -----------
    map<string, int> priorities{};
    vector<LexicalRule*>rules = ReadLexicalRulesFile::getInstance()->read_from_file("test.txt", &priorities);
    NFA* nfa = Builder::getInstance()->buildNFAFromLexicalRules(rules, priorities);

    //--------------convert NFA to DFA----------------

    DFA* dfa = Converter::getInstance()->convert(nfa, Builder::getInstance()->getAlphabet());
    map<Node *, map<char, Node *>> ans = dfa->getDTable();

    //--------------Minimize the DFA Table and save it----------------
    Minimizer::getInstance()->DFAMinimize(dfa);
    ans = dfa->getDTable();

    ReadLexicalRulesFile::getInstance()->printTable("table", ans, Builder::getInstance()->getAlphabet());


    //----------------Scanning the input program--------------
    vector<pair<string, string>> tokens = Scanner::getInstance()->scanProgramFile("prog.txt",  dfa);
    for(const pair<string, string>&token : tokens){
        cout << token.second << endl;
    }

    return 0;
}
