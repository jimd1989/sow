#include "signal_generator.h"

/* Delete later */
#include "phase.h"
#include "../utils/fixed_point.h"
#include "../waves/sine.h"
#include <stdint.h>
#include <unistd.h>

#include <err.h>
#include <stdio.h>
#include <limits.h>

/* Delete later */
static UF16_16 PHASE = 0;
static UF16_16 INC = 0;

void setPitch(Synth *sy, uint8_t note) {
  INC = sy->keyboard.keys[note].inc;
}

void synthesize(Synth *sy, double *fuck) {
  //warnx("SYNTH %p", (void *)fuck);
  //INC = sy->keyboard.keys[42].inc;
  for (size_t i = 0 ; i < sy->sizeFrames ; i++) {
    sy->buffer[i] = sine(PHASE);
    //sy->floatBuffer[i] = sineF(PHASE);
    //printf("%u ", INC);
    fuck[i] = sineF(PHASE);
    //printf("%f %d\n", fuck[i], (int16_t)((float)SHRT_MAX * fuck[i]));
    //if (sy->floatBuffer[i] > 0.0) {
    //  warnx("%f", sy->floatBuffer[i]);
    //}
    PHASE += INC;
  }
}
