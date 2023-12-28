#include "../audio/audio_config.h"
#include "../audio/audio_init.h"
#include "../audio/audio_writer.h"
#include "io.h"
#include "../midi/midi_config.h"
#include "../midi/midi_init.h"
#include "../midi/midi_reader.h"

IO io(int argc, char **argv) {
  IO io = {0};
  io.audio = audioWriter(audioConfig(argc, argv));
  io.midi = midiReader(midiConfig(argc, argv));
  return io;
}

void monitor(IO io) {
  while (1) {
    readMidi(&io.midi);
    writeAudio(&io.audio);
  }
  killAudio(&io.audio);
  killMidi(&io.midi);
}
