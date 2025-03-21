#include "../src/containers/yama_string.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/internal/new_asserts.h>
#include <criterion/internal/test.h>
#include <criterion/logging.h>

TestSuite(yama_string, .description = "String library testing suite.");

Test(yama_string, normal_usage,
     .description = "Typical library usage test. Includes everything.") {

  char temp;

  /* Create first string */
  cr_log_info("Creating a string.\n");
  char *str = "Input";
  ya_str yastr = ya_str_new(str);
  cr_expect(eq(str, yastr.val, str, "Strings do not match."));
  cr_expect(
      eq(ulong, yastr.len, strlen(str), "String does not match input length."));
  cr_expect(ne(ptr, yastr.val, str), "Their pointers should not be the same.");

  /* Create second string */
  cr_log_info("Creating our second string.\n");
  char *concat_with = " will be concatenated with this string literal.";
  ya_str yastr_2 = ya_str_new(concat_with);

  temp = yastr_2.val[yastr_2.len];
  yastr_2.val[yastr_2.len] = '\0';

  cr_expect(eq(str, yastr_2.val, concat_with, "Strings do not match."));
  cr_expect(eq(ullong, yastr_2.len, strlen(concat_with),
               "String does not match input length."));
  cr_expect(ne(ptr, yastr_2.val, concat_with),
            "Pointers should not be the same.");

  yastr_2.val[yastr_2.len] = temp;

  /* Concatenate strings */

  /* Good concatenation */
  size_t concatenated_len = (strlen(str)) + (strlen(concat_with));
  char *concat_good = calloc(sizeof(char), concatenated_len + 1);

  size_t offset = strlen(str);
  memcpy(concat_good, str, offset);
  memcpy((concat_good + offset), concat_with, strlen(concat_with));
  concat_good[concatenated_len] = '\0';

  cr_log_info("Concatenating strings.\n");

  ya_str concatenated = ya_str_concat(yastr, yastr_2);

  temp = concatenated.val[concatenated_len];
  concatenated.val[concatenated_len] = '\0';

  cr_assert(eq(str, concatenated.val, concat_good, "Failed to \
	concatenate the two strings.\nExpected: `%s`, but received:  `%s`\n",
               good_concat, concatenated.val));

  concatenated.val[concatenated_len] = temp;
  void **destroyed_ptr = &concatenated.val;
  cr_assert(not (zero(ptr, destroyed_ptr, NULL)), "This should be pointing to something real.");

  ya_str_destroy(&concatenated);
  cr_assert(zero (ptr, concatenated.val), "Freed mem should point to NULL.");
  cr_assert(zero (ptr, *destroyed_ptr, "Pointer pointing to a freed val should be NULL."));

}

Test(yama_string, slicing, .disabled=true) {

  /* Slicing strings */
  cr_skip();

}
