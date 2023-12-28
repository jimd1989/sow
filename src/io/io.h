#pragma once

#include "../audio/audio_init.h"
#include "../midi/midi_init.h"

typedef struct IO {
  AudioWriter audio;
  MidiReader  midi;
} IO;

IO io(int, char **);
void monitor(IO);
