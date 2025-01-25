/*
This header file contains the function/method declarations for the
lexpp module.
*/

// Conditional pre processor directive.
// Include guard to prevent importing headerfile more than once.
#ifndef TOKPP_H
#define TOKPP_H

#include <string>
#include <vector>
#include <iostream>

// Token kinds which can be processed.
enum class TokenKind {
    CHAR,
};

// The struct of a token. Any token consists of a value and a token kind.
struct Token {
    std::string value;
    TokenKind kind;

    Token(TokenKind k, const std::string& v)
        : kind(k), value(v)
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