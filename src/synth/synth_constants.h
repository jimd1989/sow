#pragma once

/* Length of wavetables; + 1 to avoid modulo during linear interpolation */
#define SYNTH_WAVELEN 1025

/* Shift needed to convert 32 bit phase to 10 bit (1024) wavetable index */
#define SYNTH_WAVE_SHIFT 22

/* Maximum number of voices; parameter can allow for less */
#define SYNTH_MAX_VOICES 8

/* Operator count; most likely not possible to overwrite */
#define SYNTH_OPERATORS 8
