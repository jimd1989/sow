#include <err.h>
#include <sndio.h>

#include "audio_config.h"
#include "audio_constants.h"
#include "audio_writer.h"

static NegotiatedAudioSettings negotiatedSettings(AudioConfig);
static void populateSettings(SioPar, NegotiatedAudioSettings);
static void suggestSettings(Sio *, SioPar *);
static NegotiatedAudioSettings getSettings(SioPar, NegotiatedAudioSettings);

static NegotiatedAudioSettings negotiatedSettings(AudioConfig ac) {
  int defaultBufSizeFrames = 128;
  NegotiatedAudioSettings nas = {0};
  nas.bits = AUDIO_BITS;
  nas.blocks = ac.blocks;
  nas.bufSizeFrames = defaultBufSizeFrames;
  nas.chan = ac.chan; 
  nas.rate = ac.rate;
  return nas;
}

static void populateSettings(SioPar sp, NegotiatedAudioSettings nas) {
  sio_initpar(&sp);
  sp.bits = nas.bits;
  sp.appbufsz = nas.bufSizeFrames * nas.blocks;
  sp.rate = nas.rate;
  sp.pchan = nas.chan;
}

static void suggestSettings(Sio *sio, SioPar *sp) {
  if (sio_setpar(sio, sp) == 0) {
    errx(1, "Error setting sndio settings");
  }
  if (sio_getpar(sio, sp) == 0) {
    errx(1, "Error retrieving sndio settings");
  }
} 

static
NegotiatedAudioSettings getSettings(SioPar sp, NegotiatedAudioSettings nas) {
  if (sp.bits != AUDIO_BITS) {
    errx(1, "Audio output must be 16 bit; got %d", sp.bits);
  }
  if (sp.pchan != nas.chan) {
    errx(1, "%d channel audio impossible; try %d instead", nas.chan, sp.pchan);
  }
  if (sp.rate != nas.rate) {
    errx(1, "audio rate %d impossible; try %d instead", nas.rate, sp.rate);
  }
  nas.bufSizeFrames = sp.round;
  return nas;
}

AudioWriter audioWriter(AudioConfig ac) {
  NegotiatedAudioSettings nas = negotiatedSettings(ac);
  AudioWriter aw = {0};
  /* First negotiation: all settings except buffer size */
  populateSettings(aw.par, nas);
  suggestSettings(aw.sio, &aw.par);
  nas = getSettings(aw.par, nas);
  /* Second negotiation: rounded buffer size */
  populateSettings(aw.par, nas);
  suggestSettings(aw.sio, &aw.par);
  nas = getSettings(aw.par, nas);
  aw.sizeFrames = nas.bufSizeFrames;
  aw.sizeBytes = aw.sizeFrames * aw.par.pchan * (aw.par.bits / 8);
  /* Need actual sndio init */
  return aw;
}
