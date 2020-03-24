#include <iostream>
#include "Components/ReadLexicalRulesFile.h"
#include "Components/Node.h"
#include "Components/DFA.h"


using namespace std;


int main() {
//    auto* parser = new ReadLexicalRulesFile();
//    parser->read_from_file("test.txt");
//
//    for(string s:parser->get_keywords_vector()){
//        cout << s << " ";
//    }
//    for(char c:parser->get_punctuations_vector()){
//        cout << c << " ";
//    }
//    for(auto p:parser->get_regular_expression_vector()){
//        cout << p.first << " " << p.second << endl;
//    }
//    for(auto p:parser->get_regular_definitions_vector()){
//        cout << p.first << " " << p.second << endl;
//    }


    Node* start = new Node("0");
    Node* end = new Node(true);
    Node* one = new Node("0");
    Node* two = new Node("0");
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
    vector<vector<Node*>> ans = d->NFAtoDFA(n,alphabet);
    cout << ans.size() << ans.at(0).size() << endl;
    return 0;
}
