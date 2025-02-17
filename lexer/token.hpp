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
enum class TokenKind {
    
    KEYWORD,
    IDENTIFIER,
    INT,
    STRING,
      
    // Assignment character.
    EQUALS,

    // Delimiter/Separator characters.
    SEMI_COLON,
    COLON,
    COMMA,
    DOT,

    // Comments
    HASHTAG,

    // Grouping tokens.
    OPEN_PAREN,
    CLOSE_PAREN,

    UNKNOWN
};

// The struct of a token. Any token consists of a value and a token kind.
struct Token {
    std::string value;
    TokenKind kind;
};

// Create a new token to append it to result vector.
const Token NewToken(TokenKind kind, std::string value){
    Token token{.value = value, .kind = kind};
    return token;
}

// Convert TokenKind to string. The returned string is the 
// classification of the current token.
std::string GetTokenKindName(TokenKind kind)
{
    switch (kind) {
    case TokenKind::KEYWORD:
        return "KEYWORD";
    case TokenKind::IDENTIFIER:
        return "IDENTIFIER";
    case TokenKind::INT:
        return "INT";
    case TokenKind::STRING:
        return "STRING";
    case TokenKind::EQUALS:
        return "EQUALS";
    case TokenKind::SEMI_COLON:
        return "SEMI_COLON";
    case TokenKind::COLON:
        return "COLON";
    case TokenKind::COMMA:
        return "COMMA";
    case TokenKind::DOT:
        return "DOT";
    case TokenKind::HASHTAG:
        return "HASHTAG";
    case TokenKind::OPEN_PAREN:
        return "OPEN_PAREN";
    case TokenKind::CLOSE_PAREN:
        return "CLOSE_PAREN";
    default:
        return "UNKNOWN";
    }
}

// Print tokens.
void PrintTokens(std::vector<Token> tokens) {
    int counter = 0;
    for (Token temp : tokens) {
        counter++;
        std::cout << counter << ")" << " " << GetTokenKindName(temp.kind) << " " << "(" << temp.value<< ")" << std::endl;
    }
}

#endif