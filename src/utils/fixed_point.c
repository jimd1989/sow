#include "fixed_point.h"

#include <stdint.h>
#include <limits.h>

/* Big thanks to http://sunshine2k.de/articles/coding/fp/sunfp.html */

#define F16_16_INT_BITS 16
#define F16_16_FRAC_BITS 16
#define F16_16_INT_MASK (USHRT_MAX << F16_16_FRAC_BITS)
#define F16_16_FRAC_MASK USHRT_MAX
#define F16_16_ONE (1 << F16_16_FRAC_BITS)

F16_16 f16_16(float f) {
  int32_t n = (int32_t)f;
  float r = f - (float)n;
  F16_16 x = n << F16_16_FRAC_BITS;
  x += (int32_t)(F16_16_ONE * r);
  return x;
}

float f16_16_float(F16_16 x) {
  int32_t n = (x & F16_16_INT_MASK) >> F16_16_INT_BITS;
  float r = (float)(x & F16_16_FRAC_MASK) / (float)F16_16_ONE;
  return (float)n + r;
}
