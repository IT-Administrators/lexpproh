# lexpproh

_The lexpproh header is a headerfile, which implements a lexer._

## Table of contents

1. [Introduction](#introduction)
1. [The Lexer](#the-lexer)
    1. [What is lexing](#what-is-lexing)
    1. [How to lex](#how-to-lex)
1. [License](/LICENSE)

## Introduction

Lexers, also reffered to as tokenizers, are an integral part of parsers, compilers and a lot of other software, where text needs to be interpreted.

While i'm interested in parsing, i decided to learn how to create a lexer in c++. 

This project is not meant to be used in production, it is meant to be a walkthough on how to create a lexer or how i created a lexer. This lexer is able to lex a lot of different texts, which you can find in the [examples](./examples/) folder.

This documentation will use the term lexer instead of tokenizer.

## The lexer

### What is lexing

Lexing is a part of lexical analysis, where text is divided into different tokens, which are classified following a predefined logic. This logic has to follow the rules and syntax of the language/text that will be interpreted. 

### How to lex

The first step in creating a lexer is to define the rules on how to classify what token kinds are present.

For example:

You can define a ```10``` as a **NUMBER**, which would be correct.
But depending on the text you want to lex, a more precise description would be to classify it as an **INT**, this way you can determine between decimal and non decimal.
So a ```10.5``` for example would be a **FLOAT**.

#### Lexer rules

I used the following rules to define the token kinds:

- INT: non decimal number
- FLOAT: decimal number with "."
- DOUBLE: currently not implemented
- IDENTIFIER: a word not enclosed in double quotes
- STRING: a word enclosed either in double quotes or single quotes
- SPECIAL_CHARACTERS: are all other characters where each one has its own token kind.

After the rules for token kinds are created, the programming definition of a token needs to be created.

I decided to define a token as follows:

- Contains a value.
- Contains a token kind.

```cpp
// The struct of a token. Any token consists of a value and a token kind.
struct Token {
    std::string value;
    TokenKind kind;
};
```

While the value is the current token, for example a single letter like an 'a' or a word like 'text', the tokenkind is what really matters. It defines what kind of token we got. 

This classification will be important when creating an abstract syntax tree (AST) which is the next step in creating a parser. Creating an AST is not part of this project. You can find more informations about AST's on google.

The token kind definition is as follows:

```cpp
// Token kinds which can be processed.
enum class TokenKind {
    KEYWORD,
    IDENTIFIER,
    INT,
    FLOAT,
    STRING,
    ... // A lot more kinds.
};
```
Using the definition of a token and a token kind, we can now start lexing an example text:
```(10 + 5) * 5 = 75```

The lexer would create the following list of tokens:
```cpp
1) OPEN_PAREN (()
2) INT (10)
3) PLUS (+)
4) INT (5)
5) CLOSE_PAREN ())
6) MULT (*)
7) INT (5)
8) EQUALS (=)
9) INT (75)
```
While you can find a lot different approaches on lexers, i decided to go with a character by character lexer because it has a lot of flexibility in terms of classification.
For example handling blank characters like '\n', '\r', '\t'.

In the above result you can see that blanks are ignored, as they normally don't count as a token.  

So the source text ```(10+5)*5=75``` would create the same tokens. 

Now an example with a string:
```cpp
"\"test\"test"
```
This example would create the following output:
```cpp
1) STRING ("test")
2) IDENTIFIER (test)
```
As you can see a string is following the above defined rules for **STRINGS** and **IDENTIFIERS**.

Because a **STRING** is definied as a word inside single/doubles quotes the tokens for the same string could also be:

```cpp
1) DOUBLE_QUOTES (")
2) IDENTIFIER (test)
3) DOUBLE_QUOTES (")
4) IDENTIFIER (test)
```
The different results depend on the rules the lexer is following. A reason not to classify text inside quotes, for example enables for better error checking as a quote is classified separately, and not as part of a string.

After creating the tokens. The interpretation is done by the parser, which is not part of this project.

## License

[MIT](./LICENSE)