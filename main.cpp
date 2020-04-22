#include <iostream>
#include "Parser_Generator/Evaluator/Parser.h"

using namespace std;

int main() {

    auto* parser = new Parser("tests/test1/lexical_rules", "tests/test1/production_rules", false);
    if(parser->parsing("tests/test1/program_test2")){
        for(const string& s : parser->getDerivations()){
            cout << s << endl;
        }
    }
    cout << endl;
    for(const string& s : parser->getErrors()){
        cout << s << endl;
    }
    return 0;
}