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
#include "../utils/log.h"
#include "../waves/waves.h"
#include "io.h"

void startIO(IO *io, int argc, char **argv) {
  AudioConfig ac = audioConfig(argc, argv);
  MidiConfig mc = midiConfig(argc, argv);
  SynthConfig c = synthConfig(argc, argv);
  makeWaves();
  io->audio = audioWriter(ac);
  setPhase(io->audio.par.rate);
  io->midi = midiParser(mc);
  startSynth(&io->synth, c, io->audio.synthData.data, io->audio.synthData.size);
}

void monitor(IO *io) {
  while (1) {
    parseMidi(&io->midi);
    interpretCmds(&io->midi, &io->synth, &io->audio);
    synthesize(&io->synth);
    writeAudio(&io->audio);
  }
  killAudio(&io->audio);
  killMidi(&io->midi.reader);
  killLogger();
}
