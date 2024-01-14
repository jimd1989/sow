#include <stdint.h>

#include "../utils/fixed_point.h"
#include "keyboard.h"
#include "phase.h"
#include "pitch.h"
#include "synth_constants.h"

void selectKey(Keyboard *kb, uint16_t nrpnVal) {
  kb->currentKey = nrpnVal >> 7;
}

void tuneKey(Keyboard *kb, F16_16 nrpnVal) {
  /* Decimal shift is probably wrong here. Needs to increase integer/fractional
   * resolutions when positive/negative respectively. Right shifting just loses
   * data. What actually needs to happen is a non-16.16 interpretation. 
   * Maybe okay actually? Consider a general formula. */
  Key *ky;
  if (kb->decimalShift < 0) { nrpnVal >>= kb->decimalShift; } 
  else                      { nrpnVal <<= kb->decimalShift; }
  ky = &kb->keys[kb->currentKey];
  ky->tuning = nrpnVal;
  ky->inc = phaseIncrement(ky->freq * f16_16_float(ky->tuning));
}

Keyboard keyboard() {
  int8_t defaultDecimalShift = 5;
  uint8_t i = 0;
  Keyboard kb = {0};
  kb.decimalShift = defaultDecimalShift;
  for (; i < SYNTH_KEYS ; i++) {
    kb.keys[i].freq = hz(i);
    kb.keys[i].inc = phaseIncrement(kb.keys[i].freq);
    kb.keys[i].tuning = F16_16_ONE;
    kb.keys[i].vol = F16_16_ONE;
  }
  return kb;
}
