# cmake_minimum_required(VERSION <specify CMake version here>)
project(Lexical_Analyzer_Generator)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(SOURCE_FILES main.cpp)

add_executable(Lexical_Analyzer_Generator main.cpp Components/Node.cpp Components/Node.h Components/Edge.cpp Components/Edge.h Components/NFA.cpp Components/NFA.h Builder/Builder.cpp Builder/Builder.h Components/DFA.cpp Components/DFA.h Components/ReadLexicalRulesFile.cpp  Components/ReadLexicalRulesFile.h Components/LexicalRule.h Components/LexicalRuleBuilder.cpp Components/LexicalRuleBuilder.h Components/Minimizer.h Components/Minimizer.cpp Converter/Converter.cpp Converter/Converter.h Components/Scanner.cpp Components/Scanner.h Parser_Generator/Components/ProductionRule.cpp Parser_Generator/Components/ProductionRule.h Parser_Generator/Components/ProductionTerm.h Parser_Generator/Components/SyntacticTerm.cpp Parser_Generator/Components/SyntacticTerm.h "Parser_Generator/LL(1) Converter/LL1Converter.cpp" "Parser_Generator/LL(1) Converter/LL1Converter.h" "Parser_Generator/Parsing Table Constructor/ParsingTable.cpp" "Parser_Generator/Parsing Table Constructor/ParsingTable.h" Parser_Generator/File_Reader/ReadInputFile.cpp Parser_Generator/File_Reader/ReadInputFile.h Components/Token.cpp Components/Token.h Parser_Generator/Evaluator/Parser.cpp Parser_Generator/Evaluator/Parser.h)