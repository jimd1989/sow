#include "noise.h" /* Delete later */
#include "signal_generator.h"

void synthesize(Synth *s) {
  noise(&s->noise, s->buffer, s->sizeFrames); /* Delete later */
}
