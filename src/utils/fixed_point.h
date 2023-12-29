#pragma once

#include <stdint.h>

#define F16_16_INT_BITS 16
#define F16_16_FRAC_BITS 16
#define F16_16_INT_MASK (USHRT_MAX << F16_16_FRAC_BITS)
#define F16_16_FRAC_MASK USHRT_MAX
#define F16_16_ONE (1 << F16_16_FRAC_BITS)

typedef int32_t F16_16;

F16_16 f16_16(float);
float f16_16_float(F16_16);
