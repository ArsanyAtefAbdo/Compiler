//
// Created by Michael Said on 2020-04-17.
//

#include "Token.h"

#include <utility>

Token::Token(string name, string lexeme) : name(std::move(name)), lexeme(std::move(lexeme)) {}

const string &Token::getName() const {
    return name;
}

const string &Token::getLexeme() const {
    return lexeme;
}
