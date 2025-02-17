/*
This header file contains the function/method declarations for the
lexpproh module.
*/

// Conditional pre processor directive.
// Include guard to prevent importing headerfile more than once.
#ifndef TOKPP_H
#define TOKPP_H

#include <string>
#include <vector>

// Token kinds which can be processed.
enum type {
    
    KEYWORD,
    IDENTIFIER,
    INT,
    STRING,
      
    // Assignment character.
    EQUALS,

    SEMI_COLON,

    // Grouping tokens.
    OPEN_PAREN,
    CLOSE_PAREN,

    UNKNOWN
};

// The struct of a token. Any token consists of a value and a token kind.
struct Token {
    std::string value;
    enum type kind;
};

// Convert TokenKind to string. The returned string is the 
// classification of the current token.
std::string GetTokenKindName(enum type kind)
{
    switch (kind) {
    case KEYWORD:
        return "KEYWORD";
    case IDENTIFIER:
        return "IDENTIFIER";
    case INT:
        return "INT";
    case STRING:
        return "STRING";
    case EQUALS:
        return "EQUALS";
    case SEMI_COLON:
        return "SEMI_COLON";
    case OPEN_PAREN:
        return "OPEN_PAREN";
    case CLOSE_PAREN:
        return "CLOSE_PAREN";
    default:
        return "UNKNOWN";
    }
}

// Print tokens.
void PrintTokens(std::vector<Token*> tokens) {
    int counter = 0;
    for (Token* temp : tokens) {
        counter++;
        std::cout << counter << ")" << " " << GetTokenKindName(temp->kind) << " " << "(" << temp->value << ")" << std::endl;
    }
}

#endif