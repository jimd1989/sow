#include <stdio.h>
#include <stdlib.h>

#include "bit_array.h"

FourBitArray fourBitArray(void) {
  FourBitArray ba = {0};
  return ba;
}

uint8_t get4Bits(FourBitArray *ba, size_t i) {
 uint8_t b = ba->data[i >> 1];
 return (((b & 240) >> 4) * (i & 1)) | ((b & 15) * (!(i & 1)));
}

void push4Bits(FourBitArray *ba, size_t i, uint8_t n) {
  uint8_t x = ba->data[i >> 1];
  uint8_t neighbor = ((x & 15) * (i & 1)) | ((x & 240) * (!(i & 1)));
  n = (((n << 4) & 240) * (i & 1)) | ((n & 15) * (!(i & 1)));
  ba->data[i >> 1] = n | neighbor;
}
