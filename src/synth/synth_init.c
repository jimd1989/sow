#include "../utils/fixed_point.h"
#include "keyboard.h"
#include "synth_config.h"
#include "synth_init.h"

#include <err.h>

Synth synth(SynthConfig sc, F16_16 *buffer, size_t sizeFrames, double *fb) {
  Synth sy = {0};
  //warnx("INIT SYNTH WITH %p", (void *)fb);
  sy.sizeFrames = sizeFrames;
  sy.polyphony = sc.voices;
  sy.buffer = buffer;
  sy.floatBuffer = fb;
  sy.keyboard = keyboard();
  return sy;
}
