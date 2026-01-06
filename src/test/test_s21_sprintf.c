#include <check.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_sprintf_simple_string) {
  char buf1[100] = {0};
  char buf2[100] = {0};

  s21_sprintf(buf1, "Hello");
  sprintf(buf2, "Hello");

  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_percent) {
  char buf1[100] = {0};
  char buf2[100] = {0};

  s21_sprintf(buf1, "100%%");
  sprintf(buf2, "100%%");

  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_char) {
  char buf1[100] = {0};
  char buf2[100] = {0};

  s21_sprintf(buf1, "%c", 'A');
  sprintf(buf2, "%c", 'A');

  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_char_width) {
  char buf1[100] = {0};
  char buf2[100] = {0};

  s21_sprintf(buf1, "%5c", 'A');
  sprintf(buf2, "%5c", 'A');

  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_string) {
  char buf1[100] = {0};
  char buf2[100] = {0};

  s21_sprintf(buf1, "%s", "Hello");
  sprintf(buf2, "%s", "Hello");

  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_string_width) {
  char buf1[100] = {0};
  char buf2[100] = {0};

  s21_sprintf(buf1, "%10s", "hi");
  sprintf(buf2, "%10s", "hi");

  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_string_precision) {
  char buf1[100] = {0};
  char buf2[100] = {0};

  s21_sprintf(buf1, "%.3s", "hello");
  sprintf(buf2, "%.3s", "hello");

  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_pointer) {
  char buf1[100] = {0};
  char buf2[100] = {0};
  int x = 42;

  s21_sprintf(buf1, "%p", &x);
  sprintf(buf2, "%p", &x);

  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_pointer_width) {
  char buf1[100] = {0};
  char buf2[100] = {0};
  int x = 42;

  s21_sprintf(buf1, "%25p", &x);
  sprintf(buf2, "%25p", &x);

  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_pointer_left) {
  char buf1[100] = {0};
  char buf2[100] = {0};
  int x = 42;

  s21_sprintf(buf1, "%-25p", &x);
  sprintf(buf2, "%-25p", &x);

  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_pointer_null) {
  char buf1[100] = {0};
  char buf2[100] = {0};

  s21_sprintf(buf1, "%p", NULL);
  sprintf(buf2, "%p", NULL);

  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_reverse_str) {
  char str1[] = "hello";
  s21_reverse_str(str1, 5);
  ck_assert_str_eq(str1, "olleh");

  char str2[] = "a";
  s21_reverse_str(str2, 1);
  ck_assert_str_eq(str2, "a");
}
END_TEST

START_TEST(test_int_to_str_decimal) {
  char buffer[32];

  int len = s21_int_to_str(0, buffer, 10, 0);
  ck_assert_int_eq(len, 1);
  ck_assert_str_eq(buffer, "0");

  len = s21_int_to_str(42, buffer, 10, 0);
  ck_assert_int_eq(len, 2);
  ck_assert_str_eq(buffer, "42");

  len = s21_int_to_str(-42, buffer, 10, 0);
  ck_assert_int_eq(len, 3);
  ck_assert_str_eq(buffer, "-42");
}
END_TEST

START_TEST(test_int_to_str_hex) {
  char buffer[32];

  s21_int_to_str(255, buffer, 16, 0);
  ck_assert_str_eq(buffer, "ff");

  s21_int_to_str(255, buffer, 16, 1);
  ck_assert_str_eq(buffer, "FF");
}
END_TEST

START_TEST(test_int_to_str_octal) {
  char buffer[32];

  s21_int_to_str(8, buffer, 8, 0);
  ck_assert_str_eq(buffer, "10");

  s21_int_to_str(63, buffer, 8, 0);
  ck_assert_str_eq(buffer, "77");
}
END_TEST

START_TEST(test_unint_to_str) {
  char buffer[32];

  int len = s21_unint_to_str(0, buffer, 10, 0);
  ck_assert_int_eq(len, 1);
  ck_assert_str_eq(buffer, "0");

  len = s21_unint_to_str(42, buffer, 10, 0);
  ck_assert_int_eq(len, 2);
  ck_assert_str_eq(buffer, "42");
}
END_TEST

START_TEST(test_s21_math_functions) {
  ck_assert_double_eq(s21_fabs(3.14), 3.14);
  ck_assert_double_eq(s21_fabs(-3.14), 3.14);

  ck_assert_int_eq(s21_llabs(42LL), 42LL);
  ck_assert_int_eq(s21_llabs(-42LL), 42LL);

  ck_assert_double_eq_tol(s21_pow(2.0, 3), 8.0, 1e-6);
  ck_assert_double_eq_tol(s21_pow(2.0, 0), 1.0, 1e-6);

  ck_assert_double_eq_tol(s21_round(3.4), 3.0, 1e-6);
  ck_assert_double_eq_tol(s21_round(3.5), 4.0, 1e-6);
  ck_assert_double_eq_tol(s21_round(-3.4), -3.0, 1e-6);
  ck_assert_double_eq_tol(s21_round(-3.5), -4.0, 1e-6);
}
END_TEST

START_TEST(test_format_int_basic) {
  char result[256];
  char expected[256];
  int result_len;

  FormatSpec spec = {0};
  spec.specifier = 'd';

  s21_format_int(&spec, 42, result, &result_len);
  sprintf(expected, "42");
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(result_len, strlen(expected));

  s21_format_int(&spec, -42, result, &result_len);
  sprintf(expected, "-42");
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_format_int_flag_plus) {
  char result[256];
  char expected[256];
  int result_len;

  FormatSpec spec = {0};
  spec.specifier = 'd';
  spec.flag_plus = 1;

  s21_format_int(&spec, 42, result, &result_len);
  sprintf(expected, "+42");
  ck_assert_str_eq(result, expected);

  s21_format_int(&spec, -42, result, &result_len);
  sprintf(expected, "-42");
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_format_int_flag_space) {
  char result[256];
  char expected[256];
  int result_len;

  FormatSpec spec = {0};
  spec.specifier = 'd';
  spec.flag_space = 1;

  s21_format_int(&spec, 42, result, &result_len);
  sprintf(expected, " 42");
  ck_assert_str_eq(result, expected);

  s21_format_int(&spec, -42, result, &result_len);
  sprintf(expected, "-42");
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_format_int_width) {
  char result[256];
  char expected[256];
  int result_len;

  FormatSpec spec = {0};
  spec.specifier = 'd';

  spec.width = 5;
  s21_format_int(&spec, 42, result, &result_len);
  sprintf(expected, "   42");
  ck_assert_str_eq(result, expected);

  spec.width = 2;
  s21_format_int(&spec, 123, result, &result_len);
  sprintf(expected, "123");
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_format_int_flag_minus) {
  char result[256];
  char expected[256];
  int result_len;

  FormatSpec spec = {0};
  spec.specifier = 'd';
  spec.flag_minus = 1;

  spec.width = 5;
  s21_format_int(&spec, 42, result, &result_len);
  sprintf(expected, "42   ");
  ck_assert_str_eq(result, expected);

  spec.width = 6;
  s21_format_int(&spec, -42, result, &result_len);
  sprintf(expected, "-42   ");
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_format_int_precision) {
  char result[256];
  char expected[256];
  int result_len;

  FormatSpec spec = {0};
  spec.specifier = 'd';

  spec.precision = 5;
  s21_format_int(&spec, 42, result, &result_len);
  sprintf(expected, "00042");
  ck_assert_str_eq(result, expected);

  spec.precision = 0;
  s21_format_int(&spec, 0, result, &result_len);
  ck_assert_int_eq(result_len, 0);
}
END_TEST

START_TEST(test_format_int_flag_zero) {
  char result[256];
  char expected[256];
  int result_len;

  FormatSpec spec = {0};
  spec.specifier = 'd';
  spec.flag_zero = 1;

  spec.width = 5;
  spec.precision = -1;
  s21_format_int(&spec, 42, result, &result_len);
  sprintf(expected, "00042");
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_format_unsigned_basic) {
  char result[256];
  char expected[256];
  int result_len;

  FormatSpec spec = {0};
  spec.specifier = 'u';
  spec.precision = -1;

  s21_format_unsigned(&spec, 42, result, &result_len);
  sprintf(expected, "42");
  ck_assert_str_eq(result, expected);

  s21_format_unsigned(&spec, 0, result, &result_len);
  sprintf(expected, "0");
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_format_unsigned_precision) {
  char result[256];
  char expected[256];
  int result_len;

  FormatSpec spec = {0};
  spec.specifier = 'u';

  spec.precision = 5;
  s21_format_unsigned(&spec, 42, result, &result_len);
  sprintf(expected, "00042");
  ck_assert_str_eq(result, expected);

  spec.precision = 0;
  s21_format_unsigned(&spec, 0, result, &result_len);
  ck_assert_int_eq(result_len, 0);
}
END_TEST

START_TEST(test_format_unsigned_width) {
  char result[256];
  char expected[256];
  int result_len;

  FormatSpec spec = {0};
  spec.specifier = 'u';

  spec.width = 5;
  spec.precision = -1;
  s21_format_unsigned(&spec, 42, result, &result_len);
  sprintf(expected, "   42");
  ck_assert_str_eq(result, expected);

  spec.flag_minus = 1;
  s21_format_unsigned(&spec, 42, result, &result_len);
  sprintf(expected, "42   ");
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_format_float_basic) {
  char result[256];
  char expected[256];
  int result_len;

  FormatSpec spec = {0};
  spec.specifier = 'f';
  spec.precision = -1;

  s21_format_float(&spec, 3.14159, result, &result_len);
  sprintf(expected, "3.141590");
  ck_assert_str_eq(result, expected);

  s21_format_float(&spec, -2.71828, result, &result_len);
  sprintf(expected, "-2.718280");
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_format_float_precision) {
  char result[256];
  char expected[256];
  int result_len;

  FormatSpec spec = {0};
  spec.specifier = 'f';

  spec.precision = 2;
  s21_format_float(&spec, 3.14159, result, &result_len);
  sprintf(expected, "3.14");
  ck_assert_str_eq(result, expected);

  spec.precision = 0;
  s21_format_float(&spec, 3.14159, result, &result_len);
  sprintf(expected, "3");
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_format_float_rounding) {
  char result[256];
  char expected[256];
  int result_len;

  FormatSpec spec = {0};
  spec.specifier = 'f';

  spec.precision = 1;
  s21_format_float(&spec, 9.99, result, &result_len);
  sprintf(expected, "10.0");
  ck_assert_str_eq(result, expected);

  spec.precision = 3;
  s21_format_float(&spec, 1.23456, result, &result_len);
  sprintf(expected, "1.235");
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_format_float_flags) {
  char result[256];
  char expected[256];
  int result_len;

  FormatSpec spec = {0};
  spec.specifier = 'f';

  spec.flag_plus = 1;
  spec.precision = 2;
  s21_format_float(&spec, 3.14, result, &result_len);
  sprintf(expected, "+3.14");
  ck_assert_str_eq(result, expected);

  spec.flag_plus = 0;
  spec.flag_space = 1;
  s21_format_float(&spec, 3.14, result, &result_len);
  sprintf(expected, " 3.14");
  ck_assert_str_eq(result, expected);
}
END_TEST

Suite* combined_sprintf_suite(void) {
  Suite* s = suite_create("s21_sprintf_combined");

  TCase* tc = tcase_create("s21_sprintf");

  // Тесты для s21_sprintf
  tcase_add_test(tc, test_sprintf_simple_string);
  tcase_add_test(tc, test_sprintf_percent);
  tcase_add_test(tc, test_sprintf_char);
  tcase_add_test(tc, test_sprintf_char_width);
  tcase_add_test(tc, test_sprintf_string);
  tcase_add_test(tc, test_sprintf_string_width);
  tcase_add_test(tc, test_sprintf_string_precision);
  tcase_add_test(tc, test_sprintf_pointer);
  tcase_add_test(tc, test_sprintf_pointer_width);
  tcase_add_test(tc, test_sprintf_pointer_left);
  tcase_add_test(tc, test_sprintf_pointer_null);

  // Тесты для вспомогательных функций
  tcase_add_test(tc, test_reverse_str);
  tcase_add_test(tc, test_int_to_str_decimal);
  tcase_add_test(tc, test_int_to_str_hex);
  tcase_add_test(tc, test_int_to_str_octal);
  tcase_add_test(tc, test_unint_to_str);
  tcase_add_test(tc, test_s21_math_functions);
  tcase_add_test(tc, test_format_int_basic);
  tcase_add_test(tc, test_format_int_flag_plus);
  tcase_add_test(tc, test_format_int_flag_space);
  tcase_add_test(tc, test_format_int_width);
  tcase_add_test(tc, test_format_int_flag_minus);
  tcase_add_test(tc, test_format_int_precision);
  tcase_add_test(tc, test_format_int_flag_zero);
  tcase_add_test(tc, test_format_unsigned_basic);
  tcase_add_test(tc, test_format_unsigned_precision);
  tcase_add_test(tc, test_format_unsigned_width);
  tcase_add_test(tc, test_format_float_basic);
  tcase_add_test(tc, test_format_float_precision);
  tcase_add_test(tc, test_format_float_rounding);
  tcase_add_test(tc, test_format_float_flags);

  suite_add_tcase(s, tc);

  return s;
}