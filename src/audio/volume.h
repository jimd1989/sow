#pragma once

#include <stdint.h>

#include "../utils/fixed_point.h"
#include "audio_init.h"

void setVolume(Fader *, int8_t);
int16_t mixVolume(Fader *, F16_16);

int16_t mixVolumeF(Fader *, double);
