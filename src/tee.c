#include "tee.h"

#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/// \brief Read data from a source file and write it to a destination file
/// \param[in] src The source file
/// \param[in] dest The destination file
/// \returns The number of lines written to the destination file, or -1 if an
/// error occured
int echo(FILE *const src, FILE *const dest) {
  if (src == NULL || dest == NULL) {
    return -1;
  }

  static char buffer[256] = {'\0'};
  int result = 0;

  while (fgets(buffer, sizeof buffer, src) != NULL) {
    if ((result += fputs(buffer, dest)) == EOF) {
      perror("fputs - could not write to dest");
      break;
    }
  }

  if (ferror(src)) {
    result = -1;
    perror("fgets - could not read from src");
  }

  return result;
}

/// \brief Print usage information
void printHelp(void) {
  printf(
      "%s\n",
      "Usage: tee [OPTION]... [FILE]...\n"
      "Copy standard input to each FILE, and also to standard output.\n\n"
      "-a, --append               append to the given FILEs, do not overwrite\n"
      "-i, --ignore-interrupts    ignore interrupt signals\n"
      "-p                         diagnose errors writing to non pipes\n"
      "    --output-error[=MODE]  set behaviour on write error. See MODE "
      "below\n"
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
      "writing to non pipe outputs.\0");
}

/// \brief Handle any other non-option command-line arguments
/// \details This function opens the files passed in as command-line arguments
/// in write mode and then writes the text input from stdin to those files as
/// well as to stdout
///
/// \param[in] argc The number of command-line arguments
/// \param[in] argv The array containing the command-line arguments
static void handleNonOptionArguments(int argc, char *const argv[]);

/// \brief Handle program options
/// \details This function changes the behaviour of the program depending on the
/// options provided by the user as inputs. For a full list of the options, call
/// the program with option "--help" \param[in] argc The number of command-line
/// options passed to the program \param[in] argv The array of command-line
/// options passed to the program
void handleProgramOptions(int argc, char *const argv[]) {
  static struct option const longOptions[] = {
      {.name = "help", .has_arg = no_argument, .flag = NULL, .val = 1},
      {0, 0, 0, 0}};

  int currentOption = 0;
  int currentOptionIndex = 0;

  while ((currentOption = getopt_long(argc, argv, "", longOptions,
                                      &currentOptionIndex)) != -1) {
    switch (currentOption) {
    case 0:
      break;

    case 1:
      printHelp();
      break;

    default:
      abort();
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
    handleNonOptionArguments(argc, argv);
  }
}

/// \brief Null-initialize each element in the array of pointers to FILE
/// \param[inout] files The array of pointers to FILE
/// \param[in] arrayLength The length of the array
static void nullInitialiseArrayOfFilePointers(FILE *files[],
                                              size_t arrayLength);

/// \brief Handle any other non-option command-line arguments
/// \details This function opens the files passed in as command-line arguments
/// in write mode and then writes the text input from stdin to those files as
/// well as to stdout
///
/// \param[in] argc The number of command-line arguments
/// \param[in] argv The array containing the command-line arguments
static void handleNonOptionArguments(int argc, char *const argv[]) {
  char buffer[256] = {'\0'};
  size_t const numberOfFiles = argc - optind;
  FILE *files[numberOfFiles];

  nullInitialiseArrayOfFilePointers(files, numberOfFiles);

  int optindCopy = optind;

  for (size_t i = 0; i < numberOfFiles; ++i) {
    files[i] = fopen(argv[optindCopy++], "w");

    if (!files[i]) {
      fprintf(stderr, "Could not open file %s\n", argv[optind]);
      continue;
    }
  }

  while (fgets(buffer, sizeof buffer, stdin) != NULL) {
    fputs(buffer, stdout);

    for (size_t i = 0; i < numberOfFiles; ++i) {
      if (files[i]) {
        fputs(buffer, files[i]);
      }
    }
  }

  for (size_t i = 0; i < numberOfFiles; ++i) {
    if (files[i] != NULL) {
      fclose(files[i]);
    }
  }
}

/// \brief Null-initialize each element in the array of pointers to FILE
/// \param[inout] files The array of pointers to FILE
/// \param[in] arrayLength The length of the array
static void nullInitialiseArrayOfFilePointers(FILE *files[],
                                              size_t arrayLength) {
  for (size_t i = 0; i < arrayLength; ++i) {
    files[i] = NULL;
  }
}
