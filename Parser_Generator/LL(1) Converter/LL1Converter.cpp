//
// Created by Michael Said on 2020-04-14.
//

#include "LL1Converter.h"

LL1Converter* LL1Converter::instance = nullptr;
LL1Converter *LL1Converter::getInstance() {
    if(instance == nullptr){
        instance = new LL1Converter();
    }
    return instance;
}

SyntacticTerm *LL1Converter::eliminateLeftRecursion(SyntacticTerm *E) {
    // E'
    auto *newE = new SyntacticTerm(E->getName() + "'");
    vector<ProductionRule*>productionNotStartWithE{};

    for(ProductionRule* p : E->getProductions()){

        if(p->isStartWith(E)){
            p->removeFirstTerm();
            p->addProductionTerm(newE);
            p->setNonTerminal(newE);
        } else{
            p->addProductionTerm(newE);
            productionNotStartWithE.push_back(p);
        }
    }
    E->setProductions(productionNotStartWithE);

    auto* eps = new ProductionRule(newE);
    eps->addProductionTerm(new ProductionTerm("", Terminal));

    return newE;
}

vector<SyntacticTerm *> LL1Converter::eliminateLeftRecursion(const vector<SyntacticTerm *>& terms) {
    vector<SyntacticTerm *>result{};

    for(int i = 0; i < terms.size();i++){
        for(int j = 0; j < i;j++){

            terms.at(i)->replaceProductionWith(terms.at(j));
        }
        result.push_back(terms.at(i));
        if(isContainLeftRecursion(terms.at(i))){
            result.push_back(eliminateLeftRecursion(terms.at(i)));
        }
    }
    return result;
}

bool LL1Converter::isContainLeftRecursion(SyntacticTerm *E) {
    for(ProductionRule* p: E->getProductions()){

        if(p->isStartWith(E)){
            return true;
        }
    }
    return false;
}
