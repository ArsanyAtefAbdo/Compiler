//
// Created by Michael Said on 2020-04-14.
//

#include "ProductionRule.h"

ProductionRule::ProductionRule(SyntacticTerm* nonTerminal) {
    this->nonTerminal =  nonTerminal;
}
string ProductionRule::toString() {
    string s = nonTerminal->getName() + " ----> ";
    if(isEpsilon()){
        return s + "EPS";
    }
    for(ProductionTerm* term : terms){
        s += term->getName() + " ";
    }
    s.pop_back();
    return s;
}

vector<ProductionTerm *>ProductionRule::getTerms() const{
return this->terms;
}

SyntacticTerm *ProductionRule::getNonTerminal() const {
    return nonTerminal;
}

void ProductionRule::addProductionTerm(ProductionTerm *t) {
    this->terms.push_back(t);
}

bool ProductionRule::isEpsilon() {
    return this->terms.size() == 1 && this->terms.at(0)->isEpsilon();
}
