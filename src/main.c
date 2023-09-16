#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const* argv[argc + 1])
{
    (void) argc;
    (void) argv;

    char buffer[512] = { '\0' };

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        fputs(buffer, stdout);
    }

    return EXIT_SUCCESS;
}
