#pragma once

// The different tokens that can be parsed.
typedef enum e_TokenType
{
    Number = 0,
    Addition = 1,
    Substraction = 2,
    Multiplication = 3,
    Division = 4,
    Exponentation = 5,
    BracketOpen = 6,
    BracketClose = 7,
    End = 8,
    Unknown = 9
} TokenType;

// Holds the type and the value of a token.
typedef struct s_Token
{
    TokenType type;
    double value;
} Token;

// Creates token based on the type and value passed
Token token_create(TokenType type, double value);

// Creates a number token with the value passed
Token token_create_number(double value);

// Creates an addition token
Token token_create_addition();

// Creates a substraction token
Token token_create_substraction();

// Creates a multiplication token
Token token_create_multiplication();

// Creates a division token
Token token_create_division();

// Creates an exponentation token
Token token_create_exponentation();

// Creates a bracket open token
Token token_create_bracket_open();

// Creates a bracket open token
Token token_create_bracket_close();

// Creates an end token
Token token_create_end();

// Prints the token
void token_print(Token *token);
