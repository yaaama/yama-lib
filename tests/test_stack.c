#include "../src/stack.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/new/assert.h>

/* Store 64 bytes */
#define items_size 64

/* Create stack and push some strings into it. */
Test(stack, create_stack) {

  char item1[items_size] = "Hey whats up?";
  char item2[items_size] = "This is the second item.";
  char item3[items_size] = "This is the third item.";

  Stack *stack = stack_new(sizeof(char) * items_size);
  cr_assert_not_null(stack, "Failed to create the stack.");

  /* Push item1 */
  stack_push(stack, item1);
  cr_assert_str_eq((char *)stack_peek(stack), item1,
                   "Expected top of stack to be '%s' but got '%s'", item1,
                   (char *)stack_peek(stack));

  /* Push item2 and verify */
  stack_push(stack, item2);
  cr_assert_str_eq((char *)stack_peek(stack), item2,
                   "Expected top of stack to be '%s' but got '%s'", item2,
                   (char *)stack_peek(stack));

  /* Push item3 and verify */
  stack_push(stack, item3);
  cr_assert_str_eq((char *)stack_peek(stack), item3,
                   "Expected top of stack to be '%s' but got '%s'", item3,
                   (char *)stack_peek(stack));

  cr_assert_eq(stack_size(stack), 3, "Expected stack size to be 3 but got %zu",
               (size_t)stack_size(stack));

  /* Free the stack */
  stack_destroy(stack);
}

/* Helper function to pop from the stack and verify the size and top element */
static void verify_pop(Stack *stack, size_t *expected_size,
                       const char *expected_top) {
  void *item = stack_pop(stack);
  free(item);
  --(*expected_size);

  // Check stack size
  cr_assert_eq(stack_size(stack), *expected_size,
               "Expected stack size to be %zu but got %zu", *expected_size,
               (size_t)stack_size(stack));

  // Check top element if stack is not empty
  if (*expected_size > 0) {
    cr_assert_str_eq((char *)stack_peek(stack), expected_top,
                     "Expected top of stack to be '%s' but got '%s'",
                     expected_top, (char *)stack_peek(stack));
  }
}

Test(stack, pop_items) {
  char item1[items_size] = "Hey whats up?";
  char item2[items_size] = "This is the second item.";
  char item3[items_size] = "This is the third item.";

  Stack *stack = stack_new(sizeof(char) * items_size);
  cr_assert_not_null(stack, "Failed to create the stack.");

  /* Push multiple items onto the stack */
  stack_push(stack, item1);
  stack_push(stack, item2);
  stack_push(stack, item3);
  stack_push(stack, item1);
  stack_push(stack, item2);
  stack_push(stack, item3);

  /* Initial stack size verification */
  size_t exp_size = 6;
  cr_assert_eq(stack_size(stack), exp_size,
               "Expected stack size to be %zu but got %zu", exp_size,
               (size_t)stack_size(stack));

  /* Pop items and verify */
  verify_pop(stack, &exp_size,
             item2); // Should have item2 at the top after popping item3
  verify_pop(stack, &exp_size,
             item1); // Should have item1 at the top after popping item2
  verify_pop(stack, &exp_size,
             item3); // Should have item3 at the top after popping item1
  verify_pop(stack, &exp_size,
             item2); // Should have item2 at the top after popping item3
  verify_pop(stack, &exp_size,
             item1); // Should have item1 at the top after popping item2

  /* Pop the last item */
  void *itemempty = stack_pop(stack);
  free(itemempty);

  --exp_size;
  cr_assert_eq(stack_size(stack), exp_size,
               "Expected stack size to be %zu but got %zu", exp_size,
               (size_t)stack_size(stack));
  cr_assert_null(stack_peek(stack),
                 "Expected top of stack to be NULL but got '%s'",
                 (char *)stack_peek(stack));

  /* Test underflow : pop from empty stack */
  stack_pop(stack);
  cr_assert_eq(stack_size(stack), 0,
               "Expected stack size to be 0 after popping an empty stack.");
  cr_assert_null(
      stack_peek(stack),
      "Expected top of stack to be NULL after popping an empty stack.");

  /* Destroy stack */
  stack_destroy(stack);
}
