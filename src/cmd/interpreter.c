#include <err.h>
#include <stdint.h>

#include "../audio/audio_init.h"
#include "../audio/volume.h"
#include "../midi/midi_cmd.h"
#include "../midi/midi_init.h"
#include "../synth/signal_generator.h"
#include "../synth/synth_init.h"
#include "interpreter.h"

static void volCmd(MidiParser *, AudioWriter *);
static void noteOnCmd(MidiParser *, Synth *, AudioWriter *);
static void noteOffCmd(MidiParser *, AudioWriter *);
static void interpretNrpnCmd(MidiParser *);

static void volCmd(MidiParser *mp, AudioWriter *aw) {
  setVolume(&aw->masterVol, mp->cmds[++mp->head]);
  mp->head++;
}

static void noteOnCmd(MidiParser *mp, Synth *sy, AudioWriter *aw) {
  mp->head++;
  setPitch(sy, mp->cmds[mp->head++]);
  setVolume(&aw->masterVol, mp->cmds[mp->head++]);
}

static void noteOffCmd(MidiParser *mp, AudioWriter *aw) {
  setVolume(&aw->masterVol, 0);
  mp->head += 3;
}

static void interpretNrpnCmd(MidiParser *mp) {
  uint16_t val = 0;
  mp->head++;
  switch (mp->cmds[mp->head++]) {
    case CMD_NRPN_AMP_CURVE:
      warnx("Adjusting amplitude curve");
      break;
    case CMD_NRPN_KEY_SELECT:
      warnx("Selecting keyboard key");
      break;
    case CMD_NRPN_KEY_TUNE:
      warnx("Tuning keyboard key");
      break;
    case CMD_NRPN_UNKNOWN:
      warnx("Unknown NRPN cmd");
  }
  val = (127 & mp->cmds[mp->head++]) << 7;
  val |= 127 & mp->cmds[mp->head++];
  warnx("...with value %d", val);
}

void interpretCmds(MidiParser *mp, Synth *sy, AudioWriter *aw) {
  Cmd c = CMD_UNKNOWN;
  mp->head = 0;
  while (mp->head < mp->bytesParsed) {
    c = mp->cmds[mp->head];
    switch(c) {
      case CMD_NOTE_ON:
        noteOnCmd(mp, sy, aw);
        break;
      case CMD_NOTE_OFF:
        noteOffCmd(mp, aw);
        break;
      case CMD_VOL:
        volCmd(mp, aw);
        break;
      case CMD_NRPN:
        interpretNrpnCmd(mp);
        break;
      default:
        warnx("unknown command %d; dropping entire MIDI buffer", c);
        return;
    }
  }
} 
