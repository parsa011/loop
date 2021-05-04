#include "tokenizer.h"
Error errorHandler;

TOKENS getTokenizerToken(Tokenizer tokenizer, const char *token)
{
    tokenizer.tokenize(token);
    return tokenizer.lastToken.kind;
}

void TokenizerTest::runAll()
{
    test(tokenizeKeywords());
    test(tokenizeOperators());
    test(tokenizeDataTypes());
}

bool TokenizerTest::tokenizeKeywords()
{
    testName = "Tokenize Keywords";
    Tokenizer tokenizer(errorHandler);
    assert(getTokenizerToken(tokenizer, "if") == T_IF);
    assert(getTokenizerToken(tokenizer, "namespace") == TOKENS::T_NAMESPACE);
    assert(getTokenizerToken(tokenizer, "class") == T_CLASS);
    assert(getTokenizerToken(tokenizer, "struct") == T_STRUCT);
    assert(getTokenizerToken(tokenizer, "enum") == T_ENUM);
    assert(getTokenizerToken(tokenizer, "extern") == T_EXTERN);
    assert(getTokenizerToken(tokenizer, "interface") == T_INTERFACE);
    assert(getTokenizerToken(tokenizer, "extends") == T_EXTENDS);
    assert(getTokenizerToken(tokenizer, "implements") == T_IMPLEMENTS);
    assert(getTokenizerToken(tokenizer, "abstract") == T_ABSTRACT);
    assert(getTokenizerToken(tokenizer, "public") == T_PUBLIC);
    assert(getTokenizerToken(tokenizer, "private") == T_PRIVATE);
    assert(getTokenizerToken(tokenizer, "protected") == T_PROTECTED);
    assert(getTokenizerToken(tokenizer, "static") == T_STATIC);
    assert(getTokenizerToken(tokenizer, "if") == T_IF);
    assert(getTokenizerToken(tokenizer, "else") == T_ELSE);
    assert(getTokenizerToken(tokenizer, "for") == T_FOR);
    assert(getTokenizerToken(tokenizer, "while") == T_WHILE);
    assert(getTokenizerToken(tokenizer, "return") == T_RETURN);
    assert(getTokenizerToken(tokenizer, "break") == T_BREAK);
    assert(getTokenizerToken(tokenizer, "continue") == T_CONTINUE);
    assert(getTokenizerToken(tokenizer, "using") == T_USING);
    assert(getTokenizerToken(tokenizer, "final") == T_FINAL);
    assert(getTokenizerToken(tokenizer, "true") == T_TRUE);
    assert(getTokenizerToken(tokenizer, "false") == T_FALSE);
    assert(getTokenizerToken(tokenizer, "this") == T_THIS);
    return verify();
}

bool TokenizerTest::tokenizeOperators()
{
    testName = "Tokenize Operators";
    Tokenizer tokenizer(errorHandler);
    assert(getTokenizerToken(tokenizer, "test") == T_ID);
    assert(getTokenizerToken(tokenizer, "\"Hello World\"") == T_STRING);
    assert(getTokenizerToken(tokenizer, "'a'") == T_CHAR);
    assert(getTokenizerToken(tokenizer, "1") == T_INT);
    assert(getTokenizerToken(tokenizer, "1.0") == T_DECIMAL);
    assert(getTokenizerToken(tokenizer, "0xF4") == T_HEX);
    assert(getTokenizerToken(tokenizer, "0b10") == T_BIN);
    assert(getTokenizerToken(tokenizer, "=") == T_EQUAL);
    assert(getTokenizerToken(tokenizer, "+") == T_PLUS);
    assert(getTokenizerToken(tokenizer, "-") == T_MINUS);
    assert(getTokenizerToken(tokenizer, "/") == T_SLASH);
    assert(getTokenizerToken(tokenizer, "%") == T_PERCENT);
    assert(getTokenizerToken(tokenizer, "|") == T_PIPE);
    assert(getTokenizerToken(tokenizer, "&") == T_AND);
    assert(getTokenizerToken(tokenizer, ";") == T_SEMICOLON);
    assert(getTokenizerToken(tokenizer, ":") == T_COLON);
    assert(getTokenizerToken(tokenizer, "::") == T_DOUBLE_COLON);
    assert(getTokenizerToken(tokenizer, ",") == T_COMMA);
    assert(getTokenizerToken(tokenizer, ".") == T_DOT);
    assert(getTokenizerToken(tokenizer, "(") == T_LEFT_ROUNDED_BRACKET);
    assert(getTokenizerToken(tokenizer, ")") == T_RIGHT_ROUNDED_BRACKET);
    assert(getTokenizerToken(tokenizer, "{") == T_LEFT_CURLY_BRACKET);
    assert(getTokenizerToken(tokenizer, "}") == T_RIGHT_CURLY_BRACKET);
    assert(getTokenizerToken(tokenizer, "[") == T_LEFT_SQUARE_BRACKET);
    assert(getTokenizerToken(tokenizer, "]") == T_RIGHT_SQUARE_BRACKET);
    assert(getTokenizerToken(tokenizer, "<") == T_LEFT_ANGLE_BRACKET);
    assert(getTokenizerToken(tokenizer, ">") == T_RIGHT_ANGLE_BRACKET);
    assert(getTokenizerToken(tokenizer, "==") == T_DOUBLE_EQUAL);
    assert(getTokenizerToken(tokenizer, "++") == T_DOUBLE_PLUS);
    assert(getTokenizerToken(tokenizer, "--") == T_DOUBLE_MINUS);
    assert(getTokenizerToken(tokenizer, "||") == T_DOUBLE_PIPE);
    assert(getTokenizerToken(tokenizer, "&&") == T_LOGIC_AND);
    assert(getTokenizerToken(tokenizer, "+=") == T_EQUAL_PLUS);
    assert(getTokenizerToken(tokenizer, "-=") == T_EQUAL_MINUS);
    assert(getTokenizerToken(tokenizer, "|=") == T_EQUAL_PIPE);
    assert(getTokenizerToken(tokenizer, "<=") == T_EQUAL_LESSER_BRACKET);
    assert(getTokenizerToken(tokenizer, ">=") == T_EQUAL_GREETER_BRACKET);
    return verify();
}

bool TokenizerTest::tokenizeDataTypes()
{
    testName = "Tokenize Data Types";
    Tokenizer tokenizer(errorHandler);
    assert(getTokenizerToken(tokenizer, "char") == T_CHAR_TYPE);
    assert(getTokenizerToken(tokenizer, "string") == T_STRING_TYPE);
    assert(getTokenizerToken(tokenizer, "int") == T_INT_TYPE);
    assert(getTokenizerToken(tokenizer, "float") == T_FLOAT_TYPE);
    assert(getTokenizerToken(tokenizer, "double") == T_DOUBLE_TYPE);
    assert(getTokenizerToken(tokenizer, "bool") == T_BOOLEAN_TYPE);
    assert(getTokenizerToken(tokenizer, "void") == T_VOID_TYPE);
    return verify();
}