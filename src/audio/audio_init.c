#include <err.h>
#include <sndio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "audio_config.h"
#include "audio_constants.h"
#include "audio_init.h"

#include "../synth/noise.h" /* Delete this later */

static NegotiatedAudioConfig negotiatedConfig(AudioConfig);
static SioPar setConfig(NegotiatedAudioConfig);
static void suggestConfig(Sio *, SioPar *);
static NegotiatedAudioConfig getConfig(SioPar, NegotiatedAudioConfig);

static NegotiatedAudioConfig negotiatedConfig(AudioConfig ac) {
  int defaultBufSizeFrames = 128;
  NegotiatedAudioConfig nas = {0};
  nas.bits = AUDIO_BITS;
  nas.blocks = ac.blocks;
  nas.bufSizeFrames = defaultBufSizeFrames;
  nas.chan = ac.chan; 
  nas.rate = ac.rate;
  return nas;
}

static SioPar setConfig(NegotiatedAudioConfig nas) {
  SioPar sp = {0};
  sio_initpar(&sp);
  sp.bits = nas.bits;
  sp.appbufsz = nas.bufSizeFrames * nas.blocks;
  sp.rate = nas.rate;
  sp.pchan = nas.chan;
  return sp;
}

static void suggestConfig(Sio *sio, SioPar *sp) {
  if (sio_setpar(sio, sp) == 0) {
    errx(1, "Error setting sndio settings");
  }
  if (sio_getpar(sio, sp) == 0) {
    errx(1, "Error retrieving sndio settings");
  }
} 

static NegotiatedAudioConfig getConfig(SioPar sp, NegotiatedAudioConfig nas) {
  if (sp.bits != AUDIO_BITS) {
    errx(1, "Audio output must be 16 bit; got %d", sp.bits);
  }
  if (sp.pchan != nas.chan) {
    errx(1, "%zu channel audio impossible; try %d instead", nas.chan, sp.pchan);
  }
  if (sp.rate != nas.rate) {
    errx(1, "audio rate %zu impossible; try %d instead", nas.rate, sp.rate);
  }
  nas.bufSizeFrames = sp.round;
  return nas;
}

AudioWriter audioWriter(AudioConfig ac) {
  bool nonBlockingIO = true;
  NegotiatedAudioConfig nas = negotiatedConfig(ac);
  AudioWriter aw = {0};
  aw.sio = sio_open(SIO_DEVANY, SIO_PLAY, nonBlockingIO);
  if (aw.sio == NULL) { errx(1, "Error opening sound port %s", SIO_DEVANY); }
  /* First negotiation: all settings except buffer size */
  aw.par = setConfig(nas);
  suggestConfig(aw.sio, &aw.par);
  nas = getConfig(aw.par, nas);
  /* Second negotiation: rounded buffer size */
  aw.par = setConfig(nas);
  suggestConfig(aw.sio, &aw.par);
  nas = getConfig(aw.par, nas);
  aw.sizeFrames = nas.bufSizeFrames;
  aw.sizeBytes = sizeof(*aw.output) * aw.sizeFrames * aw.par.pchan;
  aw.synthData = malloc(sizeof(*aw.synthData) * aw.sizeFrames);
  if (aw.synthData == NULL) { errx(1, "Error allocating synth buffer"); }
  aw.output = malloc(aw.sizeBytes);
  if (aw.output == NULL) { errx(1, "Error allocating audio buffer"); }
  if (sio_start(aw.sio) == 0) { errx(1, "Error starting audio"); }
  aw.rng = rng(); /* Delete this later */
  return aw;
}

void killAudio(AudioWriter *aw) {
  sio_close(aw->sio);
  free(aw->synthData);
  free(aw->output);
}
