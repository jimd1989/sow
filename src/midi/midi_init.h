#pragma once

#include <sndio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "midi_config.h"
#include "midi_constants.h"
#include "midi_reader.h"

typedef struct MidiParser {
  size_t      chan;
  size_t      head;
  size_t      size;
  MidiReader  reader;
  uint8_t     cmds[MIDI_CMD_BUFSIZE];
} MidiParser;

MidiParser midiParser(MidiConfig);
