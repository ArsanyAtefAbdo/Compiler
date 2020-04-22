#include <iostream>
#include "Parser_Generator/Evaluator/Parser.h"

using namespace std;

int main() {

    auto* parser = new Parser("tests/test1/lexical_rules", "tests/test1/production_rules", false);
    for(const string& s : parser->parsing("tests/test1/program_test")){
        cout << s << endl;
    }
    return 0;
}