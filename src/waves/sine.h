#pragma once

#include "../utils/fixed_point.h"
#include "wave_constants.h"

#define INDEX_MASK (((1 << (F16_16_INT_BITS - 2)) - 1) << F16_16_FRAC_BITS)
#define INDEX_SHIFT ((F16_16_INT_BITS - 2) - WAVE_SINE_BITS)
#define INDEX(X) (F16_16_INT(((X) & INDEX_MASK) >> INDEX_SHIFT))

void makeSine(void);
F16_16 sine(UF16_16);
