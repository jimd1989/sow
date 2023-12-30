#pragma once

#include <stdint.h>

/* Used to represent waveform-generated audio */
#define F16_16_INT_BITS 16
#define F16_16_FRAC_BITS 16
#define F16_16_FRAC_MASK ((1 << F16_16_FRAC_BITS) - 1)
#define F16_16_INT_MASK (((1 << F16_16_INT_BITS) - 1) << F16_16_FRAC_BITS)
#define F16_16_ONE (1 << F16_16_FRAC_BITS)
#define F16_16_INT(X) (((X) & F16_16_INT_MASK) >> F16_16_FRAC_BITS)
#define F16_16_FRAC(X) ((X) & F16_16_FRAC_MASK)

/* Used to represent phase of a 1024 index quarter-sine lookup table */
#define UF24_8_INT_BITS 24
#define UF24_8_FRAC_BITS 8
#define UF24_8_INT_MASK (((1 << UF24_8_INT_BITS) - 1) << UF24_8_FRAC_BITS)
#define UF24_8_FRAC_MASK (~UF24_8_INT_MASK)
#define UF24_8_ONE (1 << UF24_8_FRAC_BITS)
#define UF24_8_INT(X) (((X) & UF24_8_INT_MASK) >> UF24_8_FRAC_BITS)
#define UF24_8_FRAC(X) ((X) & UF24_8_FRAC_MASK)

typedef int32_t F16_16;
typedef uint32_t UF24_8; /* Signed vs unsigned makes a difference? */

F16_16 f16_16(float);
float f16_16_float(F16_16);
F16_16 f16_16_mult(F16_16, F16_16);
UF24_8 uf24_8(float);
float uf24_8_float(UF24_8);
UF24_8 uf24_8_mult(UF24_8, UF24_8);
