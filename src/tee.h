#ifndef TEE_H
#define TEE_H

/// \brief Copy standard input to standard output
/// \param[in] buffer Storage location of data read from standard input
/// \param[in] bufsize The size of the buffer
/// \returns An int representing the error condition that occured
int echoToStdout(char buffer[], int const bufsize);

/// \brief Print usage information
void printHelp(void);

#endif
