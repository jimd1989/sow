#pragma once

#include <stdint.h>
#include <unistd.h>

/* A compressed array intended to hold 128 numbers [0 … 15]. */ 
#define FOUR_BIT_ARRAY_SIZE (size_t)64

typedef struct FourBitArray {
  uint8_t data[FOUR_BIT_ARRAY_SIZE];
} FourBitArray;

/* A compressed array intented to hold 128 numbers [0 … 1]. */
#define ONE_BIT_ARRAY_SIZE (size_t)16

typedef struct OneBitArray {
  size_t  population;  
  size_t  size;
  uint8_t data[ONE_BIT_ARRAY_SIZE];
} OneBitArray;

FourBitArray fourBitArray(void);
uint8_t get4Bits(FourBitArray *, size_t);
void push4Bits(FourBitArray *, size_t, uint8_t);
OneBitArray oneBitArray(void);
uint8_t get1Bit(OneBitArray *, size_t);
void push1Bit(OneBitArray *, size_t);
void remove1Bit(OneBitArray *, size_t);
uint8_t highest1Bit(OneBitArray *);
