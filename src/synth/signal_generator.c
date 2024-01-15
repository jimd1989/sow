#include <stdio.h>

#include "../utils/fixed_point.h"
#include "keyboard.h"
#include "signal_generator.h"
#include "synth_constants.h"

/* Delete later */
#include "phase.h"
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

void synthStatus(FILE *f, Synth *sy) {
  int i = 0;
  Key ky = {0};
  Keyboard *kb = &sy->keyboard;
  for (i = 0; i < SYNTH_KEYS ; i++) {
    ky = kb->keys[i];
    fprintf(f, "synth.keyboard.%d.freq=%f\n", i, ky.freq);
    fprintf(f, "synth.keyboard.%d.inc=%u\n", i, ky.inc);
    fprintf(f, "synth.keyboard.%d.tuning=%f\n", i, f16_16_float(ky.tuning));
    fprintf(f, "synth.keyboard.%d.inc=%d\n", i, ky.vol >> 24);
  }
  fprintf(f, "synth.keyboard.decimalShift=%d\n", kb->decimalShift);
  fprintf(f, "synth.keyboard.selectedKey=%d\n", kb->currentKey);
  fprintf(f, "synth.voices.count=%zu\n", sy->polyphony);
}
