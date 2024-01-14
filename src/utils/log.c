#include <err.h>
#include <stdio.h>
#include <string.h>

#include "../audio/audio_init.h"
#include "../audio/audio_writer.h"
#include "../midi/midi_init.h"
#include "../midi/midi_parser.h"
#include "../synth/signal_generator.h"
#include "../synth/synth_init.h"
#include "log.h"

static FILE *LOG_FILE = NULL;

void statusReport(AudioWriter *aw, MidiParser *mp, Synth *sy) {
  if (LOG_FILE != NULL) {
    audioStatus(LOG_FILE, aw);
    midiStatus(LOG_FILE, mp);
    synthStatus(LOG_FILE, sy);
    fflush(LOG_FILE);
  }
}

void logger(char *s) {
  if      (strcmp(s, "stdout") == 0) { LOG_FILE = fopen("/dev/stdout", "w"); }
  else if (strcmp(s, "stderr") == 0) { LOG_FILE = fopen("/dev/stderr", "w"); }
  else                               { LOG_FILE = fopen(s, "w");             }
  if (LOG_FILE == NULL) { errx(1, "Couldn't open log file %s", s); }
}

void killLogger(void) {
  if (LOG_FILE != NULL) { fclose(LOG_FILE); }
}

