#include <check.h>
#include <stdlib.h>

extern void add_string_suites(SRunner *sr);
extern Suite *combined_sprintf_suite(void);

int main(void) {
  int failed = 0;

  SRunner *sr = srunner_create(combined_sprintf_suite());

  add_string_suites(sr);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}