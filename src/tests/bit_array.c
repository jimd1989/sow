#include <err.h>
#include <stdint.h>

#include "../utils/bit_array.h"
#include "bit_array.h"

void testBitArray(void) {
  FourBitArray ba = fourBitArray();
  uint8_t result = 0;
  warnx("bit array");
  warnx("  push a 4 bit value 2 to virtual index 62");
  push4Bits(&ba, 62, 2);
  result = get4Bits(&ba, 62);
  if (result != 2) {
    errx(-1, "expected 62; got %u", result);
  }
  warnx("  push a 4 bit value 3 to virtual index 63");
  push4Bits(&ba, 63, 3);
  result = get4Bits(&ba, 63);
  if (result != 3) {
    errx(-1, "expected 3; got %u", result);
  }
  warnx("  value at virtual index 62 remains same after push to 63");
  result = get4Bits(&ba, 62);
  if (result != 2) {
    errx(-1, "expected 62; got %u", result);
  }
}
