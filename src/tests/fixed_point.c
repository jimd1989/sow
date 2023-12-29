#include <err.h>
#include <limits.h>

#include "../utils/fixed_point.h"
#include "fixed_point.h"

void testFixedPoint(void) {
  F16_16 output = 0;
  F16_16 expected = 0;
  float outputF = 0.0f;
  float expectedF = 0.0f;
  warnx("fixed point numbers");
  warnx(" f16_16(0.25) = 16384");
  expected = 16384;
  output = f16_16(0.25f);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx(" f16_16(3.75) = 245760");
  expected = 245760;
  output = f16_16(3.75f);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx(" f16_16(-4.53) = -296878");
  expected = -296878;
  output = f16_16(-4.53f);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx(" f16_16(440) = 28835840");
  expected = 28835840;
  output = f16_16(440.0f);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx(" f16_16_float(f16_16(0.25)) = 0.25");
  expectedF = 0.25f;
  outputF = f16_16_float(f16_16(0.25f));
  if (outputF != expectedF) {
    errx(1, "expected %f; got %f", expectedF, outputF);
  }
  warnx(" f16_16_float(f16_16(3.75)) = 3.75");
  expectedF = 3.75f;
  outputF = f16_16_float(f16_16(3.75f));
  if (outputF != expectedF) {
    errx(1, "expected %f; got %f", expectedF, outputF);
  }
  warnx(" f16_16_float(f16_16(-4.53)) ~= -4.53");
  expectedF = -4.529999f;
  outputF = f16_16_float(f16_16(-4.53f));
  if (outputF != expectedF) {
    errx(1, "expected %f; got %f", expectedF, outputF);
  }
  warnx(" f16_16_float(f16_16(440)) = 440");
  expectedF = 440.0f;
  outputF = f16_16_float(f16_16(440.0f));
  if (outputF != expectedF) {
    errx(1, "expected %f; got %f", expectedF, outputF);
  }
  warnx(" f16_16_float(f16_16_mult(440, 2)) = 880");
  expectedF = 880.0f;
  outputF = f16_16_float(f16_16_mult(f16_16(440.0f), f16_16(2.0f)));
  if (outputF != expectedF) {
    errx(1, "expected %f; got %f", expectedF, outputF);
  }
  warnx(" f12_20_float(f12_20(1024.5)) = 1024.5");
  expectedF = 1024.5f;
  outputF = f12_20_float(f12_20(1024.5f));
  if (outputF != expectedF) {
    errx(1, "expected %f; got %f", expectedF, outputF);
  }
  warnx(" F12_20_INT(UINT_MAX) = 4095");
  expected = 4095;
  output = F12_20_INT(UINT_MAX);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
}
