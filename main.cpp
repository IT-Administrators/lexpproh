// g++ main.cpp -o test.exe

#include "lexer/lexer.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <regex>

using namespace std;

int main() {

    // Read files from specified directory.
    std::string path = "./examples/";
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        
        std::cout << std::endl;
        std::cout << "PROCESSING FILE: " << entry.path() << std::endl;
        
        std::ifstream sourcefilestream(entry.path());
        std::stringstream buffer;
        char temp;

        while (sourcefilestream.get(temp))
        {
            buffer << temp;
        }
        std::string sourceCode = buffer.str();
        Lexer lexer(sourceCode);
        std::vector<Token> tokens = lexer.tokenize();
        PrintTokens(tokens);
    }

    return 0;
}