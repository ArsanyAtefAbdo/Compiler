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

void Parser::parsing(string programFileName) {
    scanner->scanProgramFile(programFileName);
    // t--> has token(terminal) and value
    // first production
    SyntacticTerm* Firstproduction = productions.front();
    SyntacticTerm* temp;
    ProductionRule prodTemp;
    stack<ProductionTerm*> stack;
    vector<string> output;
    bool error = false;
    stack.push(new ProductionTerm("$", Terminal));
    stack.push(Firstproduction);
    for (Token *t = scanner->getNextToken(); scanner->hasNextToken();){
        if (stack.top()->getType() == Terminal){
            if (stack.top()->getName() == t->getName()){
                stack.pop();
                t = scanner->getNextToken();
            }else{
                //ERROR (missing terminal of stack)
                error = true;
                output.push_back("Error: missing '" + stack.top()->getName() + "'");
                stack.pop();
            }
        }else{
            temp = (SyntacticTerm*) stack.top();
            if (table.at(temp).find(t->getName()) == table.at(temp).end()){
                //Error:(illegal non-terminal) – discard terminal
                error = true;
                output.push_back("Error: illegal '" + stack.top()->getName()+ "'" + "Discard '" + t->getName() + "'");
                t = scanner->getNextToken();
            }else{
                if (table.at(temp).at(t->getName()).isSync()){
                    stack.pop();
                }else{
                    prodTemp = table.at(temp).at(t->getName());
                    stack.pop();
                    output.push_back(prodTemp.toString());
                    for (int i = prodTemp.getTerms().size()-1; i >= 0; i--){
                        if(!prodTemp.getTerms().at(i)->isEpsilon()){
                            stack.push(prodTemp.getTerms().at(i));
                        }
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
    while (!stack.empty()){
        cout << stack.top()->getName()<<endl;
        stack.pop();
    }
    for(int i = 0; i < output.size() ; i++){
        cout << output.at(i) << endl;
    }
}
