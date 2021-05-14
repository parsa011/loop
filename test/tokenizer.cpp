#include "tokenizer.h"
#include <string.h>

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
    test(ThrowCloseCommentError());
    test(ThrowMissingQuotationMarkError());
    test(ThrowOutOfRangeHexError());
    test(ThrowInvalidHexError());
    test(ThrowInvalidHexAndOutOfRangeHexError());
    test(ThrowOutOfRangeBinaryError());
    test(ThrowInvalidBinaryError());
    test(ThrowInvalidUnicodeError());
    //test(ThrowInvalidNumberError());
    test(ThrowUnrecognizedTokenError());
}

bool TokenizerTest::tokenizeKeywords()
{
    testName = "Tokenize Keywords";
    assert(getTokenizerToken("module") == T_MODULE);
    assert(getTokenizerToken("import") == T_IMPORT);
    assert(getTokenizerToken("fn") == T_FUNCTION);
    assert(getTokenizerToken("pub") == T_PUBLIC);
    assert(getTokenizerToken("static") == T_STATIC);
    assert(getTokenizerToken("if") == T_IF);
    assert(getTokenizerToken("else") == T_ELSE);
    assert(getTokenizerToken("loop") == T_LOOP);
    assert(getTokenizerToken("return") == T_RETURN);
    assert(getTokenizerToken("stop") == T_STOP);
    assert(getTokenizerToken("jump") == T_JUMP);
    assert(getTokenizerToken("go") == T_GO);
    assert(getTokenizerToken("in") == T_IN);
    assert(getTokenizerToken("true") == T_TRUE);
    assert(getTokenizerToken("false") == T_FALSE);
    assert(getTokenizerToken("@label") == T_LABEL);
    return verify();
}

bool TokenizerTest::tokenizeOperators()
{
    testName = "Tokenize Operators";
    assert(getTokenizerToken("test") == T_ID);
    assert(getTokenizerToken("'Hello World'") == T_STRING);
    assert(getTokenizerToken("1") == T_UINT);
    assert(getTokenizerToken("-1") == T_INT);
    assert(getTokenizerToken("1.0") == T_FLOAT);
    assert(getTokenizerToken("-1.0") == T_FLOAT);
    assert(getTokenizerToken("0xF4") == T_HEX);
    assert(getTokenizerToken("0b10") == T_BIN);
    assert(getTokenizerToken("0u12345678") == T_UNICODE);
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
    assert(getTokenizerToken("(") == T_LEFT_ROUND_BRACKET);
    assert(getTokenizerToken(")") == T_RIGHT_ROUND_BRACKET);
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
    assert(getTokenizerToken("i8") == T_I8_TYPE);
    assert(getTokenizerToken("i16") == T_I16_TYPE);
    assert(getTokenizerToken("i32") == T_I32_TYPE);
    assert(getTokenizerToken("i64") == T_I64_TYPE);
    assert(getTokenizerToken("u8") == T_U8_TYPE);
    assert(getTokenizerToken("u16") == T_U16_TYPE);
    assert(getTokenizerToken("u32") == T_U32_TYPE);
    assert(getTokenizerToken("u64") == T_U64_TYPE);
    assert(getTokenizerToken("f8") == T_F8_TYPE);
    assert(getTokenizerToken("f16") == T_F16_TYPE);
    assert(getTokenizerToken("f32") == T_F32_TYPE);
    assert(getTokenizerToken("f64") == T_F64_TYPE);
    assert(getTokenizerToken("bool") == T_BOOLEAN_TYPE);
    return verify();
}

bool TokenizerTest::ThrowCloseCommentError()
{
    testName = "Throw Close Comment Error";
    Tokenizer tokenizer;
    tokenizer.tokenize("/* Comment ");
    assert(werror.errors.size() == 1);
    assert(werror.errors[0].code == E_CLOSE_COMMENT);
    assert(strcmp(werror.errors[0].message, "You Need To Close The Comment") == 0);
    return verify();
}

bool TokenizerTest::ThrowMissingQuotationMarkError()
{
    testName = "Throw Missing Quotation Mark Error";
    tokenizer.tokenize("'Invalid String");
    assert(werror.errors.size() == 1);
    assert(werror.errors[0].code == E_MISSING_QUOTATION_MARK);
    assert(strcmp(werror.errors[0].message, "Quated String Must Be Finished") == 0);
    return verify();
}
bool TokenizerTest::ThrowOutOfRangeHexError()
{
    testName = "Throw Out Of Range Hex Error";
    tokenizer.tokenize("0xFFFFFFFFFF");
    assert(werror.errors.size() == 1);
    assert(werror.errors[0].code == E_OUT_OF_RANGE_HEX);
    assert(strcmp(werror.errors[0].message, "Out Of Range Hex") == 0);
    return verify();
}

bool TokenizerTest::ThrowInvalidHexError()
{
    testName = "Throw Invalid Hex Error";
    tokenizer.tokenize("0xLOOP");
    assert(werror.errors.size() == 1);
    assert(werror.errors[0].code == E_INVALID_HEX);
    assert(strcmp(werror.errors[0].message, "Invalid Hex") == 0);
    return verify();
}

bool TokenizerTest::ThrowInvalidHexAndOutOfRangeHexError()
{
    testName = "Throw Invalid Hex And Out Of Range Hex Error";
    tokenizer.tokenize("0xr");
    assert(werror.errors.size() == 2);
    assert(werror.errors[0].code == E_OUT_OF_RANGE_HEX);
    assert(werror.errors[1].code == E_INVALID_HEX);
    assert(strcmp(werror.errors[0].message, "Out Of Range Hex") == 0);
    assert(strcmp(werror.errors[1].message, "Invalid Hex") == 0);
    return verify();
}

bool TokenizerTest::ThrowOutOfRangeBinaryError()
{
    testName = "Throw Invalid Binary Out Of Range Error";
    tokenizer.tokenize("0b1111111111");
    assert(werror.errors.size() == 1);
    assert(werror.errors[0].code == E_OUT_OF_RANGE_BIN);
    assert(strcmp(werror.errors[0].message, "Out Of Range Binary") == 0);
    return verify();
}

bool TokenizerTest::ThrowInvalidBinaryError()
{
    testName = "Throw Invalid Binary Error";
    tokenizer.tokenize("0bLOOP");
    assert(werror.errors.size() == 1);
    assert(werror.errors[0].code == E_INVALID_BIN);
    assert(strcmp(werror.errors[0].message, "Invalid Binary") == 0);
    tokenizer.tokenize("0b");
    assert(werror.errors.size() == 1);
    assert(werror.errors[0].code == E_INVALID_BIN);
    assert(strcmp(werror.errors[0].message, "Invalid Binary") == 0);
    return verify();
}

bool TokenizerTest::ThrowInvalidUnicodeError()
{
    testName = "Throw Invalid Unicode Error";
    tokenizer.tokenize("0uFFFFFFF");
    assert(werror.errors.size() == 1);
    assert(werror.errors[0].code == E_INVALID_UNICODE);
    assert(strcmp(werror.errors[0].message, "Invalid Unicode") == 0);
    tokenizer.tokenize("0uFFFrFFFF");
    assert(werror.errors.size() == 1);
    assert(werror.errors[0].code == E_INVALID_UNICODE);
    assert(strcmp(werror.errors[0].message, "Invalid Unicode") == 0);
    return verify();
}

// !(Ali) STOPPED FOR BAD SUPPORT IN TOKENIZER
// bool TokenizerTest::ThrowInvalidNumberError()
// {
//     testName = "Throw Invalid Number Error";
//     tokenizer.tokenize("2147483648");
//     assert(werror.errors.size() == 1);
//     assert(werror.errors[0].code == E_INVALID_NUMBER);
//     assert(strcmp(werror.errors[0].message, "Invalid Number") == 0);
//     return verify();
// }

bool TokenizerTest::ThrowUnrecognizedTokenError()
{
    testName = "Throw Unrecognized Token Error";
    tokenizer.tokenize("~");
    assert(werror.errors.size() == 1);
    assert(werror.errors[0].code == E_UNRECOGNIZED_TOKEN);
    assert(strcmp(werror.errors[0].message, "Unrecognized Token") == 0);
    return verify();
}
