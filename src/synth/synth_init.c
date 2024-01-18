#include "../utils/fixed_point.h"
#include "keyboard.h"
#include "synth_config.h"
#include "synth_constants.h"
#include "synth_init.h"
#include "voices.h"

Synth synth(SynthConfig sc, F16_16 *buffer, size_t sizeFrames) {
  size_t defaultPolyphony = SYNTH_MAX_VOICES;
  Synth sy = {0};
  sy.sizeFrames = sizeFrames;
  sy.polyphony = defaultPolyphony;
  sy.buffer = buffer;
  sy.keyboard = keyboard();
  sy.voices = voices(defaultPolyphony);
  return sy;
}
