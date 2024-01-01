#pragma once

#include "../utils/fixed_point.h"
#include "synth_constants.h"

#define NEGATE(X, Y) (((Y) & (1 << 31)) ? (~(X) + 1) : (X))
#define BACKWARDS(X) ((X) & (1 << 30) ? ~(X) : (X))
#define INDEX_MASK (((1 << (F16_16_INT_BITS - 2)) - 1) << F16_16_FRAC_BITS)
#define INDEX_SHIFT ((F16_16_INT_BITS - 2) - SYNTH_WAVE_BITS)
#define INDEX(X) (F16_16_INT(((X) & INDEX_MASK) >> INDEX_SHIFT))

void makeSine(void);
F16_16 sine(UF16_16);
