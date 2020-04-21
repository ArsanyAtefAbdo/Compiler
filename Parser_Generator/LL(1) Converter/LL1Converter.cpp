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

vector<SyntacticTerm *> LL1Converter::eliminateLeftFactoring(const vector<SyntacticTerm *> &terms) {
    vector<SyntacticTerm *>result{};
    for(SyntacticTerm* term : terms){
        result.push_back(term);
        vector<SyntacticTerm *>tmp = eliminateLeftFactoring(term);
        result.insert(result.end(), tmp.begin(), tmp.end());
    }
    return result;
}

vector<SyntacticTerm *> LL1Converter::eliminateLeftFactoring(SyntacticTerm *E) {
    // E' E'' ...
    vector<SyntacticTerm *>newEs{};
    vector<ProductionRule*>newPR{};
    string s;
    unordered_map<ProductionTerm *, vector<ProductionRule*> >map{};
    vector<vector<ProductionTerm *>>firstGroup{};
    vector<ProductionTerm *>firstTerms{};
    for(ProductionRule* p : E->getProductions()){
        ProductionTerm *term = p->getTerms().front();
        if(map.find(term) == map.end()){
            firstGroup.emplace_back();
            firstGroup.back().push_back(term);
            firstTerms.push_back(term);
            map.insert(pair<ProductionTerm *, vector<ProductionRule*>>(term, vector<ProductionRule*>()));
        }
        map[term].push_back(p);
    }
    if(E->getProductions().size() == map.size()){
        return newEs;
    }
    unordered_set<ProductionTerm *>set{};
    for(int i = 0; i < firstTerms.size(); i++){
        ProductionTerm * first = firstTerms.at(i);
        bool allMatching = true;
        int window = 1;
        while(allMatching){
            for(ProductionRule* p : map[first]){
                if(p->getTerms().size() <= window){
                    allMatching = false;
                    break;
                }
                ProductionTerm *term = p->getTerms().at(window);
                if(set.empty() && set.find(term) == set.end()){
                    set.insert(term);
                }else if (set.size() == 1 && set.find(term) == set.end()){
                    allMatching = false;
                    break;
                }
            }
            if(allMatching){
                firstGroup.at(i).push_back(map[first].at(0)->getTerms().at(window));
            }
            set.clear();
            window++;
        }
    }

    for(int i = 0; i < firstTerms.size(); i++){
        ProductionTerm * term = firstTerms.at(i);
        if(map[term].size() > 1){
            s += "'";
            auto * newE = new SyntacticTerm(E->getName() + s);
            newEs.push_back(newE);
            for(ProductionRule* p : map[term]){
                for(int j = 0; j < firstGroup.at(i).size();j++) {
                    p->removeFirstTerm();
                }
                p->setNonTerminal(newE);
            }
            auto* p = new ProductionRule(E);
            p->addProductionTerms(firstGroup.at(i));
            p->addProductionTerm(newE);
            newPR.push_back(p);
            vector<SyntacticTerm *>tmp = eliminateLeftFactoring(newE);
            newEs.insert(newEs.end(), tmp.begin(), tmp.end());
        }else{
            newPR.insert(newPR.end(), map[term].begin(), map[term].end());
        }
    }
    E->setProductions(newPR);

    return newEs;
}

vector<SyntacticTerm *> LL1Converter::convertToLL1(const vector<SyntacticTerm *> &terms) {
    if(terms.empty()){
        return terms;
    }
    vector<SyntacticTerm *>tmp = eliminateLeftRecursion(terms);
    return eliminateLeftFactoring(tmp);
}
