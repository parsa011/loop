// Imports
#include <iostream>
#include "tokenizer.h"
#include "io.h"
#include "werror.h"

int main(int argc, const char *argv[])
{
    // Example: loop main.loop
    if (argc > 0)
    {
        WError werror;
        IO io(werror);
        for (size_t i = 0; (int)i < argc - 1; i++)
        {
            io.read(argv[i + 1]);
            Tokenizer tokenizer(werror);
            tokenizer.tokenize(io.reads[i].data);

            for (size_t i = 0; i < tokenizer.werror.errors.size(); i++)
            {
                std::cerr << "\x1b[91;1mE" << std::setfill('0') << std::setw(2) << tokenizer.werror.errors[i].code << " \x1b[0mIn \x1b[4m" << tokenizer.werror.errors[i].filePath << ':' << tokenizer.werror.errors[i].line << std::endl
                          << "\x1b[0;91;1mERROR\x1b[0;1m: " << tokenizer.werror.errors[i].message << std::endl;
            }

            if (tokenizer.werror.errors.size() < 1)
            {
                int tokenCount = 0;
                for (Token token : tokenizer.tokens)
                {
                    std::cout << token.kind << " : " << token.value << "\n";
                    ++tokenCount;
                }
                std::cout << "Tokenization was \x1b[92;1mSuccessful\x1b[0;1m (" << tokenCount << " tokens found)" << std::endl;
            }
            else
            {
                exit(1);
            }
        }
    }
}
