#pragma once

#include <stdint.h>
#include <unistd.h>

#include "../utils/fixed_point.h"
#include "keyboard.h"
#include "synth_config.h"
#include "voices.h"

typedef struct Synth {
  size_t      sizeFrames;
  size_t      polyphony;
  F16_16    * buffer;
  Keyboard    keyboard;
  Voices      voices;
} Synth;

void startSynth(Synth *, SynthConfig, F16_16 *, size_t);
