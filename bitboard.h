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

typedef char BitPos;
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
  /*
  int64_t mask_w = pos & board->w;
  int64_t mask_b = pos & board->w;
  mask_w <<= __builtin_clzll(mask_w);
  mask_b <<= __builtin_clzll(mask_b);
  mask_w >>= 63;
  mask_b >>= 63;
  return (W & (char)mask_w) | (B & (char)mask_b);
  */
  
  /*
  int mask_w = ((!!(pos & board->w)) << 31) >> 31;
  int mask_b = ((!!(pos & board->b)) << 31) >> 31;
  return (W & (char)mask_w) | (B & (char)mask_b);
  */

  /*
  int mask_w = ((!(pos & board->w)) << 31) >> 31;
  int mask_b = ((!(pos & board->b)) << 31) >> 31;
  return (W & ~(char)mask_w) | (B & ~(char)mask_b);
  */


  if(pos & board->w){
    return W;
  }
  if(pos & board->b){
    return B;
  }
  return X;

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
  return X;
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
extern inline BitMask my_blsi_u64(const BitMask mask){
  return mask & -mask;
}
#endif

#ifndef MY_BLSR_U64
#define MY_BLSR_U64
extern inline BitMask my_blsr_u64(const BitMask mask){
  return (mask - 1) & mask;
}
#endif


/*
  Potential places for optimization:
  1. passing by reference rather than by value for the get_pos, set_pos functions
  2. regparm
  3. 
 */
