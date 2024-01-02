#pragma once

/* MIDI → sow command parsing target. Where possible, reuses well-known CC
 * numbers. These values are read by the internal synthesizer command
 * interpreter. */
typedef enum Cmd {
  CMD_UNKNOWN = 0,
  CMD_VOL = 7
} Cmd;
