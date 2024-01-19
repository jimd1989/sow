#include <err.h>
#include <stdio.h>

#include "io/io.h"

#ifdef TEST
  #include "tests/test.h"
#endif

#ifdef TEST
int main() { 
  test(); 
  return 0; 
}
#else
int main(int argc, char **argv) {
  warnx("prod");
  IO x = {0};
  startIO(&x, argc, argv);
  monitor(&x);
  return 0;
}
#endif
