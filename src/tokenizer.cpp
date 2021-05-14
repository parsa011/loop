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
    werror.errors.clear();
    werror.warnings.clear();
    tokens.clear();
    src = data;
    index = 0;
    lastChar = src[0];
    while (!isEOF())
    {
        lastToken.value.clear();
        lastToken.index = 0;
        lastToken.kind = T_UNRECOGNIZED;
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
                    if (isEOF())
                    {
                        werror.syntaxError(E_CLOSE_COMMENT, "You Need To Close The Comment", "here", index);
                    }
                    if (lastChar == '*' && peek(1) == '/')
                    {
                        advance(2);
                        break;
                    }
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
            else if (isdigit(peek(1)))
            {
                goto LexNumber;
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
        else if (lastChar == '@')
        {
            pushChar();
            if (isalpha(lastChar))
            {
                while (!isEOF() && isalpha(lastChar))
                {
                    pushChar();
                }
                lastToken.kind = T_LABEL;
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
            lastToken.kind = T_LEFT_ROUND_BRACKET;
        }
        else if (lastChar == ')')
        {
            lastToken.kind = T_RIGHT_ROUND_BRACKET;
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
            if (lastToken.value == "bool")
            {
                lastToken.kind = T_BOOLEAN_TYPE;
            }
            else if (lastToken.value == "byte")
            {
                lastToken.kind = T_BYTE_TYPE;
            }
            else if (lastToken.value == "string")
            {
                lastToken.kind = T_STRING_TYPE;
            }
            else if (lastToken.value == "i8")
            {
                lastToken.kind = T_I8_TYPE;
            }
            else if (lastToken.value == "i16")
            {
                lastToken.kind = T_I16_TYPE;
            }
            else if (lastToken.value == "i32")
            {
                lastToken.kind = T_I32_TYPE;
            }
            else if (lastToken.value == "i64")
            {
                lastToken.kind = T_I64_TYPE;
            }
            else if (lastToken.value == "u8")
            {
                lastToken.kind = T_U8_TYPE;
            }
            else if (lastToken.value == "u16")
            {
                lastToken.kind = T_U16_TYPE;
            }
            else if (lastToken.value == "u32")
            {
                lastToken.kind = T_U32_TYPE;
            }
            else if (lastToken.value == "u64")
            {
                lastToken.kind = T_U64_TYPE;
            }
            else if (lastToken.value == "f8")
            {
                lastToken.kind = T_F8_TYPE;
            }
            else if (lastToken.value == "f16")
            {
                lastToken.kind = T_F16_TYPE;
            }
            else if (lastToken.value == "f32")
            {
                lastToken.kind = T_F32_TYPE;
            }
            else if (lastToken.value == "f64")
            {
                lastToken.kind = T_F64_TYPE;
            }
            else if (lastToken.value == "struct")
            {
                lastToken.kind = T_STRUCT;
            }
            else if (lastToken.value == "enum")
            {
                lastToken.kind = T_ENUM;
            }
            else if (lastToken.value == "module")
            {
                lastToken.kind = T_MODULE;
            }
            else if (lastToken.value == "import")
            {
                lastToken.kind = T_IMPORT;
            }
            else if (lastToken.value == "fn")
            {
                lastToken.kind = T_FUNCTION;
            }
            else if (lastToken.value == "static")
            {
                lastToken.kind = T_STATIC;
            }
            else if (lastToken.value == "pub")
            {
                lastToken.kind = T_PUBLIC;
            }
            else if (lastToken.value == "if")
            {
                lastToken.kind = T_IF;
            }
            else if (lastToken.value == "else")
            {
                lastToken.kind = T_ELSE;
            }
            else if (lastToken.value == "loop")
            {
                lastToken.kind = T_LOOP;
            }
            else if (lastToken.value == "return")
            {
                lastToken.kind = T_RETURN;
            }
            else if (lastToken.value == "stop")
            {
                lastToken.kind = T_STOP;
            }
            else if (lastToken.value == "jump")
            {
                lastToken.kind = T_JUMP;
            }
            else if (lastToken.value == "go")
            {
                lastToken.kind = T_GO;
            }
            else if (lastToken.value == "in")
            {
                lastToken.kind = T_IN;
            }
            else if (lastToken.value == "true" || lastToken.value == "false")
            {
                lastToken.kind = T_BOOLEAN;
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
                    werror.syntaxError(E_OUT_OF_RANGE_HEX, "Out Of Range Hex", "here", index);
                if (nxne)
                    werror.syntaxError(E_INVALID_HEX, "Invalid Hex", "here", index);
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
                if (i > 10)
                    werror.syntaxError(E_OUT_OF_RANGE_BIN, "Out Of Range Binary", "here", index);
                if (nbne || i < 3)
                    werror.syntaxError(E_INVALID_BIN, "Invalid Binary", "here", index);
                lastToken.kind = T_BIN;
            }
            else if (lastChar == '0' && peek(1) == 'u')
            {
                bool nune = false;
                size_t i = 0;
                for (; !isEOF() && !isspace(lastChar); i++)
                {
                    if (i > 1 && !isxdigit(lastChar) && !nune)
                        nune = true;
                    pushChar();
                }
                if (i != 10 || nune)
                    werror.syntaxError(E_INVALID_UNICODE, "Invalid Unicode", "here", index);
                lastToken.kind = T_UNICODE;
            }
            else
            {
            LexNumber:
                lastToken.kind = T_UINT;
                if (lastChar == '-')
                {
                    pushChar();
                    lastToken.kind = T_INT;
                }
                while (!isEOF())
                {
                    if (isdigit(lastChar))
                    {
                        pushChar();
                    }
                    else if (lastChar == '.' && lastToken.kind != T_FLOAT)
                    {
                        pushChar();
                        lastToken.kind = T_FLOAT;
                    }
                    else
                    {
                        break;
                    }
                }
                // TODO: Reimplement String To Int With Error Handling
                if (lastToken.kind == T_INT && std::atoll(lastToken.value.c_str()) > 9223372036854775807)
                {
                    werror.syntaxError(E_INVALID_NUMBER, "Invalid Number", "here", index);
                }
            }

            goto independent;
        }
        if (lastToken.kind == T_UNRECOGNIZED)
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