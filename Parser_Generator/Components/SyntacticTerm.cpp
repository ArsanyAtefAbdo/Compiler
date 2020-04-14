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

