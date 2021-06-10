#include <loop/test/lexer.hpp>
#include <string.h>

TOKEN LexerTest::getLexerToken(const char *token)
{
    lexer.lex(token);
    return lexer.lastToken.kind;
}

void LexerTest::runAll()
{
    test(lexKeywords());
    test(lexOperators());
    test(lexDataTypes());
    test(ThrowCloseCommentError());
    test(ThrowMissingQuotationMarkError());
    test(ThrowOutOfRangeHexError());
    test(ThrowInvalidHexError());
    test(ThrowOutOfRangeBinaryError());
    test(ThrowInvalidBinaryError());
    test(ThrowInvalidUnicodeError());
    test(ThrowUnrecognizedTokenError());
}

bool LexerTest::lexKeywords()
{
    testName = "lex Keywords";
    assert(getLexerToken("module") == T_MODULE, "test `module` keyword");
    assert(getLexerToken("import") == T_IMPORT, "test `import` keyword");
    assert(getLexerToken("fn") == T_FUNCTION, "test `fn` keyword");
    assert(getLexerToken("pub") == T_PUBLIC, "test `pub` keyword");
    assert(getLexerToken("static") == T_STATIC, "test `static` keyword");
    assert(getLexerToken("if") == T_IF, "test `if` keyword");
    assert(getLexerToken("else") == T_ELSE, "test `else` keyword");
    assert(getLexerToken("loop") == T_LOOP, "test `loop` keyword");
    assert(getLexerToken("return") == T_RETURN, "test `return` keyword");
    assert(getLexerToken("stop") == T_STOP, "test `stop` keyword");
    assert(getLexerToken("jump") == T_JUMP, "test `jump` keyword");
    assert(getLexerToken("go") == T_GO, "test `go` keyword");
    assert(getLexerToken("in") == T_IN, "test `in` keyword");
    assert(getLexerToken("@label") == T_LABEL, "test `@label` keyword");
    return verify();
}

bool LexerTest::lexOperators()
{
    testName = "lex Operators";
    assert(getLexerToken("=") == T_EQUAL, "test `=` operator");
    assert(getLexerToken("+") == T_PLUS, "test `+` operator");
    assert(getLexerToken("-") == T_MINUS, "test `-` operator");
    assert(getLexerToken("/") == T_SLASH, "test `/` operator");
    assert(getLexerToken("%") == T_PERCENT, "test `%` operator");
    assert(getLexerToken("|") == T_PIPE, "test `|` operator");
    assert(getLexerToken("&") == T_AND, "test `&` operator");
    assert(getLexerToken(";") == T_SEMICOLON, "test `;` operator");
    assert(getLexerToken(":") == T_COLON, "test `:` operator");
    assert(getLexerToken(",") == T_COMMA, "test `,` operator");
    assert(getLexerToken(".") == T_DOT, "test `.` operator");
    assert(getLexerToken("(") == T_LEFT_ROUND_BRACKET, "test `(` operator");
    assert(getLexerToken(")") == T_RIGHT_ROUND_BRACKET, "test `)` operator");
    assert(getLexerToken("{") == T_LEFT_CURLY_BRACKET, "test `{` operator");
    assert(getLexerToken("}") == T_RIGHT_CURLY_BRACKET, "test `}` operator");
    assert(getLexerToken("[") == T_LEFT_SQUARE_BRACKET, "test `[` operator");
    assert(getLexerToken("]") == T_RIGHT_SQUARE_BRACKET, "test `]` operator");
    assert(getLexerToken("<") == T_LEFT_ANGLE_BRACKET, "test `<` operator");
    assert(getLexerToken(">") == T_RIGHT_ANGLE_BRACKET, "test `>` operator");
    assert(getLexerToken("::") == T_DOUBLE_COLON, "test `::` operator");
    assert(getLexerToken("==") == T_DOUBLE_EQUAL, "test `==` operator");
    assert(getLexerToken("++") == T_DOUBLE_PLUS, "test `++` operator");
    assert(getLexerToken("--") == T_DOUBLE_MINUS, "test `--` operator");
    assert(getLexerToken("||") == T_DOUBLE_PIPE, "test `||` operator");
    assert(getLexerToken("&&") == T_LOGIC_AND, "test `&&` operator");
    assert(getLexerToken("+=") == T_EQUAL_PLUS, "test `+=` operator");
    assert(getLexerToken("-=") == T_EQUAL_MINUS, "test `-=` operator");
    assert(getLexerToken("|=") == T_EQUAL_PIPE, "test `|=` operator");
    assert(getLexerToken("<=") == T_EQUAL_LESSER_BRACKET, "test `<=` operator");
    assert(getLexerToken(">=") == T_EQUAL_GREETER_BRACKET, "test `>=` operator");
    return verify();
}

bool LexerTest::lexDataTypes()
{
    testName = "lex Data Types";
    assert(getLexerToken("test") == T_ID, "test identifires");
    assert(getLexerToken("'Hello World'") == T_STRING, "test `string` data");
    assert(getLexerToken("true") == T_BOOLEAN, "test `boolean` data (true)");
    assert(getLexerToken("false") == T_BOOLEAN, "test `boolean` data (false)");
    assert(getLexerToken("1") == T_UINT, "test `unsigned integer` data");
    assert(getLexerToken("-1") == T_INT, "test `integer` data");
    assert(getLexerToken("1.0") == T_FLOAT, "test `float` data");
    assert(getLexerToken("-1.0") == T_FLOAT, "test `float` data (signed)");
    assert(getLexerToken("0xF4") == T_HEX, "test `hex` data");
    assert(getLexerToken("0b10") == T_BIN, "test `binary` data");
    assert(getLexerToken("0u12345678") == T_UNICODE, "test `unicode` data");
    assert(getLexerToken("byte") == T_BYTE_TYPE, "test `byte` type");
    assert(getLexerToken("string") == T_STRING_TYPE, "test `string` type");
    assert(getLexerToken("i8") == T_I8_TYPE, "test `i8` type");
    assert(getLexerToken("i16") == T_I16_TYPE, "test `i16` type");
    assert(getLexerToken("i32") == T_I32_TYPE, "test `i32` type");
    assert(getLexerToken("i64") == T_I64_TYPE, "test `i64` type");
    assert(getLexerToken("u8") == T_U8_TYPE, "test `u8` type");
    assert(getLexerToken("u16") == T_U16_TYPE, "test `u16` type");
    assert(getLexerToken("u32") == T_U32_TYPE, "test `u32` type");
    assert(getLexerToken("u64") == T_U64_TYPE, "test `u64` type");
    assert(getLexerToken("f8") == T_F8_TYPE, "test `f8` type");
    assert(getLexerToken("f16") == T_F16_TYPE, "test `f16` type");
    assert(getLexerToken("f32") == T_F32_TYPE, "test `f32` type");
    assert(getLexerToken("f64") == T_F64_TYPE, "test `f64` type");
    assert(getLexerToken("bool") == T_BOOLEAN_TYPE, "test `bool` type");
    return verify();
}

bool LexerTest::ThrowCloseCommentError()
{
    werror.errors.clear();
    testName = "Throw Close Comment Error";
    Lexer lexer;
    lexer.lex("/* Comment ");
    assert(werror.errors.size() == 1, "test multi-line comment end errors size");
    assert(werror.errors[0].code == E_CLOSE_COMMENT, "test multi-line comment end error kind");
    assert(strcmp(werror.errors[0].message, "You Need To Close The Comment") == 0, "test multi-line comment end error message");
    return verify();
}

bool LexerTest::ThrowMissingQuotationMarkError()
{
    werror.errors.clear();
    testName = "Throw Missing Quotation Mark Error";
    lexer.lex("'Invalid String");
    assert(werror.errors.size() == 1, "test invalid string error size");
    assert(werror.errors[0].code == E_MISSING_QUOTATION_MARK, "test invalid string error kind");
    assert(strcmp(werror.errors[0].message, "Quated String Must Be Finished") == 0, "test invalid string error message");
    return verify();
}
bool LexerTest::ThrowOutOfRangeHexError()
{
    werror.errors.clear();
    testName = "Throw Out Of Range Hex Error";
    lexer.lex("0xFFFFFFFFFF");
    assert(werror.errors.size() == 1, "test out of range hexadecimal error size");
    assert(werror.errors[0].code == E_OUT_OF_RANGE_HEX, "test out of range hexadecimal error kind");
    assert(strcmp(werror.errors[0].message, "Out Of Range Hex") == 0, "test out of range hexadecimal error message");
    return verify();
}

bool LexerTest::ThrowInvalidHexError()
{
    werror.errors.clear();
    testName = "Throw Invalid Hex Error";
    lexer.lex("0xLOOP");
    assert(werror.errors.size() == 1, "test invalid hexadecimal error size");
    assert(werror.errors[0].code == E_INVALID_HEX, "test invalid hexadecimal error kind");
    assert(strcmp(werror.errors[0].message, "Invalid Hex") == 0, "test invalid hexadecimal error message");
    return verify();
}

bool LexerTest::ThrowOutOfRangeBinaryError()
{
    werror.errors.clear();
    testName = "Throw Out Of Range Binary Error";
    lexer.lex("0b1111111111");
    assert(werror.errors.size() == 1, "test out of range binary error size");
    assert(werror.errors[0].code == E_OUT_OF_RANGE_BIN, "test out of range binary error kind");
    assert(strcmp(werror.errors[0].message, "Out Of Range Binary") == 0, "test out of range binary error message");
    return verify();
}

bool LexerTest::ThrowInvalidBinaryError()
{
    werror.errors.clear();
    testName = "Throw Invalid Binary Error";
    lexer.lex("0bLOOP");
    assert(werror.errors.size() == 1, "test invalid binary error size");
    assert(werror.errors[0].code == E_INVALID_BIN, "test invalid binary error kind");
    assert(strcmp(werror.errors[0].message, "Invalid Binary") == 0, "test invalid binary error message");
    lexer.lex("0b");
    assert(werror.errors.size() == 1, "test invalid binary error size (2)");
    assert(werror.errors[0].code == E_INVALID_BIN, "test invalid binary error kind (2)");
    assert(strcmp(werror.errors[0].message, "Invalid Binary") == 0, "test invalid binary error message (2)");
    return verify();
}

bool LexerTest::ThrowInvalidUnicodeError()
{
    werror.errors.clear();
    testName = "Throw Invalid Unicode Error";
    lexer.lex("0uFFFFFFF");
    assert(werror.errors.size() == 1, "test invalid unicode error size");
    assert(werror.errors[0].code == E_INVALID_UNICODE, "test invalid unicode error kind");
    assert(strcmp(werror.errors[0].message, "Invalid Unicode") == 0, "test invalid unicode error message");
    lexer.lex("0uFFFrFFFF");
    assert(werror.errors.size() == 1, "test invalid unicode error size (2)");
    assert(werror.errors[0].code == E_INVALID_UNICODE, "test invalid unicode error kind (2)");
    assert(strcmp(werror.errors[0].message, "Invalid Unicode") == 0, "test invalid unicode error message (2)");
    return verify();
}

bool LexerTest::ThrowUnrecognizedTokenError()
{
    werror.errors.clear();
    testName = "Throw Unrecognized Token Error";
    lexer.lex("~");
    assert(werror.errors.size() == 1, "test `Unrecognized Token` error size");
    assert(werror.errors[0].code == E_UNRECOGNIZED_TOKEN, "test `Unrecognized Token` error kind");
    assert(strcmp(werror.errors[0].message, "Unrecognized Token") == 0, "test `Unrecognized Token` error message");
    return verify();
}
