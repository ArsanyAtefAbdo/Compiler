//
// Created by Arsany on 2020-04-17.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_PARSER_H
#define LEXICAL_ANALYZER_GENERATOR_PARSER_H

#include "../Parsing Table Constructor/ParsingTable.h"
#include "../LL(1) Converter/LL1Converter.h"
#include "../../Components/Token.h"
#include "../../Components/Scanner.h"


class Parser {
public:
    //lexical_file contains lexical rules (file name)
    //CFGFileName contains production rules (file name)
    Parser(const string& lexical_file, const string& CFGFileName, bool printTable);
    void parsing(string programFileName);

private:
    Scanner* scanner;
    vector<SyntacticTerm *> productions;
    map<SyntacticTerm*, map<string, ProductionRule>> table;

};


#endif //LEXICAL_ANALYZER_GENERATOR_PARSER_H
