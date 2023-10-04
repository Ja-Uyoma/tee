#include "tee.h"

#include <stdio.h>
#include <errno.h>
#include <getopt.h>

/// \brief Copy standard input to standard output
/// \param[in] buffer Storage location of data read from standard input
/// \param[in] bufsize The size of the buffer
/// \returns An int representing the error condition that occured
int echoToStdout(char buffer[], int const bufsize)
{
    int rv = 0;
    errno = 0;

    while (fgets(buffer, bufsize, stdin) != NULL) {
        if ((rv = fputs(buffer, stdout)) == EOF) {
            perror("fputs - could not write to standard output.");
            return rv;
        }
        
        continue;
    }

    if (ferror(stdin)) {
        rv = errno;
        perror("fgets - Could not read from standard input");
    }

    return rv;
}

/// \brief Print usage information
void printHelp(void)
{
    printf(
        "%s\n",
        "Usage: tee [OPTION]... [FILE]...\n"
        "Copy standard input to each FILE, and also to standard output.\n\n"
        "-a, --append               append to the given FILEs, do not overwrite\n"
        "-i, --ignore -interrupts   ignore interrupt signals\n"
        "-p                         diagnose errors writing to non pipes\n"
        "    --output-error[=MODE]  set behaviour on write error. See MODE below\n"
        "    --help                 display this help and exit\n"
        "    --version              output version information and exit\n\n"
        "MODE determines behaviour with write errors on the outputs:\n"
        "   'warn'          diagnose errors writing to any output\n"
        "   'warn-nopipe'   diagnose errors writing to any output not a pipe\n"
        "   'exit'          exit on error writing to any output\n"
        "   'exit-nopipe'   exit on error writing to any output not a pipe\n"
        "The default MODE for the -p option is 'warn-nopipe'.\n"
        "The default operation when --output-error is not specified, is to\n"
        "exit immediately on error writing to a pipe, and diagnose errors\n"
        "writing to non pipe outputs.\0"
    );
}

/// \brief Handle program options
/// \details This function changes the behaviour of the program depending on the options
/// provided by the user as inputs. 
/// For a full list of the options, call the program with option "--help"
/// \param[in] argc The number of command-line options passed to the program
/// \param[in] argv The array of command-line options passed to the program
void handleProgramOptions(int argc, char* const argv[argc + 1])
{
    static struct option const longOptions[] = {
        { .name = "help", .has_arg = no_argument, .flag = NULL, .val = 1 },
        { 0, 0, 0, 0 }
    };

    int currentOption = 0;
    int currentOptionIndex = 0;

    while ((currentOption = getopt_long(argc, argv, "", longOptions, &currentOptionIndex)) != -1) {
        switch (currentOption) {
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

    if (currentOption == -1 && optind < argc) {
        char buffer[256] = { '\0' };
        FILE* files[argc - optind];
        int optindCopy = optind;
        
        for (int i = 0; i < argc - optind; ++i) {
            files[i] = fopen(argv[optindCopy++], "w");

            if (!files[i]) {
                fprintf(stderr, "Could not open file %s\n", argv[optind]);
                continue;
            }
        }

        while (fgets(buffer, sizeof buffer, stdin) != NULL) {
            fputs(buffer, stdout);

            for (size_t i = 0; i < (sizeof files / sizeof files[0]); ++i) {
                if (files[i] != NULL) {
                    fputs(buffer, files[i]);
                }
            }
        }

        for (size_t i = 0; i < sizeof files / sizeof files[0]; ++i) {
            if (files[i] != NULL) {
                fclose(files[i]);
            }
        }
    }
}
