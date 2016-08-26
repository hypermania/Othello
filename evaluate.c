#include "evaluate.h"

inline BitMask flipVertical(BitMask mask){
  return __builtin_bswap64(mask);
}

BitMask flipHorizontal(BitMask mask){
  const uint64_t k1 = 0x5555555555555555;
  const uint64_t k2 = 0x3333333333333333;
  const uint64_t k4 = 0x0f0f0f0f0f0f0f0f;
  mask = ((mask >> 1) & k1) | ((mask & k1) << 1);
  mask = ((mask >> 2) & k2) | ((mask & k2) << 2);
  mask = ((mask >> 4) & k4) | ((mask & k4) << 4);
  return mask;
}

inline BitMask flipDiagA1H8(BitMask mask){
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

inline BitMask rotate90Clockwise(BitMask mask){
  return flipVertical(flipDiagA1H8(mask));
}

inline BitMask rotate90CounterClockwise(BitMask mask){
  return flipDiagA1H8(flipVertical(mask));
}

inline BitMask rotate180(BitMask mask){
  return flipVertical(flipHorizontal(mask));
}

inline double evaluate(BitState *state){

  int cat = CAT(__builtin_popcountll(state->board.w) +
		__builtin_popcountll(state->board.b));
  
  double score = 0;

  // group theoretic notations for flipped/rotated board:
  // r is for counter-clockwise rotation
  // s is for flip of all columns (flipVertical)

  BitBoard e = state->board;
  
  BitBoard s = (BitBoard) {flipVertical(e.w),
			   flipVertical(e.b)};
  
  BitBoard r = (BitBoard) {rotate90CounterClockwise(e.w),
			   rotate90CounterClockwise(e.b)};
  
  BitBoard r2 = (BitBoard) {rotate180(e.w),
			    rotate180(e.b)};

  BitBoard r3 = (BitBoard) {rotate90Clockwise(e.w),
			    rotate90Clockwise(e.b)};

  // A1-H8 diagonal flip
  BitBoard sr = (BitBoard) {flipVertical(r.w),
			    flipVertical(r.b)};

  // Horizontal flip
  BitBoard sr2 = (BitBoard) {flipVertical(r2.w),
			     flipVertical(r2.b)};
  // A8-H1 diagonal flip
  BitBoard sr3 = (BitBoard) {flipVertical(r3.w),
			     flipVertical(r3.b)};

  //BitBoard *e_ptr = (BitBoard *)state;
  //BitBoard *s_ptr = &s;
  //BitBoard *r_ptr = &r;
  //BitBoard *r2_ptr = &r2;
  //BitBoard *r3_ptr = &r3;
  BitBoard *sr_ptr = &sr;
  //BitBoard *sr2_ptr = &sr2;
  //BitBoard *sr3_ptr = &sr3;
  

  // row 1-8
  uint8_t e_w_r1 = *((uint8_t *)state + 0);
  uint8_t e_w_r2 = *((uint8_t *)state + 1);
  uint8_t e_w_r3 = *((uint8_t *)state + 2);
  uint8_t e_w_r4 = *((uint8_t *)state + 3);
  uint8_t e_w_r5 = *((uint8_t *)state + 4);
  uint8_t e_w_r6 = *((uint8_t *)state + 5);
  uint8_t e_w_r7 = *((uint8_t *)state + 6);
  uint8_t e_w_r8 = *((uint8_t *)state + 7);

  uint8_t e_b_r1 = *((uint8_t *)state + 8);
  uint8_t e_b_r2 = *((uint8_t *)state + 9);
  uint8_t e_b_r3 = *((uint8_t *)state + 10);
  uint8_t e_b_r4 = *((uint8_t *)state + 11);
  uint8_t e_b_r5 = *((uint8_t *)state + 12);
  uint8_t e_b_r6 = *((uint8_t *)state + 13);
  uint8_t e_b_r7 = *((uint8_t *)state + 14);
  uint8_t e_b_r8 = *((uint8_t *)state + 15);

  /*
  score += row_1[cat][offset_6561[e_w_r1] + _pext_u32(e_b_r1, ~e_w_r1)];
  score += row_2[cat][offset_6561[e_w_r2] + _pext_u32(e_b_r2, ~e_w_r2)];
  score += row_3[cat][offset_6561[e_w_r3] + _pext_u32(e_b_r3, ~e_w_r3)];
  score += row_4[cat][offset_6561[e_w_r4] + _pext_u32(e_b_r4, ~e_w_r4)];
  score += row_4[cat][offset_6561[e_w_r5] + _pext_u32(e_b_r5, ~e_w_r5)];
  score += row_3[cat][offset_6561[e_w_r6] + _pext_u32(e_b_r6, ~e_w_r6)];
  score += row_2[cat][offset_6561[e_w_r7] + _pext_u32(e_b_r7, ~e_w_r7)];
  score += row_1[cat][offset_6561[e_w_r8] + _pext_u32(e_b_r8, ~e_w_r8)];
  */
  

  score += row_1[cat][e_w_r1][e_b_r1];
  score += row_2[cat][e_w_r2][e_b_r2];
  score += row_3[cat][e_w_r3][e_b_r3];
  score += row_4[cat][e_w_r4][e_b_r4];
  score += row_4[cat][e_w_r5][e_b_r5];
  score += row_3[cat][e_w_r6][e_b_r6];
  score += row_2[cat][e_w_r7][e_b_r7];
  score += row_1[cat][e_w_r8][e_b_r8];

  
  /*
  double score_0 = row_1[cat][e_w_r1][e_b_r1];
  double score_1 = row_2[cat][e_w_r2][e_b_r2];
  double score_2 = row_3[cat][e_w_r3][e_b_r3];
  double score_3 = row_4[cat][e_w_r4][e_b_r4];
  double score_4 = row_4[cat][e_w_r5][e_b_r5];
  double score_5 = row_3[cat][e_w_r6][e_b_r6];
  double score_6 = row_2[cat][e_w_r7][e_b_r7];
  double score_7 = row_1[cat][e_w_r8][e_b_r8];

  score +=
    score_0 +
    score_1 +
    score_2 +
    score_3 +
    score_4 +
    score_5 +
    score_6 +
    score_7;
  */


  
  // column A-H
  uint8_t sr_w_r1 = *((uint8_t *)sr_ptr + 0);
  uint8_t sr_w_r2 = *((uint8_t *)sr_ptr + 1);
  uint8_t sr_w_r3 = *((uint8_t *)sr_ptr + 2);
  uint8_t sr_w_r4 = *((uint8_t *)sr_ptr + 3);
  uint8_t sr_w_r5 = *((uint8_t *)sr_ptr + 4);
  uint8_t sr_w_r6 = *((uint8_t *)sr_ptr + 5);
  uint8_t sr_w_r7 = *((uint8_t *)sr_ptr + 6);
  uint8_t sr_w_r8 = *((uint8_t *)sr_ptr + 7);

  uint8_t sr_b_r1 = *((uint8_t *)sr_ptr + 8);
  uint8_t sr_b_r2 = *((uint8_t *)sr_ptr + 9);
  uint8_t sr_b_r3 = *((uint8_t *)sr_ptr + 10);
  uint8_t sr_b_r4 = *((uint8_t *)sr_ptr + 11);
  uint8_t sr_b_r5 = *((uint8_t *)sr_ptr + 12);
  uint8_t sr_b_r6 = *((uint8_t *)sr_ptr + 13);
  uint8_t sr_b_r7 = *((uint8_t *)sr_ptr + 14);
  uint8_t sr_b_r8 = *((uint8_t *)sr_ptr + 15);

  /*
  score += row_1[cat][offset_6561[sr_w_r1] + _pext_u32(sr_b_r1, ~sr_w_r1)];
  score += row_2[cat][offset_6561[sr_w_r2] + _pext_u32(sr_b_r2, ~sr_w_r2)];
  score += row_3[cat][offset_6561[sr_w_r3] + _pext_u32(sr_b_r3, ~sr_w_r3)];
  score += row_4[cat][offset_6561[sr_w_r4] + _pext_u32(sr_b_r4, ~sr_w_r4)];
  score += row_4[cat][offset_6561[sr_w_r5] + _pext_u32(sr_b_r5, ~sr_w_r5)];
  score += row_3[cat][offset_6561[sr_w_r6] + _pext_u32(sr_b_r6, ~sr_w_r6)];
  score += row_2[cat][offset_6561[sr_w_r7] + _pext_u32(sr_b_r7, ~sr_w_r7)];
  score += row_1[cat][offset_6561[sr_w_r8] + _pext_u32(sr_b_r8, ~sr_w_r8)];
  */


  score += row_1[cat][sr_w_r1][sr_b_r1];
  score += row_2[cat][sr_w_r2][sr_b_r2];
  score += row_3[cat][sr_w_r3][sr_b_r3];
  score += row_4[cat][sr_w_r4][sr_b_r4];
  score += row_4[cat][sr_w_r5][sr_b_r5];
  score += row_3[cat][sr_w_r6][sr_b_r6];
  score += row_2[cat][sr_w_r7][sr_b_r7];
  score += row_1[cat][sr_w_r8][sr_b_r8];

  
  // diagonals
  uint8_t e_w_d_A1 = _pext_u64(e.w, 0x8040201008040201);
  uint8_t e_w_d_B1 = _pext_u64(e.w, 0x4020100804020100);
  uint8_t e_w_d_C1 = _pext_u64(e.w, 0x2010080402010000);
  uint8_t e_w_d_D1 = _pext_u64(e.w, 0x1008040201000000);
  uint8_t e_w_d_E1 = _pext_u64(e.w, 0x0804020100000000);
  uint8_t e_w_d_A2 = _pext_u64(e.w, 0x0080402010080402);
  uint8_t e_w_d_A3 = _pext_u64(e.w, 0x0000804020100804);
  uint8_t e_w_d_A4 = _pext_u64(e.w, 0x0000008040201008);
  uint8_t e_w_d_A5 = _pext_u64(e.w, 0x0000000080402010);

  uint8_t e_b_d_A1 = _pext_u64(e.b, 0x8040201008040201);
  uint8_t e_b_d_B1 = _pext_u64(e.b, 0x4020100804020100);
  uint8_t e_b_d_C1 = _pext_u64(e.b, 0x2010080402010000);
  uint8_t e_b_d_D1 = _pext_u64(e.b, 0x1008040201000000);
  uint8_t e_b_d_E1 = _pext_u64(e.b, 0x0804020100000000);
  uint8_t e_b_d_A2 = _pext_u64(e.b, 0x0080402010080402);
  uint8_t e_b_d_A3 = _pext_u64(e.b, 0x0000804020100804);
  uint8_t e_b_d_A4 = _pext_u64(e.b, 0x0000008040201008);
  uint8_t e_b_d_A5 = _pext_u64(e.b, 0x0000000080402010);

  /*
  score += diag_8[cat][offset_6561[e_w_d_A1] + _pext_u32(e_b_d_A1, ~e_w_d_A1)];
  score += diag_7[cat][offset_2187[e_w_d_B1] + _pext_u32(e_b_d_B1, ~e_w_d_B1)];
  score += diag_7[cat][offset_2187[e_w_d_A2] + _pext_u32(e_b_d_A2, ~e_w_d_A2)];
  score += diag_6[cat][offset_729[e_w_d_C1] + _pext_u32(e_b_d_C1, ~e_w_d_C1)];
  score += diag_6[cat][offset_729[e_w_d_A3] + _pext_u32(e_b_d_A3, ~e_w_d_A3)];
  score += diag_5[cat][offset_243[e_w_d_D1] + _pext_u32(e_b_d_D1, ~e_w_d_D1)];
  score += diag_5[cat][offset_243[e_w_d_A4] + _pext_u32(e_b_d_A4, ~e_w_d_A4)];
  score += diag_4[cat][offset_81[e_w_d_E1] + _pext_u32(e_b_d_E1, ~e_w_d_E1)];
  score += diag_4[cat][offset_81[e_w_d_A5] + _pext_u32(e_b_d_A5, ~e_w_d_A5)];
  */


  score += diag_8[cat][e_w_d_A1][e_b_d_A1];
  score += diag_7[cat][e_w_d_B1][e_b_d_B1];
  score += diag_7[cat][e_w_d_A2][e_b_d_A2];
  score += diag_6[cat][e_w_d_C1][e_b_d_C1];
  score += diag_6[cat][e_w_d_A3][e_b_d_A3];
  score += diag_5[cat][e_w_d_D1][e_b_d_D1];
  score += diag_5[cat][e_w_d_A4][e_b_d_A4];
  score += diag_4[cat][e_w_d_E1][e_b_d_E1];
  score += diag_4[cat][e_w_d_A5][e_b_d_A5];

  
  
  // anti-diagonals
  uint8_t s_w_d_A1 = _pext_u64(s.w, 0x8040201008040201);
  uint8_t s_w_d_B1 = _pext_u64(s.w, 0x4020100804020100);
  uint8_t s_w_d_C1 = _pext_u64(s.w, 0x2010080402010000);
  uint8_t s_w_d_D1 = _pext_u64(s.w, 0x1008040201000000);
  uint8_t s_w_d_E1 = _pext_u64(s.w, 0x0804020100000000);
  uint8_t s_w_d_A2 = _pext_u64(s.w, 0x0080402010080402);
  uint8_t s_w_d_A3 = _pext_u64(s.w, 0x0000804020100804);
  uint8_t s_w_d_A4 = _pext_u64(s.w, 0x0000008040201008);
  uint8_t s_w_d_A5 = _pext_u64(s.w, 0x0000000080402010);

  uint8_t s_b_d_A1 = _pext_u64(s.b, 0x8040201008040201);
  uint8_t s_b_d_B1 = _pext_u64(s.b, 0x4020100804020100);
  uint8_t s_b_d_C1 = _pext_u64(s.b, 0x2010080402010000);
  uint8_t s_b_d_D1 = _pext_u64(s.b, 0x1008040201000000);
  uint8_t s_b_d_E1 = _pext_u64(s.b, 0x0804020100000000);
  uint8_t s_b_d_A2 = _pext_u64(s.b, 0x0080402010080402);
  uint8_t s_b_d_A3 = _pext_u64(s.b, 0x0000804020100804);
  uint8_t s_b_d_A4 = _pext_u64(s.b, 0x0000008040201008);
  uint8_t s_b_d_A5 = _pext_u64(s.b, 0x0000000080402010);

  /*
  score += diag_8[cat][offset_6561[s_w_d_A1] + _pext_u32(s_b_d_A1, ~s_w_d_A1)];
  score += diag_7[cat][offset_2187[s_w_d_B1] + _pext_u32(s_b_d_B1, ~s_w_d_B1)];
  score += diag_7[cat][offset_2187[s_w_d_A2] + _pext_u32(s_b_d_A2, ~s_w_d_A2)];
  score += diag_6[cat][offset_729[s_w_d_C1] + _pext_u32(s_b_d_C1, ~s_w_d_C1)];
  score += diag_6[cat][offset_729[s_w_d_A3] + _pext_u32(s_b_d_A3, ~s_w_d_A3)];
  score += diag_5[cat][offset_243[s_w_d_D1] + _pext_u32(s_b_d_D1, ~s_w_d_D1)];
  score += diag_5[cat][offset_243[s_w_d_A4] + _pext_u32(s_b_d_A4, ~s_w_d_A4)];
  score += diag_4[cat][offset_81[s_w_d_E1] + _pext_u32(s_b_d_E1, ~s_w_d_E1)];
  score += diag_4[cat][offset_81[s_w_d_A5] + _pext_u32(s_b_d_A5, ~s_w_d_A5)];
  */


  score += diag_8[cat][s_w_d_A1][s_b_d_A1];
  score += diag_7[cat][s_w_d_B1][s_b_d_B1];
  score += diag_7[cat][s_w_d_A2][s_b_d_A2];
  score += diag_6[cat][s_w_d_C1][s_b_d_C1];
  score += diag_6[cat][s_w_d_A3][s_b_d_A3];
  score += diag_5[cat][s_w_d_D1][s_b_d_D1];
  score += diag_5[cat][s_w_d_A4][s_b_d_A4];
  score += diag_4[cat][s_w_d_E1][s_b_d_E1];
  score += diag_4[cat][s_w_d_A5][s_b_d_A5];

  
  // corner_33
  uint32_t e_w_c33 = _pext_u64(e.w, 0xE0E0E00000000000);
  uint32_t e_b_c33 = _pext_u64(e.b, 0xE0E0E00000000000);
  uint32_t r_w_c33 = _pext_u64(r.w, 0xE0E0E00000000000);
  uint32_t r_b_c33 = _pext_u64(r.b, 0xE0E0E00000000000);
  uint32_t r2_w_c33 = _pext_u64(r2.w, 0xE0E0E00000000000);
  uint32_t r2_b_c33 = _pext_u64(r2.b, 0xE0E0E00000000000);
  uint32_t r3_w_c33 = _pext_u64(r3.w, 0xE0E0E00000000000);
  uint32_t r3_b_c33 = _pext_u64(r3.b, 0xE0E0E00000000000);

  score += corner_33[cat][offset_19683[e_w_c33] + _pext_u32(e_b_c33, ~e_w_c33)];
  score += corner_33[cat][offset_19683[r_w_c33] + _pext_u32(r_b_c33, ~r_w_c33)];
  score += corner_33[cat][offset_19683[r2_w_c33] + _pext_u32(r2_b_c33, ~r2_w_c33)];
  score += corner_33[cat][offset_19683[r3_w_c33] + _pext_u32(r3_b_c33, ~r3_w_c33)];

  /*
  score += corner_33[cat][e_w_c33][e_b_c33];
  score += corner_33[cat][r_w_c33][r_b_c33];
  score += corner_33[cat][r2_w_c33][r2_b_c33];
  score += corner_33[cat][r3_w_c33][r3_b_c33];
  */
  
  // corner_25
  uint32_t e_w_c25 = _pext_u64(e.w, 0xF8F8000000000000);
  uint32_t e_b_c25 = _pext_u64(e.b, 0xF8F8000000000000);
  uint32_t r_w_c25 = _pext_u64(r.w, 0xF8F8000000000000);
  uint32_t r_b_c25 = _pext_u64(r.b, 0xF8F8000000000000);
  uint32_t r2_w_c25 = _pext_u64(r2.w, 0xF8F8000000000000);
  uint32_t r2_b_c25 = _pext_u64(r2.b, 0xF8F8000000000000);
  uint32_t r3_w_c25 = _pext_u64(r3.w, 0xF8F8000000000000);
  uint32_t r3_b_c25 = _pext_u64(r3.b, 0xF8F8000000000000);
  uint32_t s_w_c25 = _pext_u64(s.w, 0xF8F8000000000000);
  uint32_t s_b_c25 = _pext_u64(s.b, 0xF8F8000000000000);
  uint32_t sr_w_c25 = _pext_u64(sr.w, 0xF8F8000000000000);
  uint32_t sr_b_c25 = _pext_u64(sr.b, 0xF8F8000000000000);
  uint32_t sr2_w_c25 = _pext_u64(sr2.w, 0xF8F8000000000000);
  uint32_t sr2_b_c25 = _pext_u64(sr2.b, 0xF8F8000000000000);
  uint32_t sr3_w_c25 = _pext_u64(sr3.w, 0xF8F8000000000000);
  uint32_t sr3_b_c25 = _pext_u64(sr3.b, 0xF8F8000000000000);


  score += corner_25[cat][offset_59049[e_w_c25] + _pext_u32(e_b_c25, ~e_w_c25)];
  score += corner_25[cat][offset_59049[r_w_c25] + _pext_u32(r_b_c25, ~r_w_c25)];
  score += corner_25[cat][offset_59049[r2_w_c25] + _pext_u32(r2_b_c25, ~r2_w_c25)];
  score += corner_25[cat][offset_59049[r3_w_c25] + _pext_u32(r3_b_c25, ~r3_w_c25)];
  score += corner_25[cat][offset_59049[s_w_c25] + _pext_u32(s_b_c25, ~s_w_c25)];
  score += corner_25[cat][offset_59049[sr_w_c25] + _pext_u32(sr_b_c25, ~sr_w_c25)];
  score += corner_25[cat][offset_59049[sr2_w_c25] + _pext_u32(sr2_b_c25, ~sr2_w_c25)];
  score += corner_25[cat][offset_59049[sr3_w_c25] + _pext_u32(sr3_b_c25, ~sr3_w_c25)];

  /*  
  score += corner_25[cat][e_w_c25][e_b_c25];
  score += corner_25[cat][r_w_c25][r_b_c25];
  score += corner_25[cat][r2_w_c25][r2_b_c25];
  score += corner_25[cat][r3_w_c25][r3_b_c25];
  score += corner_25[cat][s_w_c25][s_b_c25];
  score += corner_25[cat][sr_w_c25][sr_b_c25];
  score += corner_25[cat][sr2_w_c25][sr2_b_c25];
  score += corner_25[cat][sr3_w_c25][sr3_b_c25];
  */


  // edge_xx
  uint32_t e_w_xx = _pext_u64(e.w, 0xFF42000000000000);
  uint32_t e_b_xx = _pext_u64(e.b, 0xFF42000000000000);
  uint32_t r_w_xx = _pext_u64(r.w, 0xFF42000000000000);
  uint32_t r_b_xx = _pext_u64(r.b, 0xFF42000000000000);
  uint32_t r2_w_xx = _pext_u64(r2.w, 0xFF42000000000000);
  uint32_t r2_b_xx = _pext_u64(r2.b, 0xFF42000000000000);
  uint32_t r3_w_xx = _pext_u64(r3.w, 0xFF42000000000000);
  uint32_t r3_b_xx = _pext_u64(r3.b, 0xFF42000000000000);


  score += edge_xx[cat][offset_59049[e_w_xx] + _pext_u32(e_b_xx, ~e_w_xx)];
  score += edge_xx[cat][offset_59049[r_w_xx] + _pext_u32(r_b_xx, ~r_w_xx)];
  score += edge_xx[cat][offset_59049[r2_w_xx] + _pext_u32(r2_b_xx, ~r2_w_xx)];
  score += edge_xx[cat][offset_59049[r3_w_xx] + _pext_u32(r3_b_xx, ~r3_w_xx)];

  /*
  score += edge_xx[cat][e_w_xx][e_b_xx];
  score += edge_xx[cat][r_w_xx][r_b_xx];
  score += edge_xx[cat][r2_w_xx][r2_b_xx];
  score += edge_xx[cat][r3_w_xx][r3_b_xx];
  */
  
  return score;
}
