//
// Created by Michael Said on 2020-03-22.
//
#include "Test_Components.h"
#include "Node.h"
#include "Edge.h"
using namespace std;

void test1_components (){
    Node* start = new Node("0");
    Node* end = new Node(true);
    Edge* edge = new Edge(end , 'a', 'z');
    edge->addDisallowedSymbol('t');
    start->addEdge(edge);
    cout << start->getEdges().at(0)->isAcceptSymbol('A');

}
