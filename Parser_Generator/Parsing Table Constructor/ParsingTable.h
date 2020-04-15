//
// Created by Yomna on 4/15/2020.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_PARSINGTABLE_H
#define LEXICAL_ANALYZER_GENERATOR_PARSINGTABLE_H

#include "../Components/ProductionTerm.h"
#include "../Components/ProductionRule.h"

class ParsingTable {
public:
    static ParsingTable *getInstance();
    /// non-terminal  ,      terminal      , ProductionRule
    map<SyntacticTerm*, map <string, ProductionRule>>* getTable(set<SyntacticTerm*> non_terminal);
    void settingFirstANDFollow(set<SyntacticTerm*> non_terminal);

private:
    ParsingTable() = default;
    static ParsingTable* instance;
    map<SyntacticTerm*, map <string, ProductionRule>> table;
    map<SyntacticTerm*, unordered_set<string>> first;
    map<SyntacticTerm*, unordered_set<string>> follow;
    unordered_set<string>getFirst(SyntacticTerm* non_terminal);
    void setFollowTable(set<SyntacticTerm*> non_terminal);
    static bool cons;
};

#endif //LEXICAL_ANALYZER_GENERATOR_PARSINGTABLE_H
