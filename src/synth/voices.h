#pragma once

#include "synth_constants.h"
#include "voice.h"

typedef struct VoiceFifo {
  size_t    head;
  size_t    population;
  size_t    size;
  Voice   * data[SYNTH_MAX_VOICES];
} VoiceFifo;

typedef struct VoiceRing {
  size_t    head;
  size_t    population;
  size_t    size;
  Voice   * data[SYNTH_MAX_VOICES];
} VoiceRing;

typedef struct Voices {
  /* Need a map between note and voice: bitarray */
  size_t    size;
  Voice     all[SYNTH_MAX_VOICES];
  VoiceFifo free;
  VoiceFifo released;
  VoiceRing playing;
} Voices;
