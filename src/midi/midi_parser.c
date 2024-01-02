#include <stdint.h>
#include <stdio.h> /* Delete later */
#include <unistd.h>

#include "midi_cmd.h"
#include "midi_init.h"
#include "midi_parser.h"
#include "midi_reader.h"

static void parseCC(MidiParser *);
static void readCmds(MidiParser *);
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

static void parseCC(MidiParser *mp) {
  mp->head++;
  mp->cmds[mp->bytesParsed++] = mp->reader.data[mp->head++];
  mp->cmds[mp->bytesParsed++] = mp->reader.data[mp->head++];
}

static void readCmds(MidiParser *mp) {
  int8_t b = 0;
  mp->bytesParsed = 0;
  mp->head = 0;
  while (mp->head < mp->reader.bytesRead) {
    b = mp->reader.data[mp->head];
    if (IS_CC(b)) { parseCC(mp); } 
    else          { mp->head++;  }
  }
}

void parseMidi(MidiParser *mp) {
  readMidi(&mp->reader);
  if (mp->reader.bytesRead) {
    readCmds(mp);
  }
}
