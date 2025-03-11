#include "char_utils.h"

#include <assert.h>

#include "common.h"

int yama_char_is_lower(char character) {
  return 'a' <= character && character <= 'z';
}

int yama_char_is_upper(char character) {
  return 'A' <= character && character <= 'Z';
}

int yama_char_is_alphanum(char character) {
  return ('0' <= character && character <= '9') ||
         ('A' <= character && character <= 'Z') ||
         ('a' <= character && character <= 'z');
}

int yama_char_is_ws(char character) {
  return character == '\t' || character == ' ' || character == '\r' ||
         character == '\v' || character == '\f';
}

void yama_str_trim_trailing_ws(char *str, u32 len) {

  assert(str && len > 0);

  if ((!str) || (len == 0)) {
    return;
  }

  /* Jump to end of string */
  char *end = str;
  end += len;

  /* While character is space and not NULL.
  * Checking for NULL is required otherwise 'isspace' will produce undefined
   behaviour when encountering a nonstandard character. */
  while (yama_char_is_ws(*end)) {
    /* Move backwards */
    --end;
  }
  *end = '\0';
}

void yama_str_trim_leading_ws(char *str, u32 len) {

  u32 count = 0;

  while ((count < len) && yama_char_is_ws(str[count])) {
    ++count;
  }

  for (u32 i = 0; (i + count) < len; i++) {
    str[i] = str[i + count];
  }

  str[len - count] = '\0';
}

/* Counts the number of characters until 'n' has reached */
int yama_str_length_n(char *str, u32 n) {

  char *curr = str;
  int count = 0;
  while ((curr) && ((u32)count < n)) {
    ++count;
    ++curr;
  }

  if (count) {
    return count;
  }

  return -1;
}
