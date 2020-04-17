//
// Created by Michael Said on 2020-03-26.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_SCANNER_H
#define LEXICAL_ANALYZER_GENERATOR_SCANNER_H
#include "Token.h"
#include "LexicalRuleBuilder.h"
#include "ReadLexicalRulesFile.h"
#include "../Builder/Builder.h"
#include "../Converter/Converter.h"
#include "../Components/Minimizer.h"

class Scanner {
public:
    explicit Scanner(DFA* recognizer);
    Scanner(const string& lexical_file, bool printTable);
    void scanProgramFile(const string& fileName);
    bool hasNextToken();
    Token* getNextToken();

private:
    void scanWord(string& word);
    DFA* recognizer;
    queue<Token*>tokens;

};


#endif //LEXICAL_ANALYZER_GENERATOR_SCANNER_H
