#include <limits.h>
#include <math.h>
#include <stdint.h>

#include "../utils/fixed_point.h"
#include "sine.h"
#include "synth_constants.h"

#define NEGATE(X, Y) ((X) |= ((Y) & (1 << 31)))
#define BACKWARDS(X) ((X) & (1 << 30) ? ~(X) : (X))

static F16_16 SINE_WAVE[SYNTH_WAVELEN] = {0};

void makeSine(void) {
  int i = 0;
  float f = 0.0f;
  for (; i < SYNTH_WAVELEN ; i++) {
    f = sin(M_PI_2 * ((float)i / (float)(SYNTH_WAVELEN - 1)));
    SINE_WAVE[i] = (uint32_t)((float)INT_MAX * f);
  }
}

/* Needs F1_31 type */
F16_16 sine(F16_16 phase) {
  uint16_t n = F16_16_INT(BACKWARDS(phase));
  /* int16_t r = F16_16_FRAC(phase) use for lerp later */
  return NEGATE(SINE_WAVE[n >> SYNTH_WAVE_SHIFT], phase);
}
