#pragma once

#include <unistd.h>

typedef struct SynthConfig {
  size_t  voices;
} SynthConfig;

SynthConfig synthConfig(int, char **);
