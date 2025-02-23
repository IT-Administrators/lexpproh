// g++ src/main.cpp -o test.exe

#include "lexer/lexer.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <regex>

using namespace std;

int main(int argc, char* argv[]) {

    // Check if more than two arguments are provided.
    if (argc > 2)
    {
        // Show wrong arguments.
        std::cerr << "Too many arguments: ";
        for (size_t i = 2; i < argc; i++)
        {
            std::cerr << argv[i] << " ";
        }
        std::cout << std::endl;
        exit(1);
    }
    else
    {
        // Catch empty parameter.
        const char* filepath;
        if (argv[1] == NULL)
        {
            filepath = "./examples/";
        }
        else 
        {
            filepath = argv[1];
        }

        // Check if provided argument is a directory. And lex all files.
        if (std::filesystem::is_directory(filepath))
        {
            for (const auto & entry : std::filesystem::directory_iterator(filepath)) {
        
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
        }
        else if (std::filesystem::is_regular_file(filepath))
        {
            // If provided argument is a file. Lex only provided file.
            std::cout << "PROCESSING FILE: " << filepath << std::endl;
                
            std::ifstream sourcefilestream(filepath);
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
        else
        {
            // If provided argument is a file. Lex only provided file.
            std::cout << "PROCESSING STRING: " << argv[1] << std::endl;
    
            Lexer lexer(argv[1]);
            std::vector<Token> tokens = lexer.tokenize();
            PrintTokens(tokens);
        }
    }

    return 0;
}