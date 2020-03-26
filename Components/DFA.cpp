//
// Created by Yomna on 3/23/2020.
//

#include "DFA.h"

/// The subset construction of a DFA from an NFA.
/// constructs a transition table Dtable.
map <Node*, map<char, Node*>> DFA::NFAtoDFA( NFA* nfa,const set<char>& alphabet)
{
    set<Node *> nfaState ;
    nfaState.clear();
    ndStates.clear();
    map <Node*,bool> mark;
    mark.clear();
    int i = 0;
    nfaState.insert(nfa->getStart());
    nfaState = closure(nfaState);
    Node * dfaState = new Node("A",false);
    for (auto f:nfa->getFinalStates()) {
        if (nfaState.find(f) != nfaState.end()) {
            dfaState->setIsFinal(true);
            break;
        }
    }
    ndStates.insert(pair<set<Node*>,Node*>(nfaState,dfaState));
    mark.insert(pair<Node*,bool>(dfaState,false));
    int flag = 0;
    int bsize ;
    do {
        bsize = ndStates.size();
        flag = 0;
        for (const auto& itr:ndStates)    // loop on all states we get
        {
            nfaState = itr.first;
            dfaState = itr.second;
            if (!mark.find(dfaState)->second) {
                flag--;
                if (mark.find(dfaState) != mark.end()){
                    mark.find(dfaState)->second = true;
                }
                auto *drow = new map<char, Node *>();
                drow->clear();
                map <char,Node*>::iterator it2;
                for (auto c:alphabet)      // loop on each input symbol
                {
                    drow->insert(pair<char,Node*>(c,nullNode));
                    if (move(nfaState, c).empty()) {
                        continue;
                    }
                    set<Node *> u = closure(move(nfaState, c));
                    bool found = false;
                    for (const auto& itr2:ndStates) {
                        if (compsets(u,itr2.first)) {
                            if (drow->find(c) != drow->end()){
                                drow->find(c)->second = itr2.second;
                            }
                            Edge* nedge = new Edge(itr2.second, c, c);
                            dfaState->addEdge(nedge);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        i++;
                        std::string s(1, 'A'+ i);
                        Node *d = new Node(s, false);
                        d->setName(s);
                        if (drow->find(c) != drow->end()){
                            drow->find(c)->second = d;
                        }
                        Edge * nedge = new Edge(d, c, c);
                        dfaState->addEdge(nedge);
                        ndStates.insert(pair<set<Node *>, Node *>(u, d));
                        mark.insert(pair<Node *, bool>(d, false));
                    }
                }
                Dtable.insert(pair<Node *, map<char, Node *>>(dfaState, *drow));
            }
            for (auto f:nfa->getFinalStates()) {
                if (nfaState.find(f) != nfaState.end()) {
                    dfaState->setIsFinal(true);
                    break;
                }
            }
        }
    } while (flag != 0 || bsize != ndStates.size());
//    for (const auto& x:ndStates) {
//        Node *p = x.second;
//        cout << p->getName() << endl;
//        for (auto &y:x.first) {
//            cout << y->getName() << " ";
//        }
//        cout << endl;
//    }
    return Dtable;
}

/// Set of Nodes "NFA states" reachable from some NFA state in nodes "NFA states" on ε-transitions alone
set<Node *> DFA::closure(set<Node *> nodes)
{
    int i = 0;
    set<Node *>::iterator itr;
    while (nodes.size() != i) {
        i = 0;
        for (itr = nodes.begin(); itr != nodes.end(); itr++)   // loop on all nodes
        {
            i++;
            vector<Edge *> edges = (*itr)->getEdges();
            Edge *x;
            for (auto &edge : edges)   // loop on edges of each node
            {
                x = edge;
                if (x->isEPSTransition()) {
                    nodes.insert(x->getDestination());
                }

            }
        }
    }
    return nodes;
}

/// Set of nodes "NFA states" reachable from node "certain NFA state" on ε-transitions alone
//set<Node *> DFA::closure(Node *node)
//{
//    set<Node *> nodes;
//    nodes.insert(node);
//    vector<Edge *> edges = node->getEdges();
//    Edge *x;
//    int i = 1;
//    for (auto &edge : edges)   // loop on edges of each node
//    {
//        x = edge;
//        if (x->isEPSTransition())
//        {
//            nodes.insert(x->getDestination());
//        }
//        i++;
//    }
//    return closure(nodes);
//}

/// Set of Nodes "NFA states" to which there is a transition on input char symbol from some state s in nodes.
set<Node *> DFA::move(const set<Node *>& nodes, char symbol)
{
    set<Node *>::iterator itr;
    set<Node *> res;
    for (itr = nodes.begin(); itr != nodes.end(); itr++)   // loop on all nodes
    {
        vector<Edge *> edges = (*itr)->getEdges();
        Edge *x;
        for (auto &edge : edges)   // loop on all edges of each node
        {
            x = edge;
            if (x->isAcceptSymbol(symbol))
            {
                res.insert(x->doTransition(symbol));
            }
        }
    }
    return res;
}

map<Node *, map<char, Node *>> DFA::getDtable() const
{
    return Dtable;
}
/// cheak if to sets are equal or not.
bool DFA::compsets(const set<Node *>& x, set<Node *> y) {
    if (x.size() != y.size()){
        return false;
    }
    int size = x.size();
    for (auto i:x){
        y.insert(i);
    }
    return y.size() == size;
}
