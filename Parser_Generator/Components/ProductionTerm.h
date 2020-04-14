//
// Created by Michael Said on 2020-04-14.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_PRODUCTIONTERM_H
#define LEXICAL_ANALYZER_GENERATOR_PRODUCTIONTERM_H
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * This class represents the term of productions.
 * Any term can be Terminal as (id, +, ...) or non-Terminal.
 */
enum ProductionTermType{Terminal, NonTerminal};
class ProductionTerm {
public:
    ProductionTerm(const string& name, ProductionTermType type){
        this->name = name;
        this->type = type;
    }
    ~ProductionTerm() = default;

    const string &getName() const {
        return name;
    }

    ProductionTermType getType() const {
        return type;
    }
    /*
     * return true if term is epsilon (empty string).
     */
    bool isEpsilon(){
        return name.empty() && type == Terminal;
    }
private:
    string name;
    ProductionTermType type;
};


#endif //LEXICAL_ANALYZER_GENERATOR_PRODUCTIONTERM_H
