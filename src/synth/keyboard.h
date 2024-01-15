#pragma once

#include <stdint.h>

#include "../utils/fixed_point.h"
#include "synth_constants.h"

typedef struct Key {
  float   freq;
  F16_16  inc;
  F16_16  tuning;
  F1_16   vol; /* probably not needed */
} Key;

typedef struct Keyboard {
  uint8_t currentKey;
  uint8_t decimalShift;
  Key     keys[SYNTH_KEYS];
} Keyboard;

Keyboard keyboard(void);
void selectKey(Keyboard *, uint16_t);
void tuneKey(Keyboard *, F16_16);
void adjustTuningDecimal(Keyboard *, uint8_t);
