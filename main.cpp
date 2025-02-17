// g++ main.cpp -o test.exe

#include "lexer/lexer.hpp"

#include <fstream>
#include <iostream>

#include <regex>

using namespace std;

int main() {

    std::ifstream sourcefilestream("./examples/test02.txt");
    std::stringstream buffer;
    char temp;

    while (sourcefilestream.get(temp))
    {
        buffer << temp;
    }
    std::string sourceCode = buffer.str();
    Lexer lexer(sourceCode);
    std::vector<Token *> tokens = lexer.tokenize();
    PrintTokens(tokens);

    return 0;
}