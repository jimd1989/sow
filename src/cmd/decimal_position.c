#include <stdint.h>

#include <err.h> /* Delete later */

#include "../synth/keyboard.h"
#include "../synth/synth_init.h"
#include "decimal_position.h"

/* Since MIDI NRPN values are only 14 bits, naively converting the max value of
 * (1 << 14) - 1 to 16.16 fixed point format yields a maximum value of 0.25.
 * These values need to be left shifted to offer practical ranges to various
 * parameters, but this comes at the expense of decimal precision. "Musical"
 * decimal positions will be set by default. If this is insufficient, users can
 * dial in extremely high or low (but not both at once) values using a decimal
 * position command.
 *
 * This can likely be represented as a single NRPN value where:
 * - MSB = Decimal adjust target
 * - LSB = Decimal left shift value */

typedef enum AdjustableDecimal {
  DECIMAL_UNKNOWN = 0,
  DECIMAL_KEY_TUNING,   /* Tuning offset of a MIDI note                 */
  DECIMAL_OP_FREQ,      /* Frequency ratio (or fixed freq) of operators */
  DECIMAL_OP_MOD_DEPTH, /* Depth of modulation between operators        */
  DECIMAL_ENV_LEN       /* Envelope length (ideally in seconds)         */
} AdjustableDecimal;

/* Scale the incoming NRPN MSB into a power of 2 table index to find the decimal
 * adjust destination. */
#define SCALE_DECIMAL_TARGET(X) ((X) >> 12)
static uint8_t ADJUSTABLE_DECIMALS[4] = {
  DECIMAL_KEY_TUNING,
  DECIMAL_OP_FREQ,
  DECIMAL_OP_MOD_DEPTH,
  DECIMAL_ENV_LEN
};
#define DECIMAL_TARGET(X) (ADJUSTABLE_DECIMALS[SCALE_DECIMAL_TARGET(X)])
#define DECIMAL_POSITION(X) ((X) & 127)

void adjustDecimal(Synth *sy, uint16_t nrpnVal) {
  uint8_t shift = DECIMAL_POSITION(nrpnVal);
  AdjustableDecimal target = DECIMAL_TARGET(nrpnVal);
  switch (target) {
    case DECIMAL_KEY_TUNING:
      adjustTuningDecimal(&sy->keyboard, shift);
      break;
    case DECIMAL_OP_FREQ:
      warnx("Adjust operator frequency");
      break;
    case DECIMAL_OP_MOD_DEPTH:
      warnx("Adjust operator modulation depth");
      break;
    case DECIMAL_ENV_LEN:
      warnx("Adjust envelope length");
      break;
    case DECIMAL_UNKNOWN:
      break;
  }
}
