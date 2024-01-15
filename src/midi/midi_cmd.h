#pragma once

#include <stdint.h>

/* MIDI → sow command parsing target. Where possible, reuses well-known CC
 * numbers directly. Most others will be hidden behind CMD_NRPN. These values 
 * are read by the internal synthesizer command interpreter. */
typedef enum Cmd {
  CMD_UNKNOWN = 0,
  CMD_STATUS = 3,
  CMD_NRPN = 6,
  CMD_VOL = 7,
  CMD_NOTE_ON = 128,
  CMD_NOTE_OFF = 129
} Cmd;

/* Undefined CC channels: 9, 14, 15, 20-31, 85-90, 102-119 */

/* Non-standard CC commands are generally expected to be addressed with NRPN
 * values, which have a 14 bit resolution. All sow-specific commands can likely
 * be handled internally by the interpreter as one byte. Interpeting a NRPN
 * would mean reading CMD_NRPN, then a second byte from this enum, then two
 * more bytes representing its 14 bit argument. Many of these commands are
 * themselves pieces of full commands that require multiple arguments. */
typedef enum NrpnCmd {
  CMD_NRPN_UNKNOWN = 0,
  CMD_NRPN_AMP_CURVE,
  CMD_NRPN_KEY_SELECT,
  CMD_NRPN_KEY_TUNE,
  CMD_NRPN_DECIMAL_ADJUST
} NrpnCmd;

/* When a full NRPN MIDI message is sent (99, <MSB>, 98, <LSB>) the parsed
 * command buffer will be populated with two bytes, the first of which is
 * CMD_NRPN, which tells the command interpreter to look up a NRPN parameter
 * from this table, and the second is the table index at which to find the
 * parameter. The index will be scaled down from ((MSB << 7) | LSB) to a power
 * of 2, which should make it easier to select a paramter from a NRPN slider. */
#define SCALE_NRPN_CMD(X) ((X) >> 12)
static uint8_t CMD_NRPNS[4] = {
  CMD_NRPN_AMP_CURVE,
  CMD_NRPN_KEY_SELECT,
  CMD_NRPN_KEY_TUNE,
  CMD_NRPN_DECIMAL_ADJUST
};

/* The maximum NRPN value should generally be a whole number. This "snapping"
 * creates a discontinuity in the range, but can be desirable. */
#define CMD_NRPN_VAL_MAX ((1 << 14) - 1)
#define SNAP_MAX_NRPN_VAL(X) ((X) == CMD_NRPN_VAL_MAX ? (X) + 1 : (X))
