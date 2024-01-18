#pragma once

#include <unistd.h>

typedef struct SynthConfig {
  size_t  placeholder;
} SynthConfig;

SynthConfig synthConfig(int, char **);
