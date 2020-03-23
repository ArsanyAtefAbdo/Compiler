//
// Created by Michael Said on 2020-03-22.
//

#include "Node.h"

#include <utility>
#include "Edge.h"

Node::Node(string name, bool isFinal) {
    this->isFinal = isFinal;
    this->name = std::move(name);

}
Node::~Node() {
    this->edges.clear();
}
Node::Node(bool isFinal) {
    this->isFinal = isFinal;
}

const string &Node::getName() const {
    return name;
}

void Node::setName(const string &name) {
    this->name = name;
}

bool Node::isFinalState() const {
    return isFinal;
}

void Node::setIsFinal(bool isFinal) {
    this->isFinal = isFinal;
}

vector<Edge *> Node::getEdges() const{
    return this->edges;
}

void Node::addEdge(Edge* edge)  {
    this->edges.push_back(edge);
}

