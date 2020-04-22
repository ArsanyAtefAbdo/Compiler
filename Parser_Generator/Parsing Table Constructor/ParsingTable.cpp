//
// Created by Yomna on 4/15/2020.
//

#include "ParsingTable.h"

map<SyntacticTerm *, map<std::string, struct ProductionRule>> ParsingTable::getTable(const vector <SyntacticTerm*>& non_terminal) {
    if(non_terminal.empty()){
        return table;
    }
    settingFirstANDFollow(non_terminal);
//    cout << "amb is "<<amb;
    return table;
}

unordered_set<string> ParsingTable::getFirst(SyntacticTerm* non_terminal) {
    unordered_set<string> res;
    if (first.find(non_terminal) == first.end()) {
        vector<ProductionRule *> x = non_terminal->getProductions();
        /// loop on each production rule and get from it first
        for (auto productionRule:x) {
            unordered_set<string> onePR;
            if (productionRule->isEpsilon()) {
                res.insert("EPS");
                continue;
            }
            int index = 0;
            auto *firstTerm = (SyntacticTerm *) productionRule->getTerms().at(index);
            /// if symbol is terminal then add to the list

            if (firstTerm->getType() == Terminal) {
                if (table.find(non_terminal) == table.end()){
                    map<std::string, struct ProductionRule> newchar;
                    newchar.insert(pair<std::string, struct ProductionRule>(firstTerm->getName(),*productionRule));
                    table.insert(pair<SyntacticTerm *, map<std::string, struct ProductionRule>>(non_terminal,newchar));
                } else {
                    if (table.find(non_terminal)->second.find(firstTerm->getName()) != table.find(non_terminal)->second.end()){
                        table.find(non_terminal)->second.find(firstTerm->getName())->second = *productionRule;
                    } else {
                        table.find(non_terminal)->second.insert(
                                pair<std::string, struct ProductionRule>(firstTerm->getName(), *productionRule));
                    }
                }
                res.insert(firstTerm->getName());
                ///else  if symbol is non-terminal then compute its first then add it
            } else {
                unordered_set<string> temp;
                /// if the first is already computed add it
                if (first.find(firstTerm) != first.end()) {
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
                    if (index < productionRule->getTerms().size()) {
                        auto *nextTerm = (SyntacticTerm *) productionRule->getTerms().at(index);
                        temp = getFirst(nextTerm);
                    } else {
                        temp.insert("EPS");
                        break;
                    }
                }
                res.insert(temp.begin(), temp.end());
                onePR.insert(temp.begin(), temp.end());
            }
            for (const auto& c:onePR){
                if (table.find(non_terminal) != table.end()){
                    if (table.find(non_terminal)->second.find(c) != table.find(non_terminal)->second.end()){
                        table.find(non_terminal)->second.find(c)->second = *productionRule;
                    } else {
                        table.find(non_terminal)->second.insert(pair <std::string, struct ProductionRule> (c, *productionRule));
                    }
                } else {
                    map<std::string, struct ProductionRule> newchar;
                    newchar.insert(pair<std::string, struct ProductionRule>(c, *productionRule));
                    table.insert(pair<SyntacticTerm *, map<std::string, struct ProductionRule>>(non_terminal,newchar));
                }
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

void ParsingTable::setFollowTable(vector<SyntacticTerm*> non_terminal) {
    map<SyntacticTerm*, unordered_set<SyntacticTerm*>> nonterm_follow;
    /// setting the sets foe follow results
    for (auto item:non_terminal) {
        unordered_set<string> newSet;
        unordered_set<SyntacticTerm*> newSetT;
        if (non_terminal.at(0) == item){ /// If S is the start symbol   $ is in FOLLOW(S)
            newSet.insert("$");
        }
        follow.insert(pair<SyntacticTerm*, unordered_set<string>>(item,newSet));
        nonterm_follow.insert(pair<SyntacticTerm*, unordered_set<SyntacticTerm*>>(item,newSetT));
    }
    /// loop on all non terminals
    for (auto item:non_terminal){
        /// loop on all productions of each non-terminal item
        for (auto p:item->getProductions()) {
            vector<ProductionTerm *> terms =p->getTerms();
            /// loop on terms of each production rule twice: forward and backward
            for (int i = 1;i <terms.size();i++){

                if (terms.at(i-1)->getType() == NonTerminal) {
                    if (terms.at(i)->getType() == Terminal) {
                        if (follow.find((SyntacticTerm *) terms.at(i - 1)) != follow.end()) {
                            follow.find((SyntacticTerm *) terms.at(i - 1))->second.insert(terms.at(i)->getName());
                        } else {
                            unordered_set<string> newSet;
                            newSet.insert(terms.at(i)->getName());
                            follow.insert(pair<SyntacticTerm*, unordered_set<string>>((SyntacticTerm *) terms.at(i - 1),newSet));
                        }
                    } else { ///  if  A-> aBb  is a production rule  everything in FIRST(b) is FOLLOW(B) except EPS
                        unordered_set<string> temp ;
                        if (first.find((SyntacticTerm *)terms.at(i)) != first.end()) {
                            temp = first.find((SyntacticTerm *)terms.at(i))->second;
                        } else {
                            temp = getFirst((SyntacticTerm *)terms.at(i));
                        }
                        if (temp.find("EPS") != temp.end()) {
                            temp.erase(temp.find("EPS"));
                        }
                        if (follow.find((SyntacticTerm *) terms.at(i - 1)) != follow.end()) {
                            follow.find((SyntacticTerm *) terms.at(i - 1))->second.insert(temp.begin(), temp.end());
                        } else {
                            unordered_set<string> newSet;
                            newSet.insert(temp.begin(), temp.end());
                            follow.insert(pair<SyntacticTerm*, unordered_set<string>>((SyntacticTerm *) terms.at(i - 1),newSet));
                        }
                    }
                }
            }
            /// loop backward to get cases for the epsilon in last elements
            if (terms.at(terms.size()-1)->getType() == NonTerminal && terms.at(terms.size()-1) != item){
                nonterm_follow.find((SyntacticTerm *) terms.at(terms.size()-1))->second.insert((SyntacticTerm *) item);
            }
            int n = terms.size();
            n--;
            for (int i = n;i > 0;i--){
                if (terms.at(i)->getType() == NonTerminal && terms.at(i-1)->getType() == NonTerminal){
                    if (((SyntacticTerm *) terms.at(i))->isDerivingToEpsilon() && ( terms.at(i - 1) != item)){
                        nonterm_follow.find((SyntacticTerm *) terms.at(i - 1))->second.insert(item);
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
        }
    }
    /// to finalize the follow results and remove non-terminal from it
    finalizingfollow(nonterm_follow);
}

void ParsingTable::settingFirstANDFollow(const vector<SyntacticTerm *>& non_terminal) {
    auto* synch = new ProductionRule();
    if (!cons) {
        for (auto i:non_terminal) {
            getFirst(i);
//            cout << "first " << i->toString() << " size:" << i->getFirst().size();
//            for (const auto& c:i->getFirst()) {
//                cout << " "<< c ;
//            }
//            cout <<  endl;
        }
//        cout << "end first "<<endl;
        setFollowTable(non_terminal);
//        cout << "---------------------"<<endl;
//        for (auto i:non_terminal) {
//            cout << "follow " << i->toString() << " size:" << follow.find(i)->second.size();
//            for (const auto& c:follow.find(i)->second) {
//                cout << " "<< c ;
//            }
//            cout <<  endl;
//        }
//        cout << "end follow"<<endl;
        for (auto i:non_terminal) {
            i->setFollow(follow.find(i)->second);
            /// add sync to table
            if (i->isDerivingToEpsilon()){
                for (auto *pr:i->getProductions()){
                    if (pr->isEpsilon()){
                        for (const auto& c:i->getFollow()){
                            if (table.find(i)->second.find(c) != table.find(i)->second.end()){
//                                table.find(i)->second.find(c)->second = *pr;
                                amb = true;
                            } else {
                                table.find(i)->second.insert(pair <std::string, struct ProductionRule>(c,*pr));
                            }
                        }
                        break;
                    }
                }
            } else {
                for (const auto& c:i->getFollow()) {
                    if (!(table.find(i)->second.find(c) != table.find(i)->second.end())){
                        table.find(i)->second.insert(pair <std::string, struct ProductionRule>(c,*synch));
                    }
                }
            }
        }
        cons = true;
    }
}

/// to finalize the follow results and remove non-terminal from it
void ParsingTable::finalizingfollow(map<SyntacticTerm *, unordered_set<SyntacticTerm *>> nonterm_follow) {
    int i = 0;
    int times = 0;
    do {
        times ++;
        i = 0;
        for (auto item:nonterm_follow) {
            if (!item.second.empty()) {
                i++;
                /// eliminate non-terminal from other elements
                for (auto item2:item.second) {
                    if (nonterm_follow.find(item2)->second.empty() && item.second.find(item2) != item.second.end()){
                        follow.find(item.first)->second.insert(
                                follow.find(item2)->second.begin(), follow.find(item2)->second.end());
                        item.second.erase(item.second.find(item2));
                        nonterm_follow.find(item.first)->second = item.second;
                    }
                }
            }
        }
    } while (i != 0 && times <= nonterm_follow.size());
}

bool ParsingTable::ambiguity() {
    return amb;
}
