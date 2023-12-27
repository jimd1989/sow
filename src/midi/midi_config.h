#pragma once

#include <stdlib.h>

typedef struct MidiConfig {
  size_t  chan;
} MidiConfig;

MidiConfig midiConfig(int, char **);
