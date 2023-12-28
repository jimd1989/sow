#include <err.h>
#include <limits.h>

#include "../utils/fixed_point.h"
#include "fixed_point.h"

void testFixedPoint(void) {
  F16_16 output = 0;
  F16_16 expected = 0;
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
}
