#include <err.h>
#include <stdint.h>
#include <unistd.h>

#include "../synth/phase.h"
#include "../utils/fixed_point.h"
#include "phase.h"

void testPhase(void) {
  int i = 0;
  UF24_8 inc = 0;
  UF24_8 oldPhase = 0;
  UF24_8 newPhase = 0;
  warnx("wave phase");
  warnx(" where rate = 48k and pitch = 440hz, cycle after 110 samples");
  setPhase(48000);
  inc = phaseIncrement(440.0f);
  for (i = 0 ; i < 110 ; i++) {
    oldPhase = newPhase;
    newPhase += inc;
  }
  newPhase = UF24_8_INT(newPhase);
  oldPhase = UF24_8_INT(oldPhase);
  if (newPhase > oldPhase) {
    errx(1, "expected %u to overflow behind %u", newPhase, oldPhase);
  }
  warnx(" where rate = 4k and pitch = 440hz, cycle after 10 samples");
  setPhase(4000);
  inc = phaseIncrement(440.0f);
  oldPhase = 0;
  newPhase = 0;
  for (i = 0 ; i < 10 ; i++) {
    oldPhase = newPhase;
    newPhase += inc;
  }
  newPhase = UF24_8_INT(newPhase);
  oldPhase = UF24_8_INT(oldPhase);
  if (newPhase > oldPhase) {
    errx(1, "expected %u to overflow behind %u", newPhase, oldPhase);
  }
}
