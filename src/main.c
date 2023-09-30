#include "tee.h"

#include <stdlib.h>

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
        handleProgramOptions(argc, argv);
    }

    return EXIT_SUCCESS;
}
