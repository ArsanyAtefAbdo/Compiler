#include <iostream>
#include "Components/Scanner.h"
#include "Parser_Generator/Components/ProductionRule.h"
#include "Parser_Generator/LL(1) Converter/LL1Converter.h"
#include "Parser_Generator/Parsing Table Constructor/ParsingTable.h"
#include "Parser_Generator/File_Reader/ReadInputFile.h"
#include "Parser_Generator/Evaluator/Parser.h"

using namespace std;

int main() {

/*    auto* scanner = new Scanner("../test", false);
    scanner->scanProgramFile("../prog");
    for (Token *t = scanner->getNextToken(); scanner->hasNextToken(); t = scanner->getNextToken()){
        cout << t->getName() << " : " << t->getLexeme()<< endl;
    }*/
    Parser* parser = new Parser("../test", "../test_input_file_phase_2.txt", false);
    parser->parsing("../prog");
//    vector<SyntacticTerm*>answer = ReadInputFile::getInstance()->read_from_file("./test_input_file_phase_2.txt");
//    for(SyntacticTerm* t :answer ){
//        cout << t->toString() << endl;
//    }
//    cout << "-------- after converting -------" << endl;
//
//    answer = LL1Converter::getInstance()->convertToLL1(answer);
//    for(SyntacticTerm* t :answer ){
//        cout << t->toString() << endl;
//    }
//    auto* ptable = new ParsingTable();
//    cout << "-------- table -------" << endl;
//    map<SyntacticTerm*, map<string, ProductionRule>> table = ptable->getTable(answer);
//    for (const auto& i:table){
//        cout << " non-terminal " << i.first->getName() << endl;
//        for (auto j:i.second){
//            if (j.second.isSync()) {
//                cout << j.first << " rule: " << "synch" << endl;
//            } else {
//                cout << j.first << " rule: " << j.second.toString() << endl;
//            }
//        }
//    }
    return 0;
}