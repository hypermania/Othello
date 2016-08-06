#include "evaluate.h"

BitMask flipVertical(BitMask mask){
  return __builtin_bswap64(mask);
}

BitMask flipDiagA1H8(BitMask mask){
  BitMask t;
  const BitMask k1 = 0x5500550055005500;
  const BitMask k2 = 0x3333000033330000;
  const BitMask k4 = 0x0f0f0f0f00000000;

  t = k4 & (mask ^ (mask << 28));
  mask ^= t ^ (t >> 28);
  t = k2 & (mask ^ (mask << 14));
  mask ^= t ^ (t >> 14);
  t = k1 & (mask ^ (mask << 7));
  mask ^= t ^ (t >> 7);

  return mask;
}

BitMask mirrorHorizontal(BitMask mask) {
  const BitMask k1 = 0x5555555555555555;
  const BitMask k2 = 0x3333333333333333;
  const BitMask k4 = 0x0f0f0f0f0f0f0f0f;

  mask = ((mask >> 1) & k1) | ((mask & k1) << 1);
  mask = ((mask >> 2) & k2) | ((mask & k2) << 2);
  mask = ((mask >> 4) & k4) | ((mask & k4) << 4);
  return mask;
}