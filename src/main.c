#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const* argv[argc + 1])
{
    (void) argc;
    (void) argv;

    char buffer[512] = { '\0' };

    while (!feof(stdin)) {
        fgets(buffer, sizeof(buffer), stdin);
        fputs(buffer, stdout);
    }

    return EXIT_SUCCESS;
}
