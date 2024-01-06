#include "../utils/fixed_point.h"
#include "keyboard.h"
#include "synth_config.h"
#include "synth_init.h"

Synth synth(SynthConfig sc, F16_16 *buffer, size_t sizeFrames) {
  Synth sy = {0};
  sy.sizeFrames = sizeFrames;
  sy.polyphony = sc.voices;
  sy.buffer = buffer;
  sy.keyboard = keyboard();
  return sy;
}
