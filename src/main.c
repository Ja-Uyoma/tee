#include "tee.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>

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
        static struct option const longOptions[] = {
            { .name = "help", .has_arg = no_argument, .flag = NULL, .val = 1 },
            { 0, 0, 0, 0 }
        };

        int option = 0;
        int optionIndex = 0;

        while ((option = getopt_long(argc, argv, "", longOptions, &optionIndex)) != -1) {
            switch (option) {
            case 0:
                break;

            case 1:
                printHelp();
                break;

            default:
                break;
            }

            // Print any remaining command-line arguments (not options)
            if (optind < argc) {
                printf("\n\n%s", "Non-option argv elements: ");

                while (optind < argc) {
                    printf("%s", argv[optind++]);
                }

                puts("");
            }
        }
    }

    return EXIT_SUCCESS;
}
