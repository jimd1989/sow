#include "voices.h"

static VoiceFifo fifo(size_t);
static VoiceRing ring(size_t);

VoiceFifo fifo(size_t size) {
  VoiceFifo vf = {0};
  vf.size = size;
  return vf;
}

VoiceRing ring(size_t size) {
  VoiceRing vr = {0};
  vr.size = size;
  return vr;
}

Voices voices(size_t size) {
  size_t i = 0;
  Voices vs = {0};
  vs.size = size;
  vs.free = fifo(size);
  vs.released = fifo(size);
  vs.playing = ring(size);
  for (; i < size ; i++) {
    /* Assign each voice to free */
  }
  return vs;
}
