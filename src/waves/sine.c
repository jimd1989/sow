#include <limits.h>
#include <math.h>
#include <stdint.h>

#include "../utils/fixed_point.h"
#include "sine.h"
#include "wave_constants.h"

#define NEGATE(X, Y) (((Y) & (1 << 31)) ? (~(X) + 1) : (X))
#define BACKWARDS(X) ((X) & (1 << 30) ? ~(X) : (X))

/* Fractional section of a quarter sine's phase. Since the top two bits are used
 * to index the quadrants, this is (30 - n) rather than (32 - n). */
#define WAVE_SINE_FRAC_MASK ((1 << (30 - WAVE_SINE_BITS)) - 1)

/* Reciprocal of fixed point n is ((1 << 32) / n). For 20 bit frac mask, this
 * is 4096. This allows division against the mask via multiplication. */
#define WAVE_SINE_FRAC_RECP 4096

static F16_16 SINE_WAVE[WAVE_SINE_LEN] = {0};

/* For a sine cycle [-1, 1], draw a quarter curve [0, 1], here represented by
 * 16.16 fixed point values [0, SHRT_MAX] */
void makeSine(void) {
  int i = 0;
  double f = 0.0;
  for (; i < WAVE_SINE_LEN ; i++) {
    f = sin(M_PI_2 * ((double)i / (double)(WAVE_SINE_LEN - 1)));
    f *= (double)SHRT_MAX;
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
 * during interpolation between adjacent indices. The decimal portion b, along
 * with the unused (shifted) part of a, weights the linear interpolation. While 
 * indices are perfectly mirrored across quadrants, their final values will be 
 * different due to continued accumulation of this fractional part. */
F16_16 sine(UF16_16 phase) {
  int b = BACKWARDS(phase);
  int i = INDEX(b);
  F16_16 s1 = SINE_WAVE[i];
  F16_16 s2 = SINE_WAVE[i + 1];
  F16_16 r = f16_16_mult(b & WAVE_SINE_FRAC_MASK, WAVE_SINE_FRAC_RECP);
  r = f16_16_mult(s2 - s1, r);
  s1 += r;
  return NEGATE(s1, phase);
}
