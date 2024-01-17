#include "test.h"

#include "audio_buffers.h"
#include "bit_array.h"
#include "fixed_point.h"
#include "midi_parser.h"
#include "phase.h"
#include "pitch.h"
#include "sine.h"

void test(void) {
  testAudioBuffers();
  testBitArray();
  testFixedPoint();
  testMidiParser();
  testPhase();
  testPitch();
  testSine();
}
