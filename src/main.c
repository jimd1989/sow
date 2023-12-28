#include <err.h>
#include <stdio.h>

#include "io/io.h"

#ifdef TEST
  #include "tests/test.h"
#endif

int main(int argc, char **argv) {
  #ifdef TEST
  test();
  #else
  warnx("prod");
  IO x = io(argc, argv);
  monitor(x);
  #endif
  return 0;
}
