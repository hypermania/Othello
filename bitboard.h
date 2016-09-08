#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#include "macro.h"
#include "const.h"

typedef struct {
  uint64_t w;
  uint64_t b;
} BitBoard;


typedef uint64_t BitMask;

extern const BitBoard empty_bitboard;
extern const BitBoard initital_bitboard;

extern inline BitBoard new_empty_bitboard(void);
extern inline BitBoard new_initial_bitboard(void);

#ifndef CPY_BITBOARD
#define CPY_BITBOARD
extern inline void cpy_bitboard(BitBoard *dest, BitBoard *src){
  memcpy(dest, src, sizeof(BitBoard));
}
#endif

#ifndef BITBOARD_GET_POS
#define BITBOARD_GET_POS
extern inline char bitboard_get_pos(BitBoard *board, BitMask pos){
  if(pos & board->w){
    return W;
  }
  if(pos & board->b){
    return B;
  }
  return EMPTY;

}
#endif

#ifndef BITBOARD_SET_POS
#define BITBOARD_SET_POS
extern inline void bitboard_set_pos(BitBoard *board, BitMask pos, char val){
  if(val == B){
    board->b |= pos;
    board->w &= ~pos;
    return;
  }

  if(val == W){
    board->b &= ~pos;
    board->w |= pos;
    return;
  }

  board->b &= ~pos;
  board->w &= ~pos;
  return;
}
#endif

#ifndef BITBOARD_GET_POS_NONREF
#define BITBOARD_GET_POS_NONREF
extern inline char bitboard_get_pos_nonref(BitBoard board, BitMask pos){
  if(pos & board.w){
    return W;
  } 
  if(pos & board.b){
    return B;
  } 
  return EMPTY;
}

#endif

#ifndef BITBOARD_SET_POS_NONREF
#define BITBOARD_SET_POS_NONREF
extern inline BitBoard bitboard_set_pos_nonref(BitBoard board, BitMask pos, char val){
  if(val == B){
    board.b |= pos;
    board.w &= ~pos;
    return board;
  }

  if(val == W){
    board.b &= ~pos;
    board.w |= pos;
    return board;
  }

  board.b &= ~pos;
  board.w &= ~pos;
  return board;
}
#endif

#ifndef BITBOARD_PIECE_DIFF
#define BITBOARD_PIECE_DIFF
extern inline int REGPARM(1) bitboard_piece_diff(BitBoard board) {
  return __builtin_popcountll(board.w) - __builtin_popcountll(board.b);
}
#endif

#endif

// find squares occupied by "side" adjacent to a given square
char bitboard_adj_given_pos(BitBoard *board, BitMask bitmask, char side);

/* bitmask utilities */

#ifndef BITMASK_TO_BITPOS
#define BITMASK_TO_BITPOS
extern inline char bitmask_to_bitpos(const BitMask mask){
  return __builtin_clzll(mask);
}
#endif

#ifndef OFFSET_BITMASK
#define OFFSET_BITMASK
extern inline BitMask offset_bitmask(const BitMask mask, char offset){
  if(offset > 0){
    return mask >> offset;
  } else {
    return mask << (-offset);
  }
}
#endif

#ifndef MY_BLSI_U64
#define MY_BLSI_U64
extern inline BitMask my_blsi_u64(BitMask mask){
  BitMask blsi;
  asm(
      "blsi %1, %0"
      : "=r" (blsi)
      : "r" (mask)
      );
  return blsi;//mask & -mask;
}
#endif

#ifndef MY_BLSR_U64
#define MY_BLSR_U64
extern inline BitMask my_blsr_u64(BitMask mask){
  BitMask blsr;
  asm(
      "blsr %1, %0"
      : "=r" (blsr)
      : "r" (mask)
      );
  return blsr;
  //return (mask - 1) & mask;
}

#ifndef BITMASK_SYMMETRY_OPERATIONS
#define BITMASK_SYMMETRY_OPERATIONS
extern inline BitMask flipVertical(BitMask mask){
  return __builtin_bswap64(mask);
}

extern inline BitMask flipHorizontal(BitMask mask){
  const uint64_t k1 = 0x5555555555555555;
  const uint64_t k2 = 0x3333333333333333;
  const uint64_t k4 = 0x0f0f0f0f0f0f0f0f;
  mask = ((mask >> 1) & k1) | ((mask & k1) << 1);
  mask = ((mask >> 2) & k2) | ((mask & k2) << 2);
  mask = ((mask >> 4) & k4) | ((mask & k4) << 4);
  return mask;
}

extern inline BitMask flipDiagA1H8(BitMask mask){
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

extern inline BitMask rotate90Clockwise(BitMask mask){
  return flipVertical(flipDiagA1H8(mask));
}

extern inline BitMask rotate90CounterClockwise(BitMask mask){
  return flipDiagA1H8(flipVertical(mask));
}

extern inline BitMask rotate180(BitMask mask){
  return flipVertical(flipHorizontal(mask));
}

#endif


#endif

