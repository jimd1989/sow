#include <stdint.h>

#include "../cmd/scaling.h"
#include "../utils/fixed_point.h"
#include "../waves/exp.h"
#include "volume.h"

#include <limits.h>
#include <err.h>

void setVolume(Fader *fa, int8_t n) {
  setFader(fa, expo(MIDI_CMD_TO_F16_16(n)));
}

int16_t mixVolume(Fader *fa, F16_16 s) {
  F16_16 v = F16_16_TO_F1_16(popFader(fa));
  return (int16_t)(f16_16_mult(s, v) >> F16_16_FRAC_BITS);
}

int16_t mixVolumeF(Fader *fa, double s) {
  double v = f16_16_float(F16_16_TO_F1_16(popFader(fa)));
  int16_t n = (double)SHRT_MAX * s * v;
  return n;
}
