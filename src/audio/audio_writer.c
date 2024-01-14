#include <err.h>
#include <poll.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../utils/fixed_point.h"
#include "audio_buffers.h"
#include "audio_init.h"
#include "audio_writer.h"
#include "volume.h"

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
  uint8_t u = 0;
  uint8_t l = 0;
  int16_t sample = 0;
  size_t s = 0;
  size_t c = 0;
  SampleBuffer *sb = &aw->synthData;
  OutputBuffer *ob = &aw->output;
  for (; s < sb->size ; s++) {
    /* No need for dithering? Trunc okay because no floating point error ? */
    sample = mixVolume(&aw->masterVol, sb->data[s]);
    u = (uint8_t)(sample & 255);
    l = (uint8_t)(sample >> 8);
    for (c = 0 ; c < aw->par.pchan ; c++) {
      ob->data[ob->bytesFilled++] = u;
      ob->data[ob->bytesFilled++] = l;
    }
  }
  ob->blocksFilled++;
  if (ob->blocksFilled == ob->blocks) {
    wait(aw->sio);
    (void)sio_write(aw->sio, ob->data, ob->bytesFilled);
    ob->blocksFilled = 0;
    ob->bytesFilled = 0;
  }
  memset(sb->data, 0, sizeof(*sb->data) * sb->size);
}

void audioStatus(FILE *f, AudioWriter *aw) {
  fprintf(f, "audio.buffer.e2e=%d\n", aw->par.bufsz);
  fprintf(f, "audio.buffer.internal=%zu\n", aw->synthData.size);
  fprintf(f, "audio.buffer.output=%d\n", aw->par.appbufsz);
  fprintf(f, "audio.bytes=%d\n", aw->par.bps);
  fprintf(f, "audio.channels=%d\n", aw->par.pchan);
  fprintf(f, "audio.rate=%d\n", aw->par.rate);
  fprintf(f, "audio.signed=%d\n", aw->par.sig);
  fprintf(f, "audio.volume.master=%d\n", aw->masterVol.new >> 24);
}
