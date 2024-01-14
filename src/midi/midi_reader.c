#include <err.h>
#include <poll.h>
#include <sndio.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "midi_config.h"
#include "midi_constants.h"
#include "midi_reader.h"

static bool midiReady(Mio *);

MidiReader midiReader(MidiConfig mc) {
  bool nonBlockingIO = true;
  MidiReader m = {0};
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

static bool midiReady(Mio *mio) {
  int nfds, revents, timeout = 0;
  struct pollfd pfds[1] = {0};
  nfds = mio_pollfd(mio, pfds, POLLIN);
  if (nfds > 0) {
    if (poll(pfds, nfds, timeout) < 0) {
      errx(1, "MIDI poll failed");
    }
  }
  revents = mio_revents(mio, pfds);
  return (revents & POLLIN);
}

void readMidi(MidiReader *mr) {
  if (mr->enabled && midiReady(mr->mio)) {
    mr->bytesRead = mio_read(mr->mio, mr->data, mr->size);
  } else {
    mr->bytesRead = 0;
  }
}
