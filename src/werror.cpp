#include "werror.h"

void WError::compilerError(ErrorCode code, const char *message)
{
    std::cerr << "\x1b[0;91;1mE" << std::setfill('0') << std::setw(2) << code << "]\x1b[0;1m: " << message << std::endl;
    exit(1);
}

void WError::syntaxError(ErrorCode code, const char *message, const char *file_path, size_t index)
{
    Error error{code, message, file_path, index, index};
    errors.push_back(error);
}