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
        if (lastChar == '"') // Notice String Parser Is't Stable; That's Next Todo
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
                        startIndex++;
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
                    startIndex++;
                }
            }
        }
        else if (lastChar == '\'')
        {
            size_t startIndex = 0;
            while (true)
            {
                if (startIndex > 0)
                {
                    if (isLCOF() && lastChar != '\'')
                    {
                        errorHandler.syntax(Error::MISSING_APOSTROPHE_MARK, "Quated Char Must Be Finished", src.c_str(), index);
                        break;
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
                        lastToken.value += lastChar;
                        advance(1);
                        startIndex++;
                    }
                }
                else
                {
                    lastToken.value += lastChar;
                    advance(1);
                    startIndex++;
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