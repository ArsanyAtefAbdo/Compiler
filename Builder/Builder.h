//
// Created by Michael Said on 2020-03-22.
//

#ifndef LEXICAL_ANALYZER_GENERATOR_BUILDER_H
#define LEXICAL_ANALYZER_GENERATOR_BUILDER_H
#include "../Components/NFA.h"

class NFA;
class Builder {
public:
    virtual ~Builder() = default;
    static Builder* getInstance();

private:
    Builder() = default;
    static Builder* instance;

    NFA* buildLetterRecognizer(char letter);
    NFA* buildEPSRecognizer();
    NFA* buildAlphabetRecognizer(char startAlphabet , char endAlphabet);
    NFA* buildORRecognizer(NFA* recognizer1, NFA* recognizer2);
    NFA* buildCombineRecognizer(NFA* recognizer1, NFA* recognizer2);
    NFA* buildANDRecognizer(NFA* recognizer1, NFA* recognizer2);
    NFA* buildClosureRecognizer(NFA* recognizer);
    NFA* buildPositiveClosureRecognizer(NFA* recognizer);

};


#endif //LEXICAL_ANALYZER_GENERATOR_BUILDER_H
