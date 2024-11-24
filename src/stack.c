#include "stack.h"
#include "common.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Create a new stack */
Stack *stack_new(int item_size) {
  assert(item_size > 0 && "item_size must be > 0");

  Stack *stack = malloc(sizeof(Stack));
  if (stack == NULL) {
    fprintf(stderr, "Failed to make allocation!\n");
    exit(-1);

  }
  stack->length = 0;
  stack->item_size = item_size;
  stack->top = NULL;
  return stack;
}

void stack_push(Stack *stack, void *data) {
  assert(stack != NULL && "Stack cannot be NULL");

  if ((stack == NULL) || (data == NULL)) {
    return;
  }

  Node *item = malloc(sizeof(Node));
  if (item == NULL) {
    fprintf(stderr, "Failed to make allocation!\n");
    exit(-1);
  }

  item->val = malloc(stack->item_size);

  if (item->val == NULL) {
    fprintf(stderr, "Failed to make allocation!\n");
    exit(-1);
  }
  memcpy(item->val, data, stack->item_size);
  item->next = stack->top;
  stack->top = item;
  stack->length += 1;
}

void *stack_pop(Stack *stack) {
  assert(stack != NULL && "Stack cannot be NULL");
  if (stack == NULL) {
    return NULL;
  }

  /* Stack is empty */
  if (stack->length == 0) {
    return NULL;
  }

  /* Allocate */
  void *top_val = malloc(stack->item_size);

  if (top_val == NULL) {
    fprintf(stderr, "Failed to make allocation!\n");
    exit(-1);
  }
  /* Copy the value */
  memcpy(top_val, stack->top->val, stack->item_size);

  Node *popped = stack->top;
  stack->top = popped->next;
  /* Free the copy inside of the node */
  free(popped->val);
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
  }

  free(stack);
}

u32 stack_size(Stack *stack) {
  assert(stack && "Stack is NULL");
  return stack->length;
}
