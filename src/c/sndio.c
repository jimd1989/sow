#include <err.h>
#include <sndio.h>
#include <stdbool.h>
#include <unistd.h>

struct sio_hdl *start_audio(char *device) {
  struct sio_hdl *sio = NULL;
  struct sio_par par  = {0};
  sio = sio_open(device, SIO_PLAY, true);
  if (sio == NULL) {
    warnx("could not open sndio device %s", device);
  }
  sio_initpar(&par);
  par.bits     = 16;
  par.appbufsz = 1; /* soundcard will overwrite with min size */
  par.rate     = 48000;
  par.pchan    = 2;
  par.rchan    = 2;
  par.le       = 1;
  par.sig      = 1;
  sio_setpar(sio, &par);
  sio_getpar(sio, &par);
  warnx("%dch %dHz %d frame buffer", par.pchan, par.rate, par.appbufsz);
  return sio; 
}
