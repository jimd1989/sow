#include "../utils/fixed_point.h"
#include "keyboard.h"
#include "synth_config.h"
#include "synth_constants.h"
#include "synth_init.h"
#include "voices.h"

void startSynth(Synth *sy, SynthConfig sc, F16_16 *buffer, size_t sizeFrames) {
  size_t defaultPolyphony = SYNTH_MAX_VOICES;
  sy->sizeFrames = sizeFrames;
  sy->polyphony = defaultPolyphony;
  sy->buffer = buffer;
  sy->keyboard = keyboard();
  startVoices(&sy->voices, defaultPolyphony);
}
