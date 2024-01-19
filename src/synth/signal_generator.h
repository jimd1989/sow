#pragma once

#include <stdint.h>
#include <stdio.h>

#include "synth_init.h"

void synthesize(Synth *);
void playNote(Synth *, uint8_t, uint8_t);
void releaseNote(Synth *, uint8_t);
void synthStatus(FILE *, Synth *);
