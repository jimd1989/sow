#include <stdint.h>
#include <unistd.h>

#include "noise.h"

static uint32_t rand(Rng *);

static uint32_t rand(Rng *r) {
  /* Blatant Park-Miller ripoff taken directly from Wikipedia. */
  uint64_t product = (uint64_t)*r * 48271;
  uint32_t x = (product & 0x7fffffff) + (product >> 31);
  x = (x & 0x7fffffff) + (x >> 31);
  return *r = x;
}

Rng rng(void) {
  /* No need for unique seed */
  return 1;
}

void noise(Rng *r, int16_t *buffer, size_t size) {
  size_t i = 0;
  for (; i < size ; i++) {
    buffer[i] = rand(r);
    buffer[i] *= 0.03f; /* Delete this later */
  }
}
