#include <iostream>
#include "Parser_Generator/Evaluator/Parser.h"

using namespace std;

int main() {

    auto* parser = new Parser("test", "test_input_file_phase_2.txt", false);
    for(const string& s : parser->parsing("prog")){
        cout << s << endl;
    }
    return 0;
}