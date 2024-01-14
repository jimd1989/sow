#include <stdint.h>
#include <stdio.h> /* Delete later */
#include <unistd.h>

#include "midi_cmd.h"
#include "midi_init.h"
#include "midi_parser.h"
#include "midi_reader.h"

#define NRPN_VAL_MSB 6
#define NRPN_VAL_LSB 38
#define NRPN_LSB 98
#define NRPN_MSB 99

static void parseNoteOff(MidiParser *, Cmd);
static void parseNoteOn(MidiParser *, Cmd);
static void parseCC(MidiParser *, Cmd);
static void readCmds(MidiParser *);
/*
static void printMidi(MidiReader *);
static void printCmds(MidiParser *);

static void printMidi(MidiReader *mr) {
  size_t i = 0;
  for (; i < mr->bytesRead ; i++) {
    printf("%d ", mr->data[i]);
  }
  printf("\n");
}

static void printCmds(MidiParser *mp) {
  size_t i = 0;
  for (; i < mp->bytesParsed ; i++) {
    printf("%d ", mp->cmds[i]);
  }
  printf("\n");
}
*/

static void parseNoteOff(MidiParser *mp, Cmd c) {
  if (!CHAN_MATCH(c, mp->chan)) {
    mp->head += 3;
    return;
  }
  mp->head++;
  mp->cmds[mp->bytesParsed++] = CMD_NOTE_OFF;
  mp->cmds[mp->bytesParsed++] = mp->reader.data[mp->head++];
  mp->cmds[mp->bytesParsed++] = mp->reader.data[mp->head++];
}

static void parseNoteOn(MidiParser *mp, Cmd c) {
  uint8_t note = 0;
  uint8_t vel = 0;
  uint8_t cmd = 0;
  if (!CHAN_MATCH(c, mp->chan)) {
    mp->head += 3;
    return;
  }
  mp->head++;
  note = mp->reader.data[mp->head++];
  vel = mp->reader.data[mp->head++];
  cmd = vel ? CMD_NOTE_ON : CMD_NOTE_OFF; /* Note on with 0 vel = note off */
  mp->cmds[mp->bytesParsed++] = cmd;
  mp->cmds[mp->bytesParsed++] = note;
  mp->cmds[mp->bytesParsed++] = vel;
}

static void parseCC(MidiParser *mp, Cmd c) {
  if (!CHAN_MATCH(c, mp->chan)) {
    mp->head += 3;
    return;
  }
  switch (mp->reader.data[++mp->head]) {
    case NRPN_MSB:
      mp->head++;
      mp->nrpn.par = (127 & mp->reader.data[mp->head++]) << 7;
      break;
    case NRPN_LSB:
      mp->head++;
      mp->nrpn.par |= (127 & mp->reader.data[mp->head++]);
      mp->cmds[mp->bytesParsed++] = CMD_NRPN;
      mp->cmds[mp->bytesParsed++] = CMD_NRPNS[SCALE_NRPN_CMD(mp->nrpn.par)];
      break;
    case NRPN_VAL_MSB:
      mp->head++;
      mp->nrpn.valMsb = (127 & mp->reader.data[mp->head++]);
      break;
    case NRPN_VAL_LSB:
      mp->head++;
      mp->nrpn.valLsb = (127 & mp->reader.data[mp->head++]);
      mp->cmds[mp->bytesParsed++] = mp->nrpn.valMsb;
      mp->cmds[mp->bytesParsed++] = mp->nrpn.valLsb;
      break;
    default:
      mp->cmds[mp->bytesParsed++] = mp->reader.data[mp->head++];
      mp->cmds[mp->bytesParsed++] = mp->reader.data[mp->head++];
  }
}

static void readCmds(MidiParser *mp) {
  Cmd c = CMD_UNKNOWN;
  mp->bytesParsed = 0;
  mp->head = 0;
  while (mp->head < mp->reader.bytesRead) {
    c = mp->reader.data[mp->head];
    if      (IS_NOTE_ON(c))  { parseNoteOn(mp, c);  } 
    else if (IS_NOTE_OFF(c)) { parseNoteOff(mp, c); }
    else if (IS_CC(c))       { parseCC(mp, c);      } 
    else                     { mp->head++;          }
  }
}

void parseMidi(MidiParser *mp) {
  readMidi(&mp->reader);
  mp->bytesParsed = 0;
  if (mp->reader.bytesRead) {
    readCmds(mp);
  }
}
