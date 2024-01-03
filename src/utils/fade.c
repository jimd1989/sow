#include "fade.h"
#include "fixed_point.h"

static F16_16 FADER_DEC;

void setFadePeriod(void) {
    /* FADER_DEC = f16_16(0.00390625f); */ /* 1/256 */
    /* FADER_DEC = f16_16(0.0078125f);  */ /* 1/128 */
    FADER_DEC = f16_16(0.015625f);         /* 1/64  */
}

void setFader(Fader *f, F16_16 new) {
  f->balance = F16_16_ONE;
  f->old = f->new;
  f->new = new;
}

F16_16 popFader(Fader *f) {
  F16_16 n = 0;
  if (!f->balance) {
    n = f->new;
  } else {
    f->balance -= FADER_DEC;
    n  = f16_16_mult(f->old, f->balance);
    n += f16_16_mult(f->new, F16_16_ONE - f->balance);
  }
  return n;
}
