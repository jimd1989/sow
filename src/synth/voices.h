#pragma once

#include "../utils/bit_array.h"
#include "events.h"
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
  size_t        size;
  OneBitArray   stolen;
  FourBitArray  assigned; /* Actually need 9 bits for 8 voices */
  Voice         data[SYNTH_MAX_VOICES];
  VoiceFifo     free;
  VoiceFifo     released;
  VoiceRing     playing;
} Voices;

Voices voices(size_t);
void triggerVoice(Voices *, NoteOn);
void releaseVoice(Voices *, uint8_t);
void playVoices(Voices *, F16_16 *, size_t);
