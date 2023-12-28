#pragma once

#include "../audio/audio_init.h"
#include "../midi/midi_init.h"
#include "../synth/synth_init.h"

typedef struct IO {
  AudioWriter audio;
  MidiReader  midi;
  Synth       synth;
} IO;

IO io(int, char **);
void monitor(IO);
