#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "util.h"
#include "token.h"
#include "token_list.h"
#include "parser.h"

/* Private utilities */
struct s_OutputQueueNode
{
    Token token;
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
    f64 value;
    struct s_ResultStackNode *next;
};

struct s_ResultStackHead
{
    struct s_ResultStackNode *node;
};

static void push_output_queue(struct s_OutputQueueHead *head, Token token)
{
    if (head != NULL)
    {
        if (head->node == NULL)
        {
            head->node = New(struct s_OutputQueueNode);
            head->node->token = token;
            head->node->next = NULL;
        }
        else
        {
            struct s_OutputQueueNode *ptr = head->node;

            for (; ptr->next != NULL; ptr = ptr->next)
                ;

            ptr->next = New(struct s_OutputQueueNode);
            ptr->next->token = token;
            ptr->next->next = NULL;
        }
    }
}

static struct s_OutputQueueNode *pop_output_queue(struct s_OutputQueueHead *head)
{
    struct s_OutputQueueNode *result = NULL;

    if (head != NULL && head->node != NULL)
    {
        result = head->node;
        head->node = head->node->next;
    }

    return result;
}

static void push_operator_stack(struct s_OperatorStackHead *head, TokenType type)
{
    if (head != NULL)
    {
        if (head->node == NULL)
        {
            head->node = New(struct s_OperatorStackNode);
            head->node->type = type;
            head->node->next = NULL;
        }
        else
        {
            struct s_OperatorStackNode *tmp = New(struct s_OperatorStackNode);
            tmp->type = type;
            tmp->next = head->node;
            head->node = tmp;
        }
    }
}

static TokenType pop_operator_stack(struct s_OperatorStackHead *head)
{
    TokenType result = Unknown;

    if (head != NULL && head->node != NULL)
    {
        result = head->node->type;
        struct s_OperatorStackNode *tmp = head->node;
        head->node = head->node->next;
        Delete(tmp);
    }

    return result;
}

static void push_result_stack(struct s_ResultStackHead *head, f64 value)
{
    if (head != NULL)
    {
        if (head->node == NULL)
        {
            head->node = New(struct s_ResultStackNode);
            head->node->value = value;
            head->node->next = NULL;
        }
        else
        {
            struct s_ResultStackNode *tmp = New(struct s_ResultStackNode);
            tmp->value = value;
            tmp->next = head->node;
            head->node = tmp;
        }
    }
}

static f64 pop_result_stack(struct s_ResultStackHead *head)
{
    f64 result = 0;

    if (head != NULL && head->node != NULL)
    {
        result = head->node->value;
        struct s_ResultStackNode *tmp = head->node;
        head->node = head->node->next;
        Delete(tmp);
    }

    return result;
}

/* Private utilities */

ParserResult parser_parse(char *expression)
{
    ParserResult result = (ParserResult){0, NULL};

    if (expression != NULL)
    {
        TokenList *list = token_list_build_from_expression(expression);
        const char *error = parser_validate_list(list);

        if (error == NULL)
        {
            struct s_OutputQueueHead queue = {NULL};
            struct s_OperatorStackHead stack = {NULL};

            for (TokenListNode *current = list; current != NULL && current->token.type != End; current = current->next)
            {
                if (current->token.type == Number)
                {
                    push_output_queue(&queue, current->token);
                }
                else if (
                    current->token.type == Addition ||
                    current->token.type == Substraction ||
                    current->token.type == Multiplication ||
                    current->token.type == Division ||
                    current->token.type == Exponentation)
                {
                    while (
                        stack.node != NULL &&
                        stack.node->type > current->token.type &&
                        stack.node->type != BracketOpen)
                    {
                        push_output_queue(&queue, (Token){pop_operator_stack(&stack), 0});
                    }
                    push_operator_stack(&stack, current->token.type);
                }
                else if (current->token.type == BracketOpen)
                {
                    push_operator_stack(&stack, current->token.type);
                }
                else if (current->token.type == BracketClose)
                {
                    while (stack.node != NULL && stack.node->type != BracketOpen)
                    {
                        TokenType type = pop_operator_stack(&stack);
                        push_output_queue(&queue, (Token){type, 0});
                    }
                    pop_operator_stack(&stack);
                }
            }

            while (stack.node != NULL)
            {
                TokenType type = pop_operator_stack(&stack);

                if (type != Unknown)
                {
                    push_output_queue(&queue, (Token){type, 0});
                }
            }

            struct s_ResultStackHead resultStack = {NULL};

            while (queue.node != NULL)
            {
                struct s_OutputQueueNode *current = pop_output_queue(&queue);

                if (current->token.type == Number)
                {
                    push_result_stack(&resultStack, current->token.value);
                }
                else if (
                    current->token.type == Addition ||
                    current->token.type == Substraction ||
                    current->token.type == Multiplication ||
                    current->token.type == Division ||
                    current->token.type == Exponentation)
                {
                    f64 value2 = pop_result_stack(&resultStack);
                    f64 value1 = pop_result_stack(&resultStack);

                    switch (current->token.type)
                    {
                    case Addition:
                        push_result_stack(&resultStack, value1 + value2);
                        break;
                    case Substraction:
                        push_result_stack(&resultStack, value1 - value2);
                        break;
                    case Multiplication:
                        push_result_stack(&resultStack, value1 * value2);
                        break;
                    case Division:
                        push_result_stack(&resultStack, value1 / value2);
                        break;
                    case Exponentation:
                        push_result_stack(&resultStack, pow(value1, value2));
                        break;
                    default:
                        break;
                    }
                }
                Delete(current);
            }
            result.result = pop_result_stack(&resultStack);
        }
        else
        {
            result.error = error;
        }
        token_list_destroy(list);
    }
    else
    {
        result.error = "The given expression is null";
    }
    return result;
}

const char *parser_validate_list(TokenList *list)
{
    char *error = NULL;

    if (list != NULL)
    {
        TokenListNode *current = list;
        i32 brackets = 0;
        i32 operators = 0;
        i32 operands = 0;

        for (; !error && current; current = current->next)
        {
            if (
                (
                    current->token.type == Addition ||
                    current->token.type == Substraction ||
                    current->token.type == Multiplication ||
                    current->token.type == Division ||
                    current->token.type == Exponentation) &&
                (!current->next ||
                 (current->next &&
                  current->next->token.type != Number &&
                  current->next->token.type != BracketOpen)))
            {
                error = "After an operator, only a number or an opening bracket are allowed";
            }
            else if (
                current->token.type == BracketOpen &&
                (!current->next ||
                 current->next->token.type != Number &&
                     current->next->token.type != BracketOpen))
            {
                error = "After an opening bracket, only a number is allowed";
            }
            else if (current->token.type == BracketClose && brackets == 0)
            {
                printf("%d\n", brackets);
                error = "Closing bracket found before any opening bracket";
            }
            else
            {
                if (current->token.type == Number)
                {
                    if (current->next && current->next->token.type == Number)
                    {
                        TokenListNode *newNode = New(TokenListNode);
                        newNode->token = token_create_addition();
                        newNode->next = current->next;
                        current->next = newNode;
                        current = newNode;
                    }
                    else if (current->next && current->next->token.type == BracketOpen)
                    {
                        TokenListNode *newNode = New(TokenListNode);
                        newNode->token = token_create_multiplication();
                        newNode->next = current->next;
                        current->next = newNode;
                        current = newNode;
                    }
                    operands++;
                }
                else if (
                    current->token.type == Addition ||
                    current->token.type == Substraction ||
                    current->token.type == Multiplication ||
                    current->token.type == Division ||
                    current->token.type == Exponentation)
                {
                    operators++;
                }
                else if (current->token.type == BracketOpen)
                {
                    brackets++;
                }
                else if (current->token.type == BracketClose)
                {
                    if (current->next && (current->next->token.type == Number || current->next->token.type == BracketOpen))
                    {
                        TokenListNode *newNode = New(TokenListNode);
                        newNode->token = token_create_multiplication();
                        newNode->next = current->next;
                        current->next = newNode;
                        current = newNode;
                    }
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
