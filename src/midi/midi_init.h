#pragma once

#include <sndio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "midi_config.h"
#include "midi_constants.h"
#include "midi_reader.h"

typedef struct MidiParser {
  size_t      bytesParsed;
  size_t      chan;
  size_t      head;
  MidiReader  reader;
  uint8_t     cmds[MIDI_CMD_BUFSIZE];
} MidiParser;

MidiParser midiParser(MidiConfig);
