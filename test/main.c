#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "tee.h"
#include <errno.h>

// A test case that does nothing and succeeds
static void null_test_success(void** state)
{
    (void) state;
}

static void echoToStdoutTest(void** state)
{
    (void) state;

    char buffer[256] = { '\0' };
    errno = 0;
    
    assert_return_code(echoToStdout(buffer, sizeof buffer), errno);
}

int main(void)
{
    struct CMUnitTest const tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(echoToStdoutTest)
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}
