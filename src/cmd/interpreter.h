#pragma once

#include "../audio/audio_init.h"
#include "../midi/midi_init.h"
#include "../synth/synth_init.h"

void interpretCmds(MidiParser *, Synth *, AudioWriter *);
