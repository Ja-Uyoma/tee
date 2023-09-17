#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
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
        "%s\n%s\n\n",
        "Usage: tee [OPTION]... [FILE]...\0",
        "Copy standard input to each FILE, and also to standard output.\0"
    );
}
