#include <err.h>
#include <limits.h>
#include <math.h>

#include "../cmd/scaling.h"
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
  warnx(" ah");
  errx(1, "%u %f", F16_16_ONE, f16_16_float(4294967295 >> 24));
}
