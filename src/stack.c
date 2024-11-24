#include "stack.h"
#include "common.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Create a new stack.*/
/* item_size must be the size (in bytes) of the items you want to push into the stack. */
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

/* Push an item to the stack. */
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


/* Pop an item from the stack. */
/* NOTE: You are responsible for the deallocation of the returned item. */
void *stack_pop(Stack *stack) {
  assert(stack != NULL && "Stack cannot be NULL");
  assert(stack->length > 0 && "Stack size must be > 0");

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

/* Peek the value stored at the top of the stack. */
void *stack_peek(Stack *stack) {
  if (stack->top == NULL) {
    return NULL;
  }
  return stack->top->val;
}

/* Destroys the stack. */
/* Deallocates all nodes and their stored values. */
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

/* Return the number of items stored in the stack. */
u32 stack_size(Stack *stack) {
  assert(stack && "Stack is NULL");
  return stack->length;
}
