#include <iostream>
#include "tokenizer.h"
#include "io.h"
#include "global.h"
#include "ast.h"

WError werror;

int main(int argc, const char *argv[])
{
    if (argc > 0)
    {
        IO io;
        for (size_t i = 0; (int)i < argc - 1; i++)
        {
            io.read(argv[i + 1]);
            Tokenizer tokenizer;
            tokenizer.tokenize(io.reads[i].data);

            for (size_t i = 0; i < werror.errors.size(); i++)
            {
                std::cerr << "\033[91;1mE" << std::setfill('0') << std::setw(2) << werror.errors[i].code << " \033[0mIn \033[4m" << werror.errors[i].filePath << ':' << werror.errors[i].line << std::endl
                          << "\033[0;91;1mERROR\x1b[0;1m: " << werror.errors[i].message << std::endl;
            }
            if (werror.errors.size() > 0)
            {
                exit(1);
            }

            for (Token token : tokenizer.tokens)
            {
                if (token.kind != T_NEWLINE)
                    std::cout << token.kind << ':' << token.value << std::endl;
            }

            std::cout << "Tokenization was \033[92;1mSuccessful\033[0;1m (" << tokenizer.tokens.size() << " tokens found)" << std::endl;
        }
    }
}
