#include "midi_config.h"
#include "midi_init.h"
#include "midi_reader.h"

MidiParser midiParser(MidiConfig mc) {
  MidiParser mp = {0};
  mp.chan = mc.chan;
  mp.reader = midiReader(mc);
  return mp;
}
