#include <err.h>
#include <math.h>

#include "../utils/fixed_point.h"
#include "../synth/sine.h"
#include "sine.h"

void testSine(void) {
  float outputF = 0.0f;
  float expectedF = 0.0f;
  warnx("sine wave");
  makeSine();
  warnx(" sine(π ÷ 2) = 1");
  expectedF = 1.0f;
  outputF = f16_16_float(sine(f16_16(M_PI / 2.0f)));
  if (outputF != expectedF) {
    errx(1, "expected %f; got %f", expectedF, outputF);
  }
}
