#include <err.h>

#include "../midi/midi_parser.h"
#include "midi_parser.h"

void testMidiParser(void) {
  int i = 0;
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
  warnx(" recognizes note off commands");
  warnx("  channel 1 note off recognized");
  expected = 1;
  output = IS_NOTE_OFF(128);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  channel 16 note off recognized");
  expected = 1;
  output = IS_NOTE_OFF(143);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  channel 1 note off -1 ignored");
  expected = 0;
  output = IS_NOTE_OFF(127);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  channel 16 note off +1 ignored");
  expected = 0;
  output = IS_NOTE_OFF(144);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  only 16 bytes are recognized as note off");
  expected = 16;
  for (i = 0, output = 0 ; i < 256 ; i++) {
    output += IS_NOTE_OFF(i);
  }
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx(" recognizes note on commands");
  warnx("  channel 1 note on recognized");
  expected = 1;
  output = IS_NOTE_ON(144);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  channel 16 note on recognized");
  expected = 1;
  output = IS_NOTE_ON(159);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  channel 1 note on -1 ignored");
  expected = 0;
  output = IS_NOTE_ON(143);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  channel 16 note on +1 ignored");
  expected = 0;
  output = IS_NOTE_ON(160);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  only 16 bytes are recognized as note on");
  expected = 16;
  for (i = 0, output = 0 ; i < 256 ; i++) {
    output += IS_NOTE_ON(i);
  }
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx(" recognizes CC commands");
  warnx("  channel 1 CC event recognized");
  expected = 1;
  output = IS_CC(176);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  channel 16 CC event recognized");
  expected = 1;
  output = IS_CC(191);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  channel 1 CC event -1 ignored");
  expected = 0;
  output = IS_CC(175);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  channel 16 CC event +1 ignored");
  expected = 0;
  output = IS_CC(192);
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
  warnx("  only 16 bytes are recognized as CC");
  expected = 16;
  for (i = 0, output = 0 ; i < 256 ; i++) {
    output += IS_CC(i);
  }
  if (output != expected) {
    errx(1, "expected %d; got %d", expected, output);
  }
}
