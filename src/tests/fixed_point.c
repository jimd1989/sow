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
    errx(1, "expected %.20f; got %.20f", expectedF, outputF);
  }
  warnx(" f16_16_float(f16_16(3.75)) = 3.75");
  expectedF = 3.75f;
  outputF = f16_16_float(f16_16(3.75f));
  if (outputF != expectedF) {
    errx(1, "expected %.20f; got %.20f", expectedF, outputF);
  }
  warnx(" f16_16_float(f16_16(-4.53)) ~= -4.53");
  expectedF = -4.529999f;
  outputF = f16_16_float(f16_16(-4.53f));
  if (outputF != expectedF) {
    errx(1, "expected %.20f; got %.20f", expectedF, outputF);
  }
  warnx(" f16_16_float(f16_16(440)) = 440");
  expectedF = 440.0f;
  outputF = f16_16_float(f16_16(440.0f));
  if (outputF != expectedF) {
    errx(1, "expected %.20f; got %.20f", expectedF, outputF);
  }
  warnx(" f16_16_float(f16_16_mult(440, 2)) = 880");
  expectedF = 880.0f;
  outputF = f16_16_float(f16_16_mult(f16_16(440.0f), f16_16(2.0f)));
  if (outputF != expectedF) {
    errx(1, "expected %.20f; got %.20f", expectedF, outputF);
  }
  warnx(" f16_16_float(f16_16_f1_16(SHRT_MAX)) ~= 1");
  expectedF = 0.999969482421875f;
  outputF = f16_16_float(F16_16_TO_F1_16(f16_16(SHRT_MAX)));
  if (outputF != expectedF) {
    errx(1, "expected %.20f; got %.20f", expectedF, outputF);
  }
  warnx(" f16_16_float(f16_16_f1_16(-SHRT_MAX)) ~= -1");
  expectedF = -0.999969482421875f;
  outputF = f16_16_float(F16_16_TO_F1_16(f16_16(-SHRT_MAX)));
  if (outputF != expectedF) {
    errx(1, "expected %.20f; got %.20f", expectedF, outputF);
  }
  warnx(" f16_16_float(f16_16_f1_16(SHRT_MAX ÷ 8)) ~= 0.125");
  expectedF = 0.124969482421875f;
  outputF = f16_16_float(F16_16_TO_F1_16(f16_16(SHRT_MAX / 8)));
  if (outputF != expectedF) {
    errx(1, "expected %.20f; got %.20f", expectedF, outputF);
  }
  warnx(" f16_16_float(f16_16_f1_16(-SHRT_MAX ÷ 8)) ~= -0.125");
  expectedF = -0.124969482421875f;
  outputF = f16_16_float(F16_16_TO_F1_16(f16_16(-SHRT_MAX / 8)));
  if (outputF != expectedF) {
    errx(1, "expected %.20f; got %.20f", expectedF, outputF);
  }
  warnx(" F16_16_FRAC(1.618) ~= 0.618");
  expectedF = 0.6179962158203125f;
  outputF = f16_16_float(F16_16_FRAC(f16_16(1.618f)));
  if (outputF != expectedF) {
    errx(1, "expected %.20f; got %.20f", expectedF, outputF);
  }
}
