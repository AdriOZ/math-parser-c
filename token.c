#include <stdlib.h>
#include <stdio.h>
#include "token.h"

Token *token_create(TokenType type, double value)
{
    Token *tmp = malloc(sizeof(Token));
    tmp->type = type;
    tmp->value = value;
    return tmp;
}

Token *token_create_number(double value)
{
    return token_create(Number, value);
}

Token *token_create_addition()
{
    return token_create(Addition, 0);
}

Token *token_create_substraction()
{
    return token_create(Substraction, 0);
}

Token *token_create_multiplication()
{
    return token_create(Multiplication, 0);
}

Token *token_create_division()
{
    return token_create(Division, 0);
}

Token *token_create_bracket_open()
{
    return token_create(BracketOpen, 0);
}

Token *token_create_bracket_close()
{
    return token_create(BracketClose, 0);
}

Token *token_create_end()
{
    return token_create(End, 0);
}

void token_destroy(Token *token)
{
    if (token != NULL)
    {
        free(token);
    }
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
            printf("Token { Number(%f) }\n", token->value);
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
        case BracketOpen:
            printf("Token { Opening Bracket('(') }\n");
            break;
        case BracketClose:
            printf("Token { Closing Bracket(')') }\n");
            break;
        case End:
            printf("Token { END }\n");
            break;
        }
    }
}
