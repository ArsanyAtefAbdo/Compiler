#include <iostream>
#include "Components/ReadLexicalRulesFile.h"
#include "Components/Node.h"
#include "Components/DFA.h"
#include "Builder/Builder.h"

using namespace std;


int main() {
//    auto* parser = new ReadLexicalRulesFile();
//    parser->read_from_file("test.txt");
    Node* start = new Node("0",false);
    Node* end = new Node(true);
    Node* one = new Node("1", false);
    Node* two = new Node("2", false);
    Edge* e2e = new Edge(end , 'a', 'z');
    e2e->addDisallowedSymbol('t');
    two->addEdge(e2e);
    Edge* e21 = new Edge(two , 'a', 'z');
    e21->addDisallowedSymbol('t');
    one->addEdge(e21);
    Edge* es1 = new Edge(one , 'a', 'z');
    es1->addDisallowedSymbol('t');
    start->addEdge(es1);
    NFA* n = new NFA(start,end);
    DFA* d = new DFA();
    set<char> alphabet = {'a','b','c','d','e','f'};
    map<Node *, map<char, struct Node *>> ans = d->NFAtoDFA(n, alphabet);
    cout << ans.size() << ans.size() << endl;

    auto* parser = new ReadLexicalRulesFile();
    parser->read_from_file("test.txt");
    NFA* nfa = Builder::getInstance()->buildNFAFromLexicalRules(parser->getRules());
    cout << nfa->toString();
    return 0;
}
