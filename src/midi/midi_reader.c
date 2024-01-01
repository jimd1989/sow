#include <err.h>
#include <poll.h>
#include <sndio.h>
#include <stdbool.h>

#include "midi_init.h"
#include "midi_reader.h"

static bool midiReady(Mio *);

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
  }
}
