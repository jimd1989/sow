#include <stdint.h>

#include "../utils/fixed_point.h"
#include "keyboard.h"
#include "phase.h"
#include "pitch.h"
#include "synth_constants.h"

Keyboard keyboard() {
  uint8_t i = 0;
  Keyboard kb = {0};
  for (; i < SYNTH_KEYS ; i++) {
    kb.keys[i].inc = phaseIncrement(hz(i));
    kb.keys[i].tuning = F16_16_ONE;
  }
  return kb;
}
