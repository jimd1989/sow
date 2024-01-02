#pragma once

#define CMD_MIDI_SCALING_BITS 25
#define MIDI_CMD_TO_F16_16(X) ((X) << CMD_MIDI_SCALING_BITS)
