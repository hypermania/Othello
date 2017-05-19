#ifndef MOVES_H
#define MOVES_H

#include "bitboard.h"
#include <x86intrin.h>

BitMask find_moves_bitmask(const BitBoard board, char side);
BitMask find_moves_bitmask_avx(const BitBoard board, char side);

BitMask *find_moves_bitmask_array(const BitBoard board, char side, int *movec);

#endif
