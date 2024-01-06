#include "signal_generator.h"

/* Delete later */
#include "phase.h"
#include "../utils/fixed_point.h"
#include "../waves/sine.h"
#include <stdint.h>
#include <unistd.h>

/* Delete later */
static UF16_16 PHASE = 0;
static UF16_16 INC = 0;

void setPitch(Synth *sy, uint8_t note) {
  INC = sy->keyboard.keys[note].inc;
}

void synthesize(Synth *sy) {
  for (size_t i = 0 ; i < sy->sizeFrames ; i++) {
    sy->buffer[i] = sine(PHASE);
    PHASE += INC;
  }
}
