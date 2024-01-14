#pragma once

#include "../audio/audio_init.h"
#include "../midi/midi_init.h"

void statusReport(AudioWriter *, MidiParser *);
void logger(char *);
void killLogger(void);
