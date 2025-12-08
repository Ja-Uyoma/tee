#include "tee.h"

#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

///
/// \brief Read data from a source file and write it to a destination file
/// \param[in] src The source file
/// \param[in] dest The destination file
/// \returns 0 on success, or -1 on failure
///
int echo(FILE* const src, FILE* const dest)
{
  if (src == NULL || dest == NULL) {
    return -1;
  }

#define BUFFER_SIZE 256

  char buffer[BUFFER_SIZE] = {'\0'};
  int result = 0;

  while (fgets(buffer, sizeof buffer, src) != NULL) {
    if (fputs(buffer, dest) == EOF) {
      perror("fputs - could not write to destination file");
      break;
    }
  }

  if (ferror(src)) {
    result = -1;
    perror("fgets - could not read from source file");
  }

#undef BUFFER_SIZE

  return result;
}

///
/// \brief Print usage information
///
void print_help(void)
{
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

///
/// \brief Print program version
///
void print_version(void)
{
  puts("tee v0.1");
}

///
/// \brief Handle any other non-option command-line arguments
///
/// This function opens the files passed in as command-line arguments
/// in write mode and then writes the text input from stdin to those files as
/// well as to stdout
///
/// \param[in] argc The number of command-line arguments
/// \param[in] argv The array containing the command-line arguments
///
static void handle_non_option_arguments(int argc, char* const argv[static 1]);

///
/// \brief Handle program options
///
/// This function changes the behaviour of the program depending on the
/// options provided by the user as inputs. For a full list of the options, call
/// the program with option "--help" \param[in] argc The number of command-line
/// options passed to the program \param[in] argv The array of command-line
/// options passed to the program
///
/// \param[in] argc The number of command-line arguments passed to the application
/// \param[in] argv An array of actual command-line arguments passed to the application
///
void handle_program_options(int argc, char* const argv[static 1])
{
  static struct option const long_options[] = {
      {.name = "help", .has_arg = no_argument, .flag = NULL, .val = 1},
      {.name = "version", .has_arg = no_argument, .flag = NULL, .val = 2},
      {0, 0, 0, 0}};

  int curr_option = 0;
  int curr_option_idx = 0;

  while ((curr_option = getopt_long(argc, argv, "", long_options, &curr_option_idx)) != -1) {
    switch (curr_option) {
      case 0:
        break;

      case 1:
        print_help();
        break;

      case 2:
        print_version();
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

  if (curr_option == -1 && optind < argc) {
    handle_non_option_arguments(argc, argv);
  }
}

///
/// \brief Null-initialize each element in the array of pointers to FILE
/// \param[in,out] files The array of pointers to FILE
/// \param[in] array_len The length of the array
///
static void null_initialise_array_of_file_pointers(FILE* files[static 1], size_t array_len);

///
/// \brief Handle any other non-option command-line arguments
///
/// This function opens the files passed in as command-line arguments
/// in write mode and then writes the text input from stdin to those files as
/// well as to stdout
///
/// \param[in] argc The number of command-line arguments
/// \param[in] argv The array containing the command-line arguments
///
static void handle_non_option_arguments(int argc, char* const argv[static 1])
{
#define BUFFER_SIZE 256

  char buffer[BUFFER_SIZE] = {'\0'};
  size_t const num_of_files = argc - optind;
  FILE* files[num_of_files];

  null_initialise_array_of_file_pointers(files, num_of_files);

  int optind_copy = optind;

  for (size_t i = 0; i < num_of_files; ++i) {
    files[i] = fopen(argv[optind_copy++], "w");

    if (!files[i]) {
      fprintf(stderr, "Could not open file %s\n", argv[optind]);
      continue;
    }
  }

  while (fgets(buffer, sizeof buffer, stdin) != NULL) {
    fputs(buffer, stdout);

    for (size_t i = 0; i < num_of_files; ++i) {
      if (files[i]) {
        fputs(buffer, files[i]);
      }
    }
  }

  for (size_t i = 0; i < num_of_files; ++i) {
    if (files[i] != NULL) {
      fclose(files[i]);
    }
  }

#undef BUFFER_SIZE
}

///
/// \brief Null-initialize each element in the array of pointers to FILE
/// \param[inout] files The array of pointers to FILE
/// \param[in] array_len The length of the array
///
static void null_initialise_array_of_file_pointers(FILE* files[static 1], size_t array_len)
{
  for (size_t i = 0; i < array_len; ++i) {
    files[i] = NULL;
  }
}
