#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "error.h"

enum TOKENS
{
    T_ID,                    // Identifiers: myVar and etc
    T_STRING,                // "String"
    T_CHAR,                  // 'Char'
    T_INT,                   // 27
    T_DECIMAL,               // 27.0
    T_HEX,                   // 0xFF
    T_BIN,                   // 0b01
    T_EQUAL,                 // =
    T_PLUS,                  // +
    T_MINUS,                 // -
    T_SLASH,                 // /
    T_PERCENT,               // %
    T_PIPE,                  // |
    T_AND,                   // &
    T_SEMICOLON,             // ;
    T_COLON,                 // :
    T_DOUBLE_COLON,          // ::
    T_COMMA,                 // ,
    T_DOT,                   // .
    T_LEFT_ROUNDED_BRACKET,  // (
    T_RIGHT_ROUNDED_BRACKET, // )
    T_LEFT_CURLY_BRACKET,    // {
    T_RIGHT_CURLY_BRACKET,   // }
    T_LEFT_SQUARE_BRACKET,   // [
    T_RIGHT_SQUARE_BRACKET,  // ]
    T_LEFT_ANGLE_BRACKET,    // <
    T_RIGHT_ANGLE_BRACKET,   // >
    T_DOUBLE_EQUAL,          // ==
    T_DOUBLE_PLUS,           // ++
    T_DOUBLE_MINUS,          // --
    T_DOUBLE_PIPE,           // ||
    T_LOGIC_AND,             // &&
    T_EQUAL_PLUS,            // +=
    T_EQUAL_MINUS,           // -=
    T_EQUAL_PIPE,            // |=
    T_EQUAL_LESSER_BRACKET,  // <=
    T_EQUAL_GREETER_BRACKET, // >=

    // Data Types
    T_CHAR_TYPE,    // char
    T_STRING_TYPE,  // string
    T_INT_TYPE,     // int
    T_FLOAT_TYPE,   // float
    T_DOUBLE_TYPE,  // double
    T_BOOLEAN_TYPE, // bool
    T_VOID_TYPE,    // void

    // Keywords
    T_NAMESPACE,  // namespace
    T_CLASS,      // class
    T_STRUCT,     // struct
    T_ENUM,       // enum
    T_EXTERN,     // extern
    T_INTERFACE,  // interface
    T_EXTENDS,    // extends
    T_IMPLEMENTS, // implements
    T_ABSTRACT,   // abstract
    T_PUBLIC,     // public
    T_PRIVATE,    // private
    T_PROTECTED,  // protected
    T_STATIC,     // static
    T_IF,         // if
    T_ELSE,       // else
    T_FOR,        // for
    T_WHILE,      // while
    T_RETURN,     // return
    T_BREAK,      // break
    T_CONTINUE,   // continue
    T_USING,      // using
    T_FINAL,      // final
    T_TRUE,       // true
    T_FALSE,      // false
    T_THIS        // this
};

struct Token
{
    std::string value;
    TOKENS kind;
    size_t index;
};

struct Tokenizer
{
    size_t index = 0;
    std::string src;
    char lastChar;
    Token lastToken;
    std::vector<Token> tokens;
    Error errorHandler;
    TOKENS getKeywordTokenKind();
    bool isEOF();
    bool isLCOF();
    char peek(int offset);
    void advance(int offset);
    void pushChar();
    Tokenizer(std::string data, Error &error);
};

#endif //TOKENIZER_H
