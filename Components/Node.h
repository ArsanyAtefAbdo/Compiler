//
// Created by Michael Said on 2020-03-22.
//


#ifndef LEXICAL_ANALYZER_GENERATOR_NODE_H
#define LEXICAL_ANALYZER_GENERATOR_NODE_H
#include <iostream>
#include <bits/stdc++.h>
#include "Edge.h"

using namespace std;

class Edge;
class Node {
public:
    Node(string& name , bool isFinal);
    explicit Node(bool isFinal);
    virtual ~Node();

private:
    string name;
    bool isFinal;
    vector<Edge*>edges;

public:
    bool isFinal1() const;

    void setIsFinal(bool isFinal);

    const string &getName() const;

    void setName(const string &name);

    vector<Edge*> getEdges() const;

    void addEdge(Edge* edge);
};


#endif //LEXICAL_ANALYZER_GENERATOR_NODE_H
