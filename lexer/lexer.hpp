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
    
    // Match any character against regex pattern.
    [[nodiscard]] const bool MatchRegex(const char c, std::regex p) {
        std::string s(1,c);
        if (std::regex_match(s, p))
        {
            return true;
        }
        return false;
    }

    // Advance current position by one.
    [[nodiscard]] std::string AdvanceN()
    {
        size_t start = pos;
        while (pos < input.length()) {
            pos++;
        }
        return input.substr(start, pos - start);
    }

    // Check if we have reached EOF.
    [[nodiscard]] const bool AtEof(){
        return Lexer::pos >= Lexer::input.length();        
    }

    [[nodiscard]] const std::string Remainder(){
        return Lexer::input.substr(Lexer::pos, Lexer::input.length());
    }

    public:
    // Function to tokenize the input string.
    [[nodiscard]] std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;
        while (!AtEof()) {
            char currentChar = input.at(pos);
            if (MatchRegex(currentChar, std::regex("[a-zA-Z]"))) {
                std::string word = AdvanceN();
                tokens.emplace_back(TokenKind::CHAR, word);
            }
            else if (MatchRegex(currentChar, std::regex("\\s+")))
            {
                pos++;
                continue;
            }          
            else if (MatchRegex(currentChar, std::regex("[0-9]")))
            {
                std::string word = AdvanceN();
                tokens.emplace_back(TokenKind::NUMBER, word);
            }
            else if (MatchRegex(currentChar, std::regex("=")))
            {
                std::string word = AdvanceN();
                tokens.emplace_back(TokenKind::ASSIGNMENT, "");
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