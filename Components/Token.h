//
// Created by Michael Said on 2020-04-17.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_TOKEN_H
#define LEXICAL_ANALYZER_GENERATOR_TOKEN_H
#include "DFA.h"

class Token {
public:
    Token(string name, string lexeme);

    const string &getName() const;

    const string &getLexeme() const;

private:
    string name;

    string lexeme;
};


#endif //LEXICAL_ANALYZER_GENERATOR_TOKEN_H
