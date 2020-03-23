//
// Created by Michael Said on 2020-03-22.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_NFA_H
#define LEXICAL_ANALYZER_GENERATOR_NFA_H
#include "Node.h"

class Node;
class NFA {
public:
    NFA(Node *start, Node *end);
    virtual ~NFA();

public:
    Node *getStart() const;

    void setStart(Node *start);

    Node *getEnd() const;

    void setEnd(Node *end);

    string toString();

private:
    Node* start;
    Node* end;

};


#endif //LEXICAL_ANALYZER_GENERATOR_NFA_H
