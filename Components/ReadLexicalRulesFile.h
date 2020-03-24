//
// Created by Kiro on 3/22/2020.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_READLEXICALRULESFILE_H
#define LEXICAL_ANALYZER_GENERATOR_READLEXICALRULESFILE_H
#include <iostream>
#include <bits/stdc++.h>
#include <regex>
#include <algorithm>

using namespace std;

class ReadLexicalRulesFile {

public:
    ReadLexicalRulesFile();
    virtual ~ReadLexicalRulesFile();

private:
    vector <pair<string,vector<string>>> regular_definitions_vector;
    vector <pair<string,vector<string>>> regular_expression_vector;
    vector <string> keywords_vector;
    vector <string> punctuations_vector;
    regex regular_definition_regex;
    regex regular_expression_regex;
    regex keywords_regex;
    regex punctuations_regex;
    smatch match;
    bool no_errors;

    vector<string> split_by_spaces(string to_be_splitted);
    string removeSpaces(string str);
    vector<string> split_each_char(string str);
    vector<string> split_for_regular_definition(string str);
    vector<string> split_for_regular_expression(string str);

public:
    void read_from_file(string input_file);

    vector<pair<string, vector<string>>> get_regular_definitions_vector();

    vector<pair<string, vector<string>>> get_regular_expression_vector();

    vector<string> get_keywords_vector();

    vector<std::string> get_punctuations_vector();

    bool is_no_errors();
};


#endif //LEXICAL_ANALYZER_GENERATOR_READLEXICALRULESFILE_H
