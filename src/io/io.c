#include "../audio/audio_config.h"
#include "../audio/audio_init.h"
#include "../audio/audio_writer.h"
#include "io.h"
#include "../midi/midi_config.h"
#include "../midi/midi_init.h"
#include "../midi/midi_reader.h"
#include "../synth/signal_generator.h"
#include "../synth/synth_config.h"
#include "../synth/synth_init.h"

IO io(int argc, char **argv) {
  IO io = {0};
  AudioConfig ac = audioConfig(argc, argv);
  MidiConfig mc = midiConfig(argc, argv);
  SynthConfig sc = synthConfig(argc, argv);
  io.audio = audioWriter(ac);
  io.midi = midiReader(mc);
  io.synth = synth(sc, io.audio.synthData, io.audio.sizeFrames);
  return io;
}

void monitor(IO io) {
  while (1) {
    readMidi(&io.midi);
    synthesize(&io.synth);
    writeAudio(&io.audio);
  }
  killAudio(&io.audio);
  killMidi(&io.midi);
}
