#include "test.h"

#include "fixed_point.h"
#include "midi_parser.h"
#include "phase.h"
#include "sine.h"

void test(void) {
  testFixedPoint();
  testMidiParser();
  testPhase();
  testSine();
}
