// clang-format off
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

// clang-format on

#include "tee.h"

// A test case that does nothing and succeeds
static void null_test_success(void** state)
{
  (void)state;
}

static void echo_fails_when_given_null_pointers_as_input(void** state)
{
  (void)state;

  FILE* input = NULL;
  FILE* output = NULL;

  int result = echo(input, output);
  assert_int_equal(result, -1);
}

int main(void)
{
  struct CMUnitTest const tests[] = {
      cmocka_unit_test(null_test_success),
      cmocka_unit_test(echo_fails_when_given_null_pointers_as_input)};

  return cmocka_run_group_tests(tests, NULL, NULL);
}
