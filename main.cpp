#include <iostream>
#include "Parser_Generator/Evaluator/Parser.h"

using namespace std;
// tests/test1/lexical_rules
// tests/test1/production_rules
// tests/test1/program_test
int main() {

    cout << "Please enter the full filename/path of the lexical rules file you want to use..." << endl;
    string lexical_rules_file;
    cin >> lexical_rules_file;
    cout << "Please enter the full filename/path of the production rules file you want to use..." << endl;
    string production_rules_file;
    cin >> production_rules_file;
    while(true){

        cout << "Please enter the full filename/path of the source program you want to analyze... (-1 to exit)" << endl;
        string src_file;
        cin >> src_file;
        if(src_file == "-1"){
            break;
        }
        auto* parser = new Parser(lexical_rules_file, production_rules_file, true);

        if(parser->parsing(src_file)){

            vector<string> derivations = parser->getDerivations();
            vector<string> errors = parser->getErrors();

            ReadInputFile::getInstance()->write(src_file + "_derivations", derivations);
            ReadInputFile::getInstance()->write(src_file + "_errors", errors);
        }
    }

    return 0;
}