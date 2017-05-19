#ifndef FLIP_COMPUTATION_H
#define FLIP_COMPUTATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <x86intrin.h>

#include "macro.h"
#include "bitboard.h"
#include "const.h"


//char flip_bitboard_w_00(BitBoard *board);
//char flip_bitboard_w_01(BitBoard *board);


//#ifndef FLIP_BITBOARD
//#define FLIP_BITBOARD
//extern char (* const flip_bitboard_w[BOARD_SIZE_SQR])(BitBoard *);
//extern char (* const flip_bitboard_b[BOARD_SIZE_SQR])(BitBoard *);
//#endif

extern uint8_t flipped_bits[8][256][256];
extern uint64_t diags_store[15];
extern uint64_t * const diags;  // access via diags[c-r]
extern uint64_t anti_diags[15]; // access via anti_diags[r+c]

void init_flipped_bits(void);
void init_diags(void);

BitMask REGPARM(2) flip_bitboard_via_pext_w(BitBoard *board, int pos_index);
BitMask REGPARM(2) flip_bitboard_via_pext_b(BitBoard *board, int pos_index);

void REGPARM(2) flip_bitboard_w_assembly(BitBoard *board, int pos_index);

#endif
