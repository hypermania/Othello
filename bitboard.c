#include "bitboard.h"


const BitBoard empty_bitboard = (BitBoard){0,0};
const BitBoard initial_bitboard = (BitBoard){ATOM(3,3) | ATOM(4,4) , ATOM(3,4) | ATOM(4,3)};

BitBoard new_empty_bitboard(void){
  return empty_bitboard;
}

BitBoard new_initial_bitboard(void){
  return initial_bitboard;
}

void cpy_bitboard(BitBoard *dest, BitBoard *src){
  memcpy(dest, src, sizeof(BitBoard));
}

/* The following codes are commented because they are defined in the header file.
   (This is done to ensure inlining.)
 */


inline char bitboard_get_pos(BitBoard *board, BitMask pos){
  if(pos & board->w){
    return W;
  } 
  if(pos & board->b){
    return B;
  } 
  return X;
}



inline char bitboard_get_pos_nonref(BitBoard board, BitMask pos){
  if(pos & board.w){
    return W;
  } 
  if(pos & board.b){
    return B;
  } 
  return X;
}



inline void bitboard_set_pos(BitBoard *board, BitMask pos, char val){
  if(val == B){
    board->b |= pos;
    board->w &= ~pos;
    return;
  }

  if(val == W){
    board->b &= ~pos;
    board->w |= pos;
    return;
  }

  board->b &= ~pos;
  board->w &= ~pos;
  return;
}



inline BitBoard bitboard_set_pos_nonref(BitBoard board, BitMask pos, char val){
  if(val == B){
    board.b |= pos;
    board.w &= ~pos;
    return board;
  }

  if(val == W){
    board.b &= ~pos;
    board.w |= pos;
    return board;
  }

  board.b &= ~pos;
  board.w &= ~pos;
  return board;
}



int bitboard_piece_diff(BitBoard board){
  return __builtin_popcountll(board.w) - __builtin_popcountll(board.b);
}

