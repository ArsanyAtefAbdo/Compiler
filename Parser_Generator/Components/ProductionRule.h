//
// Created by Michael Said on 2020-04-14.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_PRODUCTIONRULE_H
#define LEXICAL_ANALYZER_GENERATOR_PRODUCTIONRULE_H
#include "ProductionTerm.h"
#include "SyntacticTerm.h"

/*
 * This class represents the production of Context-Free Grammars.
 * ex E ----> E + E
 */

class SyntacticTerm;
class ProductionRule {
public:
    explicit ProductionRule(SyntacticTerm* nonTerminal);
    vector<ProductionTerm*> getTerms() const;
    void addProductionTerm(ProductionTerm* t);
    SyntacticTerm *getNonTerminal() const;
    string toString();
    /*
     * return true if production is Epsilon (empty string)
     * ex E ------> EPS
     */
    bool isEpsilon();

private:

    vector<ProductionTerm*> terms;
    /*
     * the left hand side of production
     * ex E ------> id
     * nonTerminal = E
     */
    SyntacticTerm* nonTerminal;


};
#endif //LEXICAL_ANALYZER_GENERATOR_PRODUCTIONRULE_H
