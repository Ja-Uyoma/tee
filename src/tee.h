#ifndef TEE_H
#define TEE_H

/// \brief Copy standard input to standard output
/// \param[in] buffer Storage location of data read from standard input
/// \param[in] bufsize The size of the buffer
/// \returns The number of bytes written or errno if an error occured
int echoToStdout(char buffer[], int const bufsize);

/// \brief Print usage information
void printHelp(void);

/// \brief Handle program options
/// \details This function changes the behaviour of the program depending on the options
/// provided by the user as inputs. 
/// For a full list of the options, call the program with option "--help"
/// \param argc The number of command-line options passed to the program
/// \param argv The array of command-line options passed to the program
void handleProgramOptions(int argc, char* const argv[]);

#endif
