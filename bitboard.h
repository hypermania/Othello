#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <x86intrin.h>

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

extern inline BitBoard flipVertical_packed(BitBoard board){
  return (BitBoard) {__builtin_bswap64(board.w), __builtin_bswap64(board.b)};
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

extern inline BitBoard flipHorizontal_sse(BitBoard board){
  __m128i mask = _mm_set_epi64x((long long)board.b, (long long)board.w);
  const __m128i k1 = _mm_set_epi64x(0x5555555555555555, 0x5555555555555555);
  const __m128i k2 = _mm_set_epi64x(0x3333333333333333, 0x3333333333333333);
  const __m128i k4 = _mm_set_epi64x(0x0f0f0f0f0f0f0f0f, 0x0f0f0f0f0f0f0f0f);
  
  mask = _mm_or_si128(_mm_and_si128(_mm_srli_epi64(mask, 1), k1),
		      _mm_slli_epi64(_mm_and_si128(mask, k1), 1));
  mask = _mm_or_si128(_mm_and_si128(_mm_srli_epi64(mask, 2), k2),
		      _mm_slli_epi64(_mm_and_si128(mask, k2), 2));
  mask = _mm_or_si128(_mm_and_si128(_mm_srli_epi64(mask, 4), k4),
		      _mm_slli_epi64(_mm_and_si128(mask, k4), 4));
  
  BitBoard result;
  _mm_store_si128((__m128i *)&result, mask);
  return result;
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

extern inline BitBoard flipDiagA1H8_sse(BitBoard board){
  __m128i mask = _mm_set_epi64x((long long)board.b, (long long)board.w);
  __m128i t;
  const __m128i k1 = _mm_set_epi64x(0x5500550055005500, 0x5500550055005500);
  const __m128i k2 = _mm_set_epi64x(0x3333000033330000, 0x3333000033330000);
  const __m128i k4 = _mm_set_epi64x(0x0f0f0f0f00000000, 0x0f0f0f0f00000000);
  
  t = _mm_and_si128(k4, _mm_xor_si128(mask, _mm_slli_epi64(mask, 28)));
  mask = _mm_xor_si128(mask, _mm_xor_si128(t, _mm_srli_epi64(t, 28)));
  t = _mm_and_si128(k2, _mm_xor_si128(mask, _mm_slli_epi64(mask, 14)));
  mask = _mm_xor_si128(mask, _mm_xor_si128(t, _mm_srli_epi64(t, 14)));
  t = _mm_and_si128(k1, _mm_xor_si128(mask, _mm_slli_epi64(mask, 7)));
  mask = _mm_xor_si128(mask, _mm_xor_si128(t, _mm_srli_epi64(t, 7)));
  
  BitBoard result;
  _mm_store_si128((__m128i *)&result, mask);
  return result;
}

extern inline BitBoard flipDiagA1H8_avx(BitBoard board){
  __m128i mask = _mm_set_epi64x((long long)board.b, (long long)board.w);
  __m128i t;
  const __m128i k1 = _mm_set_epi64x(0x5500550055005500, 0x5500550055005500);
  const __m128i k2 = _mm_set_epi64x(0x3333000033330000, 0x3333000033330000);
  const __m128i k4 = _mm_set_epi64x(0x0f0f0f0f00000000, 0x0f0f0f0f00000000);
  
  t = _mm_and_si128(k4, _mm_xor_si128(mask, _mm_slli_epi64(mask, 28)));
  mask = _mm_xor_si128(mask, _mm_xor_si128(t, _mm_srli_epi64(t, 28)));
  t = _mm_and_si128(k2, _mm_xor_si128(mask, _mm_slli_epi64(mask, 14)));
  mask = _mm_xor_si128(mask, _mm_xor_si128(t, _mm_srli_epi64(t, 14)));
  t = _mm_and_si128(k1, _mm_xor_si128(mask, _mm_slli_epi64(mask, 7)));
  mask = _mm_xor_si128(mask, _mm_xor_si128(t, _mm_srli_epi64(t, 7)));
  
  BitBoard result;
  _mm_store_si128((__m128i *)&result, mask);
  return result;
}

extern inline BitMask rotate90Clockwise(BitMask mask){
  return flipVertical(flipDiagA1H8(mask));
}

extern inline BitBoard rotate90Clockwise_sse(BitBoard board){
  return flipVertical_packed(flipDiagA1H8_sse(board));
}

extern inline BitMask rotate90CounterClockwise(BitMask mask){
  return flipDiagA1H8(flipVertical(mask));
}

extern inline BitBoard rotate90CounterClockwise_sse(BitBoard board){
  return flipDiagA1H8_sse(flipVertical_packed(board));
}

extern inline BitMask rotate180(BitMask mask){
  return flipVertical(flipHorizontal(mask));
}

extern inline BitBoard rotate180_sse(BitBoard board){
  return flipVertical_packed(flipHorizontal_sse(board));
}


#endif


#endif

