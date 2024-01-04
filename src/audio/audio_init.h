#pragma once

#include <sndio.h>
#include <stdlib.h>

#include "../utils/fade.h"
#include "audio_buffers.h"
#include "audio_config.h"

typedef struct sio_hdl Sio;
typedef struct sio_par SioPar;

typedef struct AudioWriter {
  Fader           masterVol;
  SioPar          par;
  Sio           * sio;
  SampleBuffer    synthData;
  OutputBuffer    output;
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
