#include "char_utils.h"
#include "common.h"
#include <string.h>


int yama_char_is_lowercase(char c) {
  return 'a' <= c && c <= 'z';
}

int yama_char_is_uppercase(char c) {
  return 'A' <= c && c <= 'Z';
}

int yama_char_is_alphanumerical(char c) {
  return ('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') ||
         ('a' <= c && c <= 'z');
}

int yama_char_is_space(char c) {

  return c == '\t' || c == ' ' || c == '\r' || c == '\v' || c == '\f';
}

int yama_char_is_digit(char c) { return '0' <= c && '9' >= c; }

void yama_str_trim_trailing_ws(char *str, u32 len) {

  /* Jump to end of string */
  char *end = str;
  end += len;

  /* While character is space and not NULL.
  * Checking for NULL is required otherwise 'isspace' will produce undefined
   behaviour when encountering a nonstandard character. */
  while ((end != null) && yama_char_is_space(*end)) {
    /* Move backwards */
    --end;
  }
  *end = '\0';
}

void yama_str_trim_leading_ws(char *str, u32 len) {

  u32 count = 0;

  while ((count < len) && yama_char_is_space(str[count])) {
    ++count;
  }

  for (u32 i = 0; (i + count) < len; i++) {
    str[i] = str[i + count];
  }

  str[len - count] = '\0';

}
