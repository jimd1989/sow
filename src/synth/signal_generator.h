#pragma once

#include <stdio.h>

#include "synth_init.h"

#include <stdint.h> /* Delete later */

void synthesize(Synth *);
void synthStatus(FILE *, Synth *);

/* Delete later */
void setPitch(Synth *, uint8_t);
