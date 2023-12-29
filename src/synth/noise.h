#pragma once

#include <stdint.h>
#include <unistd.h>

#include "../utils/fixed_point.h"

typedef uint32_t Rng;

Rng rng(void);
void noise(Rng *, F16_16 *, size_t);
