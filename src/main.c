#include "tee.h"

#include <stdlib.h>
#include <string.h>

int main(int argc, char const* argv[argc + 1])
{
    char buffer[512] = { '\0' };

    if (argc == 1) {
        int rv = echoToStdout(buffer, sizeof(buffer));

        if (rv != 0) {
            return EXIT_FAILURE;
        }
    }
    
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        printHelp();
    }

    return EXIT_SUCCESS;
}
