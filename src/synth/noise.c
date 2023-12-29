#include <stdint.h>
#include <unistd.h>

#include "../utils/fixed_point.h"
#include "noise.h"

static uint32_t rand(Rng *);

static uint32_t rand(Rng *r) {
  /* Blatant Park-Miller ripoff taken directly from Wikipedia. */
  /* uint32_t can be cast to arbitrary fixed point representation. */
  uint64_t product = (uint64_t)*r * 48271;
  uint32_t x = (product & 0x7fffffff) + (product >> 31);
  x = (x & 0x7fffffff) + (x >> 31);
  return *r = x;
}

Rng rng(void) {
  /* No need for unique seed */
  return 1;
}

void noise(Rng *r, F16_16 *buffer, size_t size) {
  size_t i = 0;
  for (; i < size ; i++) {
    buffer[i] = rand(r);
    buffer[i] *= 0.03f; /* Delete this later */
  }
}
