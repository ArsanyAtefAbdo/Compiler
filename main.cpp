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
    vector<LexicalRule*>rules = ReadLexicalRulesFile::getInstance()->read_from_file("test.txt");
    NFA* nfa = Builder::getInstance()->buildNFAFromLexicalRules(rules);

    //------------------------------

    DFA* dfa = Converter::getInstance()->convert(nfa, Builder::getInstance()->getAlphabet());
    map<Node *, map<char, Node *>> ans = dfa->getDTable();

//    for(pair<Node *, map<char,  Node *>>row : ans){
//        cout << row.first->getName() << " : ";
//        for(pair<char, Node *> n :row.second){
//            cout << "(" << n.first << " , " << n.second->getName() << ")  ";
//        }
//        cout << endl;
//    }

    Minimizer::getInstance()->DFAMinimize(dfa);
    ans = dfa->getDTable();
//    cout << "---------after minimizing ----------------"<< endl;
//    for(pair<Node *, map<char,  Node *>>row : ans){
//        cout << row.first->getName() << " : ";
//        for(pair<char, Node *> n :row.second){
//            cout << "(" << n.first << " , " << n.second->getName() << ")  ";
//        }
//        cout << endl;
//    }
    vector<pair<string, string>> tokens = Scanner::getInstance()->scanProgramFile("prog.txt",  dfa);
    for(const pair<string, string>&token : tokens){
        cout << token.second << endl;
    }
    return 0;
}
