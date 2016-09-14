#ifndef CONFCOUNT_H
#define CONFCOUNT_H

#include <x86intrin.h>

#include "bitboard.h"
#include "offset.h"
#include "symmetry_map.h"

/* 
   Counter for a single category, 
   corresponding exactly to the weights in weights.h.
*/
typedef struct {
  
  uint32_t row_1[256][256];
  uint32_t row_2[256][256];
  uint32_t row_3[256][256];
  uint32_t row_4[256][256];

  uint32_t diag_8[256][256];
  uint32_t diag_7[128][128];
  uint32_t diag_6[64][64];
  uint32_t diag_5[32][32];
  uint32_t diag_4[16][16];
  
  uint32_t corner_33[19683];
  uint32_t corner_25[59049];
  uint32_t edge_xx[59049];
  
} ConfigCounter;

// Increment a ConfigCounter against one BitBoard.
// The indexes incremented are exactly the indexes accessed when the same
// BitBoard is used to call evaluate().
void increment_confcount(ConfigCounter *ccount, BitBoard board);



#endif
