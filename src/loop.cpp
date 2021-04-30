#include <iostream>
#include "tokenizer.h"
#include "io.h"
#include "error.h"

int main(int argc, const char *argv[])
{
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
                    Tokenizer tokenizer(io.reads[i].data, error_handler);

                    if (!tokenizer.errorHandler.abort)
                    {
                        int tokenCount = 0;
                        for (Token token : tokenizer.tokens)
                        {
                            std::cout << token.kind << " : " << token.value << "\n";
                            ++tokenCount;
                        }
                        std::cout << "Tokenization was \x1b[92;1msuccessful\x1b[0;1m (" << tokenCount << " token found)\n";
                    }
                }
            }
            catch (const std::exception &e)
            {
                exit(1);
            }
        }
    }
    return 0;
}
