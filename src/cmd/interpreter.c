#include <err.h>

#include "../audio/audio_init.h"
#include "../audio/volume.h"
#include "../midi/midi_cmd.h"
#include "../midi/midi_init.h"
#include "interpreter.h"

static void volCmd(MidiParser *, AudioWriter *);

static void volCmd(MidiParser *mp, AudioWriter *aw) {
  setVolume(aw, mp->cmds[++mp->head]);
  mp->head++;
}

void interpretCmds(MidiParser *mp, AudioWriter *aw) {
  Cmd c = CMD_UNKNOWN;
  mp->head = 0;
  while (mp->head < mp->bytesParsed) {
    c = mp->cmds[mp->head];
    switch(c) {
      case CMD_VOL:
        volCmd(mp, aw);
        break;
      default:
        warnx("unknown command %d; dropping entire MIDI buffer", c);
        return;
    }
  }
} 
