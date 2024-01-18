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

OneBitArray oneBitArray(void) {
  OneBitArray ba = {0};
  ba.size = ONE_BIT_ARRAY_SIZE;
  return ba;
}

uint8_t get1Bit(OneBitArray *ba, size_t i) {
 uint8_t b = ba->data[i >> 3];
 return b & (1 << (i % 8));
}

void push1Bit(OneBitArray *ba, size_t i) {
  ba->data[i >> 3] |= (1 << (i % 8));
  ba->population++;
}

void remove1Bit(OneBitArray *ba, size_t i) {
  uint8_t b = ba->data[i >> 3];
  ba->data[i >> 3] = b & ~(1 << (i % 8));
  ba->population--;
}

uint8_t highest1Bit(OneBitArray *ba) {
  size_t i = 0;
  size_t r = 0;
  uint8_t b = 0;
  if (ba->population < 1) { return 0; } 
  for (i = ba->size -1 ; i >= 0 ; i--) {
    if (ba->data[i] > 0) {
      b = ba->data[i];
      break;
    }
  }
  while (b >>= 1) { r++; }
  return (i << 3) + r;
}
