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
    STRING,
    NUMBER,
    ASSIGNMENT,
    IDENTIFIER,

    _UNDEFINED
};

// The struct of a token. Any token consists of a value and a token kind.
struct Token {
    std::string value;
    TokenKind kind;

    Token(TokenKind k, const std::string& v)
        : kind(k), value(v)
    {}
};

// Get the right string to the provided token kind.
std::string GetTokenKindName(TokenKind type)
{
    switch (type) {
    case TokenKind::CHAR:
        return "CHAR";
    case TokenKind::STRING:
        return "STRING";
    case TokenKind::NUMBER:
        return "NUMBER";
    case TokenKind::ASSIGNMENT:
        return "ASSIGNMENT";
    case TokenKind::IDENTIFIER:
        return "IDENTIFIER";
    default:
        return "UNDEFINED";
    }
}

// Function to print all tokens
void PrintTokens(const std::vector<Token>& tokens)
{  
    for (const auto& token : tokens) {
        std::cout << GetTokenKindName(token.kind) << " (" << token.value << ")" << std::endl;
    }
}

#endif