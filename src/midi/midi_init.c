#include <err.h>
#include <poll.h>
#include <sndio.h>
#include <stdbool.h>
#include <unistd.h>

#include "midi_config.h"
#include "midi_constants.h"
#include "midi_init.h"

MidiReader midiReader(MidiConfig mc) {
  bool nonBlockingIO = true;
  MidiReader m = {0};
  m.chan = mc.chan;
  m.size = MIDI_BUFSIZE;
  m.enabled = mc.enabled;
  m.mio = mio_open(MIO_PORTANY, MIO_IN, nonBlockingIO);
  if (m.mio == NULL) {
    warnx("Couldn't open MIDI %s; disabling MIDI", MIO_PORTANY);
    m.enabled = false;
  }
  return m;
}

void killMidi(MidiReader *mr) {
  if (mr->enabled) {
    mio_close(mr->mio);
  }
}
