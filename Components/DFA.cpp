//
// Created by Yomna on 3/23/2020.
//

#include "DFA.h"

/// The subset construction of a DFA from an NFA.
/// constructs a transition table Dtran, Each state of D is a set of NFA states.
vector<vector<Node *>> DFA::NFAtoDFA(const NFA& nfa,const set<char>& alphabet) {
    vector<vector<Node *>> res;
    set<Node *> nfaState;
    Node *dfaState = nullptr;
    int i = 0;
    set<Node *> u;
    set<Edge *> y;
    nfaState.insert(nfa.getStart());
    nfaState = closure(nfaState);
    nfaStates.push_back(nfaState);
    dfaStates.push_back(dfaState);
    mark.at(i) = true;
    set<set<Node *>>::iterator itr;
    for (int j = 0; j < nfaStates.size(); j++) {  // loop on all states we get
        nfaState = nfaStates.at(j);
        dfaState = dfaStates.at(j);
        for (auto c:alphabet) {    // loop on each input symbol
            u = closure(move(nfaState, c));
            bool found = false;
            for (int k = 0; k < nfaStates.size(); k++) {
                if (u == nfaStates.at(k)) {
                    Dtran.at(i).at(c) = dfaStates.at(k);
                    Edge nedge = Edge(dfaStates.at(k), '-', '-'); //ttrdel
                    dfaState->addEdge(&nedge );
                    found = true;
                }
            }
            if (!found) {
                nfaStates.push_back(u);
                Node *ndfaState = nullptr;
                dfaStates.push_back(ndfaState);
            }
        }
    }
    return res;
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

