//
// Created by Arsany on 2020-04-17.
//

#include "Parser.h"
#include "../../Components/Scanner.h"
#include "../File_Reader/ReadInputFile.h"

Parser::Parser(const string &lexical_file, const string& CFGFileName, bool printTable) {
    scanner = new Scanner(lexical_file, printTable);

    productions = ReadInputFile::getInstance()->read_from_file(CFGFileName);

    productions = LL1Converter::getInstance()->convertToLL1(productions);

    auto* ptable = new ParsingTable();
    //table contain under each input which production will be used
    table = ptable->getTable(productions);

}

vector<string> Parser::parsing(const string& programFileName) {
    // t--> has token(terminal) and value
    // first production
    vector<string> output{};
    if (!scanner->scanProgramFile(programFileName) || productions.empty() || table.empty()){
        return output;
    }
    SyntacticTerm* temp;
    ProductionRule prodTemp;
    stack<ProductionTerm*> stack{};
    output.push_back(productions.front()->getName());
    bool error = false;
    stack.push(new ProductionTerm("$", Terminal));
    stack.push(productions.front());
    if(!scanner->hasNextToken()){
        return output;
    }
    Token *t = scanner->getNextToken();

    while (true){
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
                error = true;
                output.push_back("Error: missing '" + stack.top()->getName() + "'");
                stack.pop();
            } else{
                stack.pop();
            }
        }else{
            temp = (SyntacticTerm*) stack.top();
            if (table.at(temp).find(t->getName()) == table.at(temp).end()){
                //Error:(illegal non-terminal) – discard terminal
                error = true;
                output.push_back("Error: illegal '" + stack.top()->getName()+ "'" + "Discard '" + t->getName() + "'");
                if(scanner->hasNextToken()){
                    t = scanner->getNextToken();
                }else{
                    break;
                }
            }else{
                if (table.at(temp).at(t->getName()).isSync()){
                    stack.pop();
                }else{
                    prodTemp = table.at(temp).at(t->getName());
                    stack.pop();
                    output.push_back(prodTemp.toString());

                    for (auto it = prodTemp.getTerms().rbegin(); it != prodTemp.getTerms().rend(); it++){
                        stack.push(*it);
                    }
                }
            }
        }
    }
    if (!error && stack.empty()){
        output.emplace_back("Accept");
    }else{
        output.emplace_back("Not-Accept");
    }
    return output;
}
