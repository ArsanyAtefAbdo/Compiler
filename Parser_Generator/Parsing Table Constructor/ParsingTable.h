//
// Created by Yomna on 4/15/2020.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_PARSINGTABLE_H
#define LEXICAL_ANALYZER_GENERATOR_PARSINGTABLE_H

#include "../Components/ProductionTerm.h"
#include "../Components/ProductionRule.h"

class ParsingTable {
public:
    /// non-terminal  ,      terminal      , ProductionRule
    static ParsingTable *getInstance();
    unordered_set<string>getFirst(SyntacticTerm* non_terminal);
    map<SyntacticTerm *, map<std::string, ProductionRule>> getTable(const vector<SyntacticTerm*>& non_terminal);
    bool ambiguity();
private:
    ParsingTable();
    static ParsingTable* instance;

    map<SyntacticTerm*, map <string, ProductionRule>> table;
    map<SyntacticTerm*, unordered_set<string>> first;
    map<SyntacticTerm*, unordered_set<string>> follow;
    void settingFirstANDFollow(const vector<SyntacticTerm*>& non_terminal);
    void setFollowTable(vector<SyntacticTerm*> non_terminal);
    void finalizingfollow(map<SyntacticTerm*, unordered_set<SyntacticTerm*>> nonterm_follow);
    bool cons;
    bool amb;
};

#endif //LEXICAL_ANALYZER_GENERATOR_PARSINGTABLE_H
