#pragma once

#include <stdint.h>
#include <unistd.h>

#include "../utils/fixed_point.h"
#include "events.h"

typedef enum VoiceStatus {
  VOICE_OFF = 0,
  VOICE_STEAL,
  VOICE_RELEASE,
  VOICE_RETURN_STEAL,
  VOICE_RETRIGGER,
  VOICE_TRIGGER,
  VOICE_PLAYING
} VoiceStatus;

typedef struct Voice {
  uint8_t     n;
  VoiceStatus status;
  NoteOn      event;
  UF16_16     phase; /* Delete later */
  /* 8 Envs */
  /* 8 Operators */
  /* - Calculate individual operator inc once at voice on */
} Voice;

void playVoice(Voice *, F16_16 *, size_t);
