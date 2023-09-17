#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const* argv[argc + 1])
{
    (void) argv;

    char buffer[512] = { '\0' };

    if (argc == 1) {
        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            fputs(buffer, stdout);
        }

        if (ferror(stdin)) {
            perror("fgets - Could not read from standard input.");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
