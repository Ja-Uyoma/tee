#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "tee.h"

#include <stdio.h>

// A test case that does nothing and succeeds
static void null_test_success(void** state)
{
    (void) state;
}

static void echo_returns_successfully_when_passed_null_files(void** state)
{
    (void) state;

    FILE* input = NULL;
    FILE* output = NULL;

    assert_int_equal(echo(input, output), -1);
}

int main(void)
{
    struct CMUnitTest const tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(echo_returns_successfully_when_passed_null_files)
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}
