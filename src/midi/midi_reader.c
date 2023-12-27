#include <err.h>
#include <poll.h>
#include <sndio.h>
#include <stdbool.h>
#include <unistd.h>

#include "midi_config.h"
#include "midi_constants.h"
#include "midi_reader.h"

static void wait(Mio *);

MidiReader midiReader(MidiConfig mc) {
  bool nonBlockingIO = true;
  Mio *mio = NULL;
  MidiReader m = {0};
  m.chan = mc.chan;
  m.size = MIDI_BUFSIZE;
  mio = mio_open(MIO_PORTANY, MIO_IN, nonBlockingIO);
  if (mio == NULL) {
    errx(1, "Couldn't open MIDI %s", MIO_PORTANY);
  }
  m.mio = mio;
  return m;
}

static void wait(Mio *mio) {
  int nfds, revents = 0;
  struct pollfd pfds[1] = {0};
  do {
    nfds = mio_pollfd(mio, pfds, POLLIN);
    if (nfds > 0) {
      if (poll(pfds, nfds, -1) < 0) {
        errx(1, "MIDI poll failed");
      }
    }
    revents = mio_revents(mio, pfds);
  } while (!(revents & POLLIN));
}

void readMidi(MidiReader *mr) {
  wait(mr->mio);
  mr->bytesRead = mio_read(mr->mio, mr->data, mr->size);
}
