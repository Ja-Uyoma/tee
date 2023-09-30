#include "tee.h"

#include <stdlib.h>
#include <string.h>

int main(int argc, char* const argv[argc + 1])
{
    char buffer[512] = { '\0' };

    if (argc == 1) {
        int rv = echoToStdout(buffer, sizeof buffer);

        if (rv != 0) {
            return EXIT_FAILURE;
        }
    }
    else if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0) {
            printHelp();
        }
    }

    return EXIT_SUCCESS;
}
