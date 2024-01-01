#include <limits.h>
#include <math.h>
#include <stdint.h>

#include "../utils/fixed_point.h"
#include "sine.h"
#include "synth_constants.h"

static F16_16 SINE_WAVE[SYNTH_WAVELEN] = {0};

/* For a sine cycle [-1, 1], draw a quarter curve [0, 1], here represented by
 * 16.16 fixed point values [0, SHRT_MAX] */
void makeSine(void) {
  int i = 0;
  float f = 0.0f;
  for (; i < SYNTH_WAVELEN ; i++) {
    f = (float)SHRT_MAX * sin(M_PI_2 * ((float)i / (float)(SYNTH_WAVELEN - 1)));
    SINE_WAVE[i] = f16_16(f);
  }
}

/* The integer part a of fixed point decimal a.b maps to the index of the sine
 * wavetable. When a overflows, the wavetable has been fully iterated across.
 * Since only one quarter of the sine is drawn, the top two bits of a are used
 * as special control values:
 *  - When the topmost bit of a is set, negate the wavetable value.
 *  - When the penultimate bit of a is set, invert the wavetable index.
 * All other bits of a are shifted right to represent the actual table index of
 * [0, 1023]. A 1024 index also exists, unreachable via this shift, that's used
 * during interpolation between adjacent indices. The decimal portion b weights 
 * the linear interpolation. While indices are perfectly mirrored across
 * quadrants, their final values will be different due to continued accumulation 
 * of this fractional part b. */
F16_16 sine(UF16_16 phase) {
  int i = INDEX(BACKWARDS(phase));
  F16_16 s1 = SINE_WAVE[i];
  F16_16 s2 = SINE_WAVE[i + 1];
  F16_16 r = F16_16_FRAC(phase);
  r = f16_16_mult(s2 - s1, r);
  s1 += r;
  return NEGATE(s1, phase);
}
