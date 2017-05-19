#include "evaluate.h"


inline double evaluate(BitState *state){

  int cat = CAT(__builtin_popcountll(state->board.w) +
		__builtin_popcountll(state->board.b));

  double score = 0;
  
  // group theoretic notations for flipped/rotated board:
  // r is for counter-clockwise rotation
  // s is for flip of all columns (flipVertical)

  BitBoard e = state->board;
  
  //BitBoard s = (BitBoard) {flipVertical(e.w), flipVertical(e.b)};
  BitBoard s = flipVertical_packed(e);
  
  //BitBoard r = (BitBoard) {rotate90CounterClockwise(e.w), rotate90CounterClockwise(e.b)};
  BitBoard r = rotate90CounterClockwise_sse(e);
  
  //BitBoard r2 = (BitBoard) {rotate180(e.w), rotate180(e.b)};
  BitBoard r2 = rotate180_sse(e);

  //BitBoard r3 = (BitBoard) {rotate90Clockwise(e.w), rotate90Clockwise(e.b)};
  BitBoard r3 = rotate90Clockwise_sse(e);

  // A1-H8 diagonal flip
  //BitBoard sr = (BitBoard) {flipVertical(r.w), flipVertical(r.b)};
  BitBoard sr = flipVertical_packed(r);

  // Horizontal flip
  //BitBoard sr2 = (BitBoard) {flipVertical(r2.w), flipVertical(r2.b)};
  BitBoard sr2 = flipVertical_packed(r2);
  
  // A8-H1 diagonal flip
  //BitBoard sr3 = (BitBoard) {flipVertical(r3.w), flipVertical(r3.b)};
  BitBoard sr3 = flipVertical_packed(r3);

  //BitBoard *e_ptr = &state->board;
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


  score += row_1[cat][e_w_r1][e_b_r1];
  score += row_2[cat][e_w_r2][e_b_r2];
  score += row_3[cat][e_w_r3][e_b_r3];
  score += row_4[cat][e_w_r4][e_b_r4];
  score += row_4[cat][e_w_r5][e_b_r5];
  score += row_3[cat][e_w_r6][e_b_r6];
  score += row_2[cat][e_w_r7][e_b_r7];
  score += row_1[cat][e_w_r8][e_b_r8];

  
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

  
  return score;

}

inline double evaluate_0(BitState *state){

  int cat = 0;

  double score = 0;
  
  // group theoretic notations for flipped/rotated board:
  // r is for counter-clockwise rotation
  // s is for flip of all columns (flipVertical)

  BitBoard e = state->board;
  
  //BitBoard s = (BitBoard) {flipVertical(e.w), flipVertical(e.b)};
  BitBoard s = flipVertical_packed(e);
  
  //BitBoard r = (BitBoard) {rotate90CounterClockwise(e.w), rotate90CounterClockwise(e.b)};
  BitBoard r = rotate90CounterClockwise_sse(e);
  
  //BitBoard r2 = (BitBoard) {rotate180(e.w), rotate180(e.b)};
  BitBoard r2 = rotate180_sse(e);

  //BitBoard r3 = (BitBoard) {rotate90Clockwise(e.w), rotate90Clockwise(e.b)};
  BitBoard r3 = rotate90Clockwise_sse(e);

  // A1-H8 diagonal flip
  //BitBoard sr = (BitBoard) {flipVertical(r.w), flipVertical(r.b)};
  BitBoard sr = flipVertical_packed(r);

  // Horizontal flip
  //BitBoard sr2 = (BitBoard) {flipVertical(r2.w), flipVertical(r2.b)};
  BitBoard sr2 = flipVertical_packed(r2);
  
  // A8-H1 diagonal flip
  //BitBoard sr3 = (BitBoard) {flipVertical(r3.w), flipVertical(r3.b)};
  BitBoard sr3 = flipVertical_packed(r3);

  //BitBoard *e_ptr = &state->board;
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


  score += row_1[cat][e_w_r1][e_b_r1];
  score += row_2[cat][e_w_r2][e_b_r2];
  score += row_3[cat][e_w_r3][e_b_r3];
  score += row_4[cat][e_w_r4][e_b_r4];
  score += row_4[cat][e_w_r5][e_b_r5];
  score += row_3[cat][e_w_r6][e_b_r6];
  score += row_2[cat][e_w_r7][e_b_r7];
  score += row_1[cat][e_w_r8][e_b_r8];

  
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

  
  return score;

}


/*
inline double evaluate_use_avx(BitState *state){

  int cat = CAT(__builtin_popcountll(state->board.w) +
		__builtin_popcountll(state->board.b));

  double score = 0;
  
  ATTR_ALIGN(32) double buffer[16];
  __m256d *packed_buffer = (__m256d *)buffer;

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

  //BitBoard *e_ptr = &state->board;
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


  buffer[0] = row_1[cat][e_w_r1][e_b_r1];
  buffer[1] = row_2[cat][e_w_r2][e_b_r2];
  buffer[2] = row_3[cat][e_w_r3][e_b_r3];
  buffer[3] = row_4[cat][e_w_r4][e_b_r4];
  buffer[4] = row_4[cat][e_w_r5][e_b_r5];
  buffer[5] = row_3[cat][e_w_r6][e_b_r6];
  buffer[6] = row_2[cat][e_w_r7][e_b_r7];
  buffer[7] = row_1[cat][e_w_r8][e_b_r8];

  
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


  buffer[8] = row_1[cat][sr_w_r1][sr_b_r1];
  buffer[9] = row_2[cat][sr_w_r2][sr_b_r2];
  buffer[10] = row_3[cat][sr_w_r3][sr_b_r3];
  buffer[11] = row_4[cat][sr_w_r4][sr_b_r4];
  buffer[12] = row_4[cat][sr_w_r5][sr_b_r5];
  buffer[13] = row_3[cat][sr_w_r6][sr_b_r6];
  buffer[14] = row_2[cat][sr_w_r7][sr_b_r7];
  buffer[15] = row_1[cat][sr_w_r8][sr_b_r8];

  asm(
      "vmovapd %0, %%ymm2\n"
      "vmovapd %1, %%ymm3\n"
      "vmovapd %2, %%ymm4\n"
      "vmovapd %3, %%ymm5\n"
      ::
       "m" (packed_buffer[0]), "m" (packed_buffer[1]), "m" (packed_buffer[2]), "m" (packed_buffer[3])
      );


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


  buffer[0] = diag_8[cat][e_w_d_A1][e_b_d_A1];
  buffer[1] = diag_7[cat][e_w_d_B1][e_b_d_B1];
  buffer[2] = diag_7[cat][e_w_d_A2][e_b_d_A2];
  buffer[3] = diag_6[cat][e_w_d_C1][e_b_d_C1];
  buffer[4] = diag_6[cat][e_w_d_A3][e_b_d_A3];
  buffer[5] = diag_5[cat][e_w_d_D1][e_b_d_D1];
  buffer[6] = diag_5[cat][e_w_d_A4][e_b_d_A4];
  buffer[7] = diag_4[cat][e_w_d_E1][e_b_d_E1];
  buffer[8] = diag_4[cat][e_w_d_A5][e_b_d_A5];

  
  
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


  buffer[9] = diag_8[cat][s_w_d_A1][s_b_d_A1];
  buffer[10] = diag_7[cat][s_w_d_B1][s_b_d_B1];
  buffer[11] = diag_7[cat][s_w_d_A2][s_b_d_A2];
  buffer[12] = diag_6[cat][s_w_d_C1][s_b_d_C1];
  buffer[13] = diag_6[cat][s_w_d_A3][s_b_d_A3];
  buffer[14] = diag_5[cat][s_w_d_D1][s_b_d_D1];
  buffer[15] = diag_5[cat][s_w_d_A4][s_b_d_A4];

  asm(
      "vmovapd %0, %%ymm6\n"
      "vmovapd %1, %%ymm7\n"
      "vmovapd %2, %%ymm8\n"
      "vmovapd %3, %%ymm9\n"
      ::
       "m" (packed_buffer[0]), "m" (packed_buffer[1]), "m" (packed_buffer[2]), "m" (packed_buffer[3])
      );

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

  buffer[0] = corner_33[cat][offset_19683[e_w_c33] + _pext_u32(e_b_c33, ~e_w_c33)];
  buffer[1] = corner_33[cat][offset_19683[r_w_c33] + _pext_u32(r_b_c33, ~r_w_c33)];
  buffer[2] = corner_33[cat][offset_19683[r2_w_c33] + _pext_u32(r2_b_c33, ~r2_w_c33)];
  buffer[3] = corner_33[cat][offset_19683[r3_w_c33] + _pext_u32(r3_b_c33, ~r3_w_c33)];

  
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


  buffer[4] = corner_25[cat][offset_59049[e_w_c25] + _pext_u32(e_b_c25, ~e_w_c25)];
  buffer[5] = corner_25[cat][offset_59049[r_w_c25] + _pext_u32(r_b_c25, ~r_w_c25)];
  buffer[6] = corner_25[cat][offset_59049[r2_w_c25] + _pext_u32(r2_b_c25, ~r2_w_c25)];
  buffer[7] = corner_25[cat][offset_59049[r3_w_c25] + _pext_u32(r3_b_c25, ~r3_w_c25)];
  buffer[8] = corner_25[cat][offset_59049[s_w_c25] + _pext_u32(s_b_c25, ~s_w_c25)];
  buffer[9] = corner_25[cat][offset_59049[sr_w_c25] + _pext_u32(sr_b_c25, ~sr_w_c25)];
  buffer[10] = corner_25[cat][offset_59049[sr2_w_c25] + _pext_u32(sr2_b_c25, ~sr2_w_c25)];
  buffer[11] = corner_25[cat][offset_59049[sr3_w_c25] + _pext_u32(sr3_b_c25, ~sr3_w_c25)];


  // edge_xx
  uint32_t e_w_xx = _pext_u64(e.w, 0xFF42000000000000);
  uint32_t e_b_xx = _pext_u64(e.b, 0xFF42000000000000);
  uint32_t r_w_xx = _pext_u64(r.w, 0xFF42000000000000);
  uint32_t r_b_xx = _pext_u64(r.b, 0xFF42000000000000);
  uint32_t r2_w_xx = _pext_u64(r2.w, 0xFF42000000000000);
  uint32_t r2_b_xx = _pext_u64(r2.b, 0xFF42000000000000);
  uint32_t r3_w_xx = _pext_u64(r3.w, 0xFF42000000000000);
  uint32_t r3_b_xx = _pext_u64(r3.b, 0xFF42000000000000);


  buffer[12] = edge_xx[cat][offset_59049[e_w_xx] + _pext_u32(e_b_xx, ~e_w_xx)];
  buffer[13] = edge_xx[cat][offset_59049[r_w_xx] + _pext_u32(r_b_xx, ~r_w_xx)];
  buffer[14] = edge_xx[cat][offset_59049[r2_w_xx] + _pext_u32(r2_b_xx, ~r2_w_xx)];
  buffer[15] = edge_xx[cat][offset_59049[r3_w_xx] + _pext_u32(r3_b_xx, ~r3_w_xx)];
  
  asm(
      "vmovapd %0, %%ymm10\n"
      "vmovapd %1, %%ymm11\n"
      "vmovapd %2, %%ymm12\n"
      "vmovapd %3, %%ymm13\n"
      ::
       "m" (packed_buffer[0]), "m" (packed_buffer[1]), "m" (packed_buffer[2]), "m" (packed_buffer[3])
      );
  
  asm(
      "vaddpd %%ymm2, %%ymm3, %%ymm2\n"
      "vaddpd %%ymm4, %%ymm5, %%ymm4\n"
      "vaddpd %%ymm6, %%ymm7, %%ymm6\n"
      "vaddpd %%ymm8, %%ymm9, %%ymm8\n"
      "vaddpd %%ymm10, %%ymm11, %%ymm10\n"
      "vaddpd %%ymm12, %%ymm13, %%ymm12\n"
      
      "vaddpd %%ymm2, %%ymm4, %%ymm2\n"
      "vaddpd %%ymm6, %%ymm8, %%ymm6\n"
      "vaddpd %%ymm10, %%ymm12, %%ymm10\n"
      
      "vaddpd %%ymm2, %%ymm6, %%ymm2\n"
      //"vaddpd %%ymm10, %%ymm14, %%ymm10\n"
      
      //"vaddpd %%ymm2, %%ymm10, %%ymm15\n"

      "vmovapd %%ymm2, %0\n"
      :
      "=m" (buffer[0])
      );

  //printf("(1)\n a: %lf %lf %lf %lf\n b: %lf %lf %lf %lf\n c: %lf %lf %lf %lf\n d: %lf %lf %lf %lf\n", buffer[], buffer[], buffer[], buffer[], buffer[], buffer[], buffer[], buffer[], buffer[], buffer[], buffer[], buffer[], buffer[], buffer[], buffer[], buffer[]);

  score += buffer[0] + buffer[1] + buffer[2] + buffer[3];
  
  return score;
}
*/

inline double evaluate_use_avx(BitState *state){

  int cat = CAT(__builtin_popcountll(state->board.w) +
		__builtin_popcountll(state->board.b));
  
  // group theoretic notations for flipped/rotated board:
  // r is for counter-clockwise rotation
  // s is for flip of all columns (flipVertical)

  BitBoard e = state->board;
  
  //BitBoard s = (BitBoard) {flipVertical(e.w), flipVertical(e.b)};
  BitBoard s = flipVertical_packed(e);
  
  //BitBoard r = (BitBoard) {rotate90CounterClockwise(e.w), rotate90CounterClockwise(e.b)};
  BitBoard r = rotate90CounterClockwise_sse(e);
  
  //BitBoard r2 = (BitBoard) {rotate180(e.w), rotate180(e.b)};
  BitBoard r2 = rotate180_sse(e);

  //BitBoard r3 = (BitBoard) {rotate90Clockwise(e.w), rotate90Clockwise(e.b)};
  BitBoard r3 = rotate90Clockwise_sse(e);

  // A1-H8 diagonal flip
  //BitBoard sr = (BitBoard) {flipVertical(r.w), flipVertical(r.b)};
  BitBoard sr = flipVertical_packed(r);

  // Horizontal flip
  //BitBoard sr2 = (BitBoard) {flipVertical(r2.w), flipVertical(r2.b)};
  BitBoard sr2 = flipVertical_packed(r2);
  
  // A8-H1 diagonal flip
  //BitBoard sr3 = (BitBoard) {flipVertical(r3.w), flipVertical(r3.b)};
  BitBoard sr3 = flipVertical_packed(r3);

  //BitBoard *e_ptr = &state->board;
  //BitBoard *s_ptr = &s;
  //BitBoard *r_ptr = &r;
  //BitBoard *r2_ptr = &r2;
  //BitBoard *r3_ptr = &r3;
  BitBoard *sr_ptr = &sr;
  //BitBoard *sr2_ptr = &sr2;
  //BitBoard *sr3_ptr = &sr3;

  __m256d accum1 = _mm256_setzero_pd();
  __m256d accum2 = _mm256_setzero_pd();
  __m256d increment1, increment2;
  
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

  increment1 = _mm256_set_pd(row_1[cat][e_w_r1][e_b_r1], row_2[cat][e_w_r2][e_b_r2],
			    row_3[cat][e_w_r3][e_b_r3], row_4[cat][e_w_r4][e_b_r4]);
  accum1 = _mm256_add_pd(accum1, increment1);
  
  increment2 = _mm256_set_pd(row_4[cat][e_w_r5][e_b_r5], row_3[cat][e_w_r6][e_b_r6],
			    row_2[cat][e_w_r7][e_b_r7], row_1[cat][e_w_r8][e_b_r8]);
  accum2 = _mm256_add_pd(accum2, increment2);
  
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


  increment1 = _mm256_set_pd(row_1[cat][sr_w_r1][sr_b_r1],
			    row_2[cat][sr_w_r2][sr_b_r2],
			    row_3[cat][sr_w_r3][sr_b_r3],
			    row_4[cat][sr_w_r4][sr_b_r4]);
  accum1 = _mm256_add_pd(accum1, increment1);
  
  increment2 = _mm256_set_pd(row_4[cat][sr_w_r5][sr_b_r5],
			    row_3[cat][sr_w_r6][sr_b_r6],
			    row_2[cat][sr_w_r7][sr_b_r7],
			    row_1[cat][sr_w_r8][sr_b_r8]);
  accum2 = _mm256_add_pd(accum2, increment2);
  
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


  increment1 = _mm256_set_pd(diag_8[cat][e_w_d_A1][e_b_d_A1],
			    diag_7[cat][e_w_d_B1][e_b_d_B1],
			    diag_7[cat][e_w_d_A2][e_b_d_A2],
			    diag_6[cat][e_w_d_C1][e_b_d_C1]);
  accum1 = _mm256_add_pd(accum1, increment1);
  
  increment2 = _mm256_set_pd(diag_6[cat][e_w_d_A3][e_b_d_A3],
			    diag_5[cat][e_w_d_D1][e_b_d_D1],
			    diag_5[cat][e_w_d_A4][e_b_d_A4],
			    diag_4[cat][e_w_d_E1][e_b_d_E1]);
  accum2 = _mm256_add_pd(accum2, increment2);  
  
  
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

  increment1 = _mm256_set_pd(diag_4[cat][e_w_d_A5][e_b_d_A5],
			    diag_8[cat][s_w_d_A1][s_b_d_A1],
			    diag_7[cat][s_w_d_B1][s_b_d_B1],
			    diag_7[cat][s_w_d_A2][s_b_d_A2]);
  accum1 = _mm256_add_pd(accum1, increment1);

  increment2 = _mm256_set_pd(diag_6[cat][s_w_d_C1][s_b_d_C1],
			    diag_6[cat][s_w_d_A3][s_b_d_A3],
			    diag_5[cat][s_w_d_D1][s_b_d_D1],
			    diag_5[cat][s_w_d_A4][s_b_d_A4]);
  accum2 = _mm256_add_pd(accum2, increment2);
  
  increment1 = _mm256_set_pd(diag_4[cat][s_w_d_E1][s_b_d_E1],
			    diag_4[cat][s_w_d_A5][s_b_d_A5],
			    0.0,
			    0.0);
  accum1 = _mm256_add_pd(accum1, increment1);
  
  // corner_33
  uint32_t e_w_c33 = _pext_u64(e.w, 0xE0E0E00000000000);
  uint32_t e_b_c33 = _pext_u64(e.b, 0xE0E0E00000000000);
  uint32_t r_w_c33 = _pext_u64(r.w, 0xE0E0E00000000000);
  uint32_t r_b_c33 = _pext_u64(r.b, 0xE0E0E00000000000);
  uint32_t r2_w_c33 = _pext_u64(r2.w, 0xE0E0E00000000000);
  uint32_t r2_b_c33 = _pext_u64(r2.b, 0xE0E0E00000000000);
  uint32_t r3_w_c33 = _pext_u64(r3.w, 0xE0E0E00000000000);
  uint32_t r3_b_c33 = _pext_u64(r3.b, 0xE0E0E00000000000);

  increment2 = _mm256_set_pd(corner_33[cat][offset_19683[e_w_c33] + _pext_u32(e_b_c33, ~e_w_c33)],
			     corner_33[cat][offset_19683[r_w_c33] + _pext_u32(r_b_c33, ~r_w_c33)],
			     corner_33[cat][offset_19683[r2_w_c33] + _pext_u32(r2_b_c33, ~r2_w_c33)],
			     corner_33[cat][offset_19683[r3_w_c33] + _pext_u32(r3_b_c33, ~r3_w_c33)]);
  accum2 = _mm256_add_pd(accum2, increment2);
  
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


  increment1 = _mm256_set_pd(corner_25[cat][offset_59049[e_w_c25] + _pext_u32(e_b_c25, ~e_w_c25)],
			     corner_25[cat][offset_59049[r_w_c25] + _pext_u32(r_b_c25, ~r_w_c25)],
			     corner_25[cat][offset_59049[r2_w_c25] + _pext_u32(r2_b_c25, ~r2_w_c25)],
			     corner_25[cat][offset_59049[r3_w_c25] + _pext_u32(r3_b_c25, ~r3_w_c25)]);
  accum1 = _mm256_add_pd(accum1, increment1);
  
  increment2 = _mm256_set_pd(corner_25[cat][offset_59049[s_w_c25] + _pext_u32(s_b_c25, ~s_w_c25)],
			    corner_25[cat][offset_59049[sr_w_c25] + _pext_u32(sr_b_c25, ~sr_w_c25)],
			    corner_25[cat][offset_59049[sr2_w_c25] + _pext_u32(sr2_b_c25, ~sr2_w_c25)],
			    corner_25[cat][offset_59049[sr3_w_c25] + _pext_u32(sr3_b_c25, ~sr3_w_c25)]);
  accum2 = _mm256_add_pd(accum2, increment2);

  // edge_xx
  uint32_t e_w_xx = _pext_u64(e.w, 0xFF42000000000000);
  uint32_t e_b_xx = _pext_u64(e.b, 0xFF42000000000000);
  uint32_t r_w_xx = _pext_u64(r.w, 0xFF42000000000000);
  uint32_t r_b_xx = _pext_u64(r.b, 0xFF42000000000000);
  uint32_t r2_w_xx = _pext_u64(r2.w, 0xFF42000000000000);
  uint32_t r2_b_xx = _pext_u64(r2.b, 0xFF42000000000000);
  uint32_t r3_w_xx = _pext_u64(r3.w, 0xFF42000000000000);
  uint32_t r3_b_xx = _pext_u64(r3.b, 0xFF42000000000000);


  increment1 = _mm256_set_pd(edge_xx[cat][offset_59049[e_w_xx] + _pext_u32(e_b_xx, ~e_w_xx)],
			    edge_xx[cat][offset_59049[r_w_xx] + _pext_u32(r_b_xx, ~r_w_xx)],
			    edge_xx[cat][offset_59049[r2_w_xx] + _pext_u32(r2_b_xx, ~r2_w_xx)],
			    edge_xx[cat][offset_59049[r3_w_xx] + _pext_u32(r3_b_xx, ~r3_w_xx)]);
  accum1 = _mm256_add_pd(accum1, increment1);

  accum1 = _mm256_add_pd(accum1, accum2);
  
  double score[4];
  _mm256_store_pd(score, accum1);
  
  return score[0] + score[1] + score[2] + score[3];

}

