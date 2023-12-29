#include "../utils/fixed_point.h"
#include "keyboard.h"
#include "synth_constants.h"

Keyboard keyboard(size_t rate) {
//  int i = 0;
  Keyboard kb = {0};
  kb.rate = rate;
  kb.size = SYNTH_KEYS;
  return kb;
}
