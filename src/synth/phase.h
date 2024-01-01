#pragma once

#include "../utils/fixed_point.h"
#include <stdint.h>
#include <unistd.h>

void setPhase(size_t);
UF16_16 phaseIncrement(float);
