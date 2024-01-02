#pragma once

#include "fixed_point.h"

typedef struct Fader {
  F16_16  balance;  
  F16_16  new;
  F16_16  old;
} Fader;

void setFadePeriod(void);
void setFader(Fader *, F16_16);
F16_16 popFader(Fader *);
