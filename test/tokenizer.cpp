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

    test(shouldThrowCloseCommentError());
    test(shouldThrowMissingQuotationMarkError());
    test(shouldThrowInvalidHexNumberOutOfRangeError());
    test(shouldThrowInvalidHexNumberError());
    test(shouldThrowInvalidBinaryNumberOutOfRangeError());
    test(shouldThrowInvalidBinaryNumberError());
    test(shouldThrowInvalidNumberError());
    test(shouldThrowUnrecognizedTokenError());
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
    assert(getTokenizerToken("loop") == T_LOOP);
    assert(getTokenizerToken("return") == T_RETURN);
    assert(getTokenizerToken("break") == T_BREAK);
    assert(getTokenizerToken("continue") == T_CONTINUE);
    assert(getTokenizerToken("import") == T_IMPORT);
    assert(getTokenizerToken("final") == T_FINAL);
    assert(getTokenizerToken("true") == T_TRUE);
    assert(getTokenizerToken("false") == T_FALSE);
    assert(getTokenizerToken("this") == T_THIS);
    assert(getTokenizerToken("in") == T_IN);
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

bool TokenizerTest::shouldThrowCloseCommentError()
{
    testName = "Should throw close comment error";
    WError errorHandler;
    Tokenizer tokenizer(errorHandler);
    tokenizer.tokenize("/* Comment ");
    assert(tokenizer.werror.errors.size() == 1);
    assert(tokenizer.werror.errors[0].code == E_CLOSE_COMMENT);
    assert(strcmp(tokenizer.werror.errors[0].message, "You need to close the comment") == 0);
    return verify();
}

bool TokenizerTest::shouldThrowMissingQuotationMarkError()
{
    testName = "Should throw missing quotation mark error";
    WError errorHandler;
    Tokenizer tokenizer(errorHandler);
    tokenizer.tokenize("'Invalid String");
    assert(tokenizer.werror.errors.size() == 1);
    assert(tokenizer.werror.errors[0].code == E_MISSING_QUOTATION_MARK);
    assert(strcmp(tokenizer.werror.errors[0].message, "Quated String Must Be Finished") == 0);
    return verify();
}

bool TokenizerTest::shouldThrowInvalidHexNumberOutOfRangeError()
{
    testName = "Should throw invalid hex number out of range error";
    WError errorHandler;
    Tokenizer tokenizer(errorHandler);
    tokenizer.tokenize("0xFFFFFFFFFF");
    assert(tokenizer.werror.errors.size() == 1);
    assert(tokenizer.werror.errors[0].code == E_INVALID_HEX_NUMBER);
    assert(strcmp(tokenizer.werror.errors[0].message, "Out Of Range Hex Number") == 0);
    return verify();
}

bool TokenizerTest::shouldThrowInvalidHexNumberError()
{
    testName = "Should throw invalid hex number error";
    WError errorHandler;
    Tokenizer tokenizer(errorHandler);
    tokenizer.tokenize("0xLOOP");
    assert(tokenizer.werror.errors.size() == 1);
    assert(tokenizer.werror.errors[0].code == E_INVALID_HEX_NUMBER);
    assert(strcmp(tokenizer.werror.errors[0].message, "Invalid Hex Number") == 0);
    return verify();
}

bool TokenizerTest::shouldThrowInvalidBinaryNumberOutOfRangeError()
{
    testName = "Should throw invalid binary number out of range error";
    WError errorHandler;
    Tokenizer tokenizer(errorHandler);
    tokenizer.tokenize("0b1111111111");
    assert(tokenizer.werror.errors.size() == 1);
    assert(tokenizer.werror.errors[0].code == E_INVALID_NUMBER);
    assert(strcmp(tokenizer.werror.errors[0].message, "Out Of Range Binary Number") == 0);
    return verify();
}

bool TokenizerTest::shouldThrowInvalidBinaryNumberError()
{
    testName = "Should throw invalid binary number error";
    WError errorHandler;
    Tokenizer tokenizer(errorHandler);
    tokenizer.tokenize("0bLOOP");
    assert(tokenizer.werror.errors.size() == 1);
    assert(tokenizer.werror.errors[0].code == E_INVALID_NUMBER);
    assert(strcmp(tokenizer.werror.errors[0].message, "Invalid Binary Number") == 0);
    return verify();
}

bool TokenizerTest::shouldThrowInvalidNumberError()
{
    testName = "Should throw invalid number error";
    WError errorHandler;
    Tokenizer tokenizer(errorHandler);
    tokenizer.tokenize("2147483648");
    assert(tokenizer.werror.errors.size() == 1);
    assert(tokenizer.werror.errors[0].code == E_INVALID_NUMBER);
    assert(strcmp(tokenizer.werror.errors[0].message, "Invalid Number") == 0);
    return verify();
}

bool TokenizerTest::shouldThrowUnrecognizedTokenError()
{
    testName = "Should throw unrecognized token error";
    WError errorHandler;
    Tokenizer tokenizer(errorHandler);
    tokenizer.tokenize("~");
    assert(tokenizer.werror.errors.size() == 1);
    assert(tokenizer.werror.errors[0].code == E_UNRECOGNIZED_TOKEN);
    assert(strcmp(tokenizer.werror.errors[0].message, "Unrecognized Token") == 0);
    return verify();
}
