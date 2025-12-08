#ifndef TEE_H
#define TEE_H

#include <stdio.h>

///
/// \brief Read data from a source file and write it to a destination file
/// \param[in] src The source file
/// \param[in] dest The destination file
/// \returns The number of lines written to the destination file, or -1 if an
/// error occured
///
int echo(FILE* src, FILE* dest);

///
/// \brief Print usage information
///
void print_help(void);

///
/// \brief Print program version
///
void print_version(void);

/// \brief Handle program options
///
/// This function changes the behaviour of the program depending on the
/// options provided by the user as inputs. For a full list of the options, call
/// the program with option "--help" \param argc The number of command-line
/// options passed to the program \param argv The array of command-line options
/// passed to the program
///
/// \param[in] argc The number of command-line arguments passed to the application
/// \param[in] argv An array of actual command-line arguments passed to the application
///
void handle_program_options(int argc, char* const argv[argc + 1]);

#endif
