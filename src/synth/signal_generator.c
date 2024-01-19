#include <stdio.h>

#include "../utils/fixed_point.h"
#include "events.h"
#include "keyboard.h"
#include "signal_generator.h"
#include "synth_constants.h"
#include "voices.h"

void playNote(Synth *sy, uint8_t note, uint8_t vel) {
  triggerVoice(&sy->voices, noteOn(&sy->keyboard, note, vel));
}

void releaseNote(Synth *sy, uint8_t note) {
  releaseVoice(&sy->voices, note);
}

void synthesize(Synth *sy) {
  playVoices(&sy->voices, sy->buffer, sy->sizeFrames);
}

void synthStatus(FILE *f, Synth *sy) {
  int i = 0;
  Key ky = {0};
  Keyboard *kb = &sy->keyboard;
  for (i = 0; i < SYNTH_KEYS ; i++) {
    ky = kb->keys[i];
    fprintf(f, "synth.keyboard.%d.freq=%f\n", i, ky.freq);
    fprintf(f, "synth.keyboard.%d.inc=%u\n", i, ky.inc);
    fprintf(f, "synth.keyboard.%d.tuning=%f\n", i, f16_16_float(ky.tuning));
  }
  fprintf(f, "synth.keyboard.decimalShift=%d\n", kb->decimalShift);
  fprintf(f, "synth.keyboard.selectedKey=%d\n", kb->currentKey);
  fprintf(f, "synth.voices.count=%zu\n", sy->polyphony);
}
