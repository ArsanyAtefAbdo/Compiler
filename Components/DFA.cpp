//
// Created by Yomna on 3/23/2020.
//

#include "DFA.h"

/// The subset construction of a DFA from an NFA.
/// constructs a transition table Dtable.
map <Node* , map<char , Node*>> DFA::NFAtoDFA( NFA* nfa,const set<char>& alphabet) {

    map <set<Node*>,Node*> ndStates;
    map <Node*,bool> mark;
    set<Node *> nfaState;
    int i = 0;
    nfaState.insert(nfa->getStart());
    nfaState = closure(nfaState);
    Node * dfaState = new Node("A",false);
    ndStates.insert(pair<set<Node*>,Node*>(nfaState,dfaState));
    mark.insert(pair<Node*,bool>(dfaState,false));
    map <set<Node*>,Node*>::iterator itr;
    map <set<Node*>,Node*>::iterator itr2;
    for (itr = ndStates.begin(); (itr != ndStates.end()) ; itr++) {  // loop on all states we get
        i++;
        nfaState = itr->first;
        dfaState = itr->second;
        if (!mark.find(dfaState)->second) {
            mark.at(dfaState) = true;
            map <char , Node*> drow ;
            for (auto c:alphabet) {    // loop on each input symbol
                set<Node *> u = closure(move(nfaState, c));
                bool found = false;
                for (itr2 = ndStates.begin(); (itr2 != ndStates.end()) ; itr2++) {
                    if (u == itr2->first) {
                        drow.at(c) = itr2->second;
                        Edge nedge = Edge(itr2->second, c, c);
                        dfaState->addEdge(&nedge);
                        found = true;
                    }
                }
                if (!found) {
                    std::string s(1, 'A'+i);
                    Node * d = new Node(s,false);
                    ndStates.insert(pair<set<Node*>,Node*>(u,d));
                    mark.insert(pair<Node*,bool>(d,false));
                }
            }
            Dtable.insert(pair<Node* , map<char , Node*>>(dfaState,drow));
        }
    }
    return Dtable;
}

/// Set of Nodes "NFA states" reachable from some NFA state in nodes "NFA states" on ε-transitions alone
set<Node *> DFA::closure(set<Node *> nodes) {
    set<Node *>::iterator itr;
    for (itr = nodes.begin(); itr != nodes.end(); itr++) { // loop on all nodes
        vector<Edge *> edges = (*itr)->getEdges();
        Edge *x;
        for (auto &edge : edges) { // loop on edges of each node
            x = edge;
            if (x->isEPSTransition()) {
                nodes.insert(x->getDestination());
            }
        }
    }
    return nodes;
}

/// Set of nodes "NFA states" reachable from node "certain NFA state" on ε-transitions alone
set<Node *> DFA::closure(Node *node) {
    set<Node *> nodes;
    nodes.insert(node);
    vector<Edge *> edges = node->getEdges();
    Edge *x;
    for (auto &edge : edges) { // loop on edges of each node
        x = edge;
        if (x->isEPSTransition()) {
            nodes.insert(x->getDestination());
        }
    }
    return closure(nodes);
}

/// Set of Nodes "NFA states" to which there is a transition on input char symbol from some state s in nodes.
set<Node *> DFA::move(set<Node *> nodes, char symbol) {
    set<Node *>::iterator itr;
    set<Node *> res;
    for (itr = nodes.begin(); itr != nodes.end(); itr++) { // loop on all nodes
        vector<Edge *> edges = (*itr)->getEdges();
        Edge *x;
        for (auto &edge : edges) { // loop on all edges of each node
            x = edge;
            if (x->isAcceptSymbol(symbol)) {
                res.insert(x->doTransition(symbol));
            }
        }
    }
    return res;
}

map<Node *, map<char, Node *>> DFA::getDtable() const {
    return Dtable;
}
