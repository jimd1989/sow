#include <stdint.h>
#include <unistd.h>

#include "../utils/bit_array.h"
#include "../utils/fixed_point.h"
#include "events.h"
#include "voice.h"
#include "voices.h"

static VoiceFifo fifo(size_t);
static Voice *popFifo(VoiceFifo *);
static void pushFifo(VoiceFifo *, Voice *);
static VoiceRing ring(size_t);
static void pushRing(VoiceRing *, Voice *);
static void *popOldestFromRing(VoiceRing *);
static void removeFromRing(VoiceRing *, Voice *);
static void processReleasedVoices(Voices *, F16_16 *, size_t);

VoiceFifo fifo(size_t size) {
  VoiceFifo vf = {0};
  vf.size = size;
  return vf;
}

static Voice *popFifo(VoiceFifo *vf) {
  Voice *x = NULL;
  if (vf->population > 0) {
    x = vf->data[vf->head];
    vf->head = (vf->head + 1) % vf->size;
    vf->population--;
  }
  return x;
}

static void pushFifo(VoiceFifo *vf, Voice *x) {
  if (vf->population < vf->size) {
    vf->data[(vf->head + vf->population) % vf->size] = x;
    vf->population++;
  }
}

VoiceRing ring(size_t size) {
  VoiceRing vr = {0};
  vr.size = size;
  return vr;
}

static void pushRing(VoiceRing *vr, Voice *x) {
  vr->data[vr->head] = x;
  vr->population = vr->population == vr->size ? vr->size : vr->population + 1;
  vr->head = (vr->head + 1) % vr->size;
}

static void *popOldestFromRing(VoiceRing *vr) {
  return vr->data[vr->head];
}

static void removeFromRing(VoiceRing *vr, Voice *x) {
  size_t i = 0;
  size_t prev = 0;
  Voice *val = vr->data[vr->head];
  Voice *tmp = NULL;
  for (; i < vr->population ; i++) {
    prev = (vr->head + ((vr->size - 1) - i)) % vr->size;
    if (vr->data[prev] == x) {
      vr->data[prev] = val;
      vr->head = (vr->head + (vr->size - 1)) % vr->size;
      vr->population--;
      return;
    } else {
      tmp = vr->data[prev];
      vr->data[prev] = val;
      val = tmp;
    }
  }
}

void triggerVoice(Voices *vs, NoteOn no) {
  uint8_t n = get4Bits(&vs->assigned, no.note);
  Voice *x = NULL;
  if (n > 0) {
    /* A voice is already playing this note */
    vs->data[n - 1].status = VOICE_RETRIGGER;
    return;
  }
  remove1Bit(&vs->stolen, no.note);
  if (vs->free.population > 0) {
    /* A free voice is available */
    x = popFifo(&vs->free);
    x->status = VOICE_TRIGGER;
  } else if (vs->released.population > 0) {
    /* A released voice is available for stealing */
    x = popFifo(&vs->released);
    x->status = VOICE_STEAL;
    push1Bit(&vs->stolen, x->event.note);
    push4Bits(&vs->assigned, x->event.note, 0);
  } else {
    /* A playing voice must be stolen */
    x = popOldestFromRing(&vs->playing);
    x->status = VOICE_STEAL;
    push1Bit(&vs->stolen, x->event.note);
    push4Bits(&vs->assigned, x->event.note, 0);
  }
  x->event = no;
  push4Bits(&vs->assigned, x->event.note, x->n + 1);
  pushRing(&vs->playing, x);
}

void releaseVoice(Voices *vs, uint8_t note) { 
  uint8_t n = get4Bits(&vs->assigned, note);
  Voice *x = &vs->data[n - 1];
  remove1Bit(&vs->stolen, x->event.note);
  removeFromRing(&vs->playing, x);
  x->status = VOICE_RELEASE;
  pushFifo(&vs->released, x);
}

static void processReleasedVoices(Voices *vs, F16_16 *buffer, size_t size) {
  size_t n = vs->released.population;
  Voice *x = NULL;
  while (n > 0) {
    n--;
    x = popFifo(&vs->released);
    if (x->status == VOICE_OFF) {
      push4Bits(&vs->assigned, x->event.note, 0);
      pushFifo(&vs->free, x);
    } else {
      playVoice(x, buffer, size);
      x->status = VOICE_OFF; /* Delete later */
      pushFifo(&vs->released, x);
    }
  }
}

void playVoices(Voices *vs, F16_16 *buffer, size_t size) {
  size_t n = vs->playing.population;
  size_t i = vs->playing.head;
  Voice *x = NULL;
  for (; n >= 0 ; n--, i = (i + 1) % vs->playing.size) {
    x = vs->playing.data[i];
    playVoice(x, buffer, size);
  }
  processReleasedVoices(vs, buffer, size);
}

Voices voices(size_t size) {
  size_t i = 0;
  Voices vs = {0};
  vs.size = size;
  vs.free = fifo(size);
  vs.released = fifo(size);
  vs.playing = ring(size);
  for (; i < size ; i++) {
    vs.data[i].n = i;
    pushFifo(&vs.free, &vs.data[i]);
  }
  return vs;
}
