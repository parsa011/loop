#ifndef ERROR_H
#define ERROR_H
#include <iostream>
#include <iomanip>

struct Error
{
    bool abort = false;
    enum ERRORS
    {
        // IO
        FILE_NOT_FOUND,
        IS_DIRECTORY,
        IST_REGULAR_FILE,
        // Tokenizer
        NO_NULL_CHAR,
        MORE_THAN_ONE_BYTE,
        UNRECOGNIZED_TOKEN,
        MISSING_QUOTATION_MARK,
        MISSING_APOSTROPHE_MARK,
        UNSUPPORTED_ESCAPE_SEQUENCE,
        CLOSE_COMMENT,
        INVALID_OCTAL_NUMBER,
        INVALID_HEX_DIGIT,
        INVALID_NUMBER
    };
    void syntax(ERRORS code, const char *message, const char *file_path, size_t index);
    void compiler(ERRORS code, const char *message);
};

#endif