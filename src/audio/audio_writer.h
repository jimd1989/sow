#pragma once

#include <sndio.h>
#include <stdint.h>
#include <stdlib.h>

#include "audio_config.h"

typedef struct sio_hdl Sio;
typedef struct sio_par SioPar;

typedef struct AudioWriter {
  size_t    sizeFrames;
  size_t    sizeBytes;
  SioPar    par;
  Sio     * sio;
  uint8_t * data;
} AudioWriter;

typedef struct NegotiatedAudioSettings {
  int bits;
  int blocks;
  int bufSizeFrames;
  int chan;
  int rate;
} NegotiatedAudioSettings;

AudioWriter audioWriter(AudioConfig);
