#include "test_main.h"

int main(void) {
  int no_failed = 0;
  SRunner *runner;
  runner = srunner_create(notation_suite());
  srunner_add_suite(runner, notation_error_suite());
  srunner_add_suite(runner, notation_calc_suite());
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}