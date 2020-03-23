//
// Created by Yomna on 3/23/2020.
//

#include "DFA.h"
/// The subset construction of a DFA from an NFA.
/// constructs a transition table Dtran, Each state of D is a set of NFA states.
vector<vector<Node *>> DFA::NFAtoDFA(NFA nfa) {
    vector<vector<Node *>> res;
    set<Node *> nfaState;
    Node *dfaState;
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
        for (char c = 'a'; c < 'z'; c++) {    // loop on each input symbol tt3dl
            u = closure(move(nfaState, c)); // zawidy edge mn *itr ll x b symbol c
            bool found = false;
            for (int k = 0; k < nfaStates.size(); k++) {
                if (u == nfaStates.at(k)) {
                    Dtran.at(i).at(c) = dfaStates.at(k);
                    Edge *nedge;
                    nedge->setDestination(dfaStates.at(k));
                    dfaState->addEdge(nedge);
                    found = true;
                }
            }
            if (!found) {
                nfaStates.push_back(u);
                Node *ndfaState;
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
        for (auto & edge : edges) { // loop on edges of each node
            x = edge;
            if (x->getDestination() - x->getStartAlphabet() - x->getDisallowedAlphabet().size() ==
                nullptr) {  // e3rafy el epsilon w 3adiliha
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
    for (auto & edge : edges) { // loop on edges of each node
        x = edge;
        if (x->getDestination() - x->getStartAlphabet() - x->getDisallowedAlphabet().size() ==
            nullptr) {  // e3rafy el epsilon w 3adiliha
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
        for (auto & edge : edges) { // loop on all edges of each node
            x = edge;
            if (x->getStartAlphabet() == symbol) {  // e3tbry da el symbol w 3dliha b3d kda
                res.insert(x->getDestination());
            }
        }
    }
    return res;
}

