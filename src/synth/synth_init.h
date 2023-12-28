#pragma once

#include <stdint.h>
#include <unistd.h>

#include "noise.h"
#include "synth_config.h"

typedef struct Synth {
  size_t    sizeFrames;
  int16_t * buffer;
  Rng       noise;
} Synth;

Synth synth(SynthConfig, int16_t *, size_t);
