#include "moves.h"

inline BitMask find_moves_bitmask(const BitBoard board, char side) {

  BitMask my_bits;
  BitMask opp_bits;

  if(side == W){
    my_bits = board.w;
    opp_bits = board.b;
  } else {
    my_bits = board.b;
    opp_bits = board.w;
  }
  
  BitMask moves;
  BitMask opp_inner_bits;
  BitMask flip_bits;
  BitMask adjacent_opp_bits;

  opp_inner_bits = opp_bits & (unsigned long int)0x7E7E7E7E7E7E7E7E;

  // scan left of piece place
  flip_bits = (my_bits >> 1) & opp_inner_bits;
  flip_bits |= (flip_bits >> 1) & opp_inner_bits;

  adjacent_opp_bits = opp_inner_bits & (opp_inner_bits >> 1);
  flip_bits |= (flip_bits >> 2) & adjacent_opp_bits;
  flip_bits |= (flip_bits >> 2) & adjacent_opp_bits;

  moves = flip_bits >> 1;

  // scan right of piece place
  flip_bits = (my_bits << 1) & opp_inner_bits;
  flip_bits |= (flip_bits << 1) & opp_inner_bits;

  adjacent_opp_bits = opp_inner_bits & (opp_inner_bits << 1);
  flip_bits |= (flip_bits << 2) & adjacent_opp_bits;
  flip_bits |= (flip_bits << 2) & adjacent_opp_bits;

  moves |= flip_bits << 1;

  opp_inner_bits = opp_bits & (unsigned long int)0x00FFFFFFFFFFFF00;
  
  // scan up of piece place
  flip_bits = (my_bits >> 8) & opp_inner_bits;
  flip_bits |= (flip_bits >> 8) & opp_inner_bits;

  adjacent_opp_bits = opp_inner_bits & (opp_inner_bits >> 8);
  flip_bits |= (flip_bits >> 16) & adjacent_opp_bits;
  flip_bits |= (flip_bits >> 16) & adjacent_opp_bits;

  moves |= flip_bits >> 8;

  // scan down of piece place
  flip_bits = (my_bits << 8) & opp_inner_bits;
  flip_bits |= (flip_bits << 8) & opp_inner_bits;

  adjacent_opp_bits = opp_inner_bits & (opp_inner_bits << 8);
  flip_bits |= (flip_bits << 16) & adjacent_opp_bits;
  flip_bits |= (flip_bits << 16) & adjacent_opp_bits;

  moves |= flip_bits << 8;

  opp_inner_bits = opp_bits & (unsigned long int)0x007E7E7E7E7E7E00;
  
  // scan left_up
  flip_bits = (my_bits >> 9) & opp_inner_bits;
  flip_bits |= (flip_bits >> 9) & opp_inner_bits;

  adjacent_opp_bits = opp_inner_bits & (opp_inner_bits >> 9);
  flip_bits |= (flip_bits >> 18) & adjacent_opp_bits;
  flip_bits |= (flip_bits >> 18) & adjacent_opp_bits;

  moves |= flip_bits >> 9;

  // scan right_down
  flip_bits = (my_bits << 9) & opp_inner_bits;
  flip_bits |= (flip_bits << 9) & opp_inner_bits;

  adjacent_opp_bits = opp_inner_bits & (opp_inner_bits << 9);
  flip_bits |= (flip_bits << 18) & adjacent_opp_bits;
  flip_bits |= (flip_bits << 18) & adjacent_opp_bits;

  moves |= flip_bits << 9;

  // scan right_up
  flip_bits = (my_bits >> 7) & opp_inner_bits;
  flip_bits |= (flip_bits >> 7) & opp_inner_bits;

  adjacent_opp_bits = opp_inner_bits & (opp_inner_bits >> 7);
  flip_bits |= (flip_bits >> 14) & adjacent_opp_bits;
  flip_bits |= (flip_bits >> 14) & adjacent_opp_bits;

  moves |= flip_bits >> 7;

  // scan left_down
  flip_bits = (my_bits << 7) & opp_inner_bits;
  flip_bits |= (flip_bits << 7) & opp_inner_bits;

  adjacent_opp_bits = opp_inner_bits & (opp_inner_bits << 7);
  flip_bits |= (flip_bits << 14) & adjacent_opp_bits;
  flip_bits |= (flip_bits << 14) & adjacent_opp_bits;

  moves |= flip_bits << 7;

  
  moves &= ~(my_bits | opp_bits);
  
  return moves;
}

inline BitMask find_moves_bitmask_avx(const BitBoard board, char side) {
  
  __m256i my_bits;
  __m256i opp_bits;

  if(side == W){
    my_bits = _mm256_set1_epi64x(board.w);
    opp_bits = _mm256_set1_epi64x(board.b);
  } else {
    my_bits = _mm256_set1_epi64x(board.b);
    opp_bits = _mm256_set1_epi64x(board.w);
  }
  
  __m256i inner_mask; 
  __m256i shift_bits;
  __m256i shift_bits_twice;

  BitMask moves_combined;
  
  __m256i moves, moves1;
  __m256i opp_inner_bits;
  __m256i flip_bits, flip_bits1;
  __m256i adjacent_opp_bits, adjacent_opp_bits1;


  inner_mask = _mm256_setr_epi64x(0x7E7E7E7E7E7E7E7E, 0x00FFFFFFFFFFFF00,
				  0x007E7E7E7E7E7E00, 0x007E7E7E7E7E7E00);
  shift_bits = _mm256_setr_epi64x(1, 8, 9, 7);
  shift_bits_twice = _mm256_add_epi64(shift_bits, shift_bits);

  opp_inner_bits = _mm256_and_si256(opp_bits, inner_mask);

  
  flip_bits = _mm256_and_si256(_mm256_srlv_epi64(my_bits, shift_bits), opp_inner_bits);
  flip_bits1 = _mm256_and_si256(_mm256_sllv_epi64(my_bits, shift_bits), opp_inner_bits);
  
  flip_bits = _mm256_or_si256(flip_bits, _mm256_and_si256(_mm256_srlv_epi64(flip_bits, shift_bits), opp_inner_bits));
  flip_bits1 = _mm256_or_si256(flip_bits1, _mm256_and_si256(_mm256_sllv_epi64(flip_bits1, shift_bits), opp_inner_bits));
  
  adjacent_opp_bits = _mm256_and_si256(opp_inner_bits, _mm256_srlv_epi64(opp_inner_bits, shift_bits));
  adjacent_opp_bits1 = _mm256_and_si256(opp_inner_bits, _mm256_sllv_epi64(opp_inner_bits, shift_bits));
  
  flip_bits = _mm256_or_si256(flip_bits, _mm256_and_si256(_mm256_srlv_epi64(flip_bits, shift_bits_twice), adjacent_opp_bits));
  flip_bits1 = _mm256_or_si256(flip_bits1, _mm256_and_si256(_mm256_sllv_epi64(flip_bits1, shift_bits_twice), adjacent_opp_bits1));
  
  flip_bits = _mm256_or_si256(flip_bits, _mm256_and_si256(_mm256_srlv_epi64(flip_bits, shift_bits_twice), adjacent_opp_bits));
  flip_bits1 = _mm256_or_si256(flip_bits1, _mm256_and_si256(_mm256_sllv_epi64(flip_bits1, shift_bits_twice), adjacent_opp_bits1));
  
  moves = _mm256_srlv_epi64(flip_bits, shift_bits);
  moves1 = _mm256_or_si256(moves, _mm256_sllv_epi64(flip_bits1, shift_bits));

  
  struct {
    BitMask x1;
    BitMask x2;
    BitMask x3;
    BitMask x4;
  } a;
  
  _mm256_store_si256((__m256i *)&a, moves1);
  moves_combined = a.x1 | a.x2 | a.x3 | a.x4;
  
  moves_combined &= ~(board.w | board.b);
  
  return moves_combined;
}

inline BitMask *find_moves_bitmask_array(const BitBoard board, char side, int *movec) {
  BitMask moves = find_moves_bitmask_avx(board, side);
  *movec = __builtin_popcountll(moves);

  BitMask *result = malloc(*movec * sizeof(BitMask));

  int i;
  for(i = 0; i < *movec; i++) {
    BitMask pos = my_blsi_u64(moves);
    result[i] = pos;
    moves = my_blsr_u64(moves);
  }
  
  return result;
}

