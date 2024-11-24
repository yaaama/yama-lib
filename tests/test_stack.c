#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/new/assert.h>
#include <stdio.h>

#include "../src/stack.h"
/* Store 8 bytes */
#define items_size 8

Test(stack, create_stack) {

  char *item1 = "Hey whats up?";
  char *item2 = "This is the second item.";
  char *item3 = "This is the third item.";

  Stack *stack = stack_new(sizeof(char) * 26);
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

  /* Verify stack size if a size function is available */
  /* Assuming you have a function like stack_size() that returns the number  of
  elements */
  cr_assert_eq(stack_size(stack), 3, "Expected stack size to be 3 but got %zu",
               (size_t)stack_size(stack));

  /* Free the stack */
  stack_destroy(stack);
}
