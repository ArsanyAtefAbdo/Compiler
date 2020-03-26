#include <iostream>
#include "Components/ReadLexicalRulesFile.h"
#include "Components/Node.h"
#include "Components/DFA.h"
#include "Builder/Builder.h"

using namespace std;
#define EPS '\0'

int main() {
//    auto* parser = new ReadLexicalRulesFile();
//    parser->read_from_file("test.txt");


//    auto* parser = new ReadLexicalRulesFile();
//    parser->read_from_file("test.txt");
//    NFA* nfa = Builder::getInstance()->buildNFAFromLexicalRules(parser->getRules());
//    cout << nfa->toString();


    Node* nine = new Node("9",false);
    Node* ten = new Node("10",true);
    Node* seven = new Node("7", false);
    Node* one = new Node("1", false);
    Node* five = new Node("5",false);
    Node* six = new Node("6",false);
    Node* eight = new Node("8", false);
    Node* two = new Node("2", false);
    Node* four = new Node("4", false);
    Edge* a = new Edge(seven ,  EPS, EPS);
    eight->addEdge(a);
    Edge* b = new Edge(ten , EPS, EPS);
    nine->addEdge(b);
    Edge* c = new Edge(seven , EPS, EPS);
    nine->addEdge(c);
    Edge* d = new Edge(one , EPS, EPS);
    seven->addEdge(d);
    Edge* e = new Edge(five , EPS, EPS);
    seven->addEdge(e);
    Edge* f = new Edge(six , 'c', 'c');
    five->addEdge(f);
    Edge* g = new Edge(eight , EPS, EPS);
    six->addEdge(g);
    Edge* h = new Edge(ten , EPS, EPS);
    eight->addEdge(h);
    Edge* i = new Edge(eight , EPS, EPS);
    four->addEdge(i);
    Edge* j = new Edge(four , 'b', 'b');
    two->addEdge(j);
    Edge* k = new Edge(two , 'a', 'a');
    one->addEdge(k);

    NFA* n = new NFA(nine,ten);
    DFA* df = new DFA();

    set<char> alphabet = {'a','b','c'};
       map<Node *, map<char, Node *>> ans = df->NFAtoDFA(n, alphabet);
       cout << "size = " <<ans.size() << endl;
        for (auto itr:ans){
        Node* z = itr.first;
        cout << z->getName() << " is " << z->isFinalState() << endl;
            for (auto &x:(itr).second) {
                Node *p = (x).second;
                cout << p->getName() << endl;

            }
            cout << "end line" << endl;
        }
    return 0;
}
