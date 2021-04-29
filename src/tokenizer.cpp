#include "tokenizer.h"

bool Tokenizer::isEOF() // End Of File
{
    if (index < src.length() && lastChar != '\0' && lastChar != char(-1))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Tokenizer::isLCOF() // Is Last Char Of File
{
    if (index < src.length() - 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Tokenizer::advance(int offset)
{
    if (offset + index < src.length())
    {
        index += offset;
    }
    else
    {
        index = src.length();
    }
    lastChar = src[index];
}

char Tokenizer::peek(int offset)
{
    if (offset + index < src.length())
    {
        return src[index + offset];
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
                if (isEOF())
                {
                    errorHandler.syntax(Error::CLOSE_COMMENT, "You need to close the comment", src.c_str(), index);
                }
            }
            continue;
        }
        else if (lastChar == '"') // Notice String Parser Is't Stable; That's Next Todo
        {
            size_t startIndex = 0;
            while (!isEOF())
            {
                if (isLCOF() && lastChar != '\'')
                {
                    errorHandler.syntax(Error::MISSING_QUOTATION_MARK, "Quated Char Must Be Finished", src.c_str(), index);
                }
                else if (startIndex == 1 && lastChar == '\'')
                {
                    errorHandler.syntax(Error::NO_NULL_CHAR, "Char Type Must Be Initialized", src.c_str(), index);
                }
                else if (startIndex > 1 && lastChar != '\'')
                {
                    if (peek(-1) == '\\')
                    {
                        lastToken.value += lastChar;
                        advance(1);
                        ++startIndex;
                    }
                    else
                    {
                        errorHandler.syntax(Error::MORE_THAN_ONE_BYTE, "Char Type Cannot Give More Than 1 Byte", src.c_str(), index);
                    }
                }
                else if (lastChar == '\'' && startIndex > 0)
                {
                    lastToken.kind = T_CHAR;
                    break;
                }
                else
                {
                    lastToken.value += lastChar;
                    advance(1);
                    ++startIndex;
                }
            }
        }
        else if (lastChar == '\'')
        {
            size_t startIndex = 0;
            lastToken.value += lastChar;
            advance(1);
            ++startIndex;
            while (true)
            {
                if (isLCOF() && lastChar != '\'')
                {
                    errorHandler.syntax(Error::MISSING_APOSTROPHE_MARK, "Quated Char Must Be Finished", src.c_str(), index);
                    exit(1);
                }
                else if (startIndex == 1 && lastChar == '\'')
                {
                    errorHandler.syntax(Error::NO_NULL_CHAR, "Quated Char Must Be Initialized", src.c_str(), index);
                    break;
                }
                else if (lastChar == '\'' && peek(-1) != '\\')
                {
                    lastToken.kind = T_CHAR;
                    break;
                }
                else
                {
                    if (lastChar == '\\')
                    {
                        if (peek(1) == 'a' || peek(1) == 'b' || peek(1) == 'e' || peek(1) == 'f' || peek(1) == 'n' || peek(1) == 'r' || peek(1) == 't' || peek(1) == 'v' || peek(1) == '\\' || peek(1) == '\'' || peek(1) == '"')
                        {
                            lastToken.value += lastChar;
                            advance(1);
                            ++startIndex;
                            if (peek(1) != '\'')
                            {
                                errorHandler.syntax(Error::MORE_THAN_ONE_BYTE, "Char Type Can Only Contains 1 Byte", src.c_str(), index);
                                exit(1);
                            }
                        }
                        else if (peek(1) == 'x')
                        {
                            for (size_t i = 0; i < 4; i++)
                            {
                                lastToken.value += lastChar;
                                advance(1);
                                ++startIndex;
                                if (i > 2 && !isxdigit(lastChar))
                                {
                                    errorHandler.syntax(Error::NOT_HEX_DIGIT, "Is't Hexadecimal Digit", src.c_str(), index);
                                    std::cout << lastChar << std::endl;
                                    exit(1);
                                }
                                else
                                {
                                    lastToken.kind = T_CHAR;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            errorHandler.syntax(Error::UNSUPPORTED_ESCAPE_SEQUENCE, "Unsupported Escape Squanse", src.c_str(), index);
                            exit(1);
                        }
                    }
                    lastToken.value += lastChar;
                    advance(1);
                    ++startIndex;
                }
            }
        }
        else if (lastChar == '=')
        {
            if (peek(1) == '=')
            {
                lastToken.kind = T_DOUBLE_EQUAL;
                lastToken.value = '=';
                advance(1);
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
                lastToken.value = '+';
                advance(1);
            }
            else if (peek(1) == '+')
            {
                lastToken.kind = T_DOUBLE_PLUS;
                lastToken.value = '+';
                advance(1);
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
                lastToken.value = '-';
                advance(1);
            }
            else if (peek(1) == '-')
            {
                lastToken.kind = T_DOUBLE_MINUS;
                lastToken.value = '-';
                advance(1);
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
                lastToken.value = '|';
                advance(1);
            }
            else if (peek(1) == '|')
            {
                lastToken.kind = T_DOUBLE_PIPE;
                lastToken.value = '|';
                advance(1);
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
                lastToken.value = '<';
                advance(1);
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
                lastToken.value = '>';
                advance(1);
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
                lastToken.value = '&';
                advance(1);
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
        else
        {
            errorHandler.syntax(Error::UNRECOGNIZED_TOKEN, "Unrecognized Token", data.c_str(), index);
        }
        lastToken.value += lastChar;
        lastToken.index = index - lastToken.value.length();
        tokens.push_back(lastToken);
        advance(1);
    }
}