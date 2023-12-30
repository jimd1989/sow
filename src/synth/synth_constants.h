#pragma once

/* Number of bits used to track wavetable position */
#define SYNTH_WAVE_BITS 10

/* Length of wavetables; + 1 to avoid modulo during linear interpolation */
#define SYNTH_WAVELEN 1025

/* Maximum number of voices; parameter can allow for less */
#define SYNTH_MAX_VOICES 8

/* Operator count; most likely not possible to overwrite */
#define SYNTH_OPERATORS 8

/* Number of keys on keyboard */
#define SYNTH_KEYS 128
