#pragma once

#include <stdint.h>

#include "../utils/fixed_point.h"
#include "keyboard.h"

typedef struct NoteOn {
  uint8_t note;
  F16_16  inc;
  F16_16  vel;
} NoteOn;

NoteOn noteOn(Keyboard *, uint8_t, uint8_t);
