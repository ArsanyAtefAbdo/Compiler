//
// Created by Michael Said on 2020-04-14.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_SYNTACTICTERM_H
#define LEXICAL_ANALYZER_GENERATOR_SYNTACTICTERM_H

#include "ProductionTerm.h"
#include "ProductionRule.h"

/*
 * This class represents the non-terminal (syntactic-variable) of the productions.
 * This class inheritances from ProductionTerm class.
 * Any non-terminal can be represented by many production
 * ex p1 : E -----> E + E
 *    p2 : E -----> E / E .....
 * so there is vector of production sorted based on the order of productions in CFG file.
 */
class ProductionRule;
class SyntacticTerm : public ProductionTerm {
public:
    explicit SyntacticTerm(const string &name);
    ~SyntacticTerm();
    vector<ProductionRule *> getProductions() const;
    void addProduction(ProductionRule* p);
    const unordered_set<string> &getFirst() const;
    void setFirst(const unordered_set<string> &firstSet);
    const unordered_set<string> &getFollow() const;
    void setFollow(const unordered_set<string> &followSet);
    string toString();
    /*
     * return true if there is epsilon production.
     */
    bool isDerivingToEpsilon();

private:

    vector<ProductionRule *> productions;
    unordered_set<string>first;
    unordered_set<string>follow;

};


#endif //LEXICAL_ANALYZER_GENERATOR_SYNTACTICTERM_H
