#ifndef BITSTATE_H
#define BITSTATE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <x86intrin.h>


#include "bitboard.h"

#include "flip_computation.h"
#include "moves.h"

typedef struct {
  // info that determines the state
  BitBoard board;
  short turn;

  /*
  struct {
    // true iff transposition info are filled accordingly
    bool moves_filled;
    bool move_mask_filled;
  } control;
  
  // transposition info (dependent only on board and turn)
  int movec;
  BitMask moves[POS_STORE_SIZE];
  BitBoard positions[POS_STORE_SIZE];
  
  BitMask move_mask;
  */
} BitState;


BitState *create_initial_bitstate(void);
void init_bitstate(BitState *state);
void free_bitstate(BitState *state);
void cpy_bitstate(BitState *dest, BitState *src);

BitMask bitstate_allowed_moves(BitState *state, int *movec); // keep
BitMask *bitstate_allowed_moves_array(BitState *state, int *movec);
void bitstate_place_piece(BitState *state, BitMask pos); // keep
void bitstate_skip_turn(BitState *state); // keep

// return 1 if this is a final state (neither player can move)
int bitstate_final(BitState *state); // keep



#endif
