//
// Created by Michael Said on 2020-04-14.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_LL1CONVERTER_H
#define LEXICAL_ANALYZER_GENERATOR_LL1CONVERTER_H
#include "../Components/ProductionRule.h"
#include "../Parsing Table Constructor/ParsingTable.h"

class LL1Converter {

public:
    ~LL1Converter() = default;
    static LL1Converter *getInstance();
    vector<SyntacticTerm*>  convertToLL1(const vector<SyntacticTerm*>& terms);
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
    /*
* This function eliminate Left Factoring from productions of non-terminal (E)
* return a new non-terminal terms (E' E'' ....)
* ex term : E ----> abB | aB | cdg | cdeB | cdfB (input)
*
*    term : E ----> aE' | cdE''
*    return value : E' -----> bB | B
     *              E'' ----> g | eB | fB
*/
    vector<SyntacticTerm*> eliminateLeftFactoring(SyntacticTerm* E);
    bool isContainLeftRecursion(SyntacticTerm* E);

    vector<SyntacticTerm*>  eliminateLeftRecursion(const vector<SyntacticTerm*>& terms);
    vector<SyntacticTerm*>  eliminateLeftFactoring(const vector<SyntacticTerm*>& terms);

    bool intersectionSets(const unordered_set<string>&s1, const unordered_set<string>&s2);

};


#endif //LEXICAL_ANALYZER_GENERATOR_LL1CONVERTER_H
