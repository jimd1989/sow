#include "../utils/fixed_point.h"
#include "synth_config.h"
#include "synth_init.h"

Synth synth(SynthConfig sc, F16_16 *buffer, size_t sizeFrames) {
  Synth s = {0};
  s.buffer = buffer;
  s.sizeFrames = sizeFrames;
  return s;
}
