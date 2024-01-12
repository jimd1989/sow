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
#include "../waves/waves.h"
#include "io.h"

#include <err.h>

IO io(int argc, char **argv) {
  IO io = {0};
  AudioConfig ac = audioConfig(argc, argv);
  MidiConfig mc = midiConfig(argc, argv);
  SynthConfig sc = synthConfig(argc, argv);
  makeWaves();
  io.audio = audioWriter(ac);
  setPhase(io.audio.par.rate);
  io.midi = midiParser(mc);
  //warnx("INIT IO WITH %p", (void *)io.audio.synthData.floatData);
  io.synth = synth(sc, io.audio.synthData.data, io.audio.synthData.size, io.audio.synthData.floatData);
  io.synth.floatBuffer = io.audio.synthData.floatData;
  return io;
}

void monitor(IO io) {
  while (1) {
  //for (int i = 0 ; i < 100 ; i++) {
    //warnx("SYNTH IO %p", (void *)&io.audio.synthData.floatData);
    //warnx("AUDIO IO %p", (void *)io.synth.floatBuffer);
    parseMidi(&io.midi);
    interpretCmds(&io.midi, &io.synth, &io.audio);
    synthesize(&io.synth, io.audio.synthData.floatData);
    writeAudio(&io.audio);
  }
  killAudio(&io.audio);
  killMidi(&io.midi.reader);
}
