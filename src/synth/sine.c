#include <limits.h>
#include <math.h>
#include <stdint.h>

#include "sine.h"
#include "synth_constants.h"

static uint32_t NEGATE = (1 << 31);
static uint32_t BACKWARDS = (1 << 30);
static int16_t SINE_WAVE[SYNTH_WAVELEN] = {0};

void makeSine(void) {
  int i = 0;
  for (; i < SYNTH_WAVELEN ; i++) {
    SINE_WAVE[i] = SHRT_MAX * sin(M_PI_2 * (i / (float)(SYNTH_WAVELEN - 1)));
  }
}

int16_t sine(uint32_t phase) {
  /* Needs lots of tweaking */
  int16_t sign = phase & NEGATE ? -1 : 1; /* Can use |= */
  uint32_t directedPhase = phase & BACKWARDS ? ~phase : phase;
  return sign * SINE_WAVE[directedPhase >> SYNTH_SHIFT];
}
