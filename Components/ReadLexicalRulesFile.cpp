//
// Created by Kiro on 3/22/2020.
//

#include "ReadLexicalRulesFile.h"

#include <utility>

ReadLexicalRulesFile* ReadLexicalRulesFile::instance = nullptr;

ReadLexicalRulesFile::ReadLexicalRulesFile(){
    this->regular_definition_regex = regex(R"((\w+) *= *((\S|\s)+))");
    this->regular_expression_regex = regex(R"((\w+) *: *((\S|\s)+))");
    this->keywords_regex = regex(R"(\{ *((\w+ *)+) *})");
    this->punctuations_regex = regex(R"(\[ *(([^\d\w] *)+) *\])");
}

vector<LexicalRule*>ReadLexicalRulesFile::read_from_file(const string& input_file) {
    vector<LexicalRule*>rules;
    std::ifstream file(input_file);
    std::string str;
    while (std::getline(file, str)) {
        if (regex_search(str, match, regular_definition_regex)){
            pair<string, vector<string>> temp;
            temp.first = match.str(1);
            string set_string = match.str(2);
            set_string = removeSpaces(set_string);
            temp.second = split_for_regular_definition(set_string);
            rules.push_back(LexicalRuleBuilder::getInstance()->buildPostFixRule(temp, RegularDefinition));
        } else if (regex_search(str, match, regular_expression_regex)){
            pair<string, vector<string>> temp;
            temp.first = match.str(1);
            string set_string = match.str(2);
            //set_string = removeSpaces(set_string);
            temp.second = split_for_regular_expression(set_string);
            rules.push_back(LexicalRuleBuilder::getInstance()->buildPostFixRule(temp, RegularExpression));
        } else if (regex_search(str, match, keywords_regex)){
            vector<LexicalRule*> temp_vec = LexicalRuleBuilder::getInstance()->buildRules(split_by_spaces(match.str(1)), Keyword);
            rules.insert(rules.end(), temp_vec.begin(), temp_vec.end());
        } else if (regex_search(str, match, punctuations_regex)){
            string set_string = match.str(1);
            set_string = removeSpaces(set_string);
            vector<LexicalRule*> temp_vec = LexicalRuleBuilder::getInstance()->buildRules(split_each_char(set_string), Punctuation);
            rules.insert(rules.end(), temp_vec.begin(), temp_vec.end());
        }
    }
    file.close();
    return rules;
}

string ReadLexicalRulesFile::removeSpaces(string str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

vector<string> ReadLexicalRulesFile::split_each_char(const string& str) {
    vector<string> after_split;
    string temp;
    for (auto i : str){
        if (i != '\\'){
            temp += i;
            after_split.push_back(temp);
            temp = "";
        }
    }
    return after_split;
}

vector<string> ReadLexicalRulesFile::split_by_spaces(string to_be_splitted) {
    vector<string> returner;
    string matched  = std::move(to_be_splitted);
    string ans;
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

vector<string> ReadLexicalRulesFile::split_for_regular_definition(const string& str) {
    vector<string> after_split;
    string ans;
    for (auto i : str){
        if (!ans.empty() && (i == '|' || i == '+' || i == '*' || i == '?' || i == '(' || i == ')')){
            after_split.push_back(ans);
            ans = "";
            ans += i;
            after_split.push_back(ans);
            ans = "";
        } else {
            ans += i;
        }
    }
    if (!ans.empty()){
        after_split.push_back(ans);
    }
    return after_split;
}

vector<string> ReadLexicalRulesFile::split_for_regular_expression(const string& str) {
    vector<string> after_split;
    string ans;
    for (auto i : str){
        if (ans == "\\"){
            ans += i;
            after_split.push_back(ans);
            ans = "";
        } else if (ans.empty() && (i == '|' || i == '+' || i == '*' || i == '?' || i == '.' || i == '(' || i == ')')){
            ans += i;
            after_split.push_back(ans);
            ans = "";
        }else if (!ans.empty() && (i == '|' || i == '+' || i == '*' || i == '?' || i == '.' || i == '(' || i == ')')){
            after_split.push_back(ans);
            ans = "";
            ans += i;
            after_split.push_back(ans);
            ans = "";
        }else if(i == ' '){
            after_split.push_back(ans);
            ans = "";
        }else {
            ans += i;
        }
    }
    if (!ans.empty()){
        after_split.push_back(ans);
    }
    return after_split;
}

ReadLexicalRulesFile *ReadLexicalRulesFile::getInstance() {
    if(instance == nullptr){
        instance = new ReadLexicalRulesFile;
    }
    return instance;
}
