#include <stdio.h> /* Delete later */
#include <unistd.h>

#include "midi_init.h"
#include "midi_parser.h"
#include "midi_reader.h"

static void printMidi(MidiReader *mr) {
  size_t i = 0;
  for (; i < mr->bytesRead ; i++) {
    printf("%d ", mr->data[i]);
  }
  printf("\n");
}

void parseMidi(MidiParser *mp) {
  readMidi(&mp->reader);
  if (mp->reader.bytesRead) {
    printMidi(&mp->reader);
  }
}
