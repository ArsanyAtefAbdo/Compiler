//
// Created by Arsany on 2020-04-17.
//

#include "Parser.h"
#include "../../Components/Scanner.h"

Parser::Parser(const string &lexical_file, const string& CFGFileName, bool printTable) {
    scanner = new Scanner(lexical_file, printTable);

    productions = ReadInputFile::getInstance()->read_from_file(CFGFileName);

    productions = LL1Converter::getInstance()->convertToLL1(productions);

//    for(auto* p : productions){
//        cout << p->toString() << endl;
//    }

    table = ParsingTable::getInstance()->getTable(productions);
    if(printTable){
        ReadInputFile::getInstance()->printTable(CFGFileName + "_table", table ,productions);
    }
    this->ambiguous = ParsingTable::getInstance()->ambiguity();

}

bool Parser::parsing(const string& programFileName) {
    // t--> has token(terminal) and value
    // first production
    errors.clear();
    derivations.clear();

    if (!scanner->scanProgramFile(programFileName) || productions.empty() || table.empty()){
        return false;
    }
    if(this->ambiguous){
        cout << "Parser is ambiguous !!" << endl;
        return false;
    }
    SyntacticTerm* temp;
    ProductionRule prodTemp;
    stack<ProductionTerm*> stack{};

    stack.push(new ProductionTerm("$", Terminal));
    stack.push(productions.front());

    derivations.push_back({productions.front()});

    Token *t = scanner->getNextToken();

    while (!stack.empty()){

        if (stack.top()->getType() == Terminal){
            if (stack.top()->getName() == t->getName()){
                stack.pop();
                if(scanner->hasNextToken()){
                    t = scanner->getNextToken();
                }else{
                    break;
                }
            }else if(!stack.top()->isEpsilon()){
                //ERROR (missing terminal of stack)
                errors.push_back("Error: missing '" + stack.top()->getName() + "' inserted");
                stack.pop();
            } else{
                stack.pop();
            }
        }else{
            temp = (SyntacticTerm*) stack.top();
            if (table.at(temp).find(t->getName()) == table.at(temp).end()){
                //Error:(illegal non-terminal) – discard terminal
                errors.push_back("Error: illegal '" + stack.top()->getName()+ "'" + "Discard '" + t->getName() + "'");

                if(scanner->hasNextToken()){
                    t = scanner->getNextToken();
                }else{
                    break;
                }
            }else{
                prodTemp = table.at(temp).at(t->getName());
                handleDerivation(prodTemp);
                stack.pop();
                if (!prodTemp.isSync()){
                    for (auto it = prodTemp.getTerms().rbegin(); it != prodTemp.getTerms().rend(); it++){
                        stack.push(*it);
                    }
                }
            }
        }
    }
    if (errors.empty() && stack.empty()){
        errors.emplace_back("Accept");
    }else{
        errors.emplace_back("Not-Accept");
    }
    return true;
}

bool Parser::isAmbiguous() {
    return this->ambiguous;
}

vector<string> Parser::getDerivations() const{
    vector<string>output{};
    for(const auto& l : derivations){
        string s;
        for(auto* term : l){
            s += term->getName() + " ";
        }
        s.pop_back();
        output.push_back(s);
    }
    return output;
}

vector<string> Parser::getErrors() const {
    return errors;
}

void Parser::handleDerivation(ProductionRule p) {
    vector<ProductionTerm*>tmp{};
    int i = 0;
    while(i < derivations.back().size() && derivations.back().at(i) != p.getNonTerminal()){
        tmp.push_back(derivations.back().at(i));
        i++;
    }
    if(i < derivations.back().size()){
        if(!p.isEpsilon() && !p.isSync()){
            tmp.insert( tmp.end(), p.getTerms().begin(), p.getTerms().end());
        }
        i++;
    }
    while(i < derivations.back().size()){
        tmp.push_back(derivations.back().at(i));
        i++;
    }
    derivations.push_back(tmp);
}
