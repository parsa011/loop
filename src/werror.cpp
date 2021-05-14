#include "werror.h"
#include "console.h"
#include <iostream>

void WError::compilerError(ErrorCode code, const char *message)
{
    outerr << "\033[0;91;1mE" << std::setfill('0') << std::setw(2) << code << "\033[0;1m: " << message << '\n';
    exit(1);
}

void WError::syntaxError(ErrorCode code, const char *message, const char *file_path, size_t index)
{
    Error error{code, message, file_path, index, index};
    errors.push_back(error);
}