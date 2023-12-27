#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "midi_config.h"

static size_t chan(char *);

static size_t chan(char *a) {
  int n = atoi(a);
  if (n < 0 || n > 16) {
    errx(1, "-chan must be between 0 and 16; provided %d", n);
  }
  return (size_t)n;
}

MidiConfig midiConfig(int argc, char **argv) {
  int i = 0;
  char *a = NULL;
  size_t defaultChan = 0;
  MidiConfig mc = {0};
  mc.chan = defaultChan;
  for (i = 1; i < argc ; i++) {
    a = argv[i];
    if (strcmp(a, "-midiChan") == 0) { mc.chan = chan(argv[++i]); }
  }
  return mc;
}
