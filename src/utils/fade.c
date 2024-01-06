#include <stdlib.h>
#include <unistd.h>

#include "../cmd/scaling.h"
#include "fade.h"
#include "fixed_point.h"

/* The difference between old and new values determines the length of a fade. A 
 * MIDI-level resolution [0, 127] is a reasonable range. Scaling a stored value 
 * down to this level requires a shift of one less bit than the original MIDI 
 * command upscale. This is due to the signedness of the stored fader values. */
#define MIDI_LEVEL_BITS 24
#define MIDI_LEVEL(X) ((X) >> MIDI_LEVEL_BITS)

/* The MIDI-level difference is then scaled to quadrants [0 .. 3], which index 
 * a fading time. The higher the quadrant, the longer the fade. This hopefully 
 * guards against pops in dramatic amplitude changes, like when issuing a 
 * discrete command, but remains responsive to more gradual modifications, 
 * like the movement of a slider. */
#define FADE_LEVEL_BITS 5
#define FADE_LEVEL(X) ((X) >> FADE_LEVEL_BITS)

static F16_16 FADE_LEVELS[4] = {
  1024, /* 1/64  */
  512,  /* 1/128  */
  256,  /* 1/256 */
  128   /* 1/512 */
};

void setFader(Fader *f, F16_16 new) {
  int o = MIDI_LEVEL(f->new);
  int n = MIDI_LEVEL(new);
  size_t i = FADE_LEVEL(abs(o - n));
  f->dec = FADE_LEVELS[i];
  f->balance = F16_16_ONE;
  f->old = f->new;
  f->new = new;
}

F16_16 popFader(Fader *f) {
  F16_16 n = 0;
  if (!f->balance) {
    n = f->new;
  } else {
    f->balance -= f->dec;
    n  = f16_16_mult(f->old, f->balance);
    n += f16_16_mult(f->new, F16_16_ONE - f->balance);
  }
  return n;
}
