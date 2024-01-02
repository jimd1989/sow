#include <stdint.h>

#include "../cmd/scaling.h"
#include "../utils/fixed_point.h"
#include "../waves/exp.h"
#include "audio_init.h"
#include "volume.h"

void setVolume(AudioWriter *aw, int8_t n) {
  aw->masterVol = F16_16_TO_F1_16(expo(MIDI_CMD_TO_F16_16(n)));
}
