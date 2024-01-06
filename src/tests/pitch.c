#include <err.h>
#include <stdint.h>

#include "../synth/pitch.h"
#include "pitch.h"

void testPitch(void) {
  float expectedF = 0.0f;
  float outputF = 0.0f;
  warnx("pitch");
  warnx(" MIDI note 69 ~= 440hz");
  expectedF = 440.000030517578125f;
  outputF = hz(69);
  if (outputF != expectedF) {
    errx(1, "expected %.20f; got %.20f", expectedF, outputF);
  }
}

