#pragma once

#include <stdint.h>
#include <unistd.h>

typedef uint32_t Rng;

Rng rng(void);
void noise(Rng *, int16_t *, size_t);
