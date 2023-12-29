#include "fixed_point.h"

#include <stdint.h>
#include <limits.h>

/* Big thanks to http://sunshine2k.de/articles/coding/fp/sunfp.html */

F16_16 f16_16(float f) {
  int32_t n = (int32_t)f;
  float r = f - (float)n;
  F16_16 x = n << F16_16_FRAC_BITS;
  x += (int32_t)(F16_16_ONE * r);
  return x;
}

float f16_16_float(F16_16 x) {
  int32_t n = F16_16_INT(x);
  float r = (float)F16_16_FRAC(x) / (float)F16_16_ONE;
  return (float)n + r;
}

F12_20 f12_20(float f) {
  int32_t n = (int32_t)f;
  float r = f - (float)n;
  F16_16 x = n << F12_20_FRAC_BITS;
  x += (int32_t)(F12_20_ONE * r);
  return x;
}

float f12_20_float(F12_20 x) {
  int32_t n = F12_20_INT(x);
  float r = (float)F12_20_FRAC(x) / (float)F12_20_ONE;
  return (float)n + r;
}
