#include <limits.h>
#include <math.h>
#include <stdint.h>

#include "../utils/fixed_point.h"
#include "sine.h"
#include "wave_constants.h"

#include <err.h>
#include <stdio.h>

static F16_16 SINE_WAVE[WAVE_SINE_LEN] = {0};
static double SINE_WAVE_F[WAVE_SINE_LEN] = {0};

/* For a sine cycle [-1, 1], draw a quarter curve [0, 1], here represented by
 * 16.16 fixed point values [0, SHRT_MAX] */
void makeSine(void) {
  int i = 0;
  float f = 0.0f;
  for (; i < WAVE_SINE_LEN ; i++) {
    f = (float)SHRT_MAX * sin(M_PI_2 * ((float)i / (float)(WAVE_SINE_LEN - 1)));
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
  //F16_16 r = F16_16_FRAC(phase);
  uint32_t MASK = ((1 << (30 - 10)) - 1);
  //0.00000095367522590182
  //0.00001525902189669642
  float x = (BACKWARDS(phase) & MASK) / (float)MASK;
  F16_16 r = f16_16_mult(s2 - s1, f16_16(x));
  //F16_16 xx = f16_16_mult(F16_16_FRAC(BACKWARDS(phase)), f16_16(0.00001525902189669642f));
  //F16_16 xx = (int32_t)(F16_16_TO_F1_16((int64_t)(F16_16_FRAC(BACKWARDS(phase)) << 16) / f16_16(F16_16_FRAC_MASK)));
  F16_16 xx = f16_16_mult(BACKWARDS(phase) & 1048575, 4096);
  F16_16 rr = f16_16_mult(s2 - s1, xx);
  //warnx("%u %u %f", f16_16(x), xx, f16_16_float(128));
  //warnx("%f %f", f16_16_float(xx), f16_16_float(f16_16_mult(xx, F16_16_FRAC_MASK)));
  //warnx("%u\t%u\t%u\t%u\t%f\t%f", f16_16(x), r, xx, rr, f16_16_float(r), f16_16_float(rr)); 
  //F16_16 recp = f16_16(0.95367522590182f);
  //F16_16 r = f16_16_mult(BACKWARDS(phase) & MASK, recp);
  //r = f16_16_mult(s2 - s1, r);
  s1 += rr;
  return NEGATE(s1, phase);
}

void makeSineF(void) {
  int i;
  for (i = 0; i < WAVE_SINE_LEN ; i++) {
    SINE_WAVE_F[i] = sin(M_PI_2 * (i / (double)(WAVE_SINE_LEN - 1)));
  }
}

double sineF(UF16_16 phase) {
  int i = INDEX(BACKWARDS(phase));
  //printf("%u %d ", phase, i);
  double s = SINE_WAVE_F[i];
  double s2 = SINE_WAVE_F[i + 1];
  float x = (BACKWARDS(phase) & ((1 << (30 - 10)) - 1)) / (float) (1 << (30 - 10));
  s = s + ((s2 - s) * x);
  double neg = (phase & (1 << 31)) ? -1.0 : 1.0;
  return neg * s;
}
