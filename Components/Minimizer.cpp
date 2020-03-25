//
// Created by Arsany on 2020-03-24.
//

#include "Minimizer.h"
#include <map>
#include <string>
#include <algorithm>

// minimizer function
map<Node *, map<char, Node *>> Minimizer::DFAMinimize(DFA *dfa, const set<char> &alphabet) {

    // get dfa before minimizing
    DFAStates = dfa->getDtable();

    // loop on these states to differentiate between final and non final
    // put the final and non final in two vectors
    map <Node* , map<char , Node*>>::iterator itr;
    for (itr = DFAStates.begin(); itr != DFAStates.end(); itr++){
        if (itr->first->isFinalState()){
            Finalstates.push_back(itr->first);
        } else {
            Nonfinalstates.push_back(itr->first);
        }
    }

    // the final and non final put them in queue of vector of nodes
    partitions.push_back(Nonfinalstates);
    partitions.push_back(Finalstates);

    vector<vector<Node*>> result;
    result = Minimize(partitions);
     int index = 0;
     for (vector<Node*> r:result){
         for (Node* N:r){
             /*
              * inserting in map (MinStates)
              */
         }
     }

 /*   // loop inside the final and non final each alone then partition them again under the input
    vector<Node*> NonequalStates;
    while (!partitions.empty()){
        vector<Node*>p = partitions.front();
        partitions.pop();
        for (int i = 0; i < p.size() - 1; i++){
            vector<vector<Node*>> temp;
            vector<Node*> equalStates;
            for (int j = i + 1; j < p.size(); j++){
                equalStates.push_back((p.at(i)));
                if (DFAStates.at(p.at(i)) == DFAStates.at(p.at(j))){
                    equalStates.push_back(p.at(j));
                }else{
                    NonequalStates.push_back(p.at(j));
                }
            }
            temp.push_back(equalStates);
            if (!NonequalStates.empty()){
                partitions.push(NonequalStates);
            }
        }
    }*/

    return MinStates;
}

/*
 * minimize the results
 */
vector<vector<Node *>> Minimizer::Minimize(vector<vector<Node *>> partitions) {

    vector<vector<Node*>> res;

    int index = 0;
    for (vector<Node*> p:partitions){
        if (p.size() > 1){
            for (int i = 0; i < p.size(); i++){

                // if already in partition
                if (containState(res, p.at(i))){
                    continue;
                }
                vector<Node*> temp;
                temp.push_back(p.at(i));

                for (int j = i + 1; j < p.size(); j++){
                    Node* s1 = p.at(i);
                    Node* s2 = p.at(j);

                    if (!areStatesUnique(partitions, s1, s2)){
                        temp.push_back(s2);
                    }
                }
                res.push_back(temp);
            }
        }else{
            // when group contain one state only
            res.push_back(p);
        }
    }
    // if already minimized
    if (partitions.size() == res.size()){
        return res;
    }

    return Minimize(res);
}

/*
 * return true if two states are unique
 */
bool Minimizer::areStatesUnique(vector<vector<Node*>> partitions, Node *state1, Node *state2) {
    for (vector<Node*>p:partitions){
        for(Node* N:p){
            if (!containedBySamePartition(partitions, state1, state2)){
                return true;
            }
        }
    }
    return false;
}

/*
 * return true if two states are in the same partition
 */
bool containedBySamePartition(vector<vector<Node*>> partitions, Node* State1, Node* State2) {
    for (vector<Node*> p:partitions){
        if ((std::find(p.begin(), p.end(), State1) != p.end()) && (std::find(p.begin(), p.end(), State2) != p.end())){
            return true;
        }
    }
    return false;
}

/*
 * return true if partition contain state
 */
bool Minimizer::containState(vector<vector<Node*>> partitions, Node* state) {
    vector<vector<Node*>>::iterator itr;
    vector<Node*> ::iterator itr2;
    for (vector<Node*> p:partitions){
        for (Node* N:p){
            if (N == state){
                return true;
            }
        }
    }
    return false;
}

const vector<Node*> Minimizer::getFinalstates() const{
return Finalstates;
}

void Minimizer::setFinalstates(const vector<Node*> finalstates) {
    Finalstates = finalstates;
}

const vector<Node*> Minimizer::getNonfinalstates() const{
return Nonfinalstates;
}

void Minimizer::setNonfinalstates(const vector<Node*> nonfinalstates) {
    Nonfinalstates = nonfinalstates;
}

const vector<vector<Node*>> Minimizer::getPartitions() const{
return partitions;
}

void Minimizer::setPartitions(const vector<vector<Node*>> partitions) {
    Minimizer::partitions = partitions;
}

const map <Node* , map<char , Node*>> Minimizer::getDfaStates() const{
return DFAStates;
}

void Minimizer::setDfaStates(const map <Node* , map<char , Node*>> dfaStates) {
    DFAStates = dfaStates;
}

const map <Node* , map<char , Node*>> Minimizer::getMinStates() const{
return MinStates;
}

void Minimizer::setMinStates(const map <Node* , map<char , Node*>> minStates) {
    MinStates = minStates;
}