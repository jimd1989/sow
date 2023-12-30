#pragma once

#include "../utils/fixed_point.h"
#include "synth_constants.h"

#define NEGATE(X, Y) ((X) |= ((Y) & (1 << 31))) /* Fix? */
#define BACKWARDS(X) ((X) & (1 << 30) ? ~(X) : (X))
#define INDEX_MASK (((1 << (UF24_8_INT_BITS - 2)) - 1) << UF24_8_FRAC_BITS)
#define INDEX_SHIFT ((UF24_8_INT_BITS - 2) - SYNTH_WAVE_BITS)
#define INDEX(X) (UF24_8_INT(((X) & INDEX_MASK) >> INDEX_SHIFT))

void makeSine(void);
F16_16 sine(UF24_8);
