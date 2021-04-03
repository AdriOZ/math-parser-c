#pragma once

#include "token.h"

// Holds the information needed to tokenize an expression
typedef struct s_Tokenizer
{
    char *expression;
    char *begin;
    char *end;
    char *pointer;
} Tokenizer;

// Creates a new tokenizer for the passed expression
Tokenizer *tokenizer_create(char *expression);

// Gets the next token. This process moves the internal pointer the expression.
Token tokenizer_next(Tokenizer *tokenizer);

// Resets the internal pointer of the tokenizer to the beginning of the expression.
void tokenizer_reset(Tokenizer *tokenizer);
