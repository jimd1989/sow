#include <err.h>
#include <limits.h>

#include "../utils/fade.h"
#include "../utils/fixed_point.h"
#include "fade.h"

void testFade(void) {
  int i = 0;
  F16_16 output = 0;
  F16_16 expected = 0;
  float expectedF = 0.0f;
  float outputF = 1.0f;
  Fader fa = {0};
  warnx("faded values");
  setFadePeriod();
  warnx(" fading 256 times biases fader to 0.0");
  warnx("  fader balance begins at 1.0");
  expectedF = 1.0f;
  setFader(&fa, f16_16(100.0f));
  outputF = f16_16_float(fa.balance);
  if (outputF != expectedF) {
    errx(1, "expected %f; got %f", expectedF, outputF);
  }
  warnx("  fader balance is 0.5 after 128 iterations");
  expectedF = 0.5f;
  for (i = 0 ; i < 128 ; i++) {
    (void)popFader(&fa);
  }
  outputF = f16_16_float(fa.balance);
  if (outputF != expectedF) {
    errx(1, "expected %f; got %f", expectedF, outputF);
  }
  warnx("  fader balance is 0.0 after 256 iterations");
  expectedF = 0.0f;
  for (i = 128 ; i < 256 ; i++) {
    (void)popFader(&fa);
  }
  outputF = f16_16_float(fa.balance);
  if (outputF != expectedF) {
    errx(1, "expected %f; got %f", expectedF, outputF);
  }
  warnx(" resetting fader biases entirely towards old value");
  warnx("  fader returns old * 1.0 after reset");
  expected = f16_16(100.0f);
  setFader(&fa, f16_16(200.0f));
  output = fa.old;
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  fader returns old * 0.5 after 128 iterations");
  expected = f16_16(150.0f);
  for (i = 0 ; i < 128 ; i++) {
    output = popFader(&fa);
  }
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  fader returns old * 0.25 after 192 iterations");
  expected = f16_16(175.0f);
  for (i = 128 ; i < 192 ; i++) {
    output = popFader(&fa);
  }
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  fader returns old * 0.0 after 256 iterations");
  expected = f16_16(200.0f);
  for (i = 192 ; i < 256 ; i++) {
    output = popFader(&fa);
  }
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  fader returns old * 0.0 after 511 iterations");
  expected = f16_16(200.0f);
  for (i = 256 ; i < 511 ; i++) {
    output = popFader(&fa);
  }
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
}
