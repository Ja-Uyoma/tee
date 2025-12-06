#include <stdlib.h>

#include "tee.h"

int main(int argc, char* const argv[argc + 1])
{
  if (argc == 1) {
    int result = echo(stdin, stdout);

    if (result == -1) {
      return EXIT_FAILURE;
    }
  } else if (argc > 1) {
    handle_program_options(argc, argv);
  }

  return EXIT_SUCCESS;
}
