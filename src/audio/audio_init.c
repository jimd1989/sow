#include <err.h>
#include <sndio.h>
#include <stdbool.h>
#include <stdint.h>

#include "audio_buffers.h"
#include "audio_config.h"
#include "audio_constants.h"
#include "audio_init.h"
#include "volume.h"

#include <err.h>

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
  int8_t defaultVol = 5;
  NegotiatedAudioConfig nas = negotiatedConfig(ac);
  AudioWriter aw = {0};
  setVolume(&aw.masterVol, defaultVol);
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
  aw.synthData = sampleBuffer(nas.bufSizeFrames);
  //warnx("INIT AUDIO WITH %p", (void *)aw.synthData.floatData);
  aw.output = outputBuffer(nas.bufSizeFrames, aw.synthData.size, aw.par.pchan);
  if (sio_start(aw.sio) == 0) { errx(1, "Error starting audio"); }
  return aw;
}

void killAudio(AudioWriter *aw) {
  sio_close(aw->sio);
  killSampleBuffer(&aw->synthData);
  killOutputBuffer(&aw->output);
}
