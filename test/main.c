#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "tee.h"

#include <stdio.h>

// A test case that does nothing and succeeds
static void nullTestSuccess(void** state)
{
    (void) state;
}

static void echoFailsWhenGivenNullPointersAsInput(void** state)
{
    (void) state;

    FILE* in = NULL;
    FILE* out = NULL;

    int result = echo(in, out);
    assert_int_equal(result, -1);
}

int main(void)
{
    struct CMUnitTest const tests[] = {
        cmocka_unit_test(nullTestSuccess),
        cmocka_unit_test(echoFailsWhenGivenNullPointersAsInput)
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}
