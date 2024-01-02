#include "../audio/audio_config.h"
#include "../audio/audio_init.h"
#include "../audio/audio_writer.h"
#include "io.h"
#include "../midi/midi_config.h"
#include "../midi/midi_init.h"
#include "../midi/midi_parser.h"
#include "../synth/phase.h"
#include "../synth/signal_generator.h"
#include "../synth/synth_config.h"
#include "../synth/synth_init.h"
#include "../waves/sine.h"

IO io(int argc, char **argv) {
  IO io = {0};
  AudioConfig ac = audioConfig(argc, argv);
  MidiConfig mc = midiConfig(argc, argv);
  SynthConfig sc = synthConfig(argc, argv);
  io.audio = audioWriter(ac);
  io.midi = midiParser(mc);
  io.synth = synth(sc, io.audio.synthData, io.audio.sizeFrames);
  makeSine();
  setPhase(io.audio.par.rate);
  return io;
}

void monitor(IO io) {
  while (1) {
    parseMidi(&io.midi);
    synthesize(&io.synth);
    writeAudio(&io.audio);
  }
  killAudio(&io.audio);
  killMidi(&io.midi.reader);
}
