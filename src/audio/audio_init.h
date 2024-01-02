#pragma once

#include <sndio.h>
#include <stdint.h>
#include <stdlib.h>

#include "../utils/fade.h"
#include "../utils/fixed_point.h"
#include "audio_config.h"

typedef struct sio_hdl Sio;
typedef struct sio_par SioPar;

typedef struct AudioWriter {
  size_t    sizeFrames;
  size_t    sizeBytes;
  Fader     masterVol;
  SioPar    par;
  Sio     * sio;
  F16_16  * synthData;
  uint8_t * output;
} AudioWriter;

typedef struct NegotiatedAudioConfig {
  size_t  bits;
  size_t  blocks;
  size_t  bufSizeFrames;
  size_t  chan;
  size_t  rate;
} NegotiatedAudioConfig;

AudioWriter audioWriter(AudioConfig);
void killAudio(AudioWriter *);
