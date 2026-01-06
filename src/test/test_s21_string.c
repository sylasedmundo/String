#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_memchr_found) {
  const char str[] = "Hello, World!";
  ck_assert_ptr_eq(s21_memchr(str, 'W', 13), memchr(str, 'W', 13));
}
END_TEST

START_TEST(test_memchr_not_found) {
  const char str[] = "Hello";
  ck_assert_ptr_eq(s21_memchr(str, 'Z', 5), memchr(str, 'Z', 5));
}
END_TEST

START_TEST(test_memchr_first_char) {
  const char str[] = "Test";
  ck_assert_ptr_eq(s21_memchr(str, 'T', 4), memchr(str, 'T', 4));
}
END_TEST

START_TEST(test_memchr_last_char) {
  const char str[] = "Test";
  ck_assert_ptr_eq(s21_memchr(str, 't', 4), memchr(str, 't', 4));
}
END_TEST

START_TEST(test_memchr_null_char) {
  const char str[] = "Hello\0World";
  ck_assert_ptr_eq(s21_memchr(str, '\0', 11), memchr(str, '\0', 11));
}
END_TEST

START_TEST(test_memchr_n_zero) {
  const char str[] = "Test";
  ck_assert_ptr_eq(s21_memchr(str, 'e', 0), memchr(str, 'e', 0));
}
END_TEST

START_TEST(test_memchr_unsig) {
  unsigned char data[] = {0x00, 0x7F, 0x80, 0xFF};
  ck_assert_ptr_eq(s21_memchr(data, 0xFF, 4), memchr(data, 0xFF, 4));
}
END_TEST

START_TEST(test_memchr_n_over) {
  const char str[] = "Hello World";
  ck_assert_ptr_eq(s21_memchr(str, 'W', 4), memchr(str, 'W', 4));
}
END_TEST

START_TEST(test_memchr_binar) {
  const char data[] = {1, 0, 2, 0, 3, 3, 3, 0, 1};
  ck_assert_ptr_eq(s21_memchr(data, 3, 9), memchr(data, 3, 9));
}
END_TEST

START_TEST(test_memcmp_equal) {
  char str1[] = "Hello";
  char str2[] = "Hello";

  ck_assert_int_eq(s21_memcmp(str1, str2, 5), memcmp(str1, str2, 5));
}
END_TEST

START_TEST(test_memcmp_less) {
  char str1[] = "Apple";
  char str2[] = "Banana";

  int s21_result = s21_memcmp(str1, str2, 5);
  int std_result = memcmp(str1, str2, 5);

  // Проверяем знак результата (оба должны быть < 0)
  ck_assert_int_lt(s21_result, 0);
  ck_assert_int_lt(std_result, 0);
}
END_TEST

START_TEST(test_memcmp_greater) {
  char str1[] = "Zebra";
  char str2[] = "Apple";

  int s21_result = s21_memcmp(str1, str2, 5);
  int std_result = memcmp(str1, str2, 5);

  // Проверяем знак результата (оба должны быть > 0)
  ck_assert_int_gt(s21_result, 0);
  ck_assert_int_gt(std_result, 0);
}
END_TEST

START_TEST(test_memcmp_n_zero) {
  char str1[] = "Different";
  char str2[] = "Strings";

  ck_assert_int_eq(s21_memcmp(str1, str2, 0), memcmp(str1, str2, 0));
}
END_TEST

START_TEST(test_memcmp_partial) {
  char str1[] = "Hello World";
  char str2[] = "Hello There";

  ck_assert_int_eq(s21_memcmp(str1, str2, 5), memcmp(str1, str2, 5));
}
END_TEST

START_TEST(test_memcmp_with_nulls) {
  char str1[] = "te\0st";
  char str2[] = "te\0st";

  ck_assert_int_eq(s21_memcmp(str1, str2, 5), memcmp(str1, str2, 5));
}
END_TEST

START_TEST(test_memcmp_differ_at_end) {
  char str1[] = "test1";
  char str2[] = "test2";

  int s21_result = s21_memcmp(str1, str2, 5);
  int std_result = memcmp(str1, str2, 5);

  ck_assert_int_lt(s21_result, 0);
  ck_assert_int_lt(std_result, 0);
}
END_TEST

START_TEST(test_memcmp_num) {
  char num1[] = {1, 0, 8, 9, 3, 1, 1, 1, 1, 5};
  char num2[] = {1, 0, 8, 9, 3, 1, 1, 1, 11, 5};

  int s21_result = s21_memcmp(num1, num2, 9);
  int std_result = memcmp(num1, num2, 9);

  ck_assert_int_lt(s21_result, 0);
  ck_assert_int_lt(std_result, 0);
}
END_TEST

START_TEST(test_memcmp_unsig) {
  unsigned char a[] = {0xFF};
  unsigned char b[] = {0x00};

  int s21_result = s21_memcmp(a, b, 1);
  int std_result = memcmp(a, b, 1);

  ck_assert_int_gt(s21_result, 0);
  ck_assert_int_gt(std_result, 0);
}
END_TEST

START_TEST(test_memcpy_basic) {
  char src[] = "Hello, World!";
  char dest1[20] = {0};
  char dest2[20] = {0};

  s21_memcpy(dest1, src, 13);
  memcpy(dest2, src, 13);

  ck_assert_mem_eq(dest1, dest2, 13);
}
END_TEST

START_TEST(test_memcpy_empty) {
  char src[] = "";
  char dest1[10] = "test";
  char dest2[10] = "test";

  s21_memcpy(dest1, src, 0);
  memcpy(dest2, src, 0);

  ck_assert_mem_eq(dest1, dest2, 10);
}
END_TEST

START_TEST(test_memcpy_partial) {
  char src[] = "1234567890";
  char dest1[20] = {0};
  char dest2[20] = {0};

  s21_memcpy(dest1, src, 5);
  memcpy(dest2, src, 5);

  ck_assert_mem_eq(dest1, dest2, 20);
}
END_TEST

START_TEST(test_memcpy_full_buffer) {
  char src[10] = "123456789";
  char dest1[10] = {0};
  char dest2[10] = {0};

  s21_memcpy(dest1, src, 10);
  memcpy(dest2, src, 10);

  ck_assert_mem_eq(dest1, dest2, 10);
}
END_TEST

START_TEST(test_memcpy_with_nulls) {
  char src[] = "te\0st\0data";
  char dest1[20] = {0};
  char dest2[20] = {0};

  s21_memcpy(dest1, src, 10);
  memcpy(dest2, src, 10);

  ck_assert_mem_eq(dest1, dest2, 10);
}
END_TEST

START_TEST(test_memcpy_single_byte) {
  char src[] = "A";
  char dest1[5] = {0};
  char dest2[5] = {0};

  s21_memcpy(dest1, src, 1);
  memcpy(dest2, src, 1);

  ck_assert_mem_eq(dest1, dest2, 5);
}
END_TEST

START_TEST(test_memset_basic) {
  char buffer1[20] = {0};
  char buffer2[20] = {0};

  s21_memset(buffer1, 'A', 10);
  memset(buffer2, 'A', 10);

  ck_assert_mem_eq(buffer1, buffer2, 20);
}
END_TEST

START_TEST(test_memset_zero) {
  char buffer1[20] = "Hello";
  char buffer2[20] = "Hello";

  s21_memset(buffer1, 0, 20);
  memset(buffer2, 0, 20);

  ck_assert_mem_eq(buffer1, buffer2, 20);
}
END_TEST

START_TEST(test_memset_full) {
  char buffer1[10];
  char buffer2[10];

  s21_memset(buffer1, 'X', 10);
  memset(buffer2, 'X', 10);

  ck_assert_mem_eq(buffer1, buffer2, 10);
}
END_TEST

START_TEST(test_memset_partial) {
  char buffer1[20] = "0123456789ABCDEFGHIJ";
  char buffer2[20] = "0123456789ABCDEFGHIJ";

  s21_memset(buffer1 + 5, '*', 5);
  memset(buffer2 + 5, '*', 5);

  ck_assert_mem_eq(buffer1, buffer2, 20);
}
END_TEST

START_TEST(test_memset_n_zero) {
  char buffer1[10] = "Test";
  char buffer2[10] = "Test";

  s21_memset(buffer1, 'A', 0);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmemset-transposed-args"
  memset(buffer2, 'A', 0);
#pragma GCC diagnostic pop

  ck_assert_mem_eq(buffer1, buffer2, 10);
}
END_TEST

START_TEST(test_strlen_basic) {
  const char *str = "Hello, World!";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_empty) {
  const char *str = "";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_one_char) {
  const char *str = "A";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_long) {
  const char *str = "This is a very long string for testing purposes!";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_special_chars) {
  const char *str = "Line1\nLine2\tTab\0Hidden";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strncat_basic) {
  char dest1[30] = "Hello";
  char dest2[30] = "Hello";
  const char *src = " World";

  s21_strncat(dest1, src, 6);
  strncat(dest2, src, 6);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat_partial) {
  char dest1[30] = "Hello";
  char dest2[30] = "Hello";
  const char *src = " World!";

  s21_strncat(dest1, src, 3);
  strncat(dest2, src, 3);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat_empty_dest) {
  char dest1[30] = "";
  char dest2[30] = "";
  const char *src = "Hello";

  s21_strncat(dest1, src, 5);
  strncat(dest2, src, 5);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat_empty_src) {
  char dest1[30] = "Hello";
  char dest2[30] = "Hello";
  const char *src = "";

  s21_strncat(dest1, src, 5);
  strncat(dest2, src, 5);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat_n) {
  char dest1[30] = "Hello";
  char dest2[30] = "Hello";
  const char *src = " World";

  s21_strncat(dest1, src, 1);
  strncat(dest2, src, 1);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat_n_greater) {
  char dest1[30] = "Hi";
  char dest2[30] = "Hi";
  const char *src = "!";

  s21_strncat(dest1, src, 10);
  strncat(dest2, src, 10);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncpy_basic) {
  char dest1[20] = {0};
  char dest2[20] = {0};
  const char *src = "Hello";

  s21_strncpy(dest1, src, 10);
  strncpy(dest2, src, 10);

  ck_assert_mem_eq(dest1, dest2, 10);
}
END_TEST

START_TEST(test_strncpy_exact) {
  char dest1[6] = {0};
  char dest2[6] = {0};
  const char *src = "Hello";

  s21_strncpy(dest1, src, 5);
  strncpy(dest2, src, 5);

  ck_assert_mem_eq(dest1, dest2, 5);
}
END_TEST

START_TEST(test_strncpy_less_than_src) {
  char dest1[20] = "Hello";
  char dest2[20] = "Hello";
  const char *src = "Hi";

  s21_strncpy(dest1, src, 3);
  strncpy(dest2, src, 3);

  ck_assert_mem_eq(dest1, dest2, 20);
}
END_TEST

START_TEST(test_strncpy_n_greater) {
  char dest1[20] = "World";
  char dest2[20] = "World";
  const char *src = "Hi";

  s21_strncpy(dest1, src, 10);
  strncpy(dest2, src, 10);

  ck_assert_mem_eq(dest1, dest2, 10);
}
END_TEST

START_TEST(test_strncpy_empty) {
  char dest1[10] = "test";
  char dest2[10] = "test";
  const char *src = "";

  s21_strncpy(dest1, src, 5);
  strncpy(dest2, src, 5);

  ck_assert_mem_eq(dest1, dest2, 10);
}
END_TEST

START_TEST(test_strncpy_n) {
  char dest1[10] = "test";
  char dest2[10] = "test";
  const char *src = "H";

  s21_strncpy(dest1, src, 1);
  strncpy(dest2, src, 1);

  ck_assert_mem_eq(dest1, dest2, 10);
}
END_TEST

START_TEST(test_strstr_found) {
  const char *haystack = "Hello, World!";
  const char *needle = "World";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_not_found) {
  const char *haystack = "Hello";
  const char *needle = "xyz";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  const char *haystack = "Hello";
  const char *needle = "";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_at_beginning) {
  const char *haystack = "Hello World";
  const char *needle = "Hello";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_at_end) {
  const char *haystack = "Hello World";
  const char *needle = "World";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_single_char) {
  const char *haystack = "abcdef";
  const char *needle = "c";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_repeated) {
  const char *haystack = "aaabbbccc";
  const char *needle = "bbb";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_needle_longer) {
  const char *haystack = "Hi";
  const char *needle = "Hello";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_empty_haystack) {
  const char *haystack = "";
  const char *needle = "test";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_both_empty) {
  const char *haystack = "";
  const char *needle = "";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

static void reset_strtok_state(void) {
  char dummy[] = "";
  s21_strtok(dummy, "");
}

START_TEST(test_strchr_special_chars) {
  const char *str = "test\x01test";
  ck_assert_ptr_eq(s21_strchr(str, '\x01'), strchr(str, '\x01'));
}
END_TEST

START_TEST(test_strchr_repeated_char) {
  const char *str = "aaaabbbb";
  ck_assert_ptr_eq(s21_strchr(str, 'b'), strchr(str, 'b'));
}
END_TEST

START_TEST(test_strchr_unicode_safe) {
  const char *str = "test";
  ck_assert_ptr_eq(s21_strchr(str, 200), strchr(str, 200));
}
END_TEST

START_TEST(test_strchr_negative_char) {
  const char *str = "test";
  ck_assert_ptr_eq(s21_strchr(str, -1), strchr(str, -1));
}
END_TEST

START_TEST(test_strchr_basic) {
  const char *str = "hello world";
  ck_assert_ptr_eq(s21_strchr(str, 'w'), strchr(str, 'w'));
}
END_TEST

START_TEST(test_strchr_first_char) {
  const char *str = "hello world";
  ck_assert_ptr_eq(s21_strchr(str, 'h'), strchr(str, 'h'));
}
END_TEST

START_TEST(test_strchr_last_char) {
  const char *str = "hello world";
  ck_assert_ptr_eq(s21_strchr(str, 'd'), strchr(str, 'd'));
}
END_TEST

START_TEST(test_strchr_middle_char) {
  const char *str = "hello world";
  ck_assert_ptr_eq(s21_strchr(str, 'o'), strchr(str, 'o'));
}
END_TEST

START_TEST(test_strchr_not_found) {
  const char *str = "hello world";
  ck_assert_ptr_eq(s21_strchr(str, 'z'), strchr(str, 'z'));
}
END_TEST

START_TEST(test_strchr_null_char) {
  const char *str = "hello world";
  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
}
END_TEST

START_TEST(test_strchr_empty_string) {
  const char *str = "";
  ck_assert_ptr_eq(s21_strchr(str, 'a'), strchr(str, 'a'));
}
END_TEST

START_TEST(test_strrchr_single_char_string) {
  const char *str = "a";
  ck_assert_ptr_eq(s21_strrchr(str, 'a'), strrchr(str, 'a'));
}
END_TEST

START_TEST(test_strrchr_char_at_beginning) {
  const char *str = "abcde";
  ck_assert_ptr_eq(s21_strrchr(str, 'a'), strrchr(str, 'a'));
}
END_TEST

START_TEST(test_strrchr_char_not_present) {
  const char *str = "hello";
  ck_assert_ptr_eq(s21_strrchr(str, 'z'), strrchr(str, 'z'));
}
END_TEST

START_TEST(test_strrchr_empty_string_search) {
  const char *str = "";
  ck_assert_ptr_eq(s21_strrchr(str, 'a'), strrchr(str, 'a'));
}
END_TEST

START_TEST(test_strrchr_basic) {
  const char *str = "hello world";
  ck_assert_ptr_eq(s21_strrchr(str, 'o'), strrchr(str, 'o'));
}
END_TEST

START_TEST(test_strrchr_single_occurrence) {
  const char *str = "hello world";
  ck_assert_ptr_eq(s21_strrchr(str, 'h'), strrchr(str, 'h'));
}
END_TEST

START_TEST(test_strrchr_multiple_occurrence) {
  const char *str = "hello world";
  ck_assert_ptr_eq(s21_strrchr(str, 'l'), strrchr(str, 'l'));
}
END_TEST

START_TEST(test_strrchr_not_found) {
  const char *str = "hello world";
  ck_assert_ptr_eq(s21_strrchr(str, 'z'), strrchr(str, 'z'));
}
END_TEST

START_TEST(test_strcspn_all_reject) {
  const char *str = "hello";
  const char *reject = "helo";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_null_reject) {
  const char *str = "hello";
  const char *reject = "";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_long_string) {
  const char *str = "abcdefghijklmnopqrstuvwxyz";
  const char *reject = "xyz";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_reject_at_start) {
  const char *str = "hello";
  const char *reject = "h";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_multiple_reject_chars) {
  const char *str = "test_string";
  const char *reject = "aeiou_";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_basic) {
  const char *str = "hello world";
  const char *reject = " w";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_no_match) {
  const char *str = "hello world";
  const char *reject = "xyz";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_first_char_match) {
  const char *str = "hello world";
  const char *reject = "h";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_multiple_reject) {
  const char *str = "hello world";
  const char *reject = "aeiou";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strncmp_same_string_long_n) {
  const char *s1 = "hello";
  const char *s2 = "hello";
  ck_assert_int_eq(s21_strncmp(s1, s2, 10), strncmp(s1, s2, 10));
}
END_TEST

START_TEST(test_strncmp_diff_case) {
  const char *s1 = "Hello";
  const char *s2 = "hello";
  ck_assert_int_eq(s21_strncmp(s1, s2, 5) < 0, strncmp(s1, s2, 5) < 0);
}
END_TEST

START_TEST(test_strncmp_one_char_diff) {
  const char *s1 = "abcd";
  const char *s2 = "abce";
  ck_assert_int_eq(s21_strncmp(s1, s2, 4) < 0, strncmp(s1, s2, 4) < 0);
}
END_TEST

START_TEST(test_strncmp_partial_with_null) {
  const char s1[] = "ab\0cd";
  const char s2[] = "ab\0ef";
  ck_assert_int_eq(s21_strncmp(s1, s2, 5), strncmp(s1, s2, 5));
}
END_TEST

START_TEST(test_strncmp_large_n) {
  const char *s1 = "short";
  const char *s2 = "short";
  ck_assert_int_eq(s21_strncmp(s1, s2, 1000), strncmp(s1, s2, 1000));
}
END_TEST

START_TEST(test_strncmp_equal) {
  const char *s1 = "hello";
  const char *s2 = "hello";
  ck_assert_int_eq(s21_strncmp(s1, s2, 5), strncmp(s1, s2, 5));
}
END_TEST

START_TEST(test_strncmp_different) {
  const char *s1 = "hello";
  const char *s2 = "world";
  ck_assert_int_eq(s21_strncmp(s1, s2, 5) < 0, strncmp(s1, s2, 5) < 0);
}
END_TEST

START_TEST(test_strncmp_zero_length) {
  const char *s1 = "hello";
  const char *s2 = "world";
  ck_assert_int_eq(s21_strncmp(s1, s2, 0), strncmp(s1, s2, 0));
}
END_TEST

START_TEST(test_strncmp_partial_match) {
  const char *s1 = "hello";
  const char *s2 = "hella";
  ck_assert_int_eq(s21_strncmp(s1, s2, 5) > 0, strncmp(s1, s2, 5) > 0);
}
END_TEST

START_TEST(test_strncmp_empty_strings) {
  const char *s1 = "";
  const char *s2 = "";
  ck_assert_int_eq(s21_strncmp(s1, s2, 1), strncmp(s1, s2, 1));
}
END_TEST

START_TEST(test_strpbrk_empty_accept) {
  const char *str = "hello";
  const char *accept = "";
  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_strpbrk_empty_string) {
  const char *str = "";
  const char *accept = "abc";
  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_strpbrk_multiple_matches) {
  const char *str = "abcdef";
  const char *accept = "cf";
  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_strpbrk_special_chars) {
  const char *str = "test\nstring\t";
  const char *accept = "\n\t";
  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_strpbrk_all_chars_match) {
  const char *str = "hello";
  const char *accept = "helo";
  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_strpbrk_basic) {
  const char *str = "hello world";
  const char *accept = " w";
  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_strpbrk_multiple_accept) {
  const char *str = "hello world";
  const char *accept = "abcde";
  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_strpbrk_not_found) {
  const char *str = "hello world";
  const char *accept = "xyz";
  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_strpbrk_first_char_match) {
  const char *str = "hello world";
  const char *accept = "h";
  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_strtok_single_delimiter) {
  reset_strtok_state();
  char str1[] = "hello";
  char str2[] = "hello";

  char *token1 = s21_strtok(str1, " ");
  char *token2 = strtok(str2, " ");

  if (token1 == NULL && token2 == NULL) {
    ck_assert_ptr_eq(token1, token2);
  } else if (token1 != NULL && token2 != NULL) {
    ck_assert_str_eq(token1, token2);
  } else {
    ck_abort_msg("Mismatch: one returned string, other returned NULL");
  }
}
END_TEST

START_TEST(test_strtok_no_delimiter_in_string) {
  reset_strtok_state();
  char str1[] = "hello world";
  char str2[] = "hello world";

  char *token1 = s21_strtok(str1, ";");
  char *token2 = strtok(str2, ";");

  if (token1 && token2) {
    ck_assert_str_eq(token1, token2);
  } else {
    ck_assert_ptr_eq(token1, token2);
  }

  token1 = s21_strtok(NULL, ";");
  token2 = strtok(NULL, ";");
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_delimiter_at_end) {
  reset_strtok_state();
  char str1[] = "hello,";
  char str2[] = "hello,";

  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");

  if (token1 && token2) {
    ck_assert_str_eq(token1, token2);
    ck_assert_str_eq(token1, "hello");
  } else {
    ck_assert_ptr_eq(token1, token2);
  }

  token1 = s21_strtok(NULL, ",");
  token2 = strtok(NULL, ",");
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_delimiter_at_start) {
  reset_strtok_state();
  char str1[] = ",hello,world";
  char str2[] = ",hello,world";

  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");

  if (token1 && token2) {
    ck_assert_str_eq(token1, token2);
    ck_assert_str_eq(token1, "hello");
  } else {
    ck_assert_ptr_eq(token1, token2);
  }

  token1 = s21_strtok(NULL, ",");
  token2 = strtok(NULL, ",");
  if (token1 && token2) {
    ck_assert_str_eq(token1, token2);
    ck_assert_str_eq(token1, "world");
  } else {
    ck_assert_ptr_eq(token1, token2);
  }

  token1 = s21_strtok(NULL, ",");
  token2 = strtok(NULL, ",");
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_reset_with_new_string) {
  reset_strtok_state();
  char str1[] = "first,string";
  char str2[] = "first,string";

  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_str_eq(token1, token2);

  reset_strtok_state();
  char str3[] = "new,string";
  char str4[] = "new,string";

  token1 = s21_strtok(str3, ",");
  token2 = strtok(str4, ",");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_empty_string) {
  reset_strtok_state();
  char str1[] = "";
  char str2[] = "";

  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_only_delimiters) {
  reset_strtok_state();
  char str1[] = ",,,,";
  char str2[] = ",,,,";

  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_consecutive_delimiters) {
  reset_strtok_state();
  char str1[] = "hello,,world";
  char str2[] = "hello,,world";

  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(NULL, ",");
  token2 = strtok(NULL, ",");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(NULL, ",");
  token2 = strtok(NULL, ",");
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_basic) {
  reset_strtok_state();
  char str1[] = "hello world";
  char str2[] = "hello world";

  char *token1 = s21_strtok(str1, " ");
  char *token2 = strtok(str2, " ");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(NULL, " ");
  token2 = strtok(NULL, " ");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(NULL, " ");
  token2 = strtok(NULL, " ");
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_multiple_delimiters) {
  reset_strtok_state();
  char str1[] = "hello,world;test";
  char str2[] = "hello,world;test";

  char *token1 = s21_strtok(str1, ",;");
  char *token2 = strtok(str2, ",;");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(NULL, ",;");
  token2 = strtok(NULL, ",;");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(NULL, ",;");
  token2 = strtok(NULL, ",;");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_strerror_all_known_errors) {
  int errors_to_test[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

  for (size_t i = 0; i < sizeof(errors_to_test) / sizeof(errors_to_test[0]);
       i++) {
    int err = errors_to_test[i];
    char *s21_result = s21_strerror(err);
    char *std_result = strerror(err);

    ck_assert_ptr_nonnull(s21_result);
    ck_assert_ptr_nonnull(std_result);

    ck_assert_int_ne(s21_result[0], '\0');
  }
}
END_TEST

START_TEST(test_strerror_large_positive) {
  char *result = s21_strerror(1000000);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_ne(result[0], '\0');
}
END_TEST

START_TEST(test_strerror_large_negative) {
  char *result = s21_strerror(-1000000);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_ne(result[0], '\0');
}
END_TEST

START_TEST(test_strerror_zero_unknown) {
  char *result = s21_strerror(99999);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_ne(result[0], '\0');
}
END_TEST

START_TEST(test_strerror_negative_one) {
  char *result = s21_strerror(-1);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_ne(result[0], '\0');
}
END_TEST

START_TEST(test_strerror_success) {
  char *result = s21_strerror(0);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_ne(result[0], '\0');
}
END_TEST

START_TEST(test_strerror_enoent) {
  char *result = s21_strerror(2);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_ne(result[0], '\0');
}
END_TEST

START_TEST(test_strerror_einval) {
  char *result = s21_strerror(22);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_ne(result[0], '\0');
}
END_TEST

START_TEST(test_integration_strchr_strrchr) {
  const char *str = "mississippi";

  char *first_i = s21_strchr(str, 'i');
  char *last_i = s21_strrchr(str, 'i');

  ck_assert_ptr_nonnull(first_i);
  ck_assert_ptr_nonnull(last_i);

  ck_assert(first_i < last_i);
}
END_TEST

START_TEST(test_integration_strcspn_strpbrk) {
  const char *str = "hello world";
  const char *delimiters = " ,.!";

  s21_size span = s21_strcspn(str, delimiters);
  char *found = s21_strpbrk(str, delimiters);

  ck_assert_int_eq(span, 5);
  if (found) {
    ck_assert_ptr_eq(found, str + 5);
    ck_assert_int_eq(*found, ' ');
  }
}
END_TEST

START_TEST(test_integration_strtok_strcspn) {
  reset_strtok_state();
  char str[] = "word1,word2;word3 word4";

  char *token = s21_strtok(str, ",; ");
  int count = 0;

  while (token != NULL) {
    count++;

    s21_size span = s21_strcspn(token, ",; ");
    ck_assert_int_eq(span, strlen(token));

    token = s21_strtok(NULL, ",; ");
  }

  ck_assert_int_eq(count, 4);
}
END_TEST

START_TEST(test_integration_all_functions) {
  const char *original = "test,string;for checking";
  char str[50];
  strcpy(str, original);

  s21_size first_delim = s21_strcspn(str, ",;");
  ck_assert_int_eq(first_delim, 4);

  char *comma = s21_strchr(str, ',');
  ck_assert_ptr_nonnull(comma);

  char *delim = s21_strpbrk(str, ",;");
  ck_assert_ptr_eq(delim, comma);

  reset_strtok_state();
  char *token1 = s21_strtok(str, ",;");
  ck_assert_str_eq(token1, "test");

  char *token2 = s21_strtok(NULL, ",;");
  ck_assert_str_eq(token2, "string");
}
END_TEST

START_TEST(test_integration_edge_case_empty) {
  const char *str = "";

  ck_assert_ptr_eq(s21_strchr(str, 'a'), strchr(str, 'a'));
  ck_assert_ptr_eq(s21_strrchr(str, 'a'), strrchr(str, 'a'));
  ck_assert_int_eq(s21_strcspn(str, "abc"), strcspn(str, "abc"));
  ck_assert_int_eq(s21_strncmp(str, "", 5), strncmp(str, "", 5));
  ck_assert_ptr_eq(s21_strpbrk(str, "abc"), strpbrk(str, "abc"));
}
END_TEST

Suite *memchr_suite(void) {
  Suite *s = suite_create("s21_memchr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_memchr_found);
  tcase_add_test(tc, test_memchr_not_found);
  tcase_add_test(tc, test_memchr_first_char);
  tcase_add_test(tc, test_memchr_last_char);
  tcase_add_test(tc, test_memchr_null_char);
  tcase_add_test(tc, test_memchr_n_zero);
  tcase_add_test(tc, test_memchr_unsig);
  tcase_add_test(tc, test_memchr_n_over);
  tcase_add_test(tc, test_memchr_binar);

  suite_add_tcase(s, tc);
  return s;
}

Suite *memcmp_suite(void) {
  Suite *s = suite_create("s21_memcmp");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_memcmp_equal);
  tcase_add_test(tc, test_memcmp_less);
  tcase_add_test(tc, test_memcmp_greater);
  tcase_add_test(tc, test_memcmp_n_zero);
  tcase_add_test(tc, test_memcmp_partial);
  tcase_add_test(tc, test_memcmp_with_nulls);
  tcase_add_test(tc, test_memcmp_differ_at_end);
  tcase_add_test(tc, test_memcmp_num);
  tcase_add_test(tc, test_memcmp_unsig);

  suite_add_tcase(s, tc);
  return s;
}

Suite *memcpy_suite(void) {
  Suite *s = suite_create("s21_memcpy");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_memcpy_basic);
  tcase_add_test(tc, test_memcpy_empty);
  tcase_add_test(tc, test_memcpy_partial);
  tcase_add_test(tc, test_memcpy_full_buffer);
  tcase_add_test(tc, test_memcpy_with_nulls);
  tcase_add_test(tc, test_memcpy_single_byte);

  suite_add_tcase(s, tc);
  return s;
}

Suite *memset_suite(void) {
  Suite *s = suite_create("s21_memset");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_memset_basic);
  tcase_add_test(tc, test_memset_zero);
  tcase_add_test(tc, test_memset_full);
  tcase_add_test(tc, test_memset_partial);
  tcase_add_test(tc, test_memset_n_zero);

  suite_add_tcase(s, tc);
  return s;
}

Suite *strlen_suite(void) {
  Suite *s = suite_create("s21_strlen");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strlen_basic);
  tcase_add_test(tc, test_strlen_empty);
  tcase_add_test(tc, test_strlen_one_char);
  tcase_add_test(tc, test_strlen_long);
  tcase_add_test(tc, test_strlen_special_chars);

  suite_add_tcase(s, tc);
  return s;
}

Suite *strncat_suite(void) {
  Suite *s = suite_create("s21_strncat");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strncat_basic);
  tcase_add_test(tc, test_strncat_partial);
  tcase_add_test(tc, test_strncat_empty_dest);
  tcase_add_test(tc, test_strncat_empty_src);
  tcase_add_test(tc, test_strncat_n);
  tcase_add_test(tc, test_strncat_n_greater);

  suite_add_tcase(s, tc);
  return s;
}

Suite *strncpy_suite(void) {
  Suite *s = suite_create("s21_strncpy");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strncpy_basic);
  tcase_add_test(tc, test_strncpy_exact);
  tcase_add_test(tc, test_strncpy_less_than_src);
  tcase_add_test(tc, test_strncpy_n_greater);
  tcase_add_test(tc, test_strncpy_empty);
  tcase_add_test(tc, test_strncpy_n);

  suite_add_tcase(s, tc);
  return s;
}

Suite *strstr_suite(void) {
  Suite *s = suite_create("s21_strstr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strstr_found);
  tcase_add_test(tc, test_strstr_not_found);
  tcase_add_test(tc, test_strstr_empty_needle);
  tcase_add_test(tc, test_strstr_at_beginning);
  tcase_add_test(tc, test_strstr_at_end);
  tcase_add_test(tc, test_strstr_single_char);
  tcase_add_test(tc, test_strstr_repeated);
  tcase_add_test(tc, test_strstr_needle_longer);
  tcase_add_test(tc, test_strstr_empty_haystack);
  tcase_add_test(tc, test_strstr_both_empty);

  suite_add_tcase(s, tc);
  return s;
}

Suite *strchr_suite(void) {
  Suite *s = suite_create("s21_strchr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strchr_basic);
  tcase_add_test(tc, test_strchr_first_char);
  tcase_add_test(tc, test_strchr_last_char);
  tcase_add_test(tc, test_strchr_middle_char);
  tcase_add_test(tc, test_strchr_not_found);
  tcase_add_test(tc, test_strchr_null_char);
  tcase_add_test(tc, test_strchr_empty_string);

  tcase_add_test(tc, test_strchr_special_chars);
  tcase_add_test(tc, test_strchr_repeated_char);
  tcase_add_test(tc, test_strchr_unicode_safe);
  tcase_add_test(tc, test_strchr_negative_char);

  suite_add_tcase(s, tc);
  return s;
}

Suite *strrchr_suite(void) {
  Suite *s = suite_create("s21_strrchr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strrchr_basic);
  tcase_add_test(tc, test_strrchr_single_occurrence);
  tcase_add_test(tc, test_strrchr_multiple_occurrence);
  tcase_add_test(tc, test_strrchr_not_found);

  tcase_add_test(tc, test_strrchr_single_char_string);
  tcase_add_test(tc, test_strrchr_char_at_beginning);
  tcase_add_test(tc, test_strrchr_char_not_present);
  tcase_add_test(tc, test_strrchr_empty_string_search);

  suite_add_tcase(s, tc);
  return s;
}

Suite *strcspn_suite(void) {
  Suite *s = suite_create("s21_strcspn");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strcspn_basic);
  tcase_add_test(tc, test_strcspn_no_match);
  tcase_add_test(tc, test_strcspn_first_char_match);
  tcase_add_test(tc, test_strcspn_multiple_reject);

  tcase_add_test(tc, test_strcspn_all_reject);
  tcase_add_test(tc, test_strcspn_null_reject);
  tcase_add_test(tc, test_strcspn_long_string);
  tcase_add_test(tc, test_strcspn_reject_at_start);
  tcase_add_test(tc, test_strcspn_multiple_reject_chars);

  suite_add_tcase(s, tc);
  return s;
}

Suite *strncmp_suite(void) {
  Suite *s = suite_create("s21_strncmp");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strncmp_equal);
  tcase_add_test(tc, test_strncmp_different);
  tcase_add_test(tc, test_strncmp_zero_length);
  tcase_add_test(tc, test_strncmp_partial_match);
  tcase_add_test(tc, test_strncmp_empty_strings);

  tcase_add_test(tc, test_strncmp_same_string_long_n);
  tcase_add_test(tc, test_strncmp_diff_case);
  tcase_add_test(tc, test_strncmp_one_char_diff);
  tcase_add_test(tc, test_strncmp_partial_with_null);
  tcase_add_test(tc, test_strncmp_large_n);

  suite_add_tcase(s, tc);
  return s;
}

Suite *strpbrk_suite(void) {
  Suite *s = suite_create("s21_strpbrk");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strpbrk_basic);
  tcase_add_test(tc, test_strpbrk_multiple_accept);
  tcase_add_test(tc, test_strpbrk_not_found);
  tcase_add_test(tc, test_strpbrk_first_char_match);

  tcase_add_test(tc, test_strpbrk_empty_accept);
  tcase_add_test(tc, test_strpbrk_empty_string);
  tcase_add_test(tc, test_strpbrk_multiple_matches);
  tcase_add_test(tc, test_strpbrk_special_chars);
  tcase_add_test(tc, test_strpbrk_all_chars_match);

  suite_add_tcase(s, tc);
  return s;
}

Suite *strtok_suite(void) {
  Suite *s = suite_create("s21_strtok");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strtok_basic);
  tcase_add_test(tc, test_strtok_multiple_delimiters);

  tcase_add_test(tc, test_strtok_empty_string);
  tcase_add_test(tc, test_strtok_only_delimiters);
  tcase_add_test(tc, test_strtok_consecutive_delimiters);

  tcase_add_test(tc, test_strtok_single_delimiter);
  tcase_add_test(tc, test_strtok_no_delimiter_in_string);
  tcase_add_test(tc, test_strtok_delimiter_at_end);
  tcase_add_test(tc, test_strtok_delimiter_at_start);
  tcase_add_test(tc, test_strtok_reset_with_new_string);

  suite_add_tcase(s, tc);
  return s;
}

Suite *strerror_suite(void) {
  Suite *s = suite_create("s21_strerror");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strerror_success);
  tcase_add_test(tc, test_strerror_enoent);
  tcase_add_test(tc, test_strerror_einval);

  tcase_add_test(tc, test_strerror_all_known_errors);
  tcase_add_test(tc, test_strerror_large_positive);
  tcase_add_test(tc, test_strerror_large_negative);
  tcase_add_test(tc, test_strerror_zero_unknown);
  tcase_add_test(tc, test_strerror_negative_one);

  suite_add_tcase(s, tc);
  return s;
}

Suite *integration_suite(void) {
  Suite *s = suite_create("Integration");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_integration_strchr_strrchr);
  tcase_add_test(tc, test_integration_strcspn_strpbrk);
  tcase_add_test(tc, test_integration_strtok_strcspn);
  tcase_add_test(tc, test_integration_all_functions);
  tcase_add_test(tc, test_integration_edge_case_empty);

  suite_add_tcase(s, tc);
  return s;
}

void add_string_suites(SRunner *sr) {
  srunner_add_suite(sr, strlen_suite());
  srunner_add_suite(sr, memset_suite());
  srunner_add_suite(sr, memchr_suite());
  srunner_add_suite(sr, memcpy_suite());
  srunner_add_suite(sr, memcmp_suite());
  srunner_add_suite(sr, strncpy_suite());
  srunner_add_suite(sr, strncat_suite());
  srunner_add_suite(sr, strstr_suite());
  srunner_add_suite(sr, strchr_suite());
  srunner_add_suite(sr, strrchr_suite());
  srunner_add_suite(sr, strcspn_suite());
  srunner_add_suite(sr, strncmp_suite());
  srunner_add_suite(sr, strpbrk_suite());
  srunner_add_suite(sr, strtok_suite());
  srunner_add_suite(sr, strerror_suite());
  srunner_add_suite(sr, integration_suite());
}