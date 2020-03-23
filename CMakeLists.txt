# cmake_minimum_required(VERSION <specify CMake version here>)
project(Lexical_Analyzer_Generator)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lexical_Analyzer_Generator main.cpp Components/Node.cpp Components/Node.h Components/Edge.cpp Components/Edge.h Components/Test_Components.cpp Components/Test_Components.h Components/NFA.cpp Components/NFA.h Builder/Builder.cpp Builder/Builder.h Components/DFA.cpp Components/DFA.h)