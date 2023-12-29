#include <err.h>
#include <stdint.h>
#include <unistd.h>

#include "../synth/phase.h"
#include "../utils/fixed_point.h"
#include "phase.h"

void testPhase(void) {
  F16_16 output = 0;
  F16_16 expected = 0;
  int expectedI = 0;
  int outputI = 0;
  warnx("wave phase");
  warnx(" ");
  setPhase(48000);
  expectedI = 109;
  output = phaseIncrement(1.0f);
  warnx("INC %f", f16_16_float(output));
  outputI = (int)f16_16_float(phaseIncrement(440.0f));
  if (outputI != expectedI) {
    errx(1, "expected %d; got %d", expected, output);
  }
}
