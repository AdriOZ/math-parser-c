#pragma once

#include "token.h"
#include "token_list.h"

// Represents the result of parsing an expression.
typedef struct s_ParserResult
{
    double result;
    const char *error;
} ParserResult;

// Returns the result of the given math expression.
ParserResult *parser_parse(char *expression);

// Validates a list of tokens. Returns the error message or NULL if everythign is correct.
const char *parser_validate_list(TokenList *list);
