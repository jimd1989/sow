#include <stdint.h>

#include "events.h"
#include "keyboard.h"

/* Scaling MIDI velocity to an amplitude [0.0 … 1.0] in 16.16 format */
#define VELOCITY_SHIFT_BITS 9
#define VELOCITY_TO_VOLUME(X) ((((X) + 1) << VELOCITY_SHIFT_BITS) - 1)

/* Still needed:
 * - Scale based on frequency
 * - Adjustable velocity resolution */
NoteOn noteOn(Keyboard *kb, uint8_t note, uint8_t vel) {
  NoteOn no = {0};
  no.note = note;
  no.inc = kb->keys[note].inc;
  no.vel = VELOCITY_TO_VOLUME(vel);
  return no;
}
