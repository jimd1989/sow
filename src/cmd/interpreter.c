#include <err.h>

#include "../audio/audio_init.h"
#include "../audio/volume.h"
#include "../midi/midi_cmd.h"
#include "../midi/midi_init.h"
#include "interpreter.h"

static void volCmd(MidiParser *, AudioWriter *);
static void noteOnCmd(MidiParser *, AudioWriter *);
static void noteOffCmd(MidiParser *, AudioWriter *);

static void volCmd(MidiParser *mp, AudioWriter *aw) {
  setVolume(&aw->masterVol, mp->cmds[++mp->head]);
  mp->head++;
}

static void noteOnCmd(MidiParser *mp, AudioWriter *aw) {
  setVolume(&aw->masterVol, 8);
  mp->head += 3;
}

static void noteOffCmd(MidiParser *mp, AudioWriter *aw) {
  setVolume(&aw->masterVol, 0);
  mp->head += 3;
}

void interpretCmds(MidiParser *mp, AudioWriter *aw) {
  Cmd c = CMD_UNKNOWN;
  mp->head = 0;
  while (mp->head < mp->bytesParsed) {
    c = mp->cmds[mp->head];
    switch(c) {
      case CMD_NOTE_ON:
        noteOnCmd(mp, aw);
        break;
      case CMD_NOTE_OFF:
        noteOffCmd(mp, aw);
        break;
      case CMD_VOL:
        volCmd(mp, aw);
        break;
      default:
        warnx("unknown command %d; dropping entire MIDI buffer", c);
        return;
    }
  }
} 
