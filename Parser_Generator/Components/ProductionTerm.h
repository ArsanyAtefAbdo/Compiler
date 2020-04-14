//
// Created by Michael Said on 2020-04-14.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_PRODUCTIONTERM_H
#define LEXICAL_ANALYZER_GENERATOR_PRODUCTIONTERM_H
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
enum ProductionTermType{Terminal, NonTerminal};

class ProductionTerm {
public:
    ProductionTerm(const string& name, ProductionTermType type){
        this->name = name;
        this->type = type;
    }
    ~ProductionTerm() = default;

protected:
    string name;
    ProductionTermType type;
};


#endif //LEXICAL_ANALYZER_GENERATOR_PRODUCTIONTERM_H
