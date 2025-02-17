/*
This header file contains the function/method declarations for the
lexpproh module.
*/

// Conditional pre processor directive.
// Include guard to prevent importing headerfile more than once.
#ifndef LEXPP_H
#define LEXPP_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "token.hpp"

// Lexical analyzer.
class Lexer {
    private:
        // String to be processed.
        std::string input;
        // Current position.
        int pos;
        // Current character.
        char currentCharacter;
        // Size of input.
        int size;
        // Linenumber if text contains newline characters.
        int lineNumber;
        // Characternumber per line.
        int characterNumber;

    // Return character at current position and advance position by 1.
    const char Advance() {
        if (pos < size)
        {
            // Save current character.
            char temp = currentCharacter;
            pos++;
            // Advance character number to keep track of it.
            characterNumber++;
            currentCharacter = (pos < size) ? input[pos] : '\0';
            return temp;
        }
        else
        {
            return '\0';
        }
    }

    // Skip blank characters.
    void Skip() {
        while (currentCharacter == ' ' || currentCharacter == '\n' || currentCharacter == '\t' || currentCharacter == '\r')
        {
            // Tracking the current position.
            if (currentCharacter == '\n')
            {
                lineNumber++;
                characterNumber = 1;
            }
            Advance();
        }
    }

    // Check if we have reached EOF.
    [[nodiscard]] const bool AtEof(){
        return Lexer::pos >= Lexer::input.length();        
    }

    // Tokenize identifiers. Identifiers are strings which are not enclosed in "".
    Token* TokenizeIdentifier() {
        std::stringstream buffer;
        // Append character to buffer.
        buffer << Advance();

        while (isalnum(currentCharacter) || currentCharacter == '_')
        {
            // Append all other characters to buffer.
            buffer << Advance();
        }
        
        Token* newToken = new Token();
        newToken->kind = IDENTIFIER;
        newToken->value = buffer.str();

        return newToken;
    }
    // Tokenize integers.
    Token* TokenizeInt() {
        std::stringstream buffer;
        while (isdigit(currentCharacter))
        {
            buffer << Advance();
        }
        
        Token* newToken = new Token();
        newToken->kind = INT;
        newToken->value = buffer.str();
        return newToken;
    }

    // Tokenize special characters. Appends current character and specified tokenkind to vector.
    Token* TokenizeSpecial(enum type kind){
        Token* newToken = new Token();
        newToken->kind = kind;
        newToken->value = std::string(1, Advance());

        return newToken;
    }

    public:
    // Lexer constructor.
    Lexer(std::string source)
    : input(source), pos(0), size(source.length()), currentCharacter(source.at(pos)), lineNumber(1), characterNumber(1)
    {}

    // Function to tokenize the input string.
    [[nodiscard]] std::vector<Token*> tokenize()
    {
        // Result vector.
        std::vector<Token*> tokens;
        while (!AtEof())
        {
            Skip();
            if (isalpha(currentCharacter) || currentCharacter == '_')
            {
                tokens.push_back(TokenizeIdentifier());
                continue;
            }
            if (isdigit(currentCharacter))
            {
                tokens.push_back(TokenizeInt());
                continue;
            }
            switch (currentCharacter)
            {
            case ';':
                tokens.push_back(TokenizeSpecial(SEMI_COLON));
                break;
            case '=':
                tokens.push_back(TokenizeSpecial(EQUALS));
                break;
            case '(':
                tokens.push_back(TokenizeSpecial(OPEN_PAREN));
                break;
            case ')':
                tokens.push_back(TokenizeSpecial(CLOSE_PAREN));
                break;          
            default:
                std::cout << "UNIDENTIFIED: " << "(" << std::string(1,currentCharacter) << ")" << " ";
                std::cout << "LINE NUMBER: " << lineNumber << " " << "CHARACTER NUMBER: " << characterNumber << std::endl;
                exit(1);
            }
        }
        return tokens;
    }
};
#endif