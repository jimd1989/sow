#include <math.h>
#include <stdint.h>

#include "../utils/fixed_point.h"
#include "sine.h"
#include "synth_constants.h"

static F16_16 SINE_WAVE[SYNTH_WAVELEN] = {0};

/* For a sine cycle [-1, 1], draw a quarter curve [0, 1] */
void makeSine(void) {
  int i = 0;
  float f = 0.0f;
  for (; i < SYNTH_WAVELEN ; i++) {
    f = sin(M_PI_2 * ((float)i / (float)(SYNTH_WAVELEN - 1)));
    SINE_WAVE[i] = f16_16(f);
  }
}

F16_16 sine(UF24_8 phase) {
  /* Still need:
   *   negation
   *   backwards
   *   fractional lerp */
  int i = INDEX(phase);
  return SINE_WAVE[i];
}
