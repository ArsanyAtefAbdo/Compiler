//
// Created by Michael Said on 2020-03-24.
//

#include "LexicalRuleBuilder.h"
LexicalRuleBuilder* LexicalRuleBuilder::instance = nullptr;

LexicalRuleBuilder::~LexicalRuleBuilder() {
    this->mapOfTerms.clear();
}

LexicalRuleBuilder *LexicalRuleBuilder::getInstance() {
    if(!instance){
        instance = new LexicalRuleBuilder();
    }
    return instance;
}

LexicalRule *LexicalRuleBuilder::buildPostFixRule(const pair<string,vector<string>>& rule, enum LexicalType ruleType) {
    vector<LexicalRuleTerm *>terms = buildTerms(rule.second);
    vector<LexicalRuleTerm *>postFixTerms{};
    stack<LexicalRuleTerm*>stack{};
    for(LexicalRuleTerm* term : terms){
        if(term->getType() == parenthesis){
            if(term->getValue() == ")"){
                while (!stack.empty() && stack.top()->getValue() != "(" && stack.top()->getType() != parenthesis){
                    postFixTerms.push_back(stack.top());
                    stack.pop();
                }
                stack.pop();
            }else{
                stack.push(term);
            }
        } else if(term->getType() == Operation){
            if(term->getValue() == "@" || term->getValue() == "|"){
                while(!stack.empty() && (stack.top()->getType() == Operation && !(stack.top()->getValue() == "|"))
                                    && !(stack.top()->getType() == parenthesis && stack.top()->getValue() == "(")){
                    postFixTerms.push_back(stack.top());
                    stack.pop();
                }
            }
            stack.push(term);
        }else if(term->getType() == WORD && this->mapOfTerms.find(term->getValue()) != this->mapOfTerms.end()){
            vector<LexicalRuleTerm *>tempTerms = this->mapOfTerms.at(term->getValue());
            postFixTerms.insert(postFixTerms.end() , tempTerms.begin(), tempTerms.end());
        }else{
            postFixTerms.push_back(term);
        }
    }
    while(!stack.empty()){
        postFixTerms.push_back(stack.top());
        stack.pop();
    }
    this->mapOfTerms.insert(pair<string, vector<LexicalRuleTerm*>>(rule.first, postFixTerms));
    return new LexicalRule(rule.first , ruleType , postFixTerms);
}

vector<LexicalRule *>LexicalRuleBuilder::buildRules(const vector<string> &rules, enum LexicalType rulesType) {
    vector<LexicalRule*>results;
    for(const string& word: rules){
        auto* LRule = new LexicalRule(word, rulesType);
        LRule->addTerm(new LexicalRuleTerm(word, WORD));
        results.push_back(LRule);
    }
    return results;
}

vector<LexicalRuleTerm *> LexicalRuleBuilder::buildTerms(const vector<string> &rule) {
    vector<LexicalRuleTerm *>terms{};
    for(string s:rule){
        if(isOperation(s)){
            terms.push_back(new LexicalRuleTerm(s, Operation));
        }else if(s.find('-') == 1 && s.size() == 3){
            terms.push_back(new LexicalRuleTerm(s, CharGroup));
        }else if(s.find('\\') < s.size()){
            s.erase(remove(s.begin(), s.end(), '\\'), s.end());
            if(s == "L"){
                terms.push_back(new LexicalRuleTerm(s, EPSILON));
            }else {
                terms.push_back(new LexicalRuleTerm(s, WORD));
            }
        }else if(s == "(" || s == ")"){
            terms.push_back(new LexicalRuleTerm(s, parenthesis));
        }else if(!s.empty() && s != " "){
            terms.push_back(new LexicalRuleTerm(s, WORD));
        }
    }
    vector<LexicalRuleTerm *>expandedTerms{};
    for(int i = 0; i < terms.size() - 1 ; i++){
        LexicalRuleTerm* curTerm = terms.at(i);
        LexicalRuleTerm* nextTerm = terms.at(i+1);
        expandedTerms.push_back(curTerm);
        if(checkExpanding(curTerm, nextTerm)){
            expandedTerms.push_back(new LexicalRuleTerm("@", Operation));
        }
    }
    expandedTerms.push_back(terms.back());
    terms.clear();
    return expandedTerms;
}
bool LexicalRuleBuilder::isOperation(const string &s) {
    return s == "+" || s == "*" || s == "|";
}

bool LexicalRuleBuilder::checkExpanding(LexicalRuleTerm *curTerm, LexicalRuleTerm *nextTerm) {

    bool checkCur = (curTerm->getType() == WORD || curTerm->getType() == CharGroup || curTerm->getType() == EPSILON) ||
                    (curTerm->getType() == Operation && (curTerm->getValue() == "+" || curTerm->getValue() == "*")) ||
                    (curTerm->getType() == parenthesis && curTerm->getValue() == ")");

    bool checkNext = (nextTerm->getType() == WORD || nextTerm->getType() == CharGroup || nextTerm->getType() == EPSILON) ||
                     (nextTerm->getType() == parenthesis && nextTerm->getValue() == "(");

    return checkCur && checkNext;
}
