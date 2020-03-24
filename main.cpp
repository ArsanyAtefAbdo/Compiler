#include <iostream>
#include "Components/ReadLexicalRulesFile.h"



using namespace std;


int main() {
    auto* parser = new ReadLexicalRulesFile();
    parser->read_from_file("test.txt");

    for(string s:parser->get_keywords_vector()){
        cout << s << " ";
    }
    for(char c:parser->get_punctuations_vector()){
        cout << c << " ";
    }
    for(auto p:parser->get_regular_expression_vector()){
        cout << p.first << " " << p.second << endl;
    }
    for(auto p:parser->get_regular_definitions_vector()){
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}
