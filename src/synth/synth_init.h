#pragma once

#include <stdint.h>
#include <unistd.h>

#include "../utils/fixed_point.h"
#include "noise.h"
#include "synth_config.h"

typedef struct Synth {
  size_t    sizeFrames;
  F16_16  * buffer;
  Rng       noise;
} Synth;

Synth synth(SynthConfig, F16_16 *, size_t);
