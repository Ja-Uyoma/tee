#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "tee.h"

// A test case that does nothing and succeeds
static void null_test_success(void** state)
{
    (void) state;
}

int main(void)
{
    struct CMUnitTest const tests[] = {
        cmocka_unit_test(null_test_success),
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}
