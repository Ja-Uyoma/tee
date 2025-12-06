#ifndef TEE_H
#define TEE_H

#include <stdio.h>

/// \brief Read data from a source file and write it to a destination file
/// \param[in] src The source file
/// \param[in] dest The destination file
/// \returns The number of lines written to the destination file, or -1 if an
/// error occured
int echo(FILE *const src, FILE *const dest);

/// \brief Print usage information
void printHelp(void);

/// \brief Handle program options
/// \details This function changes the behaviour of the program depending on the
/// options provided by the user as inputs. For a full list of the options, call
/// the program with option "--help" \param argc The number of command-line
/// options passed to the program \param argv The array of command-line options
/// passed to the program
void handleProgramOptions(int argc, char *const argv[]);

#endif
