//
// Created by Michael Said on 2020-03-22.
//

#include "Edge.h"
Edge::Edge(Node* destination, char startAlphabte , char endAlphabte) {
    this->destination = destination;
    this->startAlphabte = startAlphabte;
    this->endAlphabte = endAlphabte;
    this->sizeOfAlphabte = endAlphabte - startAlphabte + 1;
}

Edge::~Edge() {

    free(this->destination);
    this->disallowedAlphabet.clear();
}

Node *Edge::getDestination() const {
    return destination;
}

void Edge::setDestination(Node *destination) {
    Edge::destination = destination;
}

char Edge::getStartAlphabte() const {
    return startAlphabte;
}

void Edge::setStartAlphabte(char startAlphabte) {
    Edge::startAlphabte = startAlphabte;
}

char Edge::getEndAlphabte() const {
    return endAlphabte;
}

void Edge::setEndAlphabte(char endAlphabte) {
    Edge::endAlphabte = endAlphabte;
}

int Edge::getSizeOfAlphabte() const {
    return sizeOfAlphabte;
}

void Edge::setSizeOfAlphabte(int sizeOfAlphabte) {
    Edge::sizeOfAlphabte = sizeOfAlphabte;
}

const unordered_set<char> &Edge::getDisallowedAlphabet() const {
    return disallowedAlphabet;
}

void Edge::setDisallowedAlphabet(const unordered_set<char> &disallowedAlphabet) {
    Edge::disallowedAlphabet = disallowedAlphabet;
}

void Edge::addDisallowedSymbol(const char symbol) {
    this->disallowedAlphabet.insert(symbol);
    if(symbol >= this->startAlphabte && symbol <= this->endAlphabte){
        this->sizeOfAlphabte--;
    }
}

bool Edge::isAcceptSymbol(const char symbol) {

    if(this->disallowedAlphabet.find(symbol) != this->disallowedAlphabet.end()){
        return false;
    }
    return symbol >= this->startAlphabte && symbol <= this->endAlphabte;
}

Node *Edge::doTransition(const char symbol) {

    if (this->isAcceptSymbol(symbol)){
        return this->destination;
    }
    return nullptr;
}

bool Edge::isEPSTransition() const {
    return this->startAlphabte == EPS && this->endAlphabte == EPS;
}
