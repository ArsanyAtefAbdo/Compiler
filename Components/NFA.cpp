//
// Created by Michael Said on 2020-03-22.
//

#include "NFA.h"

NFA::NFA(Node *start, Node *end) {
    this->start = start;
    this->end = end;
}

Node *NFA::getStart() const {
    return start;
}

void NFA::setStart(Node *start) {
    NFA::start = start;
}

Node *NFA::getEnd() const {
    return end;
}

void NFA::setEnd(Node *end) {
    NFA::end = end;
}

NFA::~NFA() {
    free(this->start);
    free(this->end);
}

string NFA::toString() {
    string str;
    unordered_map<Node*, unsigned>visited{};
    queue<Node*>s;
    unsigned count = 0;
    visited[this->start] = count;
    s.push(this->start);
    count++;
    while (!s.empty()){
        Node* node = s.front();s.pop();

        for(Edge* e:node->getEdges()){
            Node* targetNode = e->getDestination();
            if(visited.find(targetNode) == visited.end()){
                visited[targetNode] = count;
                count++;
                s.push(targetNode);
            }
            if(e->isEPSTransition()){
                str += "s" + to_string(visited[node]) + " ----->" + "s" +  to_string(visited[targetNode])+ "\n";
            }else{
                str += "s" + to_string(visited[node]) + " ---("+e->getStartAlphabet()+"-"+e->getEndAlphabet()+")-->" + "s" +  to_string(visited[targetNode])+ "\n";
            }
        }

    }
    str += "START : s" + to_string(visited[this->start]) + " END : s" + to_string(visited[this->end]) + "\n";
    return str;
}
