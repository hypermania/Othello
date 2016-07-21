#ifndef FLIP_COMPUTATION_H
#define FLIP_COMPUTATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "macro.h"
#include "bitboard.h"
#include "const.h"

//char flip_bitboard_w_00(BitBoard *board);
//char flip_bitboard_w_01(BitBoard *board);


//#ifndef FLIP_BITBOARD
//#define FLIP_BITBOARD
extern char (* const flip_bitboard_w[BOARD_SIZE_SQR])(BitBoard *);
extern char (* const flip_bitboard_b[BOARD_SIZE_SQR])(BitBoard *);
//#endif

#endif
