//
// Created by Kiro on 3/22/2020.
//

#include "ReadLexicalRulesFile.h"

#include <utility>



ReadLexicalRulesFile::ReadLexicalRulesFile(){
    this->regular_definition_regex = regex(R"((\w+) *= *((\S|\s)+))");
    this->regular_expression_regex = regex(R"((\w+) *: *((\S|\s)+))");
    this->keywords_regex = regex(R"(\{ *((\w+ *)+) *})");
    this->punctuations_regex = regex(R"(\[ *(([^\d\w] *)+) *\])");
    this->no_errors = true;
}

ReadLexicalRulesFile::~ReadLexicalRulesFile(){
    this->regular_definitions_vector.clear();
    this->regular_expression_vector.clear();
    this->keywords_vector.clear();
    this->punctuations_vector.clear();
}

void ReadLexicalRulesFile::read_from_file(string input_file) {
    std::ifstream file(input_file);
    std::string str;
    while (std::getline(file, str)) {
        if (regex_search(str, match, regular_definition_regex)){
            pair<string, vector<string>> temp;
            temp.first = match.str(1);
            string set_string = match.str(2);
            set_string = removeSpaces(set_string);
            temp.second = split_for_regular_definition(set_string);
            regular_definitions_vector.push_back(temp);
        } else if (regex_search(str, match, regular_expression_regex)){
            pair<string, vector<string>> temp;
            temp.first = match.str(1);
            string set_string = match.str(2);
            set_string = removeSpaces(set_string);
            temp.second = split_for_regular_expression(set_string);
            regular_expression_vector.push_back(temp);
        } else if (regex_search(str, match, keywords_regex)){
            keywords_vector = split_by_spaces(match.str(1));
        } else if (regex_search(str, match, punctuations_regex)){
            string set_string = match.str(1);
            set_string = removeSpaces(set_string);
            punctuations_vector = split_each_char(set_string);
        } else {
            no_errors = false;
        }
    }
}

string ReadLexicalRulesFile::removeSpaces(string str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

vector<string> ReadLexicalRulesFile::split_each_char(string str) {
    vector<string> after_split;
    string temp = "";
    for (auto i : str){
        if (i == '\\'){
            temp += i;
        } else {
            temp += i;
            after_split.push_back(temp);
            temp = "";
        }
    }
    return after_split;
}

vector<string> ReadLexicalRulesFile::split_by_spaces(string to_be_splitted) {
    vector<string> returner;
    string matched  = to_be_splitted;
    string ans = "";
    bool exist = false;
    for (auto i : matched){
        if (i == ' ' && ans != ""){
            returner.push_back(ans);
            ans = "";
            exist = false;
        } else {
            ans += i;
            exist = true;
        }
    }
    if (exist){
        returner.push_back(ans);
    }
    return returner;
}

vector<string> ReadLexicalRulesFile::split_for_regular_definition(string str) {
    vector<string> after_split;
    string ans = "";
    for (auto i : str){
        if (ans != "" && (i == '|' || i == '+' || i == '*' || i == '?' || i == '(' || i == ')')){
            after_split.push_back(ans);
            ans = "";
            ans += i;
            after_split.push_back(ans);
            ans = "";
        } else {
            ans += i;
        }
    }
    if (ans != ""){
        after_split.push_back(ans);
    }
    return after_split;
}

vector<string> ReadLexicalRulesFile::split_for_regular_expression(string str) {
    vector<string> after_split;
    string ans = "";
    for (auto i : str){
        if (ans == "\\"){
            ans += i;
            after_split.push_back(ans);
            ans = "";
        } else if (ans == "" && (i == '|' || i == '+' || i == '*' || i == '?' || i == '.' || i == '(' || i == ')')){
            ans += i;
            after_split.push_back(ans);
            ans = "";
        }else if (ans != "" && (i == '|' || i == '+' || i == '*' || i == '?' || i == '.' || i == '(' || i == ')')){
            after_split.push_back(ans);
            ans = "";
            ans += i;
            after_split.push_back(ans);
            ans = "";
        } else {
            ans += i;
        }
    }
    if (ans != ""){
        after_split.push_back(ans);
    }
    return after_split;
}

vector<pair<string, vector<string>>> ReadLexicalRulesFile::get_regular_definitions_vector() {
    return regular_definitions_vector;
}

vector<pair<string, vector<string>>> ReadLexicalRulesFile::get_regular_expression_vector() {
    return regular_expression_vector;
}

vector<string> ReadLexicalRulesFile::get_keywords_vector() {
    return keywords_vector;
}

vector<string> ReadLexicalRulesFile::get_punctuations_vector() {
    return punctuations_vector;
}

bool ReadLexicalRulesFile::is_no_errors() {
    return no_errors;
}

//            bool flag_clear_keyword_temp = false;
//            string keyword_temp = "";
//            string matched_temp = match.str(1);
//            for (auto i : matched_temp){
//                if (flag_clear_keyword_temp){
//                    flag_clear_keyword_temp = false;
//                    keyword_temp = "";
//                }
//                if (i == ' ' && keyword_temp != ""){
//                    string new_keyword_temp = keyword_temp;
//                    keywords_vector.push_back(new_keyword_temp);
//                    flag_clear_keyword_temp = true;
//                } else {
//                    keyword_temp += i;
//                }
//            }
//            if (keyword_temp != "" && !flag_clear_keyword_temp){
//                keywords_vector.push_back(keyword_temp);
//            }


//            bool flag_clear_punctuation_temp = false;
//            string punctuation_temp = "";
//            string matched_temp = match.str(1);
//            for (auto i : matched_temp){
//                if (flag_clear_punctuation_temp){
//                    flag_clear_punctuation_temp = false;
//                    punctuation_temp = "";
//                }
//                if (i == ' ' && punctuation_temp != ""){
//                    string new_punctuation_temp = punctuation_temp;
//                    punctuations_vector.push_back(new_punctuation_temp);
//                    flag_clear_punctuation_temp = true;
//                } else{
//                    punctuation_temp += i;
//                }
//            }
//            if (punctuation_temp != "" && !flag_clear_punctuation_temp){
//                punctuations_vector.push_back(punctuation_temp);
//            }