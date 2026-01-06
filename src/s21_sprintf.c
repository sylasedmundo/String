#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int fi = 0, si = 0;
  while (format[fi] != '\0') {
    if (format[fi] != '%') {
      str[si] = format[fi];
      fi++;
      si++;
    } else {
      fi++;
      if (format[fi] == '%') {
        str[si] = format[fi];
        fi++;
        si++;
      } else {
        struct FormatSpec spec = {0};
        s21_parse_format(format, &fi, &spec, args);
        if (spec.specifier == 'c') {
          s21_format_char(str, &si, args, spec);
        } else if (spec.specifier == 's') {
          s21_format_string(str, &si, args, spec);
        } else if (spec.specifier == 'p') {
          s21_format_pointer(str, &si, args, spec);
        }
      }
    }
  }

  str[si] = '\0';

  va_end(args);

  return si;
}

void s21_parse_format(const char *format, int *fi, struct FormatSpec *spec,
                      va_list args) {
  spec->width = -1;
  spec->precision = -1;

  s21_parse_flags(format, fi, spec);

  if (format[*fi] == '*') {
    spec->width = va_arg(args, int);
    if (spec->width < 0) {
      spec->flag_minus = 1;
      spec->width *= -1;
    }
    (*fi)++;
  } else {
    if (format[*fi] >= '0' && format[*fi] <= '9') {
      spec->width = 0;
      while (format[*fi] >= '0' && format[*fi] <= '9') {
        spec->width = spec->width * 10 + (format[*fi] - '0');
        (*fi)++;
      }
    }
  }

  if (format[*fi] == '.') {
    (*fi)++;
    spec->precision = 0;
    if (format[*fi] == '*') {
      spec->precision = va_arg(args, int);
      if (spec->precision < 0) spec->precision = -1;
      (*fi)++;
    } else {
      while (format[*fi] >= '0' && format[*fi] <= '9') {
        spec->precision = spec->precision * 10 + (format[*fi] - '0');
        (*fi)++;
      }
    }
  }

  if (format[*fi] == 'h' || format[*fi] == 'l' || format[*fi] == 'L') {
    spec->length = format[*fi];
    (*fi)++;
  }

  spec->specifier = format[*fi];
  (*fi)++;
}

void s21_format_char(char *str, int *si, va_list args, struct FormatSpec spec) {
  char c = (char)va_arg(args, int);

  int padding = 0;
  if (spec.width > 1) {
    padding = spec.width - 1;
  }

  if (!spec.flag_minus) {
    s21_write_padding(str, si, padding);
  }

  str[*si] = c;
  (*si)++;

  if (spec.flag_minus) {
    s21_write_padding(str, si, padding);
  }
}

void s21_format_string(char *str, int *si, va_list args,
                       struct FormatSpec spec) {
  const char *s = va_arg(args, char *);
  int len = 0, padding = 0;

  if (s == S21_NULL) {
    s = "(null)";
  }

  len = s21_strlen(s);

  if (spec.precision < len && spec.precision >= 0) len = spec.precision;

  if (spec.width > len) {
    padding = spec.width - len;
  }

  if (!spec.flag_minus) {
    s21_write_padding(str, si, padding);
  }

  for (int i = 0; i < len; i++) {
    str[*si] = s[i];
    (*si)++;
  }

  if (spec.flag_minus) {
    s21_write_padding(str, si, padding);
  }
}

void s21_format_pointer(char *str, int *si, va_list args,
                        struct FormatSpec spec) {
  void *ptr = va_arg(args, void *);
  if (ptr == S21_NULL) {
    const char *nil_str = "(nil)";
    int len = 5;
    int padding = 0;
    if (spec.width > len) {
      padding = spec.width - len;
    }

    if (!spec.flag_minus) {
      s21_write_padding(str, si, padding);
    }

    for (int i = 0; i < len; i++) {
      str[*si] = nil_str[i];
      (*si)++;
    }

    if (spec.flag_minus) {
      s21_write_padding(str, si, padding);
    }
    return;
  }

  char hex[20] = {0};
  int hex_len = s21_convert_to_hex((s21_size)ptr, hex);
  int padding = spec.width - (hex_len + 2);

  if (!spec.flag_minus) {
    s21_write_padding(str, si, padding);
  }

  str[*si] = '0';
  (*si)++;
  str[*si] = 'x';
  (*si)++;

  for (int i = 0; i < hex_len; i++) {
    str[*si] = hex[i];
    (*si)++;
  }

  if (spec.flag_minus) {
    s21_write_padding(str, si, padding);
  }
}

void s21_parse_flags(const char *format, int *fi, struct FormatSpec *spec) {
  int parsing_flags = 1;
  while (parsing_flags) {
    if (format[*fi] == '-') {
      spec->flag_minus = 1;
      (*fi)++;
    } else if (format[*fi] == '+') {
      spec->flag_plus = 1;
      (*fi)++;
    } else if (format[*fi] == ' ') {
      spec->flag_space = 1;
      (*fi)++;
    } else if (format[*fi] == '#') {
      spec->flag_hash = 1;
      (*fi)++;
    } else if (format[*fi] == '0') {
      spec->flag_zero = 1;
      (*fi)++;
    } else {
      parsing_flags = 0;
    }
  }
}

int s21_convert_to_hex(s21_size num, char *hex_buf) {
  int hi = 0;

  if (num == 0) {
    hex_buf[0] = '0';
    hi = 1;
  } else {
    while (num > 0) {
      int ost = num % 16;
      if (ost < 10) {
        hex_buf[hi] = '0' + ost;
      } else {
        hex_buf[hi] = 'a' + (ost - 10);
      }
      hi++;
      num /= 16;
    }
  }
  hex_buf[hi] = '\0';

  int left = 0, right = hi - 1;
  while (left < right) {
    char t = hex_buf[left];
    hex_buf[left] = hex_buf[right];
    hex_buf[right] = t;
    left++;
    right--;
  }

  return hi;
}

void s21_write_padding(char *str, int *si, int count) {
  while (count > 0) {
    str[*si] = ' ';
    (*si)++;
    count--;
  }
}

void s21_reverse_str(char *str, int length) {
  if (str == S21_NULL || length <= 1) return;

  int start = 0;
  int end = length - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}

int s21_int_to_str(long long num, char *str, int base, int uppercase) {
  int result = 0;
  int is_negative = 0;
  unsigned long long unum;

  if (num == 0) {
    str[result++] = '0';
  } else {
    if (base == 10 && num < 0) {
      is_negative = 1;
      unum = (unsigned long long)(-num);
    } else {
      unum = (unsigned long long)num;
    }

    while (unum != 0) {
      int rem = unum % base;
      if (rem < 10) {
        str[result++] = rem + '0';
      } else {
        str[result++] = (rem - 10) + (uppercase ? 'A' : 'a');
      }
      unum = unum / base;
    }

    if (is_negative) {
      str[result++] = '-';
    }
  }

  str[result] = '\0';
  s21_reverse_str(str, result);

  return result;
}

int s21_unint_to_str(unsigned long long num, char *str, int base,
                     int uppercase) {
  int result = 0;
  unsigned long long temp = num;

  if (temp == 0) {
    str[result++] = '0';
  } else {
    while (temp != 0) {
      int rem = temp % base;
      if (rem < 10) {
        str[result++] = rem + '0';
      } else {
        str[result++] = (rem - 10) + (uppercase ? 'A' : 'a');
      }
      temp = temp / base;
    }
  }
  str[result] = '\0';
  s21_reverse_str(str, result);

  return result;
}

double s21_fabs(double x) { return x < 0 ? -x : x; }

long long s21_llabs(long long x) { return x < 0 ? -x : x; }

double s21_pow(double base, int exp) {
  double result = 1.0;
  int abs_exp = exp < 0 ? -exp : exp;

  for (int i = 0; i < abs_exp; i++) {
    result *= base;
  }

  return exp < 0 ? 1.0 / result : result;
}

double s21_round(double x) {
  if (x >= 0.0) {
    long long int_part = (long long)x;
    double frac = x - int_part;

    if (frac > 0.5) {
      return int_part + 1.0;
    } else if (frac < 0.5) {
      return (double)int_part;
    } else {
      return (int_part % 2 == 0) ? (double)int_part : (double)(int_part + 1);
    }
  } else {
    x = -x;
    long long int_part = (long long)x;
    double frac = x - int_part;

    if (frac > 0.5) {
      return -(int_part + 1.0);
    } else if (frac < 0.5) {
      return -(double)int_part;
    } else {
      return (int_part % 2 == 0) ? -(double)int_part : -(double)(int_part + 1);
    }
  }
}

void s21_apply_precision_int(char *buffer, int *len, int precision,
                             int is_zero_value) {
  if (is_zero_value && precision == 0) {
    *len = 0;
    return;
  }

  if (precision > *len) {
    int zeros_needed = precision - *len;
    for (int i = *len - 1; i >= 0; i--) {
      buffer[i + zeros_needed] = buffer[i];
    }
    for (int i = 0; i < zeros_needed; i++) {
      buffer[i] = '0';
    }
    *len = precision;
  }
}

void s21_apply_width(char *result, int *result_len, int width, int left_align,
                     char fill_char) {
  if (width <= *result_len) return;

  int padding = width - *result_len;
  char temp[256];

  for (int i = 0; i <= *result_len; i++) {
    temp[i] = result[i];
  }

  if (left_align) {
    for (int i = 0; i < padding; i++) {
      result[*result_len + i] = ' ';
    }
    result[width] = '\0';
  } else {
    for (int i = 0; i < padding; i++) {
      result[i] = fill_char;
    }
    for (int i = 0; i < *result_len; i++) {
      result[padding + i] = temp[i];
    }
    result[width] = '\0';
  }

  *result_len = width;
}

void s21_format_int(const FormatSpec *spec, long long value, char *result,
                    int *result_len) {
  char buffer[32];
  int len = 0;

  int is_negative = 0;
  unsigned long long abs_value;

  if (value < 0) {
    is_negative = 1;
    if (value == -9223372036854775807LL - 1) {
      abs_value = 9223372036854775808ULL;
    } else {
      abs_value = (unsigned long long)(-value);
    }
  } else {
    abs_value = (unsigned long long)value;
  }

  if (abs_value == 0 && spec->precision == 0) {
    len = 0;
  } else {
    len = s21_int_to_str(abs_value, buffer, 10, 0);
  }

  if (spec->precision >= 0) {
    s21_apply_precision_int(buffer, &len, spec->precision, abs_value == 0);
  }

  int idx = 0;

  if (is_negative) {
    result[idx++] = '-';
  } else if (spec->flag_plus) {
    result[idx++] = '+';
  } else if (spec->flag_space) {
    result[idx++] = ' ';
  }

  for (int i = 0; i < len; i++) {
    result[idx++] = buffer[i];
  }
  result[idx] = '\0';
  *result_len = idx;

  if (spec->width > *result_len) {
    char fill_char = ' ';
    int use_zero_fill = 0;

    if (spec->flag_zero && !spec->flag_minus && spec->precision < 0) {
      fill_char = '0';
      use_zero_fill = 1;
    }

    if (use_zero_fill && (is_negative || spec->flag_plus || spec->flag_space)) {
      char sign_char = '\0';
      if (idx > 0) {
        if (result[0] == '-' || result[0] == '+' || result[0] == ' ') {
          sign_char = result[0];
          for (int i = 0; i < idx; i++) {
            result[i] = result[i + 1];
          }
          idx--;
          *result_len = idx;
        }
      }

      s21_apply_width(result, result_len, spec->width - (sign_char ? 1 : 0),
                      spec->flag_minus, fill_char);

      if (sign_char) {
        for (int i = *result_len - 1; i >= 0; i--) {
          result[i + 1] = result[i];
        }
        result[0] = sign_char;
        (*result_len)++;
        result[*result_len] = '\0';
      }
    } else {
      s21_apply_width(result, result_len, spec->width, spec->flag_minus,
                      fill_char);
    }
  }
}

void s21_format_unsigned(const FormatSpec *spec, unsigned long long value,
                         char *result, int *result_len) {
  char buffer[32];
  int len = 0;

  if (value == 0 && spec->precision == 0) {
    len = 0;
    buffer[0] = '\0';
  } else if (value == 0) {
    buffer[0] = '0';
    buffer[1] = '\0';
    len = 1;
  } else {
    len = s21_int_to_str(value, buffer, 10, 0);
  }

  if (spec->precision >= 0 && spec->precision > len) {
    s21_apply_precision_int(buffer, &len, spec->precision, value == 0);
  }

  for (int i = 0; i < len; i++) {
    result[i] = buffer[i];
  }
  result[len] = '\0';
  *result_len = len;

  FormatSpec temp_spec = *spec;

  if (temp_spec.width > *result_len) {
    char fill_char = ' ';
    if (temp_spec.flag_zero && !temp_spec.flag_minus &&
        temp_spec.precision < 0) {
      fill_char = '0';
    }
    s21_apply_width(result, result_len, temp_spec.width, temp_spec.flag_minus,
                    fill_char);
  }
}

void s21_split_double(double value, long long *int_part, double *frac_part) {
  if (value < 0) {
    value = -value;
  }

  *int_part = (long long)value;
  *frac_part = value - (double)(*int_part);
}

void s21_apply_width_with_sign(char *str, int *len, int width, int flag_minus,
                               char fill) {
  if (width <= *len) return;

  int has_sign = (str[0] == '-' || str[0] == '+' || str[0] == ' ');

  if (fill == '0' && has_sign && !flag_minus) {
    char temp[256];
    temp[0] = str[0];
    int zeros = width - *len;
    for (int i = 0; i < zeros; i++) temp[1 + i] = '0';
    for (int i = 1; i < *len; i++) temp[zeros + i] = str[i];
    temp[width] = '\0';
    for (int i = 0; i <= width; i++) str[i] = temp[i];
    *len = width;
  } else {
    s21_apply_width(str, len, width, flag_minus, fill);
  }
}

void s21_format_float(FormatSpec *spec, double value, char *result,
                      int *result_len) {
  int precision = (spec->precision >= 0) ? spec->precision : 6;
  int is_negative = (value < 0);
  if (is_negative) value = -value;

  unsigned long long multiplier = 1;
  for (int i = 0; i < precision; i++) multiplier *= 10;
  unsigned long long scaled = (unsigned long long)(value * multiplier + 0.5);
  unsigned long long int_part = scaled / multiplier;
  unsigned long long frac_part = scaled % multiplier;

  char buffer[256];
  int idx = 0;

  if (is_negative)
    buffer[idx++] = '-';
  else if (spec->flag_plus)
    buffer[idx++] = '+';
  else if (spec->flag_space)
    buffer[idx++] = ' ';

  char int_buf[32];
  int int_len = (int_part == 0) ? 1 : s21_int_to_str(int_part, int_buf, 10, 0);
  if (int_part == 0) int_buf[0] = '0';
  for (int i = 0; i < int_len; i++) buffer[idx++] = int_buf[i];

  if (precision > 0 || spec->flag_hash) {
    buffer[idx++] = '.';
    for (int i = precision - 1; i >= 0; i--) {
      buffer[idx + i] = '0' + (frac_part % 10);
      frac_part /= 10;
    }
    idx += precision;
  }

  buffer[idx] = '\0';
  *result_len = idx;
  for (int i = 0; i <= idx; i++) result[i] = buffer[i];

  if (spec->width > *result_len) {
    char fill = (spec->flag_zero && !spec->flag_minus) ? '0' : ' ';
    s21_apply_width_with_sign(result, result_len, spec->width, spec->flag_minus,
                              fill);
  }
}