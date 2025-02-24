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
        const std::string input;
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

    // Return next character. Dont advance position.
    const char LookAhead() {

        if (pos < size)
        {
            return input[pos +1];
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

    // Check if current character equals a newline character, if true increase lineNumber and reset characterNumber.
    void CatchNewLine() {
        // Catch newline characters in strings.
        if (currentCharacter == '\n')
        {
            lineNumber++;
            characterNumber = 1;
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

    // Tokenize Numbers. Differentiate between int and float.
    // Floats are decimal numbers with "." as separator.
    // 3.5 = FLOAT (3.5), 3,5 = INT (3), INT (5).   
    [[nodiscard]] const Token TokenizeNumber() {
        std::stringstream buffer;
        while (isdigit(currentCharacter) || currentCharacter == '.')
        {
            buffer << Advance();
        }
        // This delimiter must be changed depending on how floats are defined.
        if (buffer.str().find('.') != std::string::npos)
        {                     
            return NewToken(TokenKind::FLOAT, buffer.str());
        }
        return NewToken(TokenKind::INT, buffer.str());
    }

    // Tokenize everything in inside double quotes.
    // A string is defined as everything inside double quotes, except for other double quotes.
    [[nodiscard]] const Token TokenizeStringDoubleQuotes() {
        std::stringstream buffer;
        // Append character to buffer.
        buffer << Advance();

        while (std::regex_match(std::string(1,currentCharacter), std::regex("[^\"]")))
        {
            CatchNewLine();
            // Append all other characters to buffer.
            buffer << Advance();
        }
        buffer << Advance();
        return NewToken(TokenKind::STRING, buffer.str());
    }

    // Tokenize everything in inside single quotes.
    // A string is defined as everything inside single quotes, except for other single quotes.
    [[nodiscard]] const Token TokenizeStringSingleQuotes() {
        std::stringstream buffer;
        // Append character to buffer.
        buffer << Advance();

        while (std::regex_match(std::string(1,currentCharacter), std::regex("[^\']")))
        {
            CatchNewLine();
            // Append all other characters to buffer.
            buffer << Advance();
        }
        buffer << Advance();
        return NewToken(TokenKind::STRING, buffer.str());
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
                tokens.push_back(TokenizeNumber());
                continue;
            }
            switch (currentCharacter)
            {
            case '"':
                tokens.push_back(TokenizeStringDoubleQuotes());
                break;
            // Single quotes must be escaped.
            case '\'':
                tokens.push_back(TokenizeStringSingleQuotes());
                break;
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
            // Backslash must be escaped.
            case '\\':
                tokens.push_back(TokenizeSpecial(TokenKind::BACK_SLASH));
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
            case '%':
                tokens.push_back(TokenizeSpecial(TokenKind::MODULO));
                break;
            case '?':
                tokens.push_back(TokenizeSpecial(TokenKind::QUESTION_MARK));
                break;
            case '!':
                tokens.push_back(TokenizeSpecial(TokenKind::EXCLAMATION_MARK));
                break;
            case '&':
                tokens.push_back(TokenizeSpecial(TokenKind::AMPERSAND));
                break;
            case '|':
                tokens.push_back(TokenizeSpecial(TokenKind::PIPE));
                break;
            case '^':
                tokens.push_back(TokenizeSpecial(TokenKind::ROOF));
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
                std::cerr << "UNIDENTIFIED: " << "(" << std::string(1,currentCharacter) << ")" << " ";
                std::cerr << "LINE NUMBER: " << lineNumber << " " << "CHARACTER NUMBER: " << characterNumber << std::endl;
                exit(1);
            }
        }
        return tokens;
    }
};
#endif