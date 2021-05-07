#include "tokenizer.h"

bool Tokenizer::isEOF()
{
    if (index < src.length() && lastChar != '\0' && lastChar != char(-1))
    {
        return false;
    }
    return true;
}

bool Tokenizer::isLCOF()
{
    if (index < src.length() - 1)
    {
        return false;
    }
    return true;
}

void Tokenizer::advance(int offset)
{
    if ((size_t)offset + index < src.length())
    {
        index += (size_t)offset;
    }
    else
    {
        index = src.length();
    }
    lastChar = src[index];
}

void Tokenizer::pushChar()
{
    lastToken.value.push_back(lastChar);
    advance(1);
}

char Tokenizer::peek(int offset)
{
    if ((size_t)offset + index < src.length())
    {
        return src[index + (size_t)offset];
    }
    return src[src.length()];
}

void Tokenizer::tokenize(std::string data)
{
    tokens.clear();
    src = data;
    index = 0;
    lastChar = src[0];
    while (!isEOF())
    {
        lastToken.value.clear();
        lastToken.index = 0;
        if (lastChar == '\n')
        {
            lastToken.kind = T_NEWLINE;
            advance(1);
            goto independent;
        }
        while (isspace(lastChar))
        {
            advance(1);
        }
        if (lastChar == '/')
        {
            if (peek(1) == '*')
            {
                advance(2);
                while (!isEOF())
                {
                    advance(1);
                    if (lastChar == '*' && peek(1) == '/')
                    {
                        advance(2);
                        break;
                    }
                }
                if (isEOF())
                {
                    werror.syntaxError(E_CLOSE_COMMENT, "You need to close the comment", "here", index);
                }
                continue;
            }
            else if (peek(1) == '/')
            {
                while (!isEOF())
                {
                    advance(1);
                    if (lastChar == '\n')
                    {
                        break;
                    }
                }
                continue;
            }
            else
            {
                lastToken.kind = T_SLASH;
            }
        }
        else if (lastChar == '\'')
        {
            while (!isEOF())
            {
                pushChar();
                if (lastChar == '\'')
                {
                    if (peek(-1) != '\\')
                    {
                        break;
                    }
                }
                else if (isLCOF())
                {
                    werror.syntaxError(E_MISSING_QUOTATION_MARK, "Quated String Must Be Finished", "here", index);
                    return;
                }
            }
            lastToken.kind = T_STRING;
        }
        else if (lastChar == '=')
        {
            if (peek(1) == '=')
            {
                lastToken.kind = T_DOUBLE_EQUAL;
                pushChar();
            }
            else
            {
                lastToken.kind = T_EQUAL;
            }
        }
        else if (lastChar == '+')
        {
            if (peek(1) == '=')
            {
                lastToken.kind = T_EQUAL_PLUS;
                pushChar();
            }
            else if (peek(1) == '+')
            {
                lastToken.kind = T_DOUBLE_PLUS;
                pushChar();
            }
            else
            {
                lastToken.kind = T_PLUS;
            }
        }
        else if (lastChar == '-')
        {
            if (peek(1) == '=')
            {
                lastToken.kind = T_EQUAL_MINUS;
                pushChar();
            }
            else if (peek(1) == '-')
            {
                lastToken.kind = T_DOUBLE_MINUS;
                pushChar();
            }
            else
            {
                lastToken.kind = T_MINUS;
            }
        }
        else if (lastChar == '|')
        {
            if (peek(1) == '=')
            {
                lastToken.kind = T_EQUAL_PIPE;
                pushChar();
            }
            else if (peek(1) == '|')
            {
                lastToken.kind = T_DOUBLE_PIPE;
                pushChar();
            }
            else
            {
                lastToken.kind = T_PIPE;
            }
        }
        else if (lastChar == '<')
        {
            if (peek(1) == '=')
            {
                lastToken.kind = T_EQUAL_LESSER_BRACKET;
                pushChar();
            }
            else
            {
                lastToken.kind = T_LEFT_ANGLE_BRACKET;
            }
        }
        else if (lastChar == '>')
        {
            if (peek(1) == '=')
            {
                lastToken.kind = T_EQUAL_GREETER_BRACKET;
                pushChar();
            }
            else
            {
                lastToken.kind = T_RIGHT_ANGLE_BRACKET;
            }
        }
        else if (lastChar == '&')
        {
            if (peek(1) == '&')
            {
                lastToken.kind = T_LOGIC_AND;
                pushChar();
            }
            else
            {
                lastToken.kind = T_AND;
            }
        }
        else if (lastChar == ':')
        {
            if (peek(1) == ':')
            {
                lastToken.kind = T_DOUBLE_COLON;
                pushChar();
            }
            else
            {
                lastToken.kind = T_COLON;
            }
        }
        else if (lastChar == '%')
        {
            lastToken.kind = T_PERCENT;
        }
        else if (lastChar == ';')
        {
            lastToken.kind = T_SEMICOLON;
        }
        else if (lastChar == ',')
        {
            lastToken.kind = T_COMMA;
        }
        else if (lastChar == '.')
        {
            lastToken.kind = T_DOT;
        }
        else if (lastChar == '(')
        {
            lastToken.kind = T_LEFT_ROUNDED_BRACKET;
        }
        else if (lastChar == ')')
        {
            lastToken.kind = T_RIGHT_ROUNDED_BRACKET;
        }
        else if (lastChar == '{')
        {
            lastToken.kind = T_LEFT_CURLY_BRACKET;
        }
        else if (lastChar == '}')
        {
            lastToken.kind = T_RIGHT_CURLY_BRACKET;
        }
        else if (lastChar == '[')
        {
            lastToken.kind = T_LEFT_SQUARE_BRACKET;
        }
        else if (lastChar == ']')
        {
            lastToken.kind = T_RIGHT_SQUARE_BRACKET;
        }
        else if (isalpha(lastChar))
        {
            while (isalpha(lastChar) || isdigit(lastChar) || lastChar == '_')
            {
                pushChar();
            }
            if (lastToken.value == "byte")
            {
                lastToken.kind = T_BYTE_TYPE;
            }
            else if (lastToken.value == "string")
            {
                lastToken.kind = T_STRING_TYPE;
            }
            else if (lastToken.value == "int")
            {
                lastToken.kind = T_INT_TYPE;
            }
            else if (lastToken.value == "float")
            {
                lastToken.kind = T_FLOAT_TYPE;
            }
            else if (lastToken.value == "double")
            {
                lastToken.kind = T_DOUBLE_TYPE;
            }
            else if (lastToken.value == "bool")
            {
                lastToken.kind = T_BOOLEAN_TYPE;
            }
            else if (lastToken.value == "void")
            {
                lastToken.kind = T_VOID_TYPE;
            }
            else if (lastToken.value == "namespace")
            {
                lastToken.kind = T_NAMESPACE;
            }
            else if (lastToken.value == "class")
            {
                lastToken.kind = T_CLASS;
            }
            else if (lastToken.value == "struct")
            {
                lastToken.kind = T_STRUCT;
            }
            else if (lastToken.value == "enum")
            {
                lastToken.kind = T_ENUM;
            }
            else if (lastToken.value == "extern")
            {
                lastToken.kind = T_EXTERN;
            }
            else if (lastToken.value == "interface")
            {
                lastToken.kind = T_INTERFACE;
            }
            else if (lastToken.value == "extends")
            {
                lastToken.kind = T_EXTENDS;
            }
            else if (lastToken.value == "implements")
            {
                lastToken.kind = T_IMPLEMENTS;
            }
            else if (lastToken.value == "abstract")
            {
                lastToken.kind = T_ABSTRACT;
            }
            else if (lastToken.value == "public")
            {
                lastToken.kind = T_PUBLIC;
            }
            else if (lastToken.value == "private")
            {
                lastToken.kind = T_PRIVATE;
            }
            else if (lastToken.value == "protected")
            {
                lastToken.kind = T_PROTECTED;
            }
            else if (lastToken.value == "static")
            {
                lastToken.kind = T_STATIC;
            }
            else if (lastToken.value == "if")
            {
                lastToken.kind = T_IF;
            }
            else if (lastToken.value == "else")
            {
                lastToken.kind = T_ELSE;
            }
            else if (lastToken.value == "for")
            {
                lastToken.kind = T_FOR;
            }
            else if (lastToken.value == "while")
            {
                lastToken.kind = T_WHILE;
            }
            else if (lastToken.value == "return")
            {
                lastToken.kind = T_RETURN;
            }
            else if (lastToken.value == "break")
            {
                lastToken.kind = T_BREAK;
            }
            else if (lastToken.value == "continue")
            {
                lastToken.kind = T_CONTINUE;
            }
            else if (lastToken.value == "import")
            {
                lastToken.kind = T_IMPORT;
            }
            else if (lastToken.value == "final")
            {
                lastToken.kind = T_FINAL;
            }
            else if (lastToken.value == "true")
            {
                lastToken.kind = T_TRUE;
            }
            else if (lastToken.value == "false")
            {
                lastToken.kind = T_FALSE;
            }
            else if (lastToken.value == "this")
            {
                lastToken.kind = T_THIS;
            }
            else
            {
                lastToken.kind = T_ID;
            }
            goto independent;
        }
        else if (isdigit(lastChar))
        {
            if (lastChar == '0' && peek(1) == 'x')
            {
                bool nxne = false;
                size_t i = 0;
                for (; !isEOF() && !isspace(lastChar); i++)
                {
                    if (i > 1 && !isxdigit(lastChar))
                        nxne = true;
                    pushChar();
                }
                if (i > 10 || i < 4)
                    werror.syntaxError(E_INVALID_HEX_NUMBER, "Out Of Range Hex Number", "here", index);
                if (nxne)
                    werror.syntaxError(E_INVALID_HEX_NUMBER, "Invalid Hex Number", "here", index);
                lastToken.kind = T_HEX;
            }
            else if (lastChar == '0' && peek(1) == 'b')
            {
                bool nbne = false;
                size_t i = 0;
                for (; !isEOF() && !isspace(lastChar); i++)
                {
                    if (i > 1 && lastChar != '0' && lastChar != '1' && !nbne)
                        nbne = true;
                    pushChar();
                }
                if (i > 10 || i < 3)
                    werror.syntaxError(E_INVALID_NUMBER, "Out Of Range Binary Number", "here", index);
                if (nbne)
                    werror.syntaxError(E_INVALID_NUMBER, "Invalid Binary Number", "here", index);
                lastToken.kind = T_BIN;
            }
            else
            {
                bool isDecimal = false;
                while (true)
                {
                    if (isdigit(lastChar))
                    {
                        pushChar();
                    }
                    else if (lastChar == '.')
                    {
                        if (isDecimal)
                        {
                            lastToken.kind = T_DECIMAL;
                            break;
                        }
                        else
                        {
                            pushChar();
                            isDecimal = true;
                        }
                    }
                    else
                    {
                        if (isDecimal)
                        {
                            lastToken.kind = T_DECIMAL;
                        }
                        else
                        {

                            lastToken.kind = T_INT;
                        }
                        break;
                    }
                }
                if (lastToken.kind == T_INT && std::atoll(lastToken.value.c_str()) > 2147483647)
                {
                    werror.syntaxError(E_INVALID_NUMBER, "Invalid Number", "here", index);
                }
            }

            goto independent;
        }
        else
        {
            werror.syntaxError(E_UNRECOGNIZED_TOKEN, "Unrecognized Token", "here", index);
            return;
        }
        pushChar();
    independent:
        lastToken.index = index - lastToken.value.length();
        tokens.push_back(lastToken);
    }
}