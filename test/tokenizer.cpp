#include "tokenizer.h"

TOKEN TokenizerTest::getTokenizerToken(const char *token)
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
    assert(getTokenizerToken("if") == T_IF);
    assert(getTokenizerToken("namespace") == T_NAMESPACE);
    assert(getTokenizerToken("class") == T_CLASS);
    assert(getTokenizerToken("struct") == T_STRUCT);
    assert(getTokenizerToken("enum") == T_ENUM);
    assert(getTokenizerToken("extern") == T_EXTERN);
    assert(getTokenizerToken("interface") == T_INTERFACE);
    assert(getTokenizerToken("extends") == T_EXTENDS);
    assert(getTokenizerToken("implements") == T_IMPLEMENTS);
    assert(getTokenizerToken("abstract") == T_ABSTRACT);
    assert(getTokenizerToken("public") == T_PUBLIC);
    assert(getTokenizerToken("private") == T_PRIVATE);
    assert(getTokenizerToken("protected") == T_PROTECTED);
    assert(getTokenizerToken("static") == T_STATIC);
    assert(getTokenizerToken("if") == T_IF);
    assert(getTokenizerToken("else") == T_ELSE);
    assert(getTokenizerToken("for") == T_FOR);
    assert(getTokenizerToken("while") == T_WHILE);
    assert(getTokenizerToken("return") == T_RETURN);
    assert(getTokenizerToken("break") == T_BREAK);
    assert(getTokenizerToken("continue") == T_CONTINUE);
    assert(getTokenizerToken("import") == T_IMPORT);
    assert(getTokenizerToken("final") == T_FINAL);
    assert(getTokenizerToken("true") == T_TRUE);
    assert(getTokenizerToken("false") == T_FALSE);
    assert(getTokenizerToken("this") == T_THIS);
    return verify();
}

bool TokenizerTest::tokenizeOperators()
{
    testName = "Tokenize Operators";
    assert(getTokenizerToken("test") == T_ID);
    assert(getTokenizerToken("'Hello World'") == T_STRING);
    assert(getTokenizerToken("1") == T_INT);
    assert(getTokenizerToken("1.0") == T_DECIMAL);
    assert(getTokenizerToken("0xF4") == T_HEX);
    assert(getTokenizerToken("0b10") == T_BIN);
    assert(getTokenizerToken("=") == T_EQUAL);
    assert(getTokenizerToken("+") == T_PLUS);
    assert(getTokenizerToken("-") == T_MINUS);
    assert(getTokenizerToken("/") == T_SLASH);
    assert(getTokenizerToken("%") == T_PERCENT);
    assert(getTokenizerToken("|") == T_PIPE);
    assert(getTokenizerToken("&") == T_AND);
    assert(getTokenizerToken(";") == T_SEMICOLON);
    assert(getTokenizerToken(":") == T_COLON);
    assert(getTokenizerToken(",") == T_COMMA);
    assert(getTokenizerToken(".") == T_DOT);
    assert(getTokenizerToken("(") == T_LEFT_ROUNDED_BRACKET);
    assert(getTokenizerToken(")") == T_RIGHT_ROUNDED_BRACKET);
    assert(getTokenizerToken("{") == T_LEFT_CURLY_BRACKET);
    assert(getTokenizerToken("}") == T_RIGHT_CURLY_BRACKET);
    assert(getTokenizerToken("[") == T_LEFT_SQUARE_BRACKET);
    assert(getTokenizerToken("]") == T_RIGHT_SQUARE_BRACKET);
    assert(getTokenizerToken("<") == T_LEFT_ANGLE_BRACKET);
    assert(getTokenizerToken(">") == T_RIGHT_ANGLE_BRACKET);
    assert(getTokenizerToken("::") == T_DOUBLE_COLON);
    assert(getTokenizerToken("==") == T_DOUBLE_EQUAL);
    assert(getTokenizerToken("++") == T_DOUBLE_PLUS);
    assert(getTokenizerToken("--") == T_DOUBLE_MINUS);
    assert(getTokenizerToken("||") == T_DOUBLE_PIPE);
    assert(getTokenizerToken("&&") == T_LOGIC_AND);
    assert(getTokenizerToken("+=") == T_EQUAL_PLUS);
    assert(getTokenizerToken("-=") == T_EQUAL_MINUS);
    assert(getTokenizerToken("|=") == T_EQUAL_PIPE);
    assert(getTokenizerToken("<=") == T_EQUAL_LESSER_BRACKET);
    assert(getTokenizerToken(">=") == T_EQUAL_GREETER_BRACKET);
    return verify();
}

bool TokenizerTest::tokenizeDataTypes()
{
    testName = "Tokenize Data Types";
    assert(getTokenizerToken("byte") == T_BYTE_TYPE);
    assert(getTokenizerToken("string") == T_STRING_TYPE);
    assert(getTokenizerToken("int") == T_INT_TYPE);
    assert(getTokenizerToken("float") == T_FLOAT_TYPE);
    assert(getTokenizerToken("double") == T_DOUBLE_TYPE);
    assert(getTokenizerToken("bool") == T_BOOLEAN_TYPE);
    assert(getTokenizerToken("void") == T_VOID_TYPE);
    return verify();
}