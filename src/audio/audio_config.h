#pragma once

#include <stdlib.h>

typedef struct AudioConfig {
  int     rate;
  size_t  blocks;
  size_t  chan;
} AudioConfig;

AudioConfig audioConfig(int, char **);
