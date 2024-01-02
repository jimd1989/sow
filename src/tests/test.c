#include "test.h"

#include "fade.h"
#include "fixed_point.h"
#include "midi_parser.h"
#include "phase.h"
#include "sine.h"

void test(void) {
  testFade();
  testFixedPoint();
  testMidiParser();
  testPhase();
  testSine();
}
