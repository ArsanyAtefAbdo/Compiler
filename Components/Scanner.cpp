//
// Created by Michael Said on 2020-03-26.
//

#include "Scanner.h"

void Scanner::scanProgramFile(const string& fileName) {
    ifstream file(fileName + ".txt");
    string line;
    vector<string>words{};
    while(getline(file, line)){
        istringstream iss(line);
        vector<string> results((istream_iterator<string>(iss)),istream_iterator<string>());
        words.insert(words.end(), results.begin(), results.end());
    }
    for(string s : words){
       scanWord(s);
    }
    tokens.push(new Token("$", "$"));
}

void Scanner::scanWord(string &word) {

    Node* startState = this->recognizer->getStartState();
    Node* currentState = startState;
    Node* nullState = new Node("null", false);
    Node* finalState = nullState;
    int first = 0;
    int last = 0;
    for(int i=0;i<word.size();i++){
        currentState = this->recognizer->move(currentState, word.at(i));
        if(currentState->isFinalState()){
            last = i;
            finalState = currentState;
            if(i == word.size() - 1){
                string s = word.substr(first, last - first + 1);
                tokens.push(new Token(finalState->getName(), s));
                break;
            }
        }else if(currentState->getName() == "null" && finalState != nullState){
            string s = word.substr(first, last - first + 1);
            tokens.push(new Token(finalState->getName(), s));
            first = last + 1;
            i = last;
            finalState = nullState;
            currentState = startState;
        }
    }
}

Scanner::Scanner(DFA *recognizer) {
    this->recognizer = recognizer;
}

bool Scanner::hasNextToken() {
    return !tokens.empty();
}

Token *Scanner::getNextToken() {
    Token * token = tokens.front();
    tokens.pop();
    return token;
}

Scanner::Scanner(const string& lexical_file, bool printTable) {
    //----------------- parsing file and build -----------
    map<string, int> priorities{};
    vector<LexicalRule*> rules = ReadLexicalRulesFile::getInstance()->read_from_file(lexical_file + ".txt", &priorities);
    NFA* nfa = Builder::getInstance()->buildNFAFromLexicalRules(rules, priorities);

    //--------------convert NFA to DFA----------------

    this->recognizer = Converter::getInstance()->convert(nfa, Builder::getInstance()->getAlphabet());
    //--------------Minimize the DFA Table and save it----------------
    Minimizer::getInstance()->DFAMinimize(this->recognizer);

    if(printTable){
        ReadLexicalRulesFile::getInstance()->printTable(lexical_file + "table", this->recognizer->getDTable(), Builder::getInstance()->getAlphabet());
    }

}
