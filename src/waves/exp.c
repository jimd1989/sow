#include <limits.h>
#include <math.h>
#include <stdint.h>

#include "../utils/fixed_point.h"
#include "exp.h"
#include "wave_constants.h"

#define INDEX(X) ((X) >> (F16_16_INT_BITS - WAVE_EXP_BITS))

static F16_16 EXP_WAVE[WAVE_EXP_LEN] = {0};

void makeExp(void) {
  int i = 0;
  float phase = 0.0f;
  float f = 0.0f;
  float inc = 1.0f / (float)(WAVE_EXP_LEN - 1);
  for (; i < WAVE_EXP_LEN ; i++, phase += inc) {
    f = SHRT_MAX * (exp2(phase) - 1.0f);
    EXP_WAVE[i] = f16_16(f);
  }
}

F16_16 expo(UF16_16 phase) {
  int i = INDEX(F16_16_INT(phase));
  return EXP_WAVE[i];
}
