#include "fixed_point.h"

#include <stdint.h>
#include <limits.h>

/* Big thanks to http://sunshine2k.de/articles/coding/fp/sunfp.html */

#define F16_16_INT 16
#define F16_16_FRAC 16
#define F16_16_INT_MASK (SHRT_MAX << F16_16_FRAC)
#define F16_16_FRAC_MASK SHRT_MAX
#define F16_16_ONE (1 << F16_16_FRAC)

F16_16 f16_16(float f) {
  int32_t n = (int32_t)f;
  float r = f - (float)n;
  F16_16 x = n << F16_16_FRAC;
  x += (int32_t)(F16_16_ONE * r);
  return x;
}
