#pragma once

#include <sndio.h>
#include <stdint.h>
#include <stdlib.h>

#include "audio_config.h"

#include "../synth/noise.h" /* Delete this later */

typedef struct sio_hdl Sio;
typedef struct sio_par SioPar;

typedef struct AudioWriter {
  Rng       rng; /* Delete this later */
  size_t    sizeFrames;
  size_t    sizeBytes;
  SioPar    par;
  Sio     * sio;
  int16_t * synthData;
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
