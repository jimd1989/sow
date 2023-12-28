#include <err.h>
#include <stdio.h>

#include "audio/audio_config.h"
#include "audio/audio_init.h"
#include "midi/midi_config.h"
#include "midi/midi_init.h"
#include "midi/midi_reader.h"

#ifdef TEST
  #include "tests/test.h"
#endif

int main(int argc, char **argv) {
  #ifdef TEST
  test();
  #else
  warnx("prod");
  AudioConfig ac = audioConfig(argc, argv);
  AudioWriter aw = audioWriter(ac);
  MidiConfig mc = midiConfig(argc, argv);
  MidiReader mr = midiReader(mc);
  killMidi(&mr);
  killAudio(&aw);
  #endif
  return 0;
}
