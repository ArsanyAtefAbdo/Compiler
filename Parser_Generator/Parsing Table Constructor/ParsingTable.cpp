//
// Created by Yomna on 4/15/2020.
//

#include "ParsingTable.h"

ParsingTable *ParsingTable::getInstance() {
    if(instance == nullptr){
        instance = new ParsingTable();
        cons = false;
    }
    return instance;
}

map<SyntacticTerm*, map<string, ProductionRule>> *ParsingTable::getTable(set<SyntacticTerm*> non_terminal) {
    settingFirstANDFollow(non_terminal);
    return nullptr;
}

unordered_set<string> ParsingTable::getFirst(SyntacticTerm* non_terminal) {
    unordered_set<string> res;
    if (first.find(non_terminal) == first.end()) {
        vector<ProductionRule *> x = non_terminal->getProductions();
        /// loop on each production rule and get from it first
        for (auto productionRule:x) {
            unordered_set<string> onePR;
            int index = 0;
            SyntacticTerm *firstTerm = (SyntacticTerm *) productionRule->getTerms().at(index);
            /// if symbol is terminal then add to the list
            if (firstTerm->getType() == Terminal) {
                table.find(non_terminal)->second.find(firstTerm->getName())->second = *productionRule;
                res.insert(firstTerm->getName());
                ///else  if symbol is non-terminal then compute its first then add it
            } else {
                if (firstTerm->isEpsilon()) {
                    onePR.insert("EPS");
                    res.insert("EPS");
                } else {
                    unordered_set<string> temp;
                    /// if the first is already computed add it
                    if (first.find(firstTerm) == first.end()) {
                        temp = first.at(firstTerm);
                        ///else  if it's not computed before then recursive call the function
                    } else {
                        temp = getFirst(firstTerm);
                    }
                    /// handling special case for having epsilon at first of the first non-terminal terms.
                    while (temp.find("EPS") != temp.end()) {
                        temp.erase("EPS");
                        res.insert(temp.begin(), temp.end());
                        onePR.insert(temp.begin(), temp.end());
                        index++;
                        if (index == productionRule->getTerms().size()) {
                            temp.insert("EPS");
                            break;
                        } else {
                            SyntacticTerm *nextTerm = (SyntacticTerm *) productionRule->getTerms().at(index);
                            temp = getFirst(nextTerm);
                        }
                    }
                    res.insert(temp.begin(), temp.end());
                    onePR.insert(temp.begin(), temp.end());
                }
            }
            for (auto c:onePR){
                table.find(non_terminal)->second.find(c)->second = *productionRule;
            }
        }
        first.insert(pair<SyntacticTerm *, unordered_set<string>>(non_terminal, res));
        non_terminal->setFirst(res);
        return res;
    } else {
        non_terminal->setFirst(first.at(non_terminal));
        return first.at(non_terminal);
    }
}

//unordered_set<string> ParsingTable::getFollow(SyntacticTerm* non_terminal) {
//    return follow.find(non_terminal)->second;
//}

void ParsingTable::setFollowTable(set<SyntacticTerm*> non_terminal) {
    map<SyntacticTerm*, unordered_set<SyntacticTerm*>> nonterm_follow;
    /// setting the sets foe follow results
    for (auto item:non_terminal) {
        unordered_set<string> newSet;
        unordered_set<SyntacticTerm*> newSetT;
        follow.insert(pair<SyntacticTerm*, unordered_set<string>>(item,newSet));
        nonterm_follow.insert(pair<SyntacticTerm*, unordered_set<SyntacticTerm*>>(item,newSetT));
    }
    /// loop on all non terminals
    for (auto item:non_terminal){
        /// loop on all productions of each non-terminal item
        for (auto p:item->getProductions()) {
            vector<ProductionTerm *> terms =p->getTerms();
            if (item == terms.at(0)) { /// If S is the start symbol   $ is in FOLLOW(S)
                follow.find(item)->second.insert("$");
            }
            /// loop on terms of each production rule twice: forward and backward
            for (int i = 1;i <terms.size();i++){
                if (terms.at(i-1)->getType() == NonTerminal) {
                    if (terms.at(i)->getType() == Terminal) {
                        follow.find((SyntacticTerm *) terms.at(i - 1))->second.insert(terms.at(i)->getName());
                    } else { ///  if  A-> aBb  is a production rule  everything in FIRST(b) is FOLLOW(B) except EPS
                        unordered_set<string> temp = first.find((SyntacticTerm *)terms.at(i))->second;
                        temp.erase(temp.find("EPS"));
                        follow.find((SyntacticTerm *) terms.at(i - 1))->second.insert(temp.begin(),temp.end());
                    }
                }
            }
            /// loop backward to get cases for the epsilon in last elements
            if (terms.at(terms.size()-1)->getType() == NonTerminal){
                nonterm_follow.find((SyntacticTerm *) terms.at(terms.size()-1))->second.insert((SyntacticTerm *) item);
            }
            for (int i = terms.size()-1;i >= 0;i--){
                if (terms.at(i)->getType() == NonTerminal && terms.at(i-1)->getType() == NonTerminal){
                    if (first.find((SyntacticTerm *)terms.at(i))->second.find("EPS") != first.find((SyntacticTerm *)terms.at(i))->second.end() ){
                        nonterm_follow.find((SyntacticTerm *) terms.at(i - 1))->second.insert((SyntacticTerm *) item);
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
        }
    }
    /// loop to finalize the follow results and remove non-terminal from it
    int i;
    do {
        for (auto item:nonterm_follow) {
            i = 0;
            if (item.second.size() == 0) {
                i++;
                /// eliminate non-terminal from other elements
                for (auto item2:nonterm_follow) {
                    if ((item2 != item) && item2.second.find(item.first) != item2.second.end()) {
                        follow.find((SyntacticTerm *) item2.first)->second.insert(
                                follow.find(item.first)->second.begin(), follow.find(item.first)->second.end());
                    }
                    item2.second.erase(item2.second.find(item.first));
                }
            }
        }
    } while (i < nonterm_follow.size());
}

void ParsingTable::settingFirstANDFollow(set<SyntacticTerm *> non_terminal) {
    if (!cons) {
        for (auto i:non_terminal) {
            getFirst(i);
        }
        setFollowTable(non_terminal);
        for (auto i:non_terminal) {
            i->setFollow(follow.find(i)->second);
            /// add sync to table
//            for (auto c:i->getFollow()){
//                table.find(i)->second.find(c)->second = *synch;
//            }
        }
        cons = true;
    }
}
