#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/// \brief Print usage information
void printHelp();

int main(int argc, char const* argv[argc + 1])
{
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
    
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        printHelp();
    }

    return EXIT_SUCCESS;
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
