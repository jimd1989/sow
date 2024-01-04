#include <err.h>
#include <unistd.h>

#include "../audio/audio_buffers.h"
#include "audio_buffers.h"

void testAudioBuffers(void) {
  size_t expected = 0;
  size_t output = 0;
  SampleBuffer sb = {0};
  warnx("audio buffers");
  warnx(" sample buffer is size 128 when audio output is 128");
  expected = 128;
  sb = sampleBuffer(128);
  output = sb.size;
  killSampleBuffer(&sb);
  if (output != expected) {
    errx(1, "expected %zu; got %zu", expected, output);
  }
  warnx(" sample buffer is size 120 when audio output is 480");
  expected = 120;
  sb = sampleBuffer(480);
  output = sb.size;
  killSampleBuffer(&sb);
  if (output != expected) {
    errx(1, "expected %zu; got %zu", expected, output);
  }
  warnx(" sample buffer is 333 when audio output is 333");
  expected = 333;
  sb = sampleBuffer(333);
  output = sb.size;
  killSampleBuffer(&sb);
  if (output != expected) {
    errx(1, "expected %zu; got %zu", expected, output);
  }
  warnx(" stack data is used when audio output is 480");
  expected = 1;
  sb = sampleBuffer(480);
  output = (sb.slowData == NULL);
  killSampleBuffer(&sb);
  if (output != expected) {
    errx(1, "expected %zu; got %zu", expected, output);
  }
  warnx(" heap data is used when audio output is 333");
  expected = 1;
  sb = sampleBuffer(333);
  output = (sb.slowData != NULL);
  killSampleBuffer(&sb);
  if (output != expected) {
    errx(1, "expected %zu; got %zu", expected, output);
  }
}
