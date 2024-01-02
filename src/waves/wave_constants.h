#pragma once

/* Number of bits used to track sine wavetable position */
#define WAVE_SINE_BITS 10

/* Length of sine wavetable; + 1 to avoid modulo during linear interpolation */
#define WAVE_SINE_LEN 1025

/* Number of bits used to track exp wavetable position */
#define WAVE_EXP_BITS 7

/* Length of exp wavetable; no extra lerp index */
#define WAVE_EXP_LEN 128
