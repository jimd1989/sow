#include <err.h>
#include <poll.h>
#include <stdint.h>
#include <string.h>

#include "audio_init.h"
#include "audio_writer.h"

#include "../synth/noise.h" /* Delete this later */

static void wait(Sio *);

static void wait(Sio *sio) {
  int nfds, revents = 0;
  struct pollfd pfds[1] = {0};
  do {
    nfds = sio_pollfd(sio, pfds, POLLOUT);
    if (nfds > 0) {
      if (poll(pfds, nfds, -1) < 0) {
        errx(1, "Audio poll failed");
      }
    }
    revents = sio_revents(sio, pfds);
  } while (!(revents & POLLOUT));
}

void writeAudio(AudioWriter *aw) {
  size_t s = 0;
  size_t o = 0;
  size_t c = 0;
  uint8_t u = 0;
  uint8_t l = 0;
  int16_t sample = 0;

  /* Delete this later */
  noise(&aw->rng, aw->synthData, aw->sizeFrames);

  for (; s < aw->sizeFrames ; s++) {
    sample = aw->synthData[s];
    u = (uint8_t)(sample & 255);
    l = (uint8_t)(sample >> 8);
    for (c = 0 ; c < aw->par.pchan ; c++) {
      aw->output[o++] = u;
      aw->output[o++] = l;
    }
  }
  wait(aw->sio);
  (void)sio_write(aw->sio, aw->output, aw->sizeBytes);
  memset(aw->synthData, 0, sizeof(*aw->synthData) * aw->sizeFrames);
}