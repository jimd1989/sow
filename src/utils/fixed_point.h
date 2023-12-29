#pragma once

#include <stdint.h>

#define F16_16_INT_BITS 16
#define F16_16_FRAC_BITS 16
#define F16_16_INT_MASK (USHRT_MAX << F16_16_FRAC_BITS)
#define F16_16_FRAC_MASK USHRT_MAX
#define F16_16_ONE (1 << F16_16_FRAC_BITS)
#define F16_16_INT(X) (((X) & F16_16_INT_MASK) >> F16_16_FRAC_BITS)
#define F16_16_FRAC(X) ((X) & F16_16_FRAC_MASK)

#define F12_20_INT_BITS 12
#define F12_20_FRAC_BITS 20
#define F12_20_INT_MASK (((1 << F12_20_INT_BITS) - 1) << F12_20_FRAC_BITS)
#define F12_20_FRAC_MASK (~F12_20_INT_MASK)
#define F12_20_ONE (1 << F12_20_FRAC_BITS)
#define F12_20_INT(X) (((X) & F12_20_INT_MASK) >> F12_20_FRAC_BITS)
#define F12_20_FRAC(X) ((X) & F12_20_FRAC_MASK)

typedef int32_t F16_16;
typedef int32_t F12_20;

F16_16 f16_16(float);
float f16_16_float(F16_16);
F12_20 f12_20(float);
float f12_20_float(F12_20);
