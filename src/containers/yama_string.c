#include "yama_string.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <limits.h>

#include "../common.h"


/*****************************************************************************/
/**
 ** ya_str_new: Returns a new ya_str object.
 * To properly deallocate the object, call the ya_str_destroy function.
 ** Arguments: *str is the NULL terminated string you want to store.
 **/
ya_str ya_str_new(char *str) {
  assert(str);

  size_t len = 0;
  while (str[len] != '\0') {
    ++len;
  }

  ya_str string = {.len = len, .val = malloc(sizeof(char) * len)};

  if (!string.val) {
    ya_die "Could not allocate memory.");
  }

  memcpy(string.val, str, len);
  return string;
}

/**
 * ya_str_new_n: Returns a new ya_str object with length n.
 * To properly deallocate the object, call the ya_str_destroy function.
 * Arguments:
 * *str is the NULL terminated string you want to store.
 * len is the length of str.
 **/
ya_str ya_str_new_n(char *str, size_t len) {
  assert(str && len);

  ya_str string = {
      .len = len,
      .val = malloc(sizeof(char) * len),
  };

  if (!string.val) {
    ya_die "Could not allocate memory.");
  }

  memcpy(string.val, str, len);
  return string;
}

/**
 * ya_str_destroy: Destroys a ya_str struct, freeing it from the heap.
 * Arguments:
 * str: Struct to destroy
 **/
void ya_str_destroy(ya_str *str) {

  assert(str && str->len && str->val);

  free(str->val);
  str->val = NULL;
  str->len = 0;
}

/**
 * ya_str_concat: Concatenate two ya_str's together.
 * Arguments:
 * strB is appended to strA and a new ya_str is returned.
 * Checks if the resulting length will overflow, causing termination.
 **/
ya_str ya_str_concat(ya_str strA, ya_str strB) {
  assert(strA.val && strB.val);
  YA_SIZE_T_OVERFLOW(strA.len, strB.len);

  size_t newlen = strA.len + strB.len;

  ya_str result = {.len = newlen, .val = malloc(newlen)};

  if (!result.val) {
    ya_die("Memory allocation failed.");
  }

  memcpy(result.val, strA.val, strA.len);
  memcpy((result.val + strA.len), strB.val, strB.len);
  return result;
}
