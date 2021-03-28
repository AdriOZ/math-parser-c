#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "tokenizer.h"

/* Private utilities */
struct s_OutputQueueNode
{
    double value;
    TokenType type;
    struct s_OutputQueueNode *next;
};

struct s_OutputQueueHead
{
    struct s_OutputQueueNode *node;
};

struct s_OperatorStackNode
{
    TokenType type;
    struct s_OperatorStackNode *next;
};

struct s_OperatorStackHead
{
    struct s_OperatorStackNode *node;
};

struct s_ResultStackNode
{
    double value;
    struct s_ResultStackNode *next;
};

struct s_ResultStackHead
{
    struct s_ResultStackNode *node;
};

void push_output_queue(struct s_OutputQueueHead *head, double value, TokenType type)
{
    if (head != NULL)
    {
        if (head->node == NULL)
        {
            head->node = malloc(sizeof(struct s_OutputQueueNode));
            head->node->value = value;
            head->node->type = type;
            head->node->next = NULL;
        }
        else
        {
            struct s_OutputQueueNode *ptr = head->node;

            for (; ptr->next != NULL; ptr = ptr->next)
                ;

            ptr->next = malloc(sizeof(struct s_OutputQueueNode));
            ptr->next->value = value;
            ptr->next->type = type;
            ptr->next->next = NULL;
        }
    }
}

struct s_OutputQueueNode *pop_output_queue(struct s_OutputQueueHead *head)
{
    struct s_OutputQueueNode *result = NULL;

    if (head != NULL && head->node != NULL)
    {
        result = head->node;
        struct s_OutputQueueNode *tmp = head->node;
        head->node = head->node->next;
    }

    return result;
}

void push_operator_stack(struct s_OperatorStackHead *head, TokenType type)
{
    if (head != NULL)
    {
        if (head->node == NULL)
        {
            head->node = malloc(sizeof(struct s_OperatorStackNode));
            head->node->type = type;
            head->node->next = NULL;
        }
        else
        {
            struct s_OperatorStackNode *tmp = malloc(sizeof(struct s_OperatorStackNode));
            tmp->type = type;
            tmp->next = head->node;
            head->node = tmp;
        }
    }
}

TokenType pop_operator_stack(struct s_OperatorStackHead *head)
{
    TokenType result;

    if (head != NULL && head->node != NULL)
    {
        result = head->node->type;
        struct s_OperatorStackNode *tmp = head->node;
        head->node = head->node->next;
        free(tmp);
    }

    return result;
}

void push_result_stack(struct s_ResultStackHead *head, double value)
{
    if (head != NULL)
    {
        if (head->node == NULL)
        {
            head->node = malloc(sizeof(struct s_ResultStackNode));
            head->node->value = value;
            head->node->next = NULL;
        }
        else
        {
            struct s_ResultStackNode *tmp = malloc(sizeof(struct s_ResultStackNode));
            tmp->value = value;
            tmp->next = head->node;
            head->node = tmp;
        }
    }
}

double pop_result_stack(struct s_ResultStackHead *head)
{
    double result;

    if (head != NULL && head->node != NULL)
    {
        result = head->node->value;
        struct s_ResultStackNode *tmp = head->node;
        head->node = head->node->next;
        free(tmp);
    }

    return result;
}

/* Private utilities */

TokenList *parser_create_token_list(Token *token)
{
    TokenList *list = malloc(sizeof(TokenList));
    list->token = token;
    list->next = NULL;
}

TokenList *parser_build_from_expression(char *expression)
{
    if (expression == NULL)
    {
        return NULL;
    }

    Tokenizer *tokenizer = tokenizer_create(expression);
    Token *token = tokenizer_next(tokenizer);
    TokenList *list = parser_create_token_list(token);

    while (token->type != End)
    {
        token = tokenizer_next(tokenizer);
        parser_push_token_node(list, token);
    }

    free(tokenizer);
    return list;
}

ParserResult *parser_parse(char *expression)
{
    ParserResult *result = malloc(sizeof(ParserResult));

    if (expression != NULL)
    {
        TokenList *list = parser_build_from_expression(expression);
        const char *error = parser_validate_list(list);

        if (error == NULL)
        {
            struct s_OutputQueueHead *queue = malloc(sizeof(struct s_OutputQueueHead));
            struct s_OperatorStackHead *stack = malloc(sizeof(struct s_OutputQueueHead));
            result->error = NULL;
            result->result = 0;

            for (TokenListNode *current = list; current != NULL && current->token->type != End; current = current->next)
            {
                if (current->token->type == Number)
                {
                    push_output_queue(queue, current->token->value, Number);
                }
                else if (
                    current->token->type == Addition ||
                    current->token->type == Substraction ||
                    current->token->type == Multiplication ||
                    current->token->type == Division)
                {
                    while (stack->node != NULL && stack->node->type > current->token->type)
                    {
                        push_output_queue(queue, 0, pop_operator_stack(stack));
                    }
                    push_operator_stack(stack, current->token->type);
                }
                else if (current->token->type == BracketOpen)
                {
                    push_operator_stack(stack, current->token->type);
                }
                else if (current->token->type == BracketClose)
                {
                    while (stack->node != NULL && stack->node->type != BracketOpen)
                    {
                        push_output_queue(queue, 0, pop_operator_stack(stack));
                    }
                    pop_operator_stack(stack);
                }
            }

            while (stack->node != NULL)
            {
                push_output_queue(queue, 0, pop_operator_stack(stack));
            }

            struct s_ResultStackHead *resultStack = malloc(sizeof(struct s_ResultStackHead));

            while (queue->node != NULL)
            {
                struct s_OutputQueueNode *current = pop_output_queue(queue);

                if (current->type == Number)
                {
                    push_result_stack(resultStack, current->value);
                }
                else if (
                    current->type == Addition ||
                    current->type == Substraction ||
                    current->type == Multiplication ||
                    current->type == Division)
                {
                    double value2 = pop_result_stack(resultStack);
                    double value1 = pop_result_stack(resultStack);

                    switch (current->type)
                    {
                    case Addition:
                        push_result_stack(resultStack, value1 + value2);
                        break;
                    case Substraction:
                        push_result_stack(resultStack, value1 - value2);
                        break;
                    case Multiplication:
                        push_result_stack(resultStack, value1 * value2);
                        break;
                    case Division:
                        push_result_stack(resultStack, value1 / value2);
                        break;
                    }
                }
            }
            result->result = pop_result_stack(resultStack);
        }
        else
        {
            result->result = 0;
            result->error = error;
        }
        parser_destroy_token_list(list);
    }
    else
    {
        result->result = 0;
        result->error = "The given expression is null";
    }
    return result;
}

const char *parser_validate_list(TokenList *list)
{
    char *error = NULL;

    if (list != NULL)
    {
        TokenListNode *current = list;
        int brackets = 0;
        int operators = 0;
        int operands = 0;

        for (; !error && current; current = current->next)
        {
            if (
                current->token->type == Number &&
                (current->next && (current->next->token->type == Number || current->next->token->type == BracketOpen)))
            {
                error = "After a number only an operator or a closing bracket are allowed";
            }
            else if (
                (
                    current->token->type == Addition ||
                    current->token->type == Substraction ||
                    current->token->type == Multiplication ||
                    current->token->type == Division) &&
                (!current->next ||
                 (current->next &&
                  current->next->token->type != Number &&
                  current->next->token->type != BracketOpen)))
            {
                error = "After an operator, only a number or an opening bracket are allowed";
            }
            else if (
                current->token->type == BracketOpen &&
                (!current->next ||
                 current->next->token->type != Number))
            {
                error = "After an opening bracket, only a number is allowed";
            }
            else if (
                current->token->type == BracketClose &&
                (current->next && (current->next->token->type == Number || current->next->token->type == BracketOpen)))
            {
                error = "After a closing bracket, only an operator is allowed";
            }
            else if (current->token->type == BracketClose && brackets == 0)
            {
                printf("%d\n", brackets);
                error = "Closing bracket found before any opening bracket";
            }
            else
            {
                if (current->token->type == Number)
                {
                    operands++;
                }
                else if (
                    current->token->type == Addition ||
                    current->token->type == Substraction ||
                    current->token->type == Multiplication ||
                    current->token->type == Division)
                {
                    operators++;
                }
                else if (current->token->type == BracketOpen)
                {
                    brackets++;
                }
                else if (current->token->type == BracketClose)
                {
                    brackets--;
                }
            }
        }
        if (brackets != 0)
        {
            error = "No mathing brackets found";
        }
        else if (operators > 0 && operands == 0)
        {
            error = "No operands found";
        }
    }
    else
    {
        error = "No list specified";
    }

    return error;
}

void parser_push_token_node(TokenList *list, Token *token)
{
    if (list != NULL && token != NULL)
    {
        TokenListNode *pointer = list;

        for (; pointer->next; pointer = pointer->next)
            ;
        pointer->next = malloc(sizeof(TokenListNode));
        pointer->next->next = NULL;
        pointer->next->token = token;
    }
}

void parser_print_token_list(TokenList *list)
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
            token_print(pointer->token);
        }
    }
}

void parser_destroy_token_list(TokenList *list)
{
    TokenListNode *current = list;
    TokenListNode *next = current->next;

    while (next != NULL)
    {
        free(current);
        current = next;
        next = current->next;
    }
}
