#ifndef STACK_H_
#define STACK_H_

typedef struct Node Node;

typedef struct Node {
  void *val;
  Node *next;
} Node;

typedef struct Stack {
  Node *top;
  int length;
  int item_size;
} Stack;

Stack *stack_new(int item_size);
void stack_push(Stack *stack, void *data);
void *stack_pop(Stack *stack);
void *stack_peek(Stack *stack);
void stack_destroy(Stack *stack);


#endif // STACK_H_
