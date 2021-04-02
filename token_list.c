#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "token.h"
#include "tokenizer.h"
#include "token_list.h"

TokenList *token_list_create(Token token)
{
    TokenList *list = New(TokenList);
    list->token = token;
    list->next = NULL;
    return list;
}

TokenList *token_list_build_from_expression(char *expression)
{
    if (expression == NULL)
    {
        return NULL;
    }

    Tokenizer *tokenizer = tokenizer_create(expression);
    Token token = tokenizer_next(tokenizer);
    TokenList *list = token_list_create(token);

    while (token.type != End)
    {
        token = tokenizer_next(tokenizer);
        token_list_push_token(list, token);
    }

    Delete(tokenizer);
    return list;
}

void token_list_push_token(TokenList *list, Token token)
{
    if (list != NULL)
    {
        TokenListNode *pointer = list;

        for (; pointer->next; pointer = pointer->next)
            ;
        pointer->next = New(TokenListNode);
        pointer->next->next = NULL;
        pointer->next->token = token;
    }
}

void token_list_print(TokenList *list)
{
    if (list == NULL)
    {
        printf("TokenList{ NULL }\n");
    }
    else
    {
        printf("\nTokenList\n=========\n");

        for (TokenListNode *pointer = list; pointer; pointer = pointer->next)
        {
            token_print(&pointer->token);
        }
    }
}

void token_list_destroy(TokenList *list)
{
    TokenListNode *current = list;
    TokenListNode *next = current->next;

    while (next != NULL)
    {
        Delete(current);
        current = next;
        next = current->next;
    }
}
