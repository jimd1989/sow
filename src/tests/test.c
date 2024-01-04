#include "test.h"

#include "audio_buffers.h"
#include "fade.h"
#include "fixed_point.h"
#include "midi_parser.h"
#include "phase.h"
#include "sine.h"

void test(void) {
  testAudioBuffers();
  /* testFade(); Don't waste time testing this until a number is agreed on */
  testFixedPoint();
  testMidiParser();
  testPhase();
  testSine();
}
