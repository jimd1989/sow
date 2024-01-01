#pragma once

#include "../audio/audio_init.h"
#include "../midi/midi_parser.h"
#include "../synth/synth_init.h"

typedef struct IO {
  AudioWriter audio;
  MidiParser  midi;
  Synth       synth;
} IO;

IO io(int, char **);
void monitor(IO);
