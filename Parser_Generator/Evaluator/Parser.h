//
// Created by Arsany on 2020-04-17.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_PARSER_H
#define LEXICAL_ANALYZER_GENERATOR_PARSER_H

#include "../Parsing Table Constructor/ParsingTable.h"
#include "../LL(1) Converter/LL1Converter.h"
#include "../../Components/Token.h"
#include "../../Components/Scanner.h"
#include "../File_Reader/ReadInputFile.h"


class Parser {
public:
    //lexical_file contains lexical rules (file name)
    //CFGFileName contains production rules (file name)
    Parser(const string& lexical_file, const string& CFGFileName, bool printTable);
    bool parsing(const string& programFileName);
    bool isAmbiguous();

    vector<string> getDerivations() const;
    vector<string> getErrors() const;
private:
    Scanner* scanner;
    vector<SyntacticTerm *> productions;
    map<SyntacticTerm*, map<string, ProductionRule>> table;
    bool ambiguous;
    vector<vector<ProductionTerm*>> derivations{};
    vector<string> errors{};
    void handleDerivation(ProductionRule p);

};


#endif //LEXICAL_ANALYZER_GENERATOR_PARSER_H
