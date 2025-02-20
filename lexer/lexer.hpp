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
#include <unordered_map>
#include <regex>

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
        // Map of keywords.
        std::unordered_map<std::string,TokenKind> keymap {
            {"import", TokenKind::KEYWORD},
            {"from", TokenKind::KEYWORD},
            {"def", TokenKind::KEYWORD},
            {"str", TokenKind::KEYWORD},
            {"pass", TokenKind::KEYWORD},
            {"return", TokenKind::KEYWORD},
            {"int", TokenKind::KEYWORD},
        };

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

    // Check if key is in keyword map. Return false if not.
    [[nodiscard]] const bool CheckKey(std::unordered_map<std::string, TokenKind> m, std::string key){
        // If key is not present in map return false.
        if (m.find(key) == m.end())
        {
            return false;
        }
        return true; 
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
    [[nodiscard]] const Token TokenizeIdentifier() {
        std::stringstream buffer;
        // Append character to buffer.
        buffer << Advance();

        while (isalnum(currentCharacter) || currentCharacter == '_')
        {
            // Append all other characters to buffer.
            buffer << Advance();
        }
        // Check if identified token equals keyword.
        if (CheckKey(keymap, buffer.str()))
        {
            return NewToken(TokenKind::KEYWORD, buffer.str());
        }
        return NewToken(TokenKind::IDENTIFIER, buffer.str());
    }

    // Tokenize integers.
    [[nodiscard]] const Token TokenizeInt() {
        std::stringstream buffer;
        while (isdigit(currentCharacter))
        {
            buffer << Advance();
        }
        return NewToken(TokenKind::INT, buffer.str());
    }
    
    // Tokenize comments to ignore them. Uses a regular expression to match comments.
    // A comment can contain any symbol except newlines.
    void TokenizeComment() {
        // Match any character except newlines. 
        while (std::regex_match(std::string(1,currentCharacter), std::regex(".+")))
        {
            Advance();
        }
    }

    // Tokenize special characters. Appends current character and specified tokenkind to vector.
    [[nodiscard]] const Token TokenizeSpecial(TokenKind kind){
        return NewToken(kind, std::string(1,Advance()));
    }

    public:
    // Lexer constructor.
    Lexer(std::string source)
    : input(source), pos(0), size(source.length()), currentCharacter(source.at(pos)), lineNumber(1), characterNumber(1)
    {}

    // Function to tokenize the input string.
    [[nodiscard]] std::vector<Token> tokenize()
    {
        // Result vector.
        std::vector<Token> tokens;
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
            case '#':
                TokenizeComment();
                break;
            case ';':
                tokens.push_back(TokenizeSpecial(TokenKind::SEMI_COLON));
                break;
            case ':':
                tokens.push_back(TokenizeSpecial(TokenKind::COLON));
                break;
            case ',':
                tokens.push_back(TokenizeSpecial(TokenKind::COMMA));
                break;
            case '.':
                tokens.push_back(TokenizeSpecial(TokenKind::DOT));
                break;
            case '*':
                tokens.push_back(TokenizeSpecial(TokenKind::MULT));
                break;
            case '+':
                tokens.push_back(TokenizeSpecial(TokenKind::PLUS));
                break;
            case '-':
                tokens.push_back(TokenizeSpecial(TokenKind::MINUS));
                break;
            case '/':
                tokens.push_back(TokenizeSpecial(TokenKind::SLASH));
                break;
            case '<':
                tokens.push_back(TokenizeSpecial(TokenKind::LESSER));
                break;
            case '>':
                tokens.push_back(TokenizeSpecial(TokenKind::GREATER));
                break;
            case '=':
                tokens.push_back(TokenizeSpecial(TokenKind::EQUALS));
                break;
            case '(':
                tokens.push_back(TokenizeSpecial(TokenKind::OPEN_PAREN));
                break;
            case ')':
                tokens.push_back(TokenizeSpecial(TokenKind::CLOSE_PAREN));
                break;
            case '[':
                tokens.push_back(TokenizeSpecial(TokenKind::OPEN_BRACK));
                break;
            case ']':
                tokens.push_back(TokenizeSpecial(TokenKind::CLOSE_BRACK));
                break;
            case '{':
                tokens.push_back(TokenizeSpecial(TokenKind::OPEN_CURLY));
                break;
            case '}':
                tokens.push_back(TokenizeSpecial(TokenKind::CLOSE_CURLY));
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