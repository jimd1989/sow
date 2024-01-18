#include <err.h>
#include <stdint.h>
#include <unistd.h>

#include "../utils/bit_array.h"
#include "bit_array.h"

void testBitArray(void) {
  FourBitArray ba = fourBitArray();
  OneBitArray oba = oneBitArray();
  uint8_t result = 0;
  size_t i = 0;
  warnx("bit array");
  warnx(" 4 bit array");
  warnx("  push a 4 bit value 2 to virtual index 62");
  push4Bits(&ba, 62, 2);
  result = get4Bits(&ba, 62);
  if (result != 2) {
    errx(-1, "expected 2; got %u", result);
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
    errx(-1, "expected 2; got %u", result);
  }
  warnx("  push a 4 bit value 0 to virtual index 62");
  push4Bits(&ba, 62, 0);
  result = get4Bits(&ba, 62);
  if (result != 0) {
    errx(-1, "expected 0; got %u", result);
  }
  warnx("  value at virtual index 63 remains the same after push to 62");
  result = get4Bits(&ba, 63);
  if (result != 3) {
    errx(-1, "expected 3; got %u", result);
  }
  warnx(" 1 bit array");
  warnx("  setting virtual indices [120 … 127] saturates last byte");
  for (i = 120 ; i < 128 ; i++) {
    push1Bit(&oba, i);
  }
  result = oba.data[127 >> 3];
  if (result != 255) {
    errx(-1, "expected 255; got %u", result);
  }
  warnx("  unsetting virtual index 127 makes last byte = 127");
  remove1Bit(&oba, 127);
  result = oba.data[127 >> 3];
  if (result != 127) {
    errx(-1, "expected 127; got %u", result);
  }
  warnx("  highest virtual index is now 126");
  result = highest1Bit(&oba);
  if (result != 126) {
    errx(-1, "expected 126; got %u", result);
  }
  warnx("  unsetting virtual index 120 makes last byte = 126");
  remove1Bit(&oba, 120);
  result = oba.data[127 >> 3];
  if (result != 126) {
    errx(-1, "expected 126; got %u", result);
  }
  warnx("  double unsetting has no further effect");
  remove1Bit(&oba, 120);
  result = oba.data[127 >> 3];
  if (result != 126) {
    errx(-1, "expected 126; got %u", result);
  }
  warnx("  highest virtual index is still 126");
  result = highest1Bit(&oba);
  if (result != 126) {
    errx(-1, "expected 126; got %u", result);
  }
}
