#pragma once

#include "../utils/fixed_point.h"
#include "synth_constants.h"

typedef struct Key {
  F16_16  inc;
  F16_16  tuning;
} Key;

typedef struct Keyboard {
  Key     keys[SYNTH_KEYS];
} Keyboard;

Keyboard keyboard(void);
