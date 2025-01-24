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
#include <iostream>

// Token kinds which can be processed.
enum class TokenKind {
    CHAR,
};

// The struct of a token. Any token consist of a value and a token kind.
struct Token {
    std::string value;
    TokenKind kind;

    Token(TokenKind k, const std::string& v)
        : kind(k), value(v)
    {}
};

// Lexical analyzer.
class Lexer {
    private:
        // String to be processed.
        std::string input;
        size_t pos;
        // Mapping of tokens. Every token has an assigned tokenkind.
        std::unordered_map<std::string, TokenKind> tokenMap;
    
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

// Lookup table to get the right string for the specified tokenkind.
std::string getTokenKindName(TokenKind type)
{
    switch (type) {
    case TokenKind::CHAR:
        return "CHAR";
    default:
        return "UNDEFINED";
    }
}

// Function to print all tokens
void printTokens(const std::vector<Token>& tokens)
{
    for (const auto& token : tokens) {
        std::cout << "Type: " << getTokenKindName(token.kind)
             << ", Value: " << token.value << std::endl;
    }
}

#endif