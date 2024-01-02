#include "../audio/audio_config.h"
#include "../audio/audio_init.h"
#include "../audio/audio_writer.h"
#include "../cmd/interpreter.h"
#include "../midi/midi_config.h"
#include "../midi/midi_init.h"
#include "../midi/midi_parser.h"
#include "../synth/phase.h"
#include "../synth/signal_generator.h"
#include "../synth/synth_config.h"
#include "../synth/synth_init.h"
#include "../utils/fade.h"
#include "../waves/waves.h"
#include "io.h"

IO io(int argc, char **argv) {
  IO io = {0};
  AudioConfig ac = audioConfig(argc, argv);
  MidiConfig mc = midiConfig(argc, argv);
  SynthConfig sc = synthConfig(argc, argv);
  io.audio = audioWriter(ac);
  io.midi = midiParser(mc);
  io.synth = synth(sc, io.audio.synthData, io.audio.sizeFrames);
  makeWaves();
  setPhase(io.audio.par.rate);
  setFadePeriod();
  return io;
}

void monitor(IO io) {
  while (1) {
    parseMidi(&io.midi);
    interpretCmds(&io.midi, &io.audio);
    synthesize(&io.synth);
    writeAudio(&io.audio);
  }
  killAudio(&io.audio);
  killMidi(&io.midi.reader);
}
