#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/// \brief Copy standard input to standard output
/// \param[in] buffer Storage location of data read from standard input
/// \param[in] bufsize The size of the buffer
/// \returns An int representing the error condition that occured
int echoToStdout(char buffer[], int const bufsize);

/// \brief Print usage information
void printHelp();

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
void printHelp()
{
    printf(
        "%s\n%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
        "Usage: tee [OPTION]... [FILE]...\0",
        "Copy standard input to each FILE, and also to standard output.\0",
        "-a, --append               append to the given FILEs, do not overwrite\0",
        "-i, --ignore -interrupts   ignore interrupt signals\0",
        "-p                         diagnose errors writing to non pipes\0",
        "    --output-error[=MODE]  set behaviour on write error. See MODE below\0",
        "    --help                 display this help and exit\0",
        "    --version              output version information and exit\0",
        "MODE determines behaviour with write errors on the outputs:\0",
        "   'warn'          diagnose errors writing to any output\0",
        "   'warn-nopipe'   diagnose errors writing to any output not a pipe\0",
        "   'exit'          exit on error writing to any output\0",
        "   'exit-nopipe'   exit on error writing to any output not a pipe\0",
        "The default MODE for the -p option is 'warn-nopipe'.\0",
        "The default operation when --output-error is not specified, is to\0",
        "exit immediately on error writing to a pipe, and diagnose errors\0",
        "writing to non pipe outputs.\0"
    );
}
