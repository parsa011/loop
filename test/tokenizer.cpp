#include "tokenizer.h"
Error errorHandler;

TOKENS getTokenizerToken(const char* token)
{
    Tokenizer tokenizer(token, errorHandler);
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
    assert(getTokenizerToken("") == T_NAMESPACE);
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
    assert(getTokenizerToken("using") == T_USING);
    assert(getTokenizerToken("final") == T_FINAL);
    assert(getTokenizerToken("true") == T_TRUE);
    assert(getTokenizerToken("false") == T_FALSE);
    assert(getTokenizerToken("this") == T_THIS);
    return verify();
}

bool TokenizerTest::tokenizeOperators()
{
    testName = "Tokenize Operators";
    return verify();
}

bool TokenizerTest::tokenizeDataTypes()
{
    testName = "Tokenize Data Types";
    return verify();
}