//
// Created by Kiro on 3/22/2020.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_READLEXICALRULESFILE_H
#define LEXICAL_ANALYZER_GENERATOR_READLEXICALRULESFILE_H
#include <iostream>
#include <bits/stdc++.h>
#include <regex>

using namespace std;

class ReadLexicalRulesFile {

public:
    ReadLexicalRulesFile();
    virtual ~ReadLexicalRulesFile();

private:
    vector <pair<string,string>> regular_definitions_vector;
    vector <pair<string,string>> regular_expression_vector;
    vector <string> keywords_vector;
    vector <string> punctuations_vector;
    regex regular_definition_regex;
    regex regular_expression_regex;
    regex keywords_regex;
    regex punctuations_regex;
    smatch match;
    bool no_errors;


public:
    void read_from_file(string input_file);

    vector<pair<string, string>> get_regular_definitions_vector();

    vector<pair<string,string>> get_regular_expression_vector();

    vector<string> get_keywords_vector();

    vector<std::string> get_punctuations_vector();

    bool is_no_errors();
};


#endif //LEXICAL_ANALYZER_GENERATOR_READLEXICALRULESFILE_H
