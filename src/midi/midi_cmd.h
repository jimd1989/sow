#pragma once

/* MIDI → sow command parsing target. Where possible, reuses well-known CC
 * numbers. These values are read by the internal synthesizer command
 * interpreter. */
typedef enum Cmd {
  CMD_UNKNOWN = 0,
  CMD_VOL = 7,
  CMD_NOTE_ON = 128,
  CMD_NOTE_OFF = 129
} Cmd;
