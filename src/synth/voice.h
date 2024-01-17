#pragma once

#include <unistd.h>

#include "../utils/fixed_point.h"

typedef struct Voice {
  UF16_16 phase; /* Delete later */
  UF16_16 inc;   /* Delete later */
  F1_16   vol;   /* Delete later */
  /* 8 Envs */
  /* 8 Operators */
  /* - Calculate individual operator inc once at voice on */
} Voice;

void playVoice(Voice *, F16_16 *, size_t);
