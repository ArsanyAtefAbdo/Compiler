//
// Created by Kiro on 4/16/2020.
//

#include "ReadInputFile.h"

ReadInputFile* ReadInputFile::instance = nullptr;

ReadInputFile::ReadInputFile() {
    this->line = regex(R"(#((\w|\s)+)=((\w|\s|\.|\'|\||;|\*|\/|\-|\+|\(|\)|\{|\}|=|\\L)+))");
    this->complete_line = regex(R"(\s*(\|((\w|\s|\.|\'|\||;|\*|\/|\-|\+|\(|\)|\{|\}|=|\\L)+)))");

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
    std::ifstream file(input_file + ".txt");
    if(!file.is_open()){
        cout << input_file << " dose not exit !" <<endl;
        return vector<SyntacticTerm*>();
    }
    input_lines.clear();
    terminals.clear();
    non_terminals.clear();
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
        vector<string> splited = split_by_spaces(add_spaces(p.second));
        vector<string> final_vector;
        for(const string& s : splited){

            if(s.find('\'') != std::string::npos){
                terminals.insert(removeChar(s, '\''));
                final_vector.push_back(removeChar(s, '\''));
            } else if(s == "\\L"){
                terminals.insert("");
                final_vector.emplace_back("");
            }else {
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

string ReadInputFile::add_spaces(const string& str) {
    string with_spaces;
    for(auto i : str){
        if(i != '|'){
            with_spaces+=i;
        } else {
            with_spaces += " | ";
        }
    }
    return with_spaces;
}
void ReadInputFile::printTable(const string &fileName, const map<SyntacticTerm*, map<string, ProductionRule>> &table,
                               const vector<SyntacticTerm *>& productions) {

    if(table.empty() || productions.empty()){
        return;
    }
    ofstream of;
    of.open(fileName + ".trnstb");
    streambuf * buf = of.rdbuf();
    std::ostream stream(buf);
    string tap = "\t";
    stream << left << "Non-Terminal\\Terminal";
    terminals.insert("$");
    for(const string& s : terminals){
        stream << tap << s;
    }
    stream << endl;
    for(auto* term : productions){

        map<string, ProductionRule> row = table.at(term);
        stream << left <<term->getName();
        for(const string& s : terminals){
            if(row.find(s) != row.end()){
                stream << tap << row.at(s).toString();
            }else{
                stream << tap << "error";
            }
        }
        stream << endl;
    }
    of.close();

}

void ReadInputFile::write(const string &fileName, const vector<string>& lines) {
    fstream file;
    file.open (fileName + ".txt" ,	ios::out);
    for(const string& s : lines){
        file << s << endl;
        cout << s << endl;
    }
    file.close();
}

