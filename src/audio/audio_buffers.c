#include <err.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "../utils/fixed_point.h"
#include "audio_buffers.h"

#define MIN_SAMPLE_BUFSIZE 32

SampleBuffer sampleBuffer(size_t outputBufsize) {
  size_t n = outputBufsize;
  float r = 0.0f;
  SampleBuffer sb = {0};
  while (n > AUDIO_MAX_SAMPLE_BUFSIZE) {
    r = (float)n / 2.0f;
    n /= 2;
    r = r - (float)n;
    if (r != 0.0f) { break; }
  }
  if ((n < MIN_SAMPLE_BUFSIZE) || (n > AUDIO_MAX_SAMPLE_BUFSIZE)) {
    warnx("Could not derive a small audio buffer; size is %zu", outputBufsize);
    sb.size = outputBufsize;
    sb.slowData = malloc(sizeof(*sb.slowData) * outputBufsize);
    sb.data = sb.slowData;
    if (sb.slowData == NULL) { 
      errx(1, "Error allocating synth buffer"); 
    }
  } else {
    sb.size = n;
    sb.data = sb.fastData;
  }
  return sb;
}

void killSampleBuffer(SampleBuffer *sb) {
  if (sb->slowData != NULL) {
    free(sb->slowData);
  }
}

OutputBuffer outputBuffer(size_t outputBufsize, size_t blockSize, size_t chan) {
  OutputBuffer ob = {0};
  if ((outputBufsize % blockSize) != 0) {
    errx(1, "Block size misalignment: %zu and %zu", outputBufsize, blockSize);
  }
  ob.blocks = outputBufsize / blockSize;
  ob.data = malloc(sizeof(F16_16) * chan * outputBufsize);
  if (ob.data == NULL) { 
    errx(1, "Error allocating output buffer"); 
  }
  return ob;
}

void killOutputBuffer(OutputBuffer *ob) {
  free(ob->data);
}
