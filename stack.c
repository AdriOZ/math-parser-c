#include <stdlib.h>
#include "util.h"
#include "stack.h"

StackHead* stack_create()
{
    StackHead* stack = New(StackHead);
    stack->head = NULL;
    stack->lenght = 0;
}

void stack_push(StackHead* head, void* value)
{
    if (head == NULL || value == NULL) {
        return;
    }
    StackNode* newNode = New(StackNode);
    newNode->value = value;
    newNode->next = NULL;
    
    if (head->head != NULL) {
        newNode->next = head->head;
    }
    head->head = newNode;
    head->lenght += 1;
}

void* stack_pop(StackHead* head)
{
    if (head == NULL || head->head == NULL) {
        return NULL;
    }
    StackNode* remove = head->head;
    void* value = remove->value;
    head->head = remove->next;
    Delete(remove);
    head->lenght -= 1;
    return value;
}

void* stack_peek(StackHead* head)
{
    if (head == NULL || head->head == NULL) {
        return NULL;
    }
    return head->head->value;
}

void stack_delete(StackHead* head)
{
    if (head == NULL) {
        return;
    }
    for (; head->lenght > 0; stack_pop(head));
    Delete(head);
}
