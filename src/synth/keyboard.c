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
  Key *ky;
  nrpnVal <<= kb->decimalShift;
  ky = &kb->keys[kb->currentKey];
  ky->tuning = nrpnVal;
  ky->inc = phaseIncrement(ky->freq * f16_16_float(ky->tuning));
}

void adjustTuningDecimal(Keyboard *kb, uint8_t shift) {
  kb->decimalShift = shift;
}

Keyboard keyboard() {
  uint8_t defaultDecimalShift = 5;
  uint8_t i = 0;
  Keyboard kb = {0};
  kb.decimalShift = defaultDecimalShift;
  for (; i < SYNTH_KEYS ; i++) {
    kb.keys[i].freq = hz(i);
    kb.keys[i].inc = phaseIncrement(kb.keys[i].freq);
    kb.keys[i].tuning = F16_16_ONE;
  }
  return kb;
}
