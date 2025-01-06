#ifndef CHAR_UTILS_H_
#define CHAR_UTILS_H_
#include "common.h"

int yama_char_is_space(char c);
int yama_char_is_digit(char c);
int yama_char_is_lowercase(char c);
int yama_char_is_alphanumerical(char c);


void yama_str_trim_trailing_ws(char *str, u32 len);
void yama_str_trim_leading_ws(char *str, u32 len);

#endif // CHAR_UTILS_H_
