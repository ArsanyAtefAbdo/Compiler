//
// Created by Michael Said on 2020-03-22.
//


#ifndef LEXICAL_ANALYZER_GENERATOR_NODE_H
#define LEXICAL_ANALYZER_GENERATOR_NODE_H
#include <iostream>
#include <bits/stdc++.h>
#include "Edge.h"
#define FINALSTATE true
using namespace std;

class Edge;
class Node {
public:
    Node(string name , int isFinal);
    explicit Node(int isFinal);
    virtual ~Node();

private:
    string name;
    int isFinal;
    vector<Edge*>edges;

public:
    int isFinalState() const;

    void setIsFinal(int isFinal);

    const string &getName() const;

    void setName(const string &name);

    vector<Edge*> getEdges() const;

    void addEdge(Edge* edge);

};


#endif //LEXICAL_ANALYZER_GENERATOR_NODE_H
