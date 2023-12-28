#include <err.h>
#include <stdio.h>

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
  MidiConfig mc = midiConfig(argc, argv);
  MidiReader mr = midiReader(mc);
  while (1) {
    readMidi(&mr);
    for (size_t i = 0 ; i < mr.bytesRead ; i++) {
      printf("%d ", mr.data[i]);
    }
    printf("from chan %zu\n", mr.chan);
  }
  #endif
  return 0;
}
