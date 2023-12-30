#include <err.h>
#include <stdint.h>

#include "../utils/fixed_point.h"
#include "../synth/phase.h"
#include "../synth/sine.h"
#include "sine.h"

void testSine(void) {
  int i = 0;
  UF24_8 inc = 0;
  UF24_8 phase = 0;
  uint32_t output = 0;
  uint32_t expected = 0;
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
  outputF = f16_16_float(sine(phase));
  if (outputF != expectedF) {
    errx(1, "expected %f; got %f", expectedF, outputF);
  }
  warnx("  SINE_WAVE[1023] ~= 1.0f");
  phase = 0;
  for (i = 0 ; i < 1024 ; i++) {
    phase += inc;
  }
  expectedF = 0.9999847412109375f;
  outputF = f16_16_float(sine(phase));
  if (outputF != expectedF) {
    errx(1, "expected %f; got %f", expectedF, outputF);
  }
}
