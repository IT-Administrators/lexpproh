/*
This header file contains the function/method declarations for the
lexpp module.
*/

// Conditional pre processor directive.
// Include guard to prevent importing headerfile more than once.
#ifndef LEXPP_H
#define LEXPP_H

#include <string>
#include <vector>
#include <unordered_map>
#include <regex>

#include "token.hpp"

// Lexical analyzer.
class Lexer {
    private:
        // String to be processed.
        std::string input;
        size_t pos;
    
    bool isWhitespace(char c) const{
        std::regex ws("\\s+");
        std::string s(1,c);
        return std::regex_match(s, ws);
        // return c == ' ' || c == '\t' || c == '\n' || c == '\r';
    }

    bool isAlpha(char c){
        std::regex an("[a-zA-Z]");
        std::string s(1,c);
        return std::regex_match(s, an);
        // return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    bool isDigit(char c) {
        std::regex dg("[0-9]");
        std::string s(1,c);
        return std::regex_match(s, dg);
        // return c >= '0' && c <= '9';
    }

    std::string getNextWord()
    {
        size_t start = pos;
        while (pos < input.length() && isAlpha(input[pos])) {
            pos++;
        }
        return input.substr(start, pos - start);
    }

    public:
    // Function to tokenize the input string
    std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;

        while (pos < input.length()) {
            char currentChar = input[pos];
            if (isAlpha(currentChar)) {
                std::string word = getNextWord();
                tokens.emplace_back(TokenKind::CHAR, word);
            }
        }
        return tokens;
    }

    // Lexer constructor.
    Lexer(const std::string& source)
        : input(source) , pos(0)
    {}
};

#endif