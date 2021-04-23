#pragma once

#include "token.h"

// Represents a node in a list of tokens.
typedef struct s_TokenListNode
{
    Token token;
    struct s_TokenListNode *next;
    struct s_TokenListNode *last;
} TokenListNode;

// Alias of the head of the list.
typedef TokenListNode TokenList;

// Creates a list of tokens starting from the passed token.
TokenList *token_list_create(Token token);

// Creates a list of tokens based on the passed expression.
TokenList *token_list_build_from_expression(char *expression);

// Pushes a token into the end of the list.
void token_list_push_token(TokenList *list, Token token);

// Frees the memory of the given token list. It does not free the memory of the created tokens.
void token_list_destroy(TokenList *list);

// Prints the list of tokens.
void token_list_print(TokenList *list);
