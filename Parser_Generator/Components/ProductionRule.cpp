//
// Created by Michael Said on 2020-04-14.
//

#include "ProductionRule.h"

ProductionRule::ProductionRule(SyntacticTerm* nonTerminal) {
    this->nonTerminal =  nonTerminal;
    this->nonTerminal->addProduction(this);
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

vector<ProductionTerm *> ProductionRule::getTerms() const{
    return terms;
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

void ProductionRule::addProductionTerms(const vector<ProductionTerm *>& newTerms) {
    this->terms.insert(this->terms.end(), newTerms.begin(), newTerms.end());
}

void ProductionRule::setNonTerminal(SyntacticTerm *syntacticTerm) {
    this->nonTerminal = syntacticTerm;
    this->nonTerminal->addProduction(this);
}

bool ProductionRule::isStartWith(ProductionTerm *term) {
    return !terms.empty() && terms.at(0) == term;
}

void ProductionRule::removeFirstTerm() {
    this->terms.erase(this->terms.begin());
}

void ProductionRule::setTerms(const vector<ProductionTerm*>& newTerms) {
    this->terms.clear();
    this->terms = newTerms;
}
