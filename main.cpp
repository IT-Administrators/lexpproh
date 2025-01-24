// g++ main.cpp -o test.exe

#include "lexer/lexer.hpp"

#include <fstream>
#include <iostream>

#include <regex>

using namespace std;

int main() {

    char ch;
    std::ifstream testfile;
    // Create stream object of text.
    testfile.open("./examples/test01");
    
    // Read file char by char.
    while (testfile.get(ch))
    {
        std::string s(1, ch);
        Lexer lexer(s);
        std::vector<Token> tokens = lexer.tokenize();
        printTokens(tokens);
    }
    
    // string s = "abcd";
    // Lexer lexer(s);
    // std::vector<Token> tokens = lexer.tokenize();
    // printTokens(tokens);

    // regex t("[a-zA-Z]");
    // cout << regex_match("T", t) << endl;


    testfile.close();  

    return 0;
}