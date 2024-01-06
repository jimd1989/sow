#include <math.h>
#include <stdint.h>

#include "pitch.h"

#define LOWEST_FREQUENCY 8.1757989156f

float hz(uint8_t note) {
  return LOWEST_FREQUENCY * powf(2.0f, (float)note / 12.0f);
}
