#pragma once

#include <unistd.h>

#include "../utils/fixed_point.h"
#include "synth_constants.h"

typedef struct Key {
  F16_16  freq;
  F16_16  inc;
  F16_16  tuning;
} Key;

typedef struct Keyboard {
  size_t  rate;
  size_t  size;
  Key     keys[SYNTH_KEYS];
} Keyboard;

Keyboard keyboard(size_t);
