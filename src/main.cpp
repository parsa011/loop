#include <iostream>
#include <loop/ast.hpp>
#include <loop/global.hpp>
#include <loop/io.hpp>
#include <loop/lexer.hpp>
#include <loop/parser.hpp>
#include <loop/utils.hpp>

WError werror;

int main(int argc, const char *argv[])
{
    if (argc > 0)
    {
        IO io;
        for (int i = 0; i < argc - 1; i++)
        {
            io.read(argv[i + 1]);
            Lexer lexer;
            lexer.lex(io.reads[i].data);

            for (size_t i = 0; i < werror.errors.size(); i++)
            {
                std::cerr << "\033[91;1mE" << std::setfill('0') << std::setw(2) << werror.errors[i].code
                          << " \033[0mIn \033[4m" << werror.errors[i].filePath << ':' << werror.errors[i].line << '\n'
                          << "\033[0;91;1mERROR\x1b[0;1m: " << werror.errors[i].message << '\n';
            }
            if (werror.errors.size() > 0)
            {
                exit(1);
            }

            for (Token token : lexer.tokensArray)
            {
                if (token.kind != T_NEWLINE)
                    std::cout << token.kind << ':' << token.value << '\n';
            }

            std::cout << "Tokenization was \033[92;1mSuccessful\033[0;1m (" << lexer.tokensArray.size() << " tokens found)"
                      << '\n';
            //Parser p;
            //p.parse(&lexer.tokensArray);
        }
    }
}
