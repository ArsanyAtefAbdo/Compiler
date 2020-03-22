//
// Created by Michael Said on 2020-03-22.
//
#ifndef LEXICAL_ANALYZER_GENERATOR_EDGE_H
#define LEXICAL_ANALYZER_GENERATOR_EDGE_H
#include <iostream>
#include <bits/stdc++.h>
#include "Node.h"

#define EPS '\0'
using namespace std;

class Node;
class Edge {
public:
    Edge(Node* destination, char startAlphabte , char endAlphabte);
    virtual ~Edge();

public:
    Node *getDestination() const;

    void setDestination(Node *destination);

    char getStartAlphabte() const;

    void setStartAlphabte(char startAlphabte);

    char getEndAlphabte() const;

    void setEndAlphabte(char endAlphabte);

    int getSizeOfAlphabte() const;

    void setSizeOfAlphabte(int sizeOfAlphabte);

    const unordered_set<char> &getDisallowedAlphabet() const;

    void setDisallowedAlphabet(const unordered_set<char> &disallowedAlphabet);

    void addDisallowedSymbol(char symbol);

    bool isAcceptSymbol(char symbol);

    Node* doTransition(char symbol);

    bool isEPSTransition() const ;

private:

    Node* destination;
    char startAlphabte;
    char endAlphabte;
    int sizeOfAlphabte;
    unordered_set<char> disallowedAlphabet;

};


#endif //LEXICAL_ANALYZER_GENERATOR_EDGE_H
