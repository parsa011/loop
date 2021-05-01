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
    else
    {
        return src[src.length()];
    }
}

Tokenizer::Tokenizer(std::string data, Error &error) : src(data), errorHandler(error)
{
    lastChar = src[0];
    while (!isEOF())
    {
        lastToken.value.clear();
        while (isspace(lastChar))
        {
            advance(1);
        }

        if (lastChar == '/' && peek(1) == '*')
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
                errorHandler.syntax(Error::CLOSE_COMMENT, "You need to close the comment", src.c_str(), index);
            }
            continue;
        }
        else if (lastChar == '/' && peek(1) == '/')
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
        else if (lastChar == '"')
        {
            size_t startIndex = 0;
            while (!isEOF())
            {
                if (isLCOF() && lastChar != '"')
                {
                    errorHandler.syntax(Error::MISSING_QUOTATION_MARK, "Quated Char Must Be Finished", src.c_str(), index);
                }
                else if (startIndex == 1 && lastChar == '"')
                {
                    errorHandler.syntax(Error::NO_NULL_CHAR, "Char Type Must Be Initialized", src.c_str(), index);
                }
                else if (startIndex > 1 && lastChar == '"')
                {
                    if (peek(-1) == '\\')
                    {

                        pushChar();
                        ++startIndex;
                    }
                    else
                    {
                        lastToken.kind = T_STRING;
                        break;
                    }
                }
                else
                {

                    pushChar();
                    ++startIndex;
                }
            }
        }
        else if (lastChar == '\'')
        {
            bool charEnd = false;
            for (size_t i = 0; true; i++)
            {
                if (lastChar == '\'')
                {
                    if (i == 0)
                    {
                        pushChar();
                    }
                    else if (i == 1)
                    {
                        errorHandler.syntax(Error::NO_NULL_CHAR, "Quated Char Must Be Initialized", src.c_str(), index);
                        exit(1);
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if (isLCOF())
                    {
                        errorHandler.syntax(Error::MISSING_APOSTROPHE_MARK, "Quated Char Must Be Finished", src.c_str(), index);
                        exit(1);
                    }
                    else if (charEnd && lastChar != '\'')
                    {
                        errorHandler.syntax(Error::MORE_THAN_ONE_BYTE, "Char Type Can Only Contains 1 Byte", src.c_str(), index);
                        exit(1);
                    }
                    else if (lastChar == '\\')
                    {
                        pushChar();
                        if (lastChar == 'a' || lastChar == 'b' || lastChar == 'e' || lastChar == 'f' || lastChar == 'n' || lastChar == 'r' || lastChar == 't' || lastChar == 'v' || lastChar == '\\' || lastChar == '\'' || lastChar == '"')
                        {
                            pushChar();
                        }
                        else if (lastChar == 'x')
                        {
                            pushChar();
                            for (size_t i = 0; !isEOF(); i++)
                            {
                                if (isxdigit(lastChar))
                                {
                                    if (i > 7)
                                    {
                                        errorHandler.syntax(Error::INVALID_HEX_DIGIT, "Invalid Hex Digit", src.c_str(), index);
                                        exit(1);
                                    }
                                    else {
                                        pushChar();
                                    }
                                }
                                else
                                {
                                    if (i < 2)
                                    {
                                        errorHandler.syntax(Error::INVALID_HEX_DIGIT, "Invalid Hex Digit", src.c_str(), index);
                                        exit(1);
                                    }
                                    else {
                                        break;
                                    }
                                }
                            }
                            charEnd = true;
                        }
                        else if (isdigit(lastChar))
                        {
                            for (size_t i = 0; isdigit(lastChar); i++)
                            {
                                pushChar();
                                if (i > 1)
                                {
                                    if (std::atoi(lastToken.value.substr(lastToken.value.length() - 3, 3).c_str()) > 377)
                                    {
                                        std::cout << lastToken.value.length() << std::endl;
                                        errorHandler.syntax(Error::INVALID_OCTAL_NUMBER, "Invalid Octal Number", src.c_str(), index);
                                        exit(1);
                                    }
                                    charEnd = true;
                                }
                            }
                        }
                        else
                        {
                            errorHandler.syntax(Error::UNSUPPORTED_ESCAPE_SEQUENCE, "Unsupported Escape Squanse", src.c_str(), index);
                            exit(1);
                        }
                    }
                    else
                    {
                        pushChar();
                    }
                    charEnd = true;
                }
            }
            lastToken.kind = T_CHAR;
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
        else if (lastChar == '/')
        {
            lastToken.kind = T_SLASH;
        }
        else if (lastChar == '%')
        {
            lastToken.kind = T_PERCENT;
        }
        else if (lastChar == ';')
        {
            lastToken.kind = T_SEMICOLON;
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
            if (lastToken.value == "char")
            {
                lastToken.kind = T_CHAR_TYPE;
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
            else if (lastToken.value == "using")
            {
                lastToken.kind = T_USING;
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
            lastToken.index = index - lastToken.value.length();
            tokens.push_back(lastToken);
            continue;
        }
        else
        {
            errorHandler.syntax(Error::UNRECOGNIZED_TOKEN, "Unrecognized Token", data.c_str(), index);
        }
        lastToken.value += lastChar;
        lastToken.index = index - lastToken.value.length();
        advance(1);
        tokens.push_back(lastToken);
    }
}
