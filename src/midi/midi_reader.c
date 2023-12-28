#include <err.h>
#include <poll.h>
#include <sndio.h>

#include "midi_init.h"
#include "midi_reader.h"

static void wait (Mio *);

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
  if (mr->enabled) {
    wait(mr->mio);
    mr->bytesRead = mio_read(mr->mio, mr->data, mr->size);
  }
}
