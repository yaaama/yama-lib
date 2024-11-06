#include <stdlib.h>
#include <string.h>

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

/* Create a new stack */
Stack *stack_new(int item_size) {
  Stack *stack = malloc(sizeof(*stack));
  stack->length = 0;
  stack->item_size = item_size;
  stack->top = NULL;
  return stack;
}

void stack_push(Stack *stack, void *data) {

  Node *item = malloc(sizeof(Node));
  item->val = malloc(sizeof(stack->item_size));
  memcpy(item->val, data, stack->item_size);
  item->next = stack->top;
  stack->top = item;
  stack->length += 1;
}

void *stack_pop(Stack *stack) {

  /* Stack is empty */
  if (stack->length == 0) {
    return NULL;
  }

  Node *popped = stack->top;
  void *top_val = stack->top->val;

  stack->top = popped->next;
  free(popped);
  stack->length -= 1;

  return top_val;
}

void *stack_peek(Stack *stack) {
  if (stack->top == NULL) {
    return NULL;
  }
  return stack->top->val;
}

/* Destroys all Nodes, their stored values and also the Stack. */
void stack_destroy(Stack *stack) {

  Node *to_free = stack->top;

  while (to_free) {
    Node *next = to_free->next;
    free(to_free->val);
    free(to_free);
    to_free = next;
    stack->length -= 1;
  }

  free(stack);
}
