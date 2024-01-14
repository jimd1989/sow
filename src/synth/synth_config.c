#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/log.h"
#include "synth_config.h"
#include "synth_constants.h"

static size_t voices(char *);

static size_t voices(char *a) {
  int max = SYNTH_MAX_VOICES;
  int n = atoi(a);
  if (n < 1 || n > max) {
    errx(1, "-voices must be between 1 and %d; provided %d", max, n);
  }
  return (size_t)n;
}

SynthConfig synthConfig(int argc, char **argv) {
  int i = 0;
  char *a = NULL;
  size_t defaultVoices = SYNTH_MAX_VOICES;
  SynthConfig sc = {0};
  sc.voices = defaultVoices;
  for (i = 1; i < argc; i++) {
    a = argv[i];
    if      (strcmp(a, "-voices") == 0)   { sc.voices = voices(argv[++i]); }
    else if (strcmp(a, "-log") == 0)      { logger(argv[++i]);             }
  }
  return sc;
}
