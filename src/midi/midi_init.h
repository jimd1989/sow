#pragma once

#include <sndio.h>
#include <stdbool.h>
#include <unistd.h>

#include "midi_config.h"
#include "midi_constants.h"

typedef struct mio_hdl Mio;

typedef struct MidiReader {
  bool      enabled;  
  size_t    bytesRead;
  size_t    chan;
  size_t    size;
  Mio     * mio;
  uint8_t   data[MIDI_BUFSIZE];
} MidiReader;

MidiReader midiReader(MidiConfig);
