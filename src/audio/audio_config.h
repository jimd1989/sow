#pragma once

#include <stdlib.h>

typedef struct AudioConfig {
  size_t  rate;
  size_t  blocks;
  size_t  chan;
} AudioConfig;

AudioConfig audioConfig(int, char **);
