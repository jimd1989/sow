#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct MidiConfig {
  bool    enabled;
  size_t  chan;
} MidiConfig;

MidiConfig midiConfig(int, char **);
