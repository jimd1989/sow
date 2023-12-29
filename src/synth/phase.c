#include <limits.h>
#include <stdint.h>
#include <unistd.h>

#include "../utils/fixed_point.h"
#include "phase.h"

static F16_16 PHASE_STEP;

/* 1.  Regardless of decimal position, phase is represented by 32 bit integer.
 * 2.  An overflow represents a completed wave cycle.
 * 3.  A 440hz wave would overflow 440 times a second.
 * 4.  At 48k sample rate and 440hz, overflow every 109.0909090909091 samples.
 * 5.  For fixed point a.b, integer part a becomes the overflow target.
 * 6.  16.16 phase must overflow 65536 to complete a wave cycle.
 * 7.  At 48k rate, add 1.365311 per sample to overflow 65536 at 1hz. 
 * 8.  PHASE_STEP represents this 1hz increment.
 * 9.  At 48k rate, add 600.736694 per sample to overflow 65536 at 440hz.
 * 10. phaseIncrement(hz) provides fixed point increment for float hz. */

void setPhase(size_t rate) {
  float f = (float)F16_16_INT(UINT_MAX) / (float)rate;
  PHASE_STEP = f16_16(f);
}

F16_16 phaseIncrement(float freq) {
  return f16_16_mult(f16_16(freq), PHASE_STEP);
}
