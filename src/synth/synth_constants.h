#pragma once

/* Length of wavetables; + 1 to avoid modulo during linear interpolation */
#define SYNTH_WAVELEN 1025

/* Maximum number of voices */
#define SYNTH_MAX_VOICES 8

/* Operator count */
#define SYNTH_OPERATORS 8

/* Shift needed to convert 32 bit phase to 10 bit (1024) wavetable index */
#define SYNTH_SHIFT 22
