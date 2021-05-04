// Imports
#include <iostream>
#include "tokenizer.h"
#include "io.h"
#include "error.h"

int main(int argc, const char *argv[])
{
    // Example: loop main.loop
    if (argc > 0)
    {
        Error error_handler;
        IO io(error_handler);
        for (size_t i = 0; (int)i < argc - 1; i++)
        {
            try
            {
                if (!io.errorHandler.abort)
                {
                    io.read(argv[i + 1]);
                    Tokenizer tokenizer(error_handler);
                    tokenizer.tokenize(io.reads[i].data);

                    if (!tokenizer.errorHandler.abort)
                    {
                        int tokenCount = 0;
                        for (Token token : tokenizer.tokens)
                        {
                            std::cout << token.kind << " : " << token.value << "\n";
                            ++tokenCount;
                        }
                        std::cout << "Tokenization was \x1b[92;1mSuccessful\x1b[0;1m (" << tokenCount << " tokens found)\n";
                    }
                }
            }
            catch (const std::exception &e)
            {
                exit(1);
            }
        }
    }
}
