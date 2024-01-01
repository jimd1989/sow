#include <err.h>

#include "../midi/midi_parser.h"
#include "midi_parser.h"

void testMidiParser(void) {
  int output = 0;
  int expected = 0;
  warnx("MIDI parsing");
  warnx(" allows all channels when midiChan = 0");
  warnx("  channel 1 CC event allowed");
  expected = 1;
  output = CHAN_MATCH(176, 0);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  channel 2 note on event allowed");
  expected = 1;
  output = CHAN_MATCH(145, 0);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx(" allows only channel 2 when midiChan = 2");
  warnx("  channel 1 CC event filtered");
  expected = 0;
  output = CHAN_MATCH(176, 2);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  channel 2 note on event allowed");
  expected = 1;
  output = CHAN_MATCH(145, 2);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
}
