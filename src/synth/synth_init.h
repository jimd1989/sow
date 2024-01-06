#pragma once

#include <stdint.h>
#include <unistd.h>

#include "../utils/fixed_point.h"
#include "keyboard.h"
#include "synth_config.h"

typedef struct Synth {
  size_t      sizeFrames;
  size_t      polyphony;
  F16_16    * buffer;
  Keyboard    keyboard;
} Synth;

Synth synth(SynthConfig, F16_16 *, size_t);
