#include "signal_generator.h"

/* Delete later */
#include "phase.h"
#include "../utils/fixed_point.h"
#include "../waves/sine.h"
#include <unistd.h>

static UF16_16 PHASE = 0; /* Delete later */

void synthesize(Synth *s) {
  UF16_16 inc = phaseIncrement(220.0f);
  for (size_t i = 0 ; i < s->sizeFrames ; i++) {
    s->buffer[i] = sine(PHASE);
    PHASE += inc;
  }
}
