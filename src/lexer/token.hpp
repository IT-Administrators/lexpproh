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
    _EOF,

    KEYWORD,
    IDENTIFIER,
    INT,
    FLOAT,
    STRING,
      
    // Assignment character.
    EQUALS,

    // Delimiter/Separator characters.
    SEMI_COLON,
    COLON,
    COMMA,
    DOT,

    //Operator
    MULT,
    PLUS,
    MINUS,
    SLASH,
    BACK_SLASH,
    LESSER,
    GREATER,
    MODULO,
    QUESTION_MARK,
    EXCLAMATION_MARK,

    AMPERSAND,
    PIPE,
    ROOF, // ^ 

    // Comments
    HASHTAG,

    // Grouping tokens.
    OPEN_PAREN,
    CLOSE_PAREN,
    OPEN_BRACK,
    CLOSE_BRACK,
    OPEN_CURLY,
    CLOSE_CURLY,

    // Start of a string.
    DOUBLE_QUOTES,
    SINGLE_QUOTE,

    UNKNOWN
};

// The struct of a token. Any token consists of a value and a token kind.
struct Token {
    std::string value;
    TokenKind kind;
    // Describes the position of the token in the input text.
    int lineNumber;
    int characterNumber;
};

// // Create a new token to append it to result vector.
// const Token NewToken(TokenKind kind, std::string value){
//     Token token{.value = value, .kind = kind};
//     return token;
// }

// Create a new token to append it to result vector.
const Token NewToken(TokenKind kind, std::string value, int lineNumber, int characterNumber){
    Token token{.value = value, .kind = kind, .lineNumber = lineNumber, .characterNumber = characterNumber};
    return token;
}

// Convert TokenKind to string. The returned string is the 
// classification of the current token.
std::string GetTokenKindName(TokenKind kind)
{
    switch (kind) {
    case TokenKind::_EOF:
        return "EOF";
    case TokenKind::KEYWORD:
        return "KEYWORD";
    case TokenKind::IDENTIFIER:
        return "IDENTIFIER";
    case TokenKind::INT:
        return "INT";
    case TokenKind::FLOAT:
        return "FLOAT";
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
    case TokenKind::MULT:
        return "MULT";
    case TokenKind::PLUS:
        return "PLUS";
    case TokenKind::MINUS:
        return "MINUS";
    case TokenKind::SLASH:
        return "SLASH";
    case TokenKind::BACK_SLASH:
        return "BACK_SLASH";
    case TokenKind::LESSER:
        return "LESSER";
    case TokenKind::GREATER:
        return "GREATER";
    case TokenKind::MODULO:
        return "MODULO";
    case TokenKind::QUESTION_MARK:
        return "QUESTION_MARK";
    case TokenKind::EXCLAMATION_MARK:
        return "EXCLAMATION_MARK";
    case TokenKind::AMPERSAND:
        return "AMPERSAND";
    case TokenKind::PIPE:
        return "PIPE";
    case TokenKind::ROOF:
        return "ROOF";
    case TokenKind::HASHTAG:
        return "HASHTAG";
    case TokenKind::OPEN_PAREN:
        return "OPEN_PAREN";
    case TokenKind::CLOSE_PAREN:
        return "CLOSE_PAREN";
    case TokenKind::OPEN_BRACK:
        return "OPEN_BRACK";
    case TokenKind::CLOSE_BRACK:
        return "CLOSE_BRACK";
    case TokenKind::OPEN_CURLY:
        return "OPEN_CURLY";
    case TokenKind::CLOSE_CURLY:
        return "CLOSE_CURLY";
    case TokenKind::DOUBLE_QUOTES:
        return "DOUBLE_QUOTES";
    case TokenKind::SINGLE_QUOTE:
        return "SINGLE_QUOTE";
    default:
        return "UNKNOWN";
    }
}

// Print tokens.
void PrintTokens(std::vector<Token> tokens) {
    int counter = 0;
    for (Token temp : tokens) {
        counter++;
        std::cout << counter << ")" << " " << temp.lineNumber << "," << temp.characterNumber << " " << GetTokenKindName(temp.kind) << " " << "(" << temp.value << ")" << std::endl;
    }
} 

#endif