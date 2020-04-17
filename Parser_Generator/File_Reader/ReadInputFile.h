//
// Created by Kiro on 4/16/2020.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_READINPUTFILE_H
#define LEXICAL_ANALYZER_GENERATOR_READINPUTFILE_H
#include <iostream>
#include <bits/stdc++.h>
#include <regex>
#include <algorithm>

using namespace std;

class ReadInputFile {
public:
    virtual ~ReadInputFile() = default;
    static ReadInputFile *getInstance();
    vector<pair<string, vector<string>>> read_from_file(const string& input_file);
    set<string> get_terminals();
    set<string> get_non_terminals();
private:
    regex line;
    regex complete_line;
    smatch match;
    vector<pair<string,vector<string>>> input_lines;
    set<string> terminals;
    set<string> non_terminals;

private:
    ReadInputFile();
    static ReadInputFile* instance;
    vector<string> split_by_spaces(string to_be_splitted);
    string removeQuotes(string str);
    vector<pair<string,vector<string>>> handle_input_lines(vector<pair<string,string>> my_lines);

};


#endif //LEXICAL_ANALYZER_GENERATOR_READINPUTFILE_H
