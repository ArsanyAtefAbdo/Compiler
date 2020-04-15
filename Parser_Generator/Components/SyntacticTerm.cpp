//
// Created by Michael Said on 2020-04-14.
//

#include "SyntacticTerm.h"

SyntacticTerm::SyntacticTerm(const string &name) : ProductionTerm(name, NonTerminal) {
}

vector<ProductionRule*> SyntacticTerm::getProductions() const{
    return this->productions;
}

void SyntacticTerm::addProduction(ProductionRule *p) {
    this->productions.push_back(p);
}

SyntacticTerm::~SyntacticTerm() {

    for(ProductionRule* r : productions){
        delete r;
    }
    productions.clear();
}

bool SyntacticTerm::isDerivingToEpsilon() {

    for(ProductionRule* p : productions){
        if(p->isEpsilon()){
            return true;
        }
    }
    return false;
}

const unordered_set<string> &SyntacticTerm::getFirst() const {
    return first;
}

void SyntacticTerm::setFirst(const unordered_set<string> &firstSet) {
    SyntacticTerm::first = firstSet;
}

const unordered_set<string> &SyntacticTerm::getFollow() const {
    return follow;
}

void SyntacticTerm::setFollow(const unordered_set<string> &followSet) {
    SyntacticTerm::follow = followSet;
}

string SyntacticTerm::toString() {
    string s;
    for(auto* p : productions){
        s += p->toString() + "\n";
    }
    s.pop_back();
    return s;
}

void SyntacticTerm::setProductions(const vector<ProductionRule*>& newProductions) {
    this->productions.clear();
    this->productions = newProductions;
}

void SyntacticTerm::replaceProductionWith(SyntacticTerm *E) {
    vector<ProductionRule *>temp = this->productions;
    this->productions.clear();
    for(ProductionRule* p : temp){
        if(p->isStartWith(E)){
            p->removeFirstTerm();
            for(ProductionRule* pr : E->getProductions()){
                auto* newP = new ProductionRule(this);
                newP->addProductionTerms(pr->getTerms());
                newP->addProductionTerms(p->getTerms());
            }
            delete p;
        }else{
            this->productions.push_back(p);
        }
    }
}

