#pragma once

#include <stdint.h>

/* F16_16  = signed 16.16 decimal representing audio signal
 * F1_16   = signed 1.16 decimal representing amplitude (negative needed for FM)
 * UF16_16 = unsigned 16.16 decimal representing wave phase */

#define F16_16_INT_BITS 16
#define F16_16_FRAC_BITS 16
#define F16_16_FRAC_MASK ((1 << F16_16_FRAC_BITS) - 1)
#define F16_16_INT_MASK (((1 << F16_16_INT_BITS) - 1) << F16_16_FRAC_BITS)
#define F16_16_ONE (1 << F16_16_FRAC_BITS)
#define F16_16_INT(X) (((X) & F16_16_INT_MASK) >> F16_16_FRAC_BITS)
#define F16_16_FRAC(X) ((X) & F16_16_FRAC_MASK)
#define F16_16_TO_F1_16(X) ((F1_16)((X) >> (F16_16_FRAC_BITS - 1)))

typedef int32_t F16_16;
typedef int32_t F1_16;
typedef uint32_t UF16_16;

F16_16 f16_16(float);
float f16_16_float(F16_16);
F16_16 f16_16_mult(F16_16, F16_16);
UF16_16 uf16_16(float);
