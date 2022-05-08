#include <stdio.h>

#include "token.h"
#include "util.h"

Token token_create(TokenType type, f64 value)
{
    return (Token){type, value};
}

Token token_create_number(f64 value)
{
    return token_create(Number, value);
}

Token token_create_addition()
{
    return token_create(Addition, 0);
}

Token token_create_substraction()
{
    return token_create(Substraction, 0);
}

Token token_create_multiplication()
{
    return token_create(Multiplication, 0);
}

Token token_create_division()
{
    return token_create(Division, 0);
}

Token token_create_exponentation()
{
    return token_create(Exponentation, 0);
}

Token token_create_bracket_open()
{
    return token_create(BracketOpen, 0);
}

Token token_create_bracket_close()
{
    return token_create(BracketClose, 0);
}

Token token_create_end()
{
    return token_create(End, 0);
}

void token_print(Token *token)
{
    if (token == NULL)
    {
        printf("Token { NULL }\n");
    }
    else
    {
        switch (token->type)
        {
        case Number:
            printf("Token { Number(%Lf) }\n", token->value);
            break;
        case Addition:
            printf("Token { Addition('+') }\n");
            break;
        case Substraction:
            printf("Token { Substraction('-') }\n");
            break;
        case Multiplication:
            printf("Token { Multiplication('*') }\n");
            break;
        case Division:
            printf("Token { Division('/') }\n");
            break;
        case Exponentation:
            printf("Token { Exponentation('^') }\n");
            break;
        case BracketOpen:
            printf("Token { Opening Bracket('(') }\n");
            break;
        case BracketClose:
            printf("Token { Closing Bracket(')') }\n");
            break;
        case End:
            printf("Token { END }\n");
            break;
        default:
            printf("Token { UNKNOWN }\n");
            break;
        }
    }
}
