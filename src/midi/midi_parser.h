#pragma once

#include "midi_init.h"

#define CHAN_MASK ((1 << 4) - 1)
#define CHAN_MATCH(X, Y) ((!(Y)) || (((X) & CHAN_MASK) == ((Y) - 1)))

void parseMidi(MidiParser *);
