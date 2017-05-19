#include "bitstate.h"

// fill all transposition data
//static void bitstate_fill_moves(BitState *state);
// copies board to dest and attempts to place for side at pos
//static void bitstate_try_to_place_w(BitBoard *board, BitBoard *dest, BitMask pos);
//static void bitstate_try_to_place_b(BitBoard *board, BitBoard *dest, BitMask pos);


inline BitState *create_initial_bitstate(void){
  BitState *state = malloc(sizeof(BitState));
  state->board = new_initial_bitboard();
  state->turn = B;
  //state->control.moves_filled = false;
  //state->control.move_mask_filled = false;
  return state;
}

inline void init_bitstate(BitState *state){
  state->board = new_initial_bitboard();
  state->turn = B;
  //state->control.moves_filled = false;
  //state->control.move_mask_filled = false;
}

inline void free_bitstate(BitState *state){
  free(state);
}

inline void cpy_bitstate(BitState *dest, BitState *src){
  memcpy((void *)dest, (void *)src, sizeof(BitState));
}

inline BitMask bitstate_allowed_moves(BitState *state, int *movec){
  /*
  bitstate_fill_moves(state);
  if(movec != NULL){
    *movec = state->movec;
  }
  */
  BitMask ret = find_moves_bitmask_avx(state->board, state->turn);
  *movec = __builtin_popcountll(ret);
  return ret;
}

inline void bitstate_place_piece(BitState *state, BitMask pos){
  int pos_index = __builtin_clzll(pos);  
  
  if(state->turn == W)
    flip_bitboard_via_pext_w(&state->board, pos_index);
  else
    flip_bitboard_via_pext_b(&state->board, pos_index);
  
  //bitstate_fill_moves(state);
  //state->board = state->positions[move_num];
  state->turn = OPPOSITE_SIDE(state->turn);
  //state->control.moves_filled = false;
  //state->control.move_mask_filled = false;
}

inline void bitstate_skip_turn(BitState *state){

  state->turn = OPPOSITE_SIDE(state->turn);
  //state->control.moves_filled = false;
  //state->control.move_mask_filled = false;
}

int temp_movec;

inline int bitstate_final(BitState *state){
  return
    find_moves_bitmask_avx(state->board, state->turn) == 0
    && find_moves_bitmask_avx(state->board, OPPOSITE_SIDE(state->turn)) == 0;
  /*
  bitstate_allowed_moves(state, &temp_movec);
  if(temp_movec > 0){
    return 0;
  }
  
  if(find_moves_bitmask_avx(state->board, OPPOSITE_SIDE(state->turn)) == 0){
    return 1;
  } else {
    return 0;
  }
  */
}

/*
inline void bitstate_fill_moves(BitState *state){
  if(state->control.moves_filled){
    return;
  }

  state->movec = 0;

  BitMask moves;
  if(state->control.move_mask_filled){
    moves = state->move_mask;
  } else {
    moves = find_moves_bitmask_avx(state->board, state->turn);
  }

  if(state->turn == W){
    BitMask pos;
    for(; moves != 0; moves = my_blsr_u64(moves)){
      pos = my_blsi_u64(moves);
    
      bitstate_try_to_place_w(&state->board, &state->positions[state->movec], pos);
      state->moves[state->movec] = pos;
      state->movec++;

    }
  } else {
    BitMask pos;
    for(; moves != 0; moves = my_blsr_u64(moves)){
      pos = my_blsi_u64(moves);
    
      bitstate_try_to_place_b(&state->board, &state->positions[state->movec], pos);
      state->moves[state->movec] = pos;
      state->movec++;

    }
  }
  state->control.moves_filled = true;
  
}


inline void bitstate_try_to_place_w(BitBoard *board, BitBoard *dest, BitMask pos){
  cpy_bitboard(dest, board);

  int pos_index = __builtin_clzll(pos);
  
  //flip_bitboard_w[pos_index](dest);
  flip_bitboard_via_pext_w(dest, pos_index);

  return;
}

inline void bitstate_try_to_place_b(BitBoard *board, BitBoard *dest, BitMask pos){
  cpy_bitboard(dest, board);

  int pos_index = __builtin_clzll(pos);

  //flip_bitboard_b[pos_index](dest);
  flip_bitboard_via_pext_b(dest, pos_index);

  return;
}

*/

inline BitMask *bitstate_allowed_moves_array(BitState *state, int *movec) {
  return find_moves_bitmask_array(state->board, state->turn, movec);
}
