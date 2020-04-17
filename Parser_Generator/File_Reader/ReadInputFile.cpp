//
// Created by Kiro on 4/16/2020.
//

#include "ReadInputFile.h"

ReadInputFile* ReadInputFile::instance = nullptr;

ReadInputFile::ReadInputFile() {
    this->line = regex(R"(#((\w|\s)+)=((\w|\s|\.|\'|\||;|\*|\/|\-|\+|\(|\)|\{|\}|=)+))");
    this->complete_line = regex(R"(\s*(\|((\w|\s|\.|\'|\||;|\*|\/|\-|\+|\(|\)|\{|\}|=)+)))");

}

ReadInputFile *ReadInputFile::getInstance() {
    if(instance == nullptr){
        instance = new ReadInputFile();
    }
    return instance;
}

string ReadInputFile::removeChar(string str, char c) {
    str.erase(remove(str.begin(), str.end(), c), str.end());
    return str;
}



vector<string> ReadInputFile::split_by_spaces(string to_be_splitted) {
    vector<string> returner;
    string matched  = std::move(to_be_splitted);
    string ans;
    bool exist = false;
    for (auto i : matched){
        if (i == ' ' && !ans.empty()){
            returner.push_back(ans);
            ans = "";
            exist = false;
        } else if(i != ' ') {
            ans += i;
            exist = true;
        }
    }
    if (exist){
        returner.push_back(ans);
    }
    return returner;
}

vector<SyntacticTerm*> ReadInputFile::read_from_file(const string& input_file){
    vector<pair<string,string>> lines;
    std::ifstream file(input_file);
    std::string str;
    while (std::getline(file, str)) {
        if (regex_search(str, match, line)){
            pair<string,string> temp;
            temp.first = removeChar(match.str(1), ' ');
            non_terminals.insert(temp.first);
            temp.second = match.str(3);
            lines.push_back(temp);
        } else if (regex_search(str, match, complete_line)){
            string new_str = match.str(1);
            string temp = lines.back().second;
            temp += " ";
            temp += new_str;
            lines.back().second = temp;
        }
    }
    file.close();
    handle_input_lines(lines);
    return buildRules();
}

void ReadInputFile::handle_input_lines(const vector<pair<string, string>>& my_lines) {

    for (const pair<string, string>& p : my_lines){
        pair<string, vector<string>> temp;
        temp.first = p.first;
        vector<string> splited = split_by_spaces(p.second);
        vector<string> final_vector;
        for(const string& s : splited){
            if(s.find('\'') != std::string::npos){
                terminals.insert(removeChar(s, '\''));
                final_vector.push_back(removeChar(s, '\''));
            } else  {
                final_vector.push_back(s);
            }
        }
        temp.second = final_vector;
        input_lines.push_back(temp);
    }
}

set<string> ReadInputFile::get_non_terminals() {
    return terminals;
}

set<string> ReadInputFile::get_terminals() {
    return non_terminals;
}

vector<SyntacticTerm *> ReadInputFile::buildRules() {
    vector<SyntacticTerm *> rules{};
    unordered_map<string, ProductionTerm*> map{};
    for(const string& s : terminals){
        map[s] = new ProductionTerm(s, Terminal);
    }
    for(const string& s : non_terminals){
        map[s] = new SyntacticTerm(s);
    }
    for(const auto& p : input_lines){
        auto* nonTerminal = (SyntacticTerm*) map[p.first];
        auto* production = new ProductionRule(nonTerminal);
        for(const string& s : p.second){
            if(s == "|"){
                production = new ProductionRule(nonTerminal);
            }else{
                production->addProductionTerm(map[s]);
            }
        }
        rules.push_back(nonTerminal);
    }
    return rules;
}

