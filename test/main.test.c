// clang-format off
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

// clang-format on

#include "tee.h"

// A test case that does nothing and succeeds
static void nullTestSuccess(void **state) { (void)state; }

static void echoFailsWhenGivenNullPointersAsInput(void **state) {
  (void)state;

  FILE *in = NULL;
  FILE *out = NULL;

  int result = echo(in, out);
  assert_int_equal(result, -1);
}

int main(void) {
  struct CMUnitTest const tests[] = {
      cmocka_unit_test(nullTestSuccess),
      cmocka_unit_test(echoFailsWhenGivenNullPointersAsInput)};

  return cmocka_run_group_tests(tests, NULL, NULL);
}
