//
// Created by Michael Said on 2020-03-22.
//

#include "Builder.h"
Builder* Builder::instance = nullptr;

Builder* Builder::getInstance()  {

    if(!instance){
        instance = new Builder();
    }
    return instance;
}

NFA* Builder::buildEPSRecognizer() {
    return Builder::buildLetterRecognizer(EPS);
}

NFA* Builder::buildLetterRecognizer(char letter) {

    return buildAlphabetRecognizer(letter, letter);
}

NFA *Builder::buildAlphabetRecognizer(char startAlphabet, char endAlphabet) {
    Node* start = new Node("0" , !FINALSTATE);
    Node* end = new Node("1" , FINALSTATE);
    start->addEdge(new Edge(end, startAlphabet, endAlphabet));
    return new NFA(start, end);
}

NFA *Builder::buildORRecognizer(NFA *recognizer1, NFA *recognizer2) {
    Node* start = new Node(!FINALSTATE);
    Node* end = new Node (FINALSTATE);

    recognizer1->getEnd()->setIsFinal(!FINALSTATE);
    recognizer2->getEnd()->setIsFinal(!FINALSTATE);

    start->addEdge(new Edge(recognizer1->getStart(), EPS, EPS));
    start->addEdge(new Edge(recognizer2->getStart(), EPS, EPS));

    recognizer1->getEnd()->addEdge(new Edge(end, EPS, EPS));
    recognizer2->getEnd()->addEdge(new Edge(end, EPS, EPS));

    free(recognizer1);
    free(recognizer2);

    return new NFA(start, end);
}

NFA *Builder::buildANDRecognizer(NFA *recognizer1, NFA *recognizer2) {
    Node* start = recognizer1->getStart();
    Node* end = recognizer2->getEnd();

    recognizer1->getEnd()->setIsFinal(!FINALSTATE);
    recognizer1->getEnd()->addEdge(new Edge(recognizer2->getStart(), EPS, EPS));

    free(recognizer1);
    free(recognizer2);

    return new NFA(start, end);
}

NFA *Builder::buildClosureRecognizer(NFA *recognizer) {

    NFA* result = buildPositiveClosureRecognizer(recognizer);
    result->getStart()->addEdge(new Edge(result->getEnd(), EPS, EPS));

    return result;
}

NFA *Builder::buildPositiveClosureRecognizer(NFA *recognizer) {

    Node* start = new Node(!FINALSTATE);
    Node* end = new Node (FINALSTATE);
    start->addEdge(new Edge(recognizer->getStart(), EPS, EPS));

    recognizer->getEnd()->setIsFinal(!FINALSTATE);

    recognizer->getEnd()->addEdge(new Edge(recognizer->getStart(), EPS, EPS));
    recognizer->getEnd()->addEdge(new Edge(end, EPS, EPS));

    free(recognizer);

    return new NFA(start, end);
}

NFA *Builder::buildCombineRecognizer(NFA *recognizer1, NFA *recognizer2) {

    Node* start = new Node(!FINALSTATE);

    start->addEdge(new Edge(recognizer1->getStart(), EPS, EPS));
    start->addEdge(new Edge(recognizer2->getStart(), EPS, EPS));

    free(recognizer1);
    free(recognizer2);

    return new NFA(start, nullptr);
}
