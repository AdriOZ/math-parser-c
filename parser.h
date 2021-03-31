#pragma once

#include "token.h"
#include "token_list.h"

// Represents the result of parsing an expression.
typedef struct s_ParserResult
{
    double result;
    const char *error;
} ParserResult;

// Creates a list of tokens starting from the passed token.
TokenList *parser_create_token_list(Token token);

// Creates a list of tokens based on the passed expression.
TokenList *parser_build_from_expression(char *expression);

// Returns the result of the given math expression.
ParserResult *parser_parse(char *expression);

// Validates a list of tokens. Returns the error message or NULL if everythign is correct.
const char *parser_validate_list(TokenList *list);

// Pushes a token into the end of the list.
void parser_push_token_node(TokenList *list, Token token);

// Frees the memory of the given token list. It does not free the memory of the created tokens.
void parser_destroy_token_list(TokenList *list);

// Prints the list of tokens.
void parser_print_token_list(TokenList *list);
