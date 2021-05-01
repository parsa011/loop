#include "tokenizer.h"

std::map<std::string, TOKENS> StringToTokenKind = {
    //Data Types
    { "char" ,       T_CHAR_TYPE    },
    { "string" ,     T_STRING       },
    { "int" ,        T_INT_TYPE     },
    { "float" ,      T_FLOAT_TYPE   },
    { "double" ,     T_DOUBLE_TYPE  },
    { "bool" ,       T_BOOLEAN_TYPE },
    { "void" ,       T_VOID_TYPE    },
    //Keywords
    { "namespace" ,  T_NAMESPACE    },
    { "class" ,      T_CLASS        },
    { "struct",      T_STRUCT       },
    { "enum" ,       T_ENUM         },
    { "extern" ,     T_EXTERN       },
    { "interface" ,  T_INTERFACE    },
    { "extends" ,    T_EXTENDS      },
    { "implements" , T_IMPLEMENTS   },
    { "abstract" ,   T_ABSTRACT     },
    { "public" ,     T_PUBLIC       },
    { "private" ,    T_PRIVATE      },
    { "protected" ,  T_PROTECTED    },
    { "static" ,     T_STATIC       },
    { "if" ,         T_IF           },
    { "else" ,       T_ELSE         },
    { "for" ,        T_FOR          },
    { "while" ,      T_WHILE        },
    { "return" ,     T_RETURN       },
    { "break" ,      T_BREAK        },
    { "continue" ,   T_CONTINUE     },
    { "using" ,      T_USING        },
    { "final" ,      T_FINAL        },
    { "true" ,       T_TRUE         },
    { "false" ,      T_FALSE        },
    { "this" ,       T_THIS         }
};

auto Tokenizer::getKind(const std::string& type) {
  auto kind = StringToTokenKind.find(type);
  if (kind == std::end(StringToTokenKind)) return T_ID;
  return kind->second;
}

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
            pushChar();
            while (!isEOF())
            {
                if (lastChar == '"')
                {
                    if (peek(-1) == '\\')
                    {
                        pushChar();
                    }
                    else
                    {
                        break;
                    }
                }
                else if (isLCOF() && lastChar != '"')
                {
                    errorHandler.syntax(Error::MISSING_QUOTATION_MARK, "Quated String Must Be Finished", src.c_str(), index);
                    exit(1);
                }
                else
                {
                    pushChar();
                }
            }
            lastToken.kind = T_CHAR;
        }
        else if (lastChar == '\'')
        {
            bool charEnd = false;
                        pushChar();
            for (size_t i = 0; !isEOF(); i++)
            {
                if (lastChar == '\'')
                {
                    if (i == 0)
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
                                    else
                                    {
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
                                    else
                                    {
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
            
            lastToken.kind = getKind(lastToken.value);
            
            lastToken.index = index - lastToken.value.length();
            tokens.push_back(lastToken);
            continue;
        }
        else
        {
            errorHandler.syntax(Error::UNRECOGNIZED_TOKEN, "Unrecognized Token", data.c_str(), index);
            exit(1);
        }
        lastToken.value += lastChar;
        lastToken.index = index - lastToken.value.length();
        advance(1);
        tokens.push_back(lastToken);
    }
}
