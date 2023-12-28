#include "noise.h"
#include "synth_config.h"
#include "synth_init.h"

Synth synth(SynthConfig sc, int16_t *buffer, size_t sizeFrames) {
  Synth s = {0};
  s.noise = rng();
  s.buffer = buffer;
  s.sizeFrames = sizeFrames;
  return s;
}
