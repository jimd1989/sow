#include <err.h>
#include <poll.h>
#include <stdint.h>
#include <string.h>

#include "audio_buffers.h"
#include "audio_init.h"
#include "audio_writer.h"
#include "volume.h"

#include <limits.h>
#include <stdio.h>

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
  //warnx("AUDIO %p", (void *)aw->synthData.floatData);
  for (; s < sb->size ; s++) {
    /* No need for dithering? Trunc okay because no floating point error ? */
    sample = mixVolume(&aw->masterVol, sb->data[s]);
    //sample = mixVolumeF(&aw->masterVol, sb->floatData[s]);
    //sample = (float)SHRT_MAX * sb->floatData[s];
    //printf("%d\n", sample);
    //if (sb->floatData[s] > 0.0) {
    //  warnx("%f", sb->floatData[s]);
    //}
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
    for (int zzz = 0; zzz < ob->bytesFilled ; zzz++) {
      //putchar(ob->data[zzz]);
      //ob->data[zzz] = 0;
    }
    (void)sio_write(aw->sio, ob->data, ob->bytesFilled);
    ob->blocksFilled = 0;
    ob->bytesFilled = 0;
  }
  memset(sb->data, 0, sizeof(*sb->data) * sb->size);
}
