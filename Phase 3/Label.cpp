//
// Created by Michael Said on 2020-05-24.
//

#include "Label.h"

Label::Label() {
    this->name = Label::label_char + to_string(Label::label_num);
    if(label_num == UINT_MAX){
        Label::label_char++;
    }
    label_num++;

}

string Label::getName() {
    return this->name;
}
