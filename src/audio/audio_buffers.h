#pragma once

#include <stdint.h>
#include <unistd.h>

#include "../utils/fixed_point.h"
#include "audio_constants.h"

/* Small non-heap-allocated buffer used to process internal synthesizer data.
 * Written to larger output buffer in AudioWriter. This buffer must be a perfect
 * divisor of the output buffer, meaning that it may be smaller than
 * AUDIO_MAX_SAMPLE_BUFSIZE in practice, or not actually used if no reasonable
 * divisor can be derived. */
typedef struct SampleBuffer {
  size_t    size;
  F16_16    fastData[AUDIO_MAX_SAMPLE_BUFSIZE];
  F16_16  * data;
  F16_16  * slowData;
} SampleBuffer;

/* Actual audio output data. A multiple of the SampleBuffer size. */
typedef struct OutputBuffer {
  size_t    blocks;
  size_t    blocksFilled;
  size_t    bytesFilled;
  uint8_t * data;
} OutputBuffer;

SampleBuffer sampleBuffer(size_t);
void killSampleBuffer(SampleBuffer *);
OutputBuffer outputBuffer(size_t, size_t, size_t);
void killOutputBuffer(OutputBuffer *);
