#ifndef WERROR_H
#define WERROR_H
#include <iostream>
#include <vector>
#include <iomanip>

enum ErrorCode
{
    // IO
    E_FILE_NOT_FOUND,
    E_IS_DIRECTORY,
    E_IST_REGULAR_FILE,
    // Tokenizer
    E_NO_NULL_CHAR,
    E_MORE_THAN_ONE_BYTE,
    E_UNRECOGNIZED_TOKEN,
    E_MISSING_QUOTATION_MARK,
    E_MISSING_APOSTROPHE_MARK,
    E_UNSUPPORTED_ESCAPE_SEQUENCE,
    E_CLOSE_COMMENT,
    E_INVALID_OCTAL_NUMBER,
    E_INVALID_HEX,
    E_INVALID_BIN,
    E_INVALID_UNICODE,
    E_INVALID_NUMBER,
    E_OUT_OF_RANGE_HEX,
    E_OUT_OF_RANGE_BIN
};

enum WarningCode
{

};

struct Error
{
    ErrorCode code;
    const char *message;
    const char *filePath;
    size_t line;
    size_t column;
};

struct Warning
{
    WarningCode code;
    const char *message;
    const char *filePath;
    size_t line;
    size_t column;
};

struct WError
{
    std::vector<Error> errors;
    std::vector<Warning> warnings;
    void syntaxError(ErrorCode code, const char *message, const char *file_path, size_t index);
    void compilerError(ErrorCode code, const char *message);
    void syntaxWarning(WarningCode code, const char *message, const char *file_path, size_t index);
    void compilerWarning(WarningCode code, const char *message);
};

#endif