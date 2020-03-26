//
// Created by Yomna on 3/23/2020.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_DFA_H
#define LEXICAL_ANALYZER_GENERATOR_DFA_H
#include <map>
#include "NFA.h"
class Node;
class NFA;
class DFA {
public:
    map <Node* , map<char , Node*>> NFAtoDFA( NFA* nfa,const set<char>& alphabet);
    static set<Node*> closure(set<Node *> nodes);
//    set<Node*> closure(Node * node);
    static set<Node *> move(const set<Node*>& nodes, char symbol);
    map<Node*, map<char , Node*>> getDtable() const;
private:
    map <Node* , map<char , Node*>> Dtable;
    static bool compsets(const set<Node*>&x ,set<Node*>y);
    /**
     Sim:
     map<   Node*        ,        map<char , Node*>    >
            dfaStates
                             a   b   c   d   e ...    <----- alphabet
               A             B   -   -   E   - ...    <----- go from A to B by input a.
               .
               .
               .
     **/
     Node* nullNode = new Node("null",false);
     map <set<Node*>,Node*> ndStates;
};
#endif //LEXICAL_ANALYZER_GENERATOR_DFA_H
