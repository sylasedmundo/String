#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size n) {
  const unsigned char *ptr = (const unsigned char *)str;
  void *result = S21_NULL;
  s21_size i = 0;
  while (i < n && result == S21_NULL) {
    if (ptr[i] == (unsigned char)c) result = (void *)(ptr + i);
    i++;
  }

  return result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size n) {
  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;
  int res = 0;
  for (s21_size i = 0; i < n && res == 0; i++) {
    if (s1[i] != s2[i]) {
      res = s1[i] - s2[i];
    }
  }

  return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  for (s21_size i = 0; i < n; i++) {
    d[i] = s[i];
  }

  return dest;
}

void *s21_memset(void *str, int c, s21_size n) {
  unsigned char *ptr = (unsigned char *)str;

  for (s21_size i = 0; i < n; i++) {
    ptr[i] = (unsigned char)c;
  }

  return str;
}

s21_size s21_strlen(const char *str) {
  s21_size length = 0;

  const char *ptr = str;

  while (*ptr != '\0') {
    length++;
    ptr++;
  }

  return length;
}

char *s21_strncat(char *dest, const char *src, s21_size n) {
  s21_size d_end = 0, i = 0;

  while (dest[d_end] != '\0') d_end++;

  while (i < n && src[i] != '\0') {
    dest[d_end + i] = src[i];
    i++;
  }

  dest[d_end + i] = '\0';

  return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size n) {
  s21_size i = 0;

  while (i < n && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }

  while (i < n) {
    dest[i] = '\0';
    i++;
  }

  return dest;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;

  if (needle[0] == '\0') {
    result = (char *)haystack;
  } else {
    s21_size i = 0;
    int found = 0;
    while (haystack[i] != '\0' && !found) {
      s21_size j = 0;
      while (needle[j] != '\0' && haystack[i + j] != '\0' &&
             haystack[i + j] == needle[j]) {
        j++;
      }
      if (needle[j] == '\0') {
        result = (char *)(haystack + i);
        found = 1;
      }
      i++;
    }
  }
  return result;
}

char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;
  unsigned char uc = (unsigned char)c;

  while (*str != '\0' && result == S21_NULL) {
    if ((unsigned char)*str == uc) {
      result = (char *)str;
    }
    str++;
  }
  if (result == S21_NULL && uc == '\0') {
    result = (char *)str;
  }
  return result;
}

char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;
  unsigned char uc = (unsigned char)c;

  while (*str != '\0') {
    if ((unsigned char)*str == uc) {
      result = (char *)str;
    }
    str++;
  }
  if (result == S21_NULL && uc == '\0') {
    result = (char *)str;
  }
  return result;
}

s21_size s21_strcspn(const char *str1, const char *str2) {
  s21_size result = 0;
  int match = 0;
  while (str1[result] && !match) {
    const char *temp = str2;
    while (*temp && (unsigned char)*temp != (unsigned char)str1[result]) {
      temp++;
    }
    match = (*temp != '\0');
    if (!match) {
      result++;
    }
  }
  return result;
}

int s21_strncmp(const char *str1, const char *str2, s21_size n) {
  int result = 0;
  s21_size sym = 0;
  while (sym < n && result == 0) {
    unsigned char ch1 = (unsigned char)str1[sym];
    unsigned char ch2 = (unsigned char)str2[sym];
    result = ch1 - ch2;
    if (result == 0) {
      sym++;
      if (ch1 == '\0') {
        break;
      }
    }
  }
  return result;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  int match = 0;

  while (*str1 && !match) {
    const char *temp = str2;
    while (*temp && !match) {
      if ((unsigned char)*str1 == (unsigned char)*temp) {
        result = (char *)str1;
        match++;
      }
      temp++;
    }
    str1++;
  }
  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *next = S21_NULL;
  char *token = S21_NULL;
  if (str != S21_NULL) next = str;
  int has_data = (next != S21_NULL && *next != '\0');
  if (has_data) {
    int skip = 1;
    while (*next != '\0' && skip) {
      const char *d = delim;
      int is_delim = 0;
      while (*d != '\0' && !is_delim) {
        if (*next == *d) is_delim = 1;
        d++;
      }
      if (is_delim) {
        next++;
      } else {
        skip = 0;
      }
    }
    if (*next == '\0') {
      next = S21_NULL;
      has_data = 0;
    }
  }
  if (has_data) {
    token = next;
    int scan = 1;
    while (*next != '\0' && scan) {
      const char *d = delim;
      int is_delim = 0;
      while (*d != '\0' && !is_delim) {
        if (*next == *d) is_delim = 1;
        d++;
      }
      if (is_delim) {
        *next = '\0';
        next++;
        scan = 0;
      } else {
        next++;
      }
    }
    if (scan) {
      next = S21_NULL;
    }
  }
  return token;
}

char *s21_strerror(int errnum) {
  static const char *error_array[] = S21_ERROR_LIST;
  static char unknown_error[256] = {0};
#ifdef __APPLE__
  const int max_error = 106;
#elif __linux__
  const int max_error = 133;
#else
  const int max_error = 34;
#endif
  if (errnum >= 0 && errnum <= max_error) {
    return (char *)error_array[errnum];
  } else {
    char *ptr = unknown_error;
    const char *prefix = "Unknown error ";
    while (*prefix) {
      *ptr++ = *prefix++;
    }
    int n = errnum;
    char buffer[20];
    char *buf_ptr = buffer;
    if (n < 0) {
      *ptr++ = '-';
      n = -n;
    }
    if (n == 0) {
      *buf_ptr++ = '0';
    } else {
      while (n > 0) {
        *buf_ptr++ = (n % 10) + '0';
        n /= 10;
      }
    }
    while (buf_ptr > buffer) {
      *ptr++ = *(--buf_ptr);
    }
    *ptr = '\0';
    return unknown_error;
  }
}