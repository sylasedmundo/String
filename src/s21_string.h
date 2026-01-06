#ifndef S21_STRING_H
#define S21_STRING_H

#define S21_NULL ((void *)0)

#include <stdarg.h>

typedef unsigned long s21_size;

// Вычисляет длину строки str до символа '\0'
s21_size s21_strlen(const char *str);

// Заполняет первые n байт области памяти str значением c
void *s21_memset(void *str, int c, s21_size n);

// Ищет первое вхождение символа c в первых n байтах памяти str
void *s21_memchr(const void *str, int c, s21_size n);

// Копирует n байт из src в dest
void *s21_memcpy(void *dest, const void *src, s21_size n);

// Сравнивает первые n байт областей памяти str1 и str2
int s21_memcmp(const void *str1, const void *str2, s21_size n);

// Копирует до n символов из src в dest
char *s21_strncpy(char *dest, const char *src, s21_size n);

// Добавляет до n символов из src в конец строки dest
char *s21_strncat(char *dest, const char *src, s21_size n);

// Находит первое вхождение подстроки needle в строке haystack
char *s21_strstr(const char *haystack, const char *needle);

// Выполняет поиск первого вхождения символа
char *s21_strchr(const char *str, int c);

// Выполняет поиск последнего вхождения символа
char *s21_strrchr(const char *str, int c);

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2.
s21_size s21_strcspn(const char *str1, const char *str2);

// Сравнивает не более первых n байтов str1 и str2.
int s21_strncmp(const char *str1, const char *str2, s21_size n);

// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2);

// Разбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim);
// Ошибки для Mac, Linux, и в else для других ОС
char *s21_strerror(int errnum);

typedef struct FormatSpec {
  int flag_minus;
  int flag_plus;
  int flag_space;
  int flag_hash;
  int flag_zero;
  int width;
  int precision;
  char length;
  char specifier;
} FormatSpec;

int s21_sprintf(char *str, const char *format, ...);

void s21_parse_format(const char *format, int *pos, struct FormatSpec *spec,
                      va_list args);

void s21_format_char(char *str, int *str_i, va_list args,
                     struct FormatSpec spec);

void s21_format_string(char *str, int *si, va_list args,
                       struct FormatSpec spec);

void s21_format_pointer(char *str, int *si, va_list args,
                        struct FormatSpec spec);

int s21_convert_to_hex(s21_size num, char *hex_buf);

void s21_parse_flags(const char *format, int *fi, struct FormatSpec *spec);

void s21_write_padding(char *str, int *si, int count);

void s21_reverse_str(char *str, int length);

int s21_int_to_str(long long num, char *str, int base, int uppercase);

int s21_unint_to_str(unsigned long long num, char *str, int base,
                     int uppercase);

double s21_fabs(double x);

long long s21_llabs(long long x);

double s21_pow(double base, int exp);

double s21_round(double x);

void s21_apply_precision_int(char *buffer, int *len, int precision,
                             int is_zero_value);
void s21_apply_width(char *result, int *result_len, int width, int left_align,
                     char fill_char);
void s21_format_int(const FormatSpec *spec, long long value, char *result,
                    int *result_len);
void s21_format_unsigned(const FormatSpec *spec, unsigned long long value,
                         char *result, int *result_len);
void s21_split_double(double value, long long *int_part, double *frac_part);

void s21_format_float(FormatSpec *spec, double value, char *result,
                      int *result_len);

void s21_apply_width_with_sign(char *str, int *len, int width, int flag_minus,
                               char fill);

#ifdef __APPLE__
#define S21_OS_MAC 1
#define S21_OS_LINUX 0
#define S21_ERROR_MAX 106
#elif __linux__
#define S21_OS_MAC 0
#define S21_OS_LINUX 1
#define S21_ERROR_MAX 133
#else
#define S21_OS_MAC 0
#define S21_OS_LINUX 0
#define S21_ERROR_MAX 0
#endif

#ifdef __APPLE__
#define S21_ERROR_LIST                                                         \
  {                                                                            \
    [0] = "Undefined error: 0", [1] = "Operation not permitted",               \
    [2] = "No such file or directory", [3] = "No such process",                \
    [4] = "Interrupted system call", [5] = "Input/output error",               \
    [6] = "Device not configured", [7] = "Argument list too long",             \
    [8] = "Exec format error", [9] = "Bad file descriptor",                    \
    [10] = "No child processes", [11] = "Resource deadlock avoided",           \
    [12] = "Cannot allocate memory", [13] = "Permission denied",               \
    [14] = "Bad address", [15] = "Block device required",                      \
    [16] = "Resource busy", [17] = "File exists", [18] = "Cross-device link",  \
    [19] = "Operation not supported by device", [20] = "Not a directory",      \
    [21] = "Is a directory", [22] = "Invalid argument",                        \
    [23] = "Too many open files in system", [24] = "Too many open files",      \
    [25] = "Inappropriate ioctl for device", [26] = "Text file busy",          \
    [27] = "File too large", [28] = "No space left on device",                 \
    [29] = "Illegal seek", [30] = "Read-only file system",                     \
    [31] = "Too many links", [32] = "Broken pipe",                             \
    [33] = "Numerical argument out of domain",                                 \
    [34] = "Numerical result out of range",                                    \
    [35] = "Resource temporarily unavailable",                                 \
    [36] = "Operation now in progress",                                        \
    [37] = "Operation already in progress",                                    \
    [38] = "Socket operation on non-socket",                                   \
    [39] = "Destination address required", [40] = "Message too long",          \
    [41] = "Protocol wrong type for socket", [42] = "Protocol not available",  \
    [43] = "Protocol not supported", [44] = "Socket type not supported",       \
    [45] = "Operation not supported", [46] = "Protocol family not supported",  \
    [47] = "Address family not supported by protocol family",                  \
    [48] = "Address already in use", [49] = "Cannot assign requested address", \
    [50] = "Network is down", [51] = "Network is unreachable",                 \
    [52] = "Network dropped connection on reset",                              \
    [53] = "Software caused connection abort",                                 \
    [54] = "Connection reset by peer", [55] = "No buffer space available",     \
    [56] = "Socket is already connected", [57] = "Socket is not connected",    \
    [58] = "Cannot send after socket shutdown",                                \
    [59] = "Too many references: cannot splice",                               \
    [60] = "Connection timed out", [61] = "Connection refused",                \
    [62] = "Too many levels of symbolic links", [63] = "File name too long",   \
    [64] = "Host is down", [65] = "No route to host",                          \
    [66] = "Directory not empty", [67] = "Too many processes",                 \
    [68] = "Too many users", [69] = "Disc quota exceeded",                     \
    [70] = "Stale NFS file handle",                                            \
    [71] = "Too many levels of remote in path", [72] = "RPC struct is bad",    \
    [73] = "RPC version wrong", [74] = "RPC prog. not avail",                  \
    [75] = "Program version wrong", [76] = "Bad procedure for program",        \
    [77] = "No locks available", [78] = "Function not implemented",            \
    [79] = "Inappropriate file type or format", [80] = "Authentication error", \
    [81] = "Need authenticator", [82] = "Device power is off",                 \
    [83] = "Device error", [84] = "Value too large to be stored in data type", \
    [85] = "Bad executable (or shared library)",                               \
    [86] = "Bad CPU type in executable",                                       \
    [87] = "Shared library version mismatch", [88] = "Malformed Mach-o file",  \
    [89] = "Operation canceled", [90] = "Identifier removed",                  \
    [91] = "No message of desired type", [92] = "Illegal byte sequence",       \
    [93] = "Attribute not found", [94] = "Bad message",                        \
    [95] = "EMULTIHOP (Reserved)", [96] = "No message available on STREAM",    \
    [97] = "ENOLINK (Reserved)", [98] = "No STREAM resources",                 \
    [99] = "Not a STREAM", [100] = "Protocol error",                           \
    [101] = "STREAM ioctl timeout",                                            \
    [102] = "Operation not supported on socket", [103] = "Policy not found",   \
    [104] = "State not recoverable", [105] = "Previous owner died",            \
    [106] = "Interface output queue is full"                                   \
  }

#elif __linux__
#define S21_ERROR_LIST                                                         \
  {                                                                            \
    [0] = "Success", [1] = "Operation not permitted",                          \
    [2] = "No such file or directory", [3] = "No such process",                \
    [4] = "Interrupted system call", [5] = "Input/output error",               \
    [6] = "No such device or address", [7] = "Argument list too long",         \
    [8] = "Exec format error", [9] = "Bad file descriptor",                    \
    [10] = "No child processes", [11] = "Resource temporarily unavailable",    \
    [12] = "Cannot allocate memory", [13] = "Permission denied",               \
    [14] = "Bad address", [15] = "Block device required",                      \
    [16] = "Device or resource busy", [17] = "File exists",                    \
    [18] = "Invalid cross-device link", [19] = "No such device",               \
    [20] = "Not a directory", [21] = "Is a directory",                         \
    [22] = "Invalid argument", [23] = "Too many open files in system",         \
    [24] = "Too many open files", [25] = "Inappropriate ioctl for device",     \
    [26] = "Text file busy", [27] = "File too large",                          \
    [28] = "No space left on device", [29] = "Illegal seek",                   \
    [30] = "Read-only file system", [31] = "Too many links",                   \
    [32] = "Broken pipe", [33] = "Numerical argument out of domain",           \
    [34] = "Numerical result out of range",                                    \
    [35] = "Resource deadlock avoided", [36] = "File name too long",           \
    [37] = "No locks available", [38] = "Function not implemented",            \
    [39] = "Directory not empty", [40] = "Too many levels of symbolic links",  \
    [41] = "Unknown error 41", [42] = "No message of desired type",            \
    [43] = "Identifier removed", [44] = "Channel number out of range",         \
    [45] = "Level 2 not synchronized", [46] = "Level 3 halted",                \
    [47] = "Level 3 reset", [48] = "Link number out of range",                 \
    [49] = "Protocol driver not attached",                                     \
    [50] = "No CSI structure available", [51] = "Level 2 halted",              \
    [52] = "Invalid exchange", [53] = "Invalid request descriptor",            \
    [54] = "Exchange full", [55] = "No anode", [56] = "Invalid request code",  \
    [57] = "Invalid slot", [58] = "Bad font file format",                      \
    [59] = "Device not a stream", [60] = "No data available",                  \
    [61] = "Timer expired", [62] = "Out of streams resources",                 \
    [63] = "Machine is not on the network", [64] = "Package not installed",    \
    [65] = "Object is remote", [66] = "Link has been severed",                 \
    [67] = "Advertise error", [68] = "Srmount error",                          \
    [69] = "Communication error on send", [70] = "Protocol error",             \
    [71] = "Multihop attempted", [72] = "RFS specific error",                  \
    [73] = "Not a data message",                                               \
    [74] = "Value too large for defined data type",                            \
    [75] = "Name not unique on network",                                       \
    [76] = "File descriptor in bad state", [77] = "Remote address changed",    \
    [78] = "Can not access a needed shared library",                           \
    [79] = "Accessing a corrupted shared library",                             \
    [80] = ".lib section in a.out corrupted",                                  \
    [81] = "Attempting to link in too many shared libraries",                  \
    [82] = "Cannot exec a shared library directly",                            \
    [83] = "Invalid or incomplete multibyte or wide character",                \
    [84] = "Interrupted system call should be restarted",                      \
    [85] = "Streams pipe error", [86] = "Too many users",                      \
    [87] = "Socket operation on non-socket",                                   \
    [88] = "Destination address required", [89] = "Message too long",          \
    [90] = "Protocol wrong type for socket", [91] = "Protocol not available",  \
    [92] = "Protocol not supported", [93] = "Socket type not supported",       \
    [94] = "Operation not supported", [95] = "Protocol family not supported",  \
    [96] = "Address family not supported by protocol",                         \
    [97] = "Address already in use", [98] = "Cannot assign requested address", \
    [99] = "Network is down", [100] = "Network is unreachable",                \
    [101] = "Network dropped connection on reset",                             \
    [102] = "Software caused connection abort",                                \
    [103] = "Connection reset by peer", [104] = "No buffer space available",   \
    [105] = "Transport endpoint is already connected",                         \
    [106] = "Transport endpoint is not connected",                             \
    [107] = "Cannot send after transport endpoint shutdown",                   \
    [108] = "Too many references: cannot splice",                              \
    [109] = "Connection timed out", [110] = "Connection refused",              \
    [111] = "Host is down", [112] = "No route to host",                        \
    [113] = "Operation already in progress",                                   \
    [114] = "Operation now in progress", [115] = "Stale file handle",          \
    [116] = "Structure needs cleaning", [117] = "Not a XENIX named type file", \
    [118] = "No XENIX semaphores available", [119] = "Is a named type file",   \
    [120] = "Remote I/O error", [121] = "Disk quota exceeded",                 \
    [122] = "No medium found", [123] = "Wrong medium type",                    \
    [124] = "Operation canceled", [125] = "Required key not available",        \
    [126] = "Key has expired", [127] = "Key has been revoked",                 \
    [128] = "Key was rejected by service", [129] = "Owner died",               \
    [130] = "State not recoverable", [131] = "Operation would block",          \
    [132] = "No record locks available", [133] = "Invalid system call number"  \
  }

#else
#define S21_ERROR_LIST                                                      \
  {                                                                         \
    [0] = "Success", [1] = "Operation not permitted",                       \
    [2] = "No such file or directory", [3] = "No such process",             \
    [4] = "Interrupted system call", [5] = "Input/output error",            \
    [6] = "No such device or address", [7] = "Argument list too long",      \
    [8] = "Exec format error", [9] = "Bad file descriptor",                 \
    [10] = "No child processes", [11] = "Resource temporarily unavailable", \
    [12] = "Cannot allocate memory", [13] = "Permission denied",            \
    [14] = "Bad address", [15] = "Block device required",                   \
    [16] = "Device or resource busy", [17] = "File exists",                 \
    [18] = "Invalid cross-device link", [19] = "No such device",            \
    [20] = "Not a directory", [21] = "Is a directory",                      \
    [22] = "Invalid argument", [23] = "Too many open files in system",      \
    [24] = "Too many open files", [25] = "Inappropriate ioctl for device",  \
    [26] = "Text file busy", [27] = "File too large",                       \
    [28] = "No space left on device", [29] = "Illegal seek",                \
    [30] = "Read-only file system", [31] = "Too many links",                \
    [32] = "Broken pipe", [33] = "Numerical argument out of domain",        \
    [34] = "Numerical result out of range"                                  \
  }
#endif
#endif