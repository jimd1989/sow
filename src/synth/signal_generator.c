#include "noise.h" /* Delete later */
#include "signal_generator.h"

/* Delete later */
#include "phase.h"
#include "sine.h"
#include "../utils/fixed_point.h"
#include <unistd.h>

static UF16_16 PHASE = 0; /* Delete later */

void synthesize(Synth *s) {
  UF16_16 inc = phaseIncrement(220.0f);
  for (size_t i = 0 ; i < s->sizeFrames ; i++) {
    s->buffer[i] = f16_16_mult(sine(PHASE), f16_16(0.07f));
    PHASE += inc;
  }
  //noise(&s->noise, s->buffer, s->sizeFrames); /* Delete later */
}
