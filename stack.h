#pragma once

typedef struct s_StackNode {
    void* value;
    struct s_StackNode* next;
} StackNode;

typedef struct s_StackHead {
    StackNode* head;
    size_t lenght;
} StackHead;

StackHead* stack_create();
void stack_push(StackHead* head, void* value);
void* stack_pop(StackHead* head);
void* stack_peek(StackHead* head);
void stack_delete(StackHead* head);
