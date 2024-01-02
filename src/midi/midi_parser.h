#pragma once

#include "midi_init.h"

#define CHAN_MASK ((1 << 4) - 1)
#define CHAN_MATCH(X, Y) ((!(Y)) || (((X) & CHAN_MASK) == ((Y) - 1)))
#define CC_START 176
#define IS_CC(X) (((X) & CC_START) == CC_START)

/* Well-known CC numbers map directly to the internal sow Cmd enum where
 * possible. All non-standard CC numbers are mapped to their respective commands
 * here. */
//typedef enum CmdCC {
//} MidiCC;

void parseMidi(MidiParser *);
