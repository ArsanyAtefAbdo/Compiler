//
// Created by Arsany on 2020-03-24.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_MINIMIZER_H
#define LEXICAL_ANALYZER_GENERATOR_MINIMIZER_H

#include "DFA.h"

class Node;
class NFA;
class Minimizer {
public:
    map <Node* , map<char , Node*>> DFAMinimize( DFA* dfa,const set<char>& alphabet);
    vector<vector<Node*>> Minimize (vector<vector<Node*>> partitions);
    bool areStatesUnique(vector<vector<Node*>> partitions, Node* state1, Node* state2);
    bool containedBySamePartition(vector<vector<Node*>> partitions, Node* State1, Node* State2);
    bool containState(vector<vector<Node*>> partitions, Node* state);
    void updateTable(vector<Node*> temp);

private:
    vector<Node*> Finalstates;
    vector<Node*> Nonfinalstates;
    vector<vector<Node*>> partitions;
    map <Node* , map<char , Node*>> DFAStates;

public:
    const vector<Node*> getFinalstates() const;

    void setFinalstates(const vector<Node*> finalstates);

    const vector<Node*> getNonfinalstates() const;

    void setNonfinalstates(const vector<Node*> nonfinalstates);

    const vector<vector<Node*>> getPartitions() const;

    void setPartitions(const vector<vector<Node*>> partitions);

    const map <Node* , map<char , Node*>> getDfaStates() const;

    void setDfaStates(const map <Node* , map<char , Node*>> dfaStates);

};

#endif //LEXICAL_ANALYZER_GENERATOR_MINIMIZER_H