#pragma once

#include "token.h"

// Represents a node in a list of tokens.
typedef struct s_TokenListNode
{
    Token token;
    struct s_TokenListNode *next;
} TokenListNode;

// Alias of the head of the list.
typedef TokenListNode TokenList;
