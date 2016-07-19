#ifndef BITSTATE_H
#define BITSTATE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "board.h"
#include "bitboard.h"

typedef struct {
  // info that determines the state
  BitBoard board;
  short turn;

  struct {
    // true iff transposition info are filled accordingly
    bool moves_filled;
  } control;
  
  // transposition info (dependent only on board and turn)
  int movec;
  BitMask moves[POS_STORE_SIZE];
  BitBoard positions[POS_STORE_SIZE];
} BitState;


BitState *create_initial_bitstate(void);
void init_bitstate(BitState *state);
void free_bitstate(BitState *state);
void cpy_bitstate(BitState *dest, BitState *src);

BitMask *bitstate_allowed_moves(BitState *state, int *movec);
void bitstate_place_piece(BitState *state, int move_num);
void bitstate_skip_turn(BitState *state);

// return 1 if this is a final state (neither player can move)
int bitstate_final(BitState *state);

// fill all transposition data
void bitstate_fill_moves(BitState *state);
// copies board to dest and attempts to place for side at pos
// returns 1 when that positions is placeable
// returns 0 otherwise
// if 0 is returned, there is no guranteed behavior on dest
int bitstate_try_to_place(BitBoard *board, BitBoard *dest, BitMask pos, char side); 

BitMask find_moves_bitmask(const BitBoard board, char side);


#endif
