#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "audio_config.h"

static size_t rate(char *);
static size_t blocks(char *);
static size_t chan(char *);

static size_t rate(char *a) {
  int n = atoi(a);
  if (n < 1) {
    errx(1, "-rate must be greater than 0; provided %d", n);
  }
  return (size_t)n;
}

static size_t blocks(char *a) {
  int n = atoi(a);
  if (n < 1) {
    errx(1, "-blocks must be greater than 0; provided %d", n);
  }
  return (size_t)n;
}

static size_t chan(char *a) {
  int n = atoi(a);
  if (n < 0) {
    errx(1, "-chan must be greater than 0; provided %d", n);
  }
  return (size_t)n;
}

AudioConfig audioConfig(int argc, char **argv) {
  int i = 0;
  char *a = NULL;
  size_t defaultRate = 48000;
  size_t defaultBlocks = 1;
  size_t defaultChannels = 2;
  AudioConfig ac = {0};
  ac.rate = defaultRate;
  ac.blocks = defaultBlocks;
  ac.chan = defaultChannels;
  for (i = 1; i < argc; i++) {
    a = argv[i];
    if      (strcmp(a, "-rate") == 0)   { ac.rate = rate(argv[++i]);     }
    else if (strcmp(a, "-blocks") == 0) { ac.blocks = blocks(argv[++i]); }
    else if (strcmp(a, "-chan") == 0)   { ac.chan = chan(argv[++i]);     }
  }
  return ac;
}
