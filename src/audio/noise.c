#include <stdint.h>
#include <unistd.h>

#include "../utils/fixed_point.h"
#include "noise.h"

static uint32_t RAND = 1; /* No need for unique seed */

uint32_t rando(void) {
  /* Blatant Park-Miller ripoff taken directly from Wikipedia. */
  /* uint32_t can be cast to arbitrary fixed point representation. */
  uint64_t product = (uint64_t)RAND * 48271;
  uint32_t x = (product & 0x7fffffff) + (product >> 31);
  x = (x & 0x7fffffff) + (x >> 31);
  RAND = x;
  return x;
}
