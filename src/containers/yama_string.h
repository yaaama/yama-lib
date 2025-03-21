#ifndef YAMA_STRING_H_
#define YAMA_STRING_H_

#include <stddef.h>
#include "common.h"

typedef struct {
	size_t len;
	char *val;
} ya_str;

ya_str ya_str_new(char *str);
ya_str ya_str_new_n(char *str, size_t len);
void ya_str_destroy(ya_str *str);
ya_str ya_str_concat(ya_str strA, ya_str strB);
ya_str *ya_str_slice(ya_str *str, size_t start, size_t end);
int ya_str_compare(ya_str *strA, ya_str *that);

#endif  // YAMA_STRING_H_
