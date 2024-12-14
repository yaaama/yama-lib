#include "char_utils.h"
#include <ctype.h>
#include <stdlib.h>

static inline void trim_trailing_ws(char *str, size_t len) {

  /* Jump to end of string */
  char *end = str;
  end += len;

  /* While character is space and not NULL.
  * Checking for NULL is required otherwise 'isspace' will produce undefined
   behaviour when encountering a nonstandard character. */
  while ((end != NULL) && isspace(end)) {
    /* Move backwards */
    --end;
  }
  *end = '\0';
}
