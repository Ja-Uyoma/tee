#include "tee.h"

#include <stdlib.h>

int main(int argc, char *const argv[argc + 1]) {
  if (argc == 1) {
    int rv = echo(stdin, stdout);

    if (rv == -1) {
      return EXIT_FAILURE;
    }
  } else if (argc > 1) {
    handleProgramOptions(argc, argv);
  }

  return EXIT_SUCCESS;
}
