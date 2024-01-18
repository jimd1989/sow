#include <unistd.h>

#include "../utils/fixed_point.h"
#include "../waves/sine.h"
#include "voice.h"

/* If voice count is a power of 2, then voices can be mixed via simple shifts.
 * log2(8) = 3 */
#define VOICE_MIX_BITS 3
#define MIX_VOICE(X) ((X) >> VOICE_MIX_BITS)

void playVoice(Voice *v, F16_16 *buffer, size_t size) {
  size_t i = 0;
  for (; i < size ; i++, v->phase += v->event.inc) {
    buffer[i] += MIX_VOICE(sine(v->phase));
  }
}
