#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/log.h"
#include "synth_config.h"
#include "synth_constants.h"

static size_t placeholder(char *);

static size_t placeholder(char *a) {
  int max = SYNTH_MAX_VOICES;
  int n = atoi(a);
  if (n < 1 || n > max) {
    errx(1, "-placeholder must be between 1 and %d; provided %d", max, n);
  }
  return (size_t)n;
}

SynthConfig synthConfig(int argc, char **argv) {
  int i = 0;
  char *a = NULL;
  SynthConfig sc = {0};
  for (i = 1; i < argc; i++) {
    a = argv[i];
    if (strcmp(a, "-log") == 0)      { logger(argv[++i]); }
  }
  return sc;
}
