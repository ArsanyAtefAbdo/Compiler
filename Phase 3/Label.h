//
// Created by Michael Said on 2020-05-24.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_LABEL_H
#define LEXICAL_ANALYZER_GENERATOR_LABEL_H

#include <bits/stdc++.h>
using namespace std;

class Label {
public:
    Label();
    string getName();
public:
    static unsigned label_num;
    static char label_char;
private:
    string name;

};


#endif //LEXICAL_ANALYZER_GENERATOR_LABEL_H
