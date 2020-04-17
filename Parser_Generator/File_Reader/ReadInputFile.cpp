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
        instance = new ReadInputFile;
    }
    return instance;
}

string ReadInputFile::removeQuotes(string str) {
    str.erase(remove(str.begin(), str.end(), '\''), str.end());
    return str;
}



vector<string> ReadInputFile::split_by_spaces(string to_be_splitted) {
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

vector<pair<string, vector<string>>> ReadInputFile::read_from_file(const string& input_file){
    vector<pair<string,string>> lines;
    std::ifstream file(input_file);
    std::string str;
    while (std::getline(file, str)) {
        if (regex_search(str, match, line)){
            pair<string,string> temp;
            temp.first = match.str(1);
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
    input_lines = handle_input_lines(lines);
    return input_lines;
}

vector<pair<string, vector<string>>> ReadInputFile::handle_input_lines(vector<pair<string, string>> my_lines) {
    vector<pair<string, vector<string>>> handled_lines;
    for (const pair<string, string> p : my_lines){
        pair<string, vector<string>> temp;
        temp.first = p.first;
        vector<string> splited = split_by_spaces(p.second);
        vector<string> final_vector;
        for(const string s : splited){
            if(s.find("\'") != std::string::npos){
                terminals.insert(removeQuotes(s));
                final_vector.push_back(removeQuotes(s));
            } else {
                non_terminals.insert(s);
                final_vector.push_back(s);
            }
        }
        temp.second = final_vector;
        handled_lines.push_back(temp);
    }
    return handled_lines;
}

set<string> ReadInputFile::get_non_terminals() {
    return terminals;
}

set<string> ReadInputFile::get_terminals() {
    return non_terminals;
}

