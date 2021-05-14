#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <vector>
#include <iostream>
#include "global.h"

enum TOKEN
{
    T_UNRECOGNIZED,          // Unrecognized
    T_NEWLINE,               // Newline
    T_ID,                    // Identifiers: myVar and etc
    T_BOOLEAN,               // true or false
    T_STRING,                // 'String'
    T_INT,                   // -128 to 127
    T_UINT,                  // 255
    T_FLOAT,                 // 127.1
    T_HEX,                   // 0xFF
    T_BIN,                   // 0b01
    T_UNICODE,               // 0u12345678
    T_EQUAL,                 // =
    T_PLUS,                  // +
    T_MINUS,                 // -
    T_SLASH,                 // /
    T_PERCENT,               // %
    T_PIPE,                  // |
    T_AND,                   // &
    T_DOT,                   // .
    T_COMMA,                 // ,
    T_COLON,                 // :
    T_SEMICOLON,             // ;
    T_LEFT_ROUND_BRACKET,    // (
    T_RIGHT_ROUND_BRACKET,   // )
    T_LEFT_CURLY_BRACKET,    // {
    T_RIGHT_CURLY_BRACKET,   // }
    T_LEFT_SQUARE_BRACKET,   // [
    T_RIGHT_SQUARE_BRACKET,  // ]
    T_LEFT_ANGLE_BRACKET,    // <
    T_RIGHT_ANGLE_BRACKET,   // >
    T_DOUBLE_COLON,          // ::
    T_LOGIC_AND,             // &&
    T_DOUBLE_PIPE,           // ||
    T_DOUBLE_EQUAL,          // ==
    T_DOUBLE_PLUS,           // ++
    T_DOUBLE_MINUS,          // --
    T_EQUAL_PLUS,            // +=
    T_EQUAL_MINUS,           // -=
    T_EQUAL_PIPE,            // |=
    T_EQUAL_LESSER_BRACKET,  // <=
    T_EQUAL_GREETER_BRACKET, // >=

    // Data Types
    T_BOOLEAN_TYPE, // bool
    T_BYTE_TYPE,    // byte
    T_STRING_TYPE,  // string
    T_I8_TYPE,      // int-8bit
    T_I16_TYPE,     // int-16bit
    T_I32_TYPE,     // int-32bit
    T_I64_TYPE,     // int-64bit
    T_U8_TYPE,      // unsigned int-8bit
    T_U16_TYPE,     // unsigned int-16bit
    T_U32_TYPE,     // unsigned int-32bit
    T_U64_TYPE,     // unsigned int-64bit
    T_F8_TYPE,      // float int-8bit
    T_F16_TYPE,     // float int-16bit
    T_F32_TYPE,     // float int-32bit
    T_F64_TYPE,     // float int-64bit
    T_STRUCT,       // struct
    T_ENUM,         // enum

    // Keywords
    T_MODULE,   // module
    T_IMPORT,   // import
    T_FUNCTION, // fn
    T_PUBLIC,   // pub
    T_STATIC,   // static
    T_IF,       // if
    T_ELSE,     // else
    T_LOOP,     // loop
    T_RETURN,   // return
    T_STOP,     // stop
    T_JUMP,     // jump
    T_GO,       // go
    T_IN,       // in

    // Others

    T_LABEL
};

struct Token
{
    std::string value;
    TOKEN kind;
    size_t index;
};

struct Tokenizer
{
public:
    size_t index = 0;
    std::string src;
    char lastChar;
    Token lastToken;
    std::vector<Token> tokens;
    bool isEOF();
    bool isLCOF();
    char peek(int offset);
    void advance(int offset);
    void pushChar();
    void tokenize(std::string data);
};

#endif
