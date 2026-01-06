CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
AR = ar
ARFLAGS = rcs

LIB_NAME = s21_string.a
SRC = s21_string.c s21_sprintf.c
OBJ = $(SRC:.c=.o)
HEADER = s21_string.h

TEST_SRC = test/test_main.c test/test_s21_string.c test/test_s21_sprintf.c
TEST_EXEC = test_program

CHECK_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
COV_DIR = coverage_report

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    CFLAGS += -D__linux__
endif

.PHONY: all clean clean_coverage test gcov_report rebuild

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^
	@echo "$(LIB_NAME) created"

s21_string.o: s21_string.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

s21_sprintf.o: s21_sprintf.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(LIB_NAME)
	@echo "Running all tests..."
	$(CC) $(CFLAGS) $(TEST_SRC) -L. s21_string.a $(CHECK_FLAGS) -o $(TEST_EXEC)
	./$(TEST_EXEC)
	@rm -f $(TEST_EXEC)

gcov_report:
	@echo "Cleaning..."
	@rm -f *.gcda *.gcno *.gcov coverage.info
	@rm -rf coverage_report
	@echo "Building with coverage..."
	$(CC) -g -O0 --coverage $(SRC) $(TEST_SRC) $(CHECK_FLAGS) -o test_program_cov
	@./test_program_cov
	@lcov --capture --directory . --output-file coverage_all.info --quiet
	@lcov --extract coverage_all.info "*/s21_string.c" "*/s21_sprintf.c" -o coverage.info --quiet
	@genhtml coverage.info --output-directory coverage_report --quiet
	@echo "COVERAGE REPORT: coverage_report/index.html"
	@rm -f coverage_all.info test_program_cov

clean_coverage:
	@echo "Cleaning coverage files..."
	rm -f *.gcno *.gcda *.gcov
	rm -f test_program_cov coverage.info
	rm -rf $(COV_DIR)

clean: clean_coverage
	@echo "Cleaning all..."
	rm -f *.o *.a $(TEST_EXEC) test_sprintf_exec
	@echo "Clean complete"

rebuild: clean all