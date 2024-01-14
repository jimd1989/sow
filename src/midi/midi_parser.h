#pragma once

#include <stdio.h>

#include "midi_init.h"

#define CHAN_MASK ((1 << 4) - 1)
#define CHAN_MATCH(X, Y) ((!(Y)) || (((X) & CHAN_MASK) == ((Y) - 1)))
#define IS_CMD(X, Y) (((X) ^ (Y)) < 16)
#define IS_NOTE_OFF(X) (IS_CMD(X, 128))
#define IS_NOTE_ON(X) (IS_CMD(X, 144))
#define IS_CC(X) (IS_CMD(X, 176))

void parseMidi(MidiParser *);
void midiStatus(FILE *, MidiParser *);
