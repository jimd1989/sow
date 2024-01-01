#include <err.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "midi_config.h"

static bool enabled(char *);
static size_t chan(char *);

static bool enabled(char *a) {
  return !(strcmp(a, "off") == 0);
}

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
  bool defaultEnabled = true;
  size_t defaultChan = 0;
  MidiConfig mc = {0};
  mc.enabled = defaultEnabled;
  mc.chan = defaultChan;
  for (i = 1; i < argc ; i++) {
    a = argv[i];
    if      (strcmp(a, "-midiChan") == 0) { mc.chan = chan(argv[++i]);       }
    else if (strcmp(a, "-midi") == 0)     { mc.enabled = enabled(argv[++i]); }
  }
  return mc;
}
