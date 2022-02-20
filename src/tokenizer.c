#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "util.h"
#include "tokenizer.h"

static int tokenizer_is_valid_char(char c)
{
    return isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')' || c == '.';
}

Tokenizer *tokenizer_create(char *expression)
{
    if (expression == NULL)
    {
        return NULL;
    }

    Tokenizer *tokenizer = New(Tokenizer);
    tokenizer->expression = expression;
    tokenizer->begin = expression;
    tokenizer->end = expression;
    tokenizer->pointer = expression;
    while (*(tokenizer->end++))
        ;
    tokenizer->end--;
    return tokenizer;
}

Token tokenizer_next(Tokenizer *tokenizer)
{
    while (!tokenizer_is_valid_char(*tokenizer->pointer) && tokenizer->pointer < tokenizer->end)
    {
        tokenizer->pointer++;
    }

    Token result;

    if (tokenizer->pointer >= tokenizer->end)
    {
        result = token_create_end();
    }
    else if (*tokenizer->pointer == '+')
    {
        if (isdigit(*(tokenizer->pointer + 1)))
        {
            tokenizer->pointer++;
            char *current = tokenizer->pointer;
            int lenght = 0;
            int decimal_separator_count = 0;

            for (; isdigit(*tokenizer->pointer) || (*tokenizer->pointer == '.' && decimal_separator_count == 0) || *tokenizer->pointer == ','; tokenizer->pointer++, lenght++)
            {
                if (*tokenizer->pointer == '.')
                {
                    decimal_separator_count++;
                }
                else if (*tokenizer->pointer == ',')
                {
                    lenght--;
                }
            }
            char *value = NewArray(char, (lenght + 1));
            for (int i = 0; i < lenght; i++, current++)
            {
                if (*current != ',')
                {
                    value[i] = *current;
                }
                else
                {
                    i--;
                }
            }
            value[lenght] = '\0';
            result = token_create_number(strtod(value, NULL));
            Delete(value);
            tokenizer->pointer -= 1;
        }
        else
        {
            result = token_create_addition();
        }
    }
    else if (*tokenizer->pointer == '-')
    {
        if (isdigit(*(tokenizer->pointer + 1)))
        {
            tokenizer->pointer++;
            char *current = tokenizer->pointer;
            int lenght = 0;
            int decimal_separator_count = 0;

            for (; isdigit(*tokenizer->pointer) || (*tokenizer->pointer == '.' && decimal_separator_count == 0) || *tokenizer->pointer == ','; tokenizer->pointer++, lenght++)
            {
                if (*tokenizer->pointer == '.')
                {
                    decimal_separator_count++;
                }
                else if (*tokenizer->pointer == ',')
                {
                    lenght--;
                }
            }
            char *value = NewArray(char, (lenght + 1));
            for (int i = 0; i < lenght; i++, current++)
            {
                if (*current != ',')
                {
                    value[i] = *current;
                }
                else
                {
                    i--;
                }
            }
            value[lenght] = '\0';
            result = token_create_number(strtod(value, NULL) * -1);
            Delete(value);
            tokenizer->pointer -= 1;
        }
        else
        {
            result = token_create_substraction();
        }
    }
    else if (*tokenizer->pointer == '*')
    {
        result = token_create_multiplication();
    }
    else if (*tokenizer->pointer == '/')
    {
        result = token_create_division();
    }
    else if (*tokenizer->pointer == '^')
    {
        result = token_create_exponentation();
    }
    else if (*tokenizer->pointer == '(')
    {
        result = token_create_bracket_open();
    }
    else if (*tokenizer->pointer == ')')
    {
        result = token_create_bracket_close();
    }
    else if (*tokenizer->pointer == '.')
    {
        char *current = tokenizer->pointer;
        int lenght = 1;

        for (tokenizer->pointer++; isdigit(*tokenizer->pointer); tokenizer->pointer++, lenght++)
            ;
        char *value = NewArray(char, (lenght + 2));
        value[0] = '0';

        for (int i = 1; i <= lenght; i++, current++)
        {
            value[i] = *current;
        }
        value[lenght + 1] = '\0';
        result = token_create_number(strtod(value, NULL));
        Delete(value);
        tokenizer->pointer -= 1;
    }
    else if (isdigit(*tokenizer->pointer))
    {
        char *current = tokenizer->pointer;
        int lenght = 0;
        int decimal_separator_count = 0;

        for (; isdigit(*tokenizer->pointer) || (*tokenizer->pointer == '.' && decimal_separator_count == 0) || *tokenizer->pointer == ','; tokenizer->pointer++, lenght++)
        {
            if (*tokenizer->pointer == '.')
            {
                decimal_separator_count++;
            }
            else if (*tokenizer->pointer == ',')
            {
                lenght--;
            }
        }
        char *value = NewArray(char, (lenght + 1));
        for (int i = 0; i < lenght; i++, current++)
        {
            if (*current != ',')
            {
                value[i] = *current;
            }
            else
            {
                i--;
            }
        }
        value[lenght] = '\0';
        result = token_create_number(strtod(value, NULL));
        Delete(value);
        tokenizer->pointer -= 1;
    }

    tokenizer->pointer++;
    return result;
}

void tokenizer_reset(Tokenizer *tokenizer)
{
    if (tokenizer != NULL)
    {
        tokenizer->pointer = tokenizer->begin;
    }
}
