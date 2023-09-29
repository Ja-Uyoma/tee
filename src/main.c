#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "tee.h"

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
