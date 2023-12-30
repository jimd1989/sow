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

F16_16 f16_16_mult(F16_16 x, F16_16 y) {
  int64_t product = (int64_t)x * (int64_t)y;
  return product >> F16_16_FRAC_BITS;
}

/* Clean up */
F16_16 f16_16_f1_16(F16_16 x) {
  F16_16 n = ((1 << (F16_16_INT_BITS - 1)) - 1) << F16_16_FRAC_BITS;
  n >>= F16_16_FRAC_BITS - 1;
  /* Use NEGATE here? */
  return n;
}

UF24_8 uf24_8(float f) {
  uint32_t n = (int32_t)f;
  float r = f - (float)n;
  UF24_8 x = n << UF24_8_FRAC_BITS;
  x += (uint32_t)(UF24_8_ONE * r);
  return x;
}

float uf24_8_float(UF24_8 x) {
  uint32_t n = UF24_8_INT(x);
  float r = (float)UF24_8_FRAC(x) / (float)UF24_8_ONE;
  return (float)n + r;
}

UF24_8 uf24_8_mult(UF24_8 x, UF24_8 y) {
  uint64_t product = (uint64_t)x * (uint64_t)y;
  return product >> UF24_8_FRAC_BITS;
}
