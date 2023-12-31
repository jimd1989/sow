#include <err.h>
#include <stdint.h>
#include <stdlib.h>

#include "../synth/phase.h"
#include "../utils/fixed_point.h"
#include "../waves/sine.h"
#include "sine.h"

#define EXCEEDS_EPSILON(X, Y, E) (abs((X) - (Y)) > E)
#define SINE_EPSILON 25

void testSine(void) {
  int i = 0;
  UF16_16 inc = 0;
  UF16_16 phase = 0;
  uint32_t output = 0;
  uint32_t expected = 0;
  F16_16 expected16 = 0;
  F16_16 output16 = 0;
  float expectedF = 0.0f;
  float outputF = 0.0f;
  warnx("sine wave");
  makeSine();
  warnx(" 4096 rate and 1hz pitch maps to wavetable indices");
  setPhase(4096);
  inc = phaseIncrement(1.0f);
  warnx("  after 0.25 seconds, reach end of wavetable");
  for (i = 0 ; i < 1024 ; i++) {
    phase += inc;
  }
  expected = 1023;
  output = INDEX(phase);
  if (output != expected) {
    errx(1, "expected %u; got %u", expected, output);
  }
  warnx("  after 0.25 + ε seconds, wrap to start of wavetable");
  phase = 0;
  for (i = 0 ; i < 1025 ; i++) {
    phase += inc;
  }
  expected = 0;
  output = INDEX(phase);
  if (output != expected) {
    errx(1, "expected %u; got %u", expected, output);
  }
  warnx("  after 0.5 seconds, reach end of wavetable again");
  phase = 0;
  for (i = 0 ; i < 2048 ; i++) {
    phase += inc;
  }
  expected = 1023;
  output = INDEX(phase);
  if (output != expected) {
    errx(1, "expected %u; got %u", expected, output);
  }
  warnx("  after 0.75 seconds, reach end of wavetable again");
  phase = 0;
  for (i = 0 ; i < 3072 ; i++) {
    phase += inc;
  }
  expected = 1023;
  output = INDEX(phase);
  if (output != expected) {
    errx(1, "expected %u; got %u", expected, output);
  }
  warnx("  after 1.0 + ε seconds, wrap to start of wavetable");
  phase = 0;
  for (i = 0 ; i < 4097 ; i++) {
    phase += inc;
  }
  expected = 0;
  output = INDEX(phase);
  if (output != expected) {
    errx(1, "expected %u; got %u", expected, output);
  }
  warnx(" wavetable only represents ¼ cycle: [0, 1]");
  warnx("  SINE_WAVE[0] = 0.0f");
  phase = 0;
  expectedF = 0.0f;
  outputF = f16_16_float(F16_16_TO_F1_16(sine(phase)));
  if (outputF != expectedF) {
    errx(1, "expected %.20f; got %.20f", expectedF, outputF);
  }
  warnx("  SINE_WAVE[1023] ~= 1.0f");
  phase = 0;
  for (i = 0 ; i < 1024 ; i++) {
    phase += inc;
  }
  expectedF = 0.9999542236328125f;
  outputF = f16_16_float(F16_16_TO_F1_16(sine(phase)));
  if (outputF != expectedF) {
    errx(1, "expected %.20f; got %.20f", expectedF, outputF);
  }
  warnx(" mirror wavetable index for second quadrant of a cycle: [1, 0]");
  warnx("  sine(1537) ~= sine(510)");
  phase = 0;
  for (i = 0; i < 511 ; i++) {
    phase += inc;
  }
  expected16 = F16_16_INT(sine(phase));
  phase = 0;
  for (i = 0; i < 1538 ; i++) {
    phase += inc;
  }
  output16 = F16_16_INT(sine(phase));
  if (EXCEEDS_EPSILON(expected16, output16, SINE_EPSILON)) {
    errx(1, "expected %d; got %d", expected16, output16);
  }
  warnx("  sine(1536) ~= sine(511)");
  phase = 0;
  for (i = 0; i < 512 ; i++) {
    phase += inc;
  }
  expected16 = F16_16_INT(sine(phase));
  phase = 0;
  for (i = 0; i < 1537 ; i++) {
    phase += inc;
  }
  output16 = F16_16_INT(sine(phase));
  if (EXCEEDS_EPSILON(expected16, output16, SINE_EPSILON)) {
    errx(1, "expected %d; got %d", expected16, output16);
  }
  warnx("  sine(1535) ~= sine(512)");
  phase = 0;
  for (i = 0; i < 513 ; i++) {
    phase += inc;
  }
  expected16 = F16_16_INT(sine(phase));
  phase = 0;
  for (i = 0; i < 1536 ; i++) {
    phase += inc;
  }
  output16 = F16_16_INT(sine(phase));
  if (EXCEEDS_EPSILON(expected16, output16, SINE_EPSILON)) {
    errx(1, "expected %d; got %d", expected16, output16);
  }
  warnx(" negate sample for third quadrant of a cycle: [-0, -1]");
  warnx("  NEGATE(100, (1 << 31)) = -100");
  expected16 = F16_16_INT(f16_16(-100.0f));
  output16 = F16_16_INT(NEGATE(f16_16(100.0f), (1 << 31)));
  if (output16 != expected16) {
    errx(1, "expected %d; got %d", expected16, output16);
  }
  warnx("  NEGATE(100, (1 << 30)) = 100");
  expected16 = F16_16_INT(f16_16(100.0f));
  output16 = F16_16_INT(NEGATE(f16_16(100.0f), (1 << 30)));
  if (output16 != expected16) {
    errx(1, "expected %d; got %d", expected16, output16);
  }
  warnx("  sine(2049) ~= -sine(1)");
  phase = 0;
  for (i = 0; i < 2050 ; i++) {
    phase += inc;
  }
  expected16 = F16_16_INT(f16_16_mult(f16_16(-1.0f), sine(phase)));
  phase = 0;
  for (i = 0; i < 2 ; i++) {
    phase += inc;
  }
  output16 = F16_16_INT(sine(phase));
  if (EXCEEDS_EPSILON(expected16, output16, SINE_EPSILON)) {
    errx(1, "expected %d; got %d", expected16, output16);
  }
  warnx("  sine(2559) ~= -sine(511)");
  phase = 0;
  for (i = 0; i < 2560 ; i++) {
    phase += inc;
  }
  expected16 = F16_16_INT(f16_16_mult(f16_16(-1.0f), sine(phase)));
  phase = 0;
  for (i = 0; i < 512 ; i++) {
    phase += inc;
  }
  output16 = F16_16_INT(sine(phase));
  if (EXCEEDS_EPSILON(expected16, output16, SINE_EPSILON)) {
    errx(1, "expected %d; got %d", expected16, output16);
  }
  warnx("  sine(2560) ~= -sine(512)");
  phase = 0;
  for (i = 0; i < 2561 ; i++) {
    phase += inc;
  }
  expected16 = F16_16_INT(f16_16_mult(f16_16(-1.0f), sine(phase)));
  phase = 0;
  for (i = 0; i < 513 ; i++) {
    phase += inc;
  }
  output16 = F16_16_INT(sine(phase));
  if (EXCEEDS_EPSILON(expected16, output16, SINE_EPSILON)) {
    errx(1, "expected %d; got %d", expected16, output16);
  }
  warnx("  sine(2561) ~= -sine(513)");
  phase = 0;
  for (i = 0; i < 2562 ; i++) {
    phase += inc;
  }
  expected16 = F16_16_INT(f16_16_mult(f16_16(-1.0f), sine(phase)));
  phase = 0;
  for (i = 0; i < 514 ; i++) {
    phase += inc;
  }
  output16 = F16_16_INT(sine(phase));
  if (EXCEEDS_EPSILON(expected16, output16, SINE_EPSILON)) {
    errx(1, "expected %d; got %d", expected16, output16);
  }
  warnx(" negate and mirror sample for fourth quadrant of a cycle: [-1, -0]");
  warnx("  sine(3581) ~= -sine(513)");
  phase = 0;
  for (i = 0; i < 3582 ; i++) {
    phase += inc;
  }
  expected16 = F16_16_INT(f16_16_mult(f16_16(-1.0f), sine(phase)));
  phase = 0;
  for (i = 0; i < 514 ; i++) {
    phase += inc;
  }
  output16 = F16_16_INT(sine(phase));
  if (EXCEEDS_EPSILON(expected16, output16, SINE_EPSILON)) {
    errx(1, "expected %d; got %d", expected16, output16);
  }
  warnx("  sine(3582) ~= -sine(512)");
  phase = 0;
  for (i = 0; i < 3583 ; i++) {
    phase += inc;
  }
  expected16 = F16_16_INT(f16_16_mult(f16_16(-1.0f), sine(phase)));
  phase = 0;
  for (i = 0; i < 513 ; i++) {
    phase += inc;
  }
  output16 = F16_16_INT(sine(phase));
  if (EXCEEDS_EPSILON(expected16, output16, SINE_EPSILON)) {
    errx(1, "expected %d; got %d", expected16, output16);
  }
  warnx("  sine(3583) ~= -sine(511)");
  phase = 0;
  for (i = 0; i < 3584 ; i++) {
    phase += inc;
  }
  expected16 = F16_16_INT(f16_16_mult(f16_16(-1.0f), sine(phase)));
  phase = 0;
  for (i = 0; i < 512 ; i++) {
    phase += inc;
  }
  output16 = F16_16_INT(sine(phase));
  if (EXCEEDS_EPSILON(expected16, output16, SINE_EPSILON)) {
    errx(1, "expected %d; got %d", expected16, output16);
  }
}
