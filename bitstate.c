#include "bitstate.h"

inline BitState *create_initial_bitstate(void){
  BitState *state = malloc(sizeof(BitState));
  state->board = new_initial_bitboard();
  state->turn = B;
  state->control.moves_filled = false;
  state->control.move_mask_filled = false;
  return state;
}

inline void init_bitstate(BitState *state){
  state->board = new_initial_bitboard();
  state->turn = B;
  state->control.moves_filled = false;
  state->control.move_mask_filled = false;
}

inline void free_bitstate(BitState *state){
  free(state);
}

inline void cpy_bitstate(BitState *dest, BitState *src){
  memcpy((void *)dest, (void *)src, sizeof(BitState));
}

inline BitMask *bitstate_allowed_moves(BitState *state, int *movec){
  bitstate_fill_moves(state);
  if(movec != NULL){
    *movec = state->movec;
  }
  return state->moves;
}

inline void bitstate_place_piece(BitState *state, int move_num){
  assert(state->control.moves_filled);
  
  state->board = state->positions[move_num];
  state->turn = OPPOSITE_SIDE(state->turn);
  state->control.moves_filled = false;
  state->control.move_mask_filled = false;
}

inline void bitstate_skip_turn(BitState *state){
  assert(state->control.moves_filled);

  state->turn = OPPOSITE_SIDE(state->turn);
  state->control.moves_filled = false;
  state->control.move_mask_filled = false;
}

int temp_movec;

inline int bitstate_final(BitState *state){
  bitstate_allowed_moves(state, &temp_movec);
  if(temp_movec > 0){
    return 0;
  }
  
  if(find_moves_bitmask(state->board, OPPOSITE_SIDE(state->turn)) == 0){
    return 1;
  } else {
    return 0;
  }

}

inline void bitstate_fill_moves(BitState *state){
  if(state->control.moves_filled){
    return;
  }

  state->movec = 0;

  BitMask moves;
  if(state->control.move_mask_filled){
    moves = state->move_mask;
    //printf("correct: remaining = %d\n", 64 - (__builtin_popcountll(state->board.w) + __builtin_popcountll(state->board.b)));
  } else {
    moves = find_moves_bitmask(state->board, state->turn);
    //printf("fail: remaining = %d\n", 64 - (__builtin_popcountll(state->board.w) + __builtin_popcountll(state->board.b)));
  }
  
  BitMask pos;
  for(; moves != 0; moves = my_blsr_u64(moves)){
    pos = my_blsi_u64(moves);
    
    bitstate_try_to_place(&state->board, &state->positions[state->movec], pos, state->turn);
    state->moves[state->movec] = pos;
    state->movec++;

  }
  state->control.moves_filled = true;
  
}


inline void bitstate_try_to_place(BitBoard *board, BitBoard *dest, BitMask pos, char side){
  cpy_bitboard(dest, board);

  int pos_index = __builtin_clzll(pos);
  
  if(side == W){
    flip_bitboard_w[pos_index](dest);
  } else {
    flip_bitboard_b[pos_index](dest);
  }
  return;
}

inline BitMask find_moves_bitmask(const BitBoard board, char side){

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
  BitMask flip_bits; //BitMask flip_bits_1;
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
