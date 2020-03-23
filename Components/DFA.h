//
// Created by Yomna on 3/23/2020.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_DFA_H
#define LEXICAL_ANALYZER_GENERATOR_DFA_H

#include "NFA.h"
class Node;
class NFA;
class DFA {
public:
    vector<vector<Node*>> NFAtoDFA(const NFA& nfa,const set<char>& alphabet);

private:
    vector <set<Node*>> nfaStates;
    vector<vector<Node*>> Dtran;
    vector<Node*> dfaStates;
    vector<bool> mark;
    /**
    Sim:
        nfaStates   dfaStates  mark              Dtran
                                          a   b   c   d   e ...
         <..,..>        A       1         B   -   -   E   - ...
         .
         .
         .
    **/
    static set<Node*> closure(set<Node *> nodes);
    set<Node*> closure(Node * node);
    static set<Node *> move(set<Node*> nodes, char symbol);

};
#endif //LEXICAL_ANALYZER_GENERATOR_DFA_H
