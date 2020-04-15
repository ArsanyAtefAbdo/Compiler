//
// Created by Michael Said on 2020-04-14.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_LL1CONVERTER_H
#define LEXICAL_ANALYZER_GENERATOR_LL1CONVERTER_H
#include "../Components/ProductionRule.h"

class LL1Converter {

public:
    ~LL1Converter() = default;
    static LL1Converter *getInstance();
    vector<SyntacticTerm*>  eliminateLeftRecursion(const vector<SyntacticTerm*>& terms);
private:
    static LL1Converter* instance;
    LL1Converter() = default;
    /*
* This function eliminate Left Recursion from productions of non-terminal (E)
* return a new non-terminal term (E')
* ex term : E ----> EA | B (input)
*
*    term : E ----> BE'
*    return value : E' -----> AE' | EPS
*/
    SyntacticTerm*  eliminateLeftRecursion(SyntacticTerm* E);
    bool isContainLeftRecursion(SyntacticTerm* E);

};


#endif //LEXICAL_ANALYZER_GENERATOR_LL1CONVERTER_H
