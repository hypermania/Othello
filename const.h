#ifndef CONST_H
#define CONST_H

#include <inttypes.h>
#include "macro.h"

extern const unsigned long int row_diag[256];
extern const unsigned long int row_rdiag[256];
extern const unsigned long int row_bdiag[256];

extern const int pow3[20];

extern const uint64_t pos_mask[BOARD_SIZE][BOARD_SIZE];

extern const uint64_t adj_pos_mask[BOARD_SIZE_SQR][ADJ_SIZE];


#endif
