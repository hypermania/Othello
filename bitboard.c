#include "bitboard.h"


const BitBoard empty_bitboard = (BitBoard){0,0};
const BitBoard initial_bitboard = (BitBoard){ATOM(3,3) | ATOM(4,4) , ATOM(3,4) | ATOM(4,3)};

inline BitBoard new_empty_bitboard(void){
  return empty_bitboard;
}

inline BitBoard new_initial_bitboard(void){
  return initial_bitboard;
}

inline void cpy_bitboard(BitBoard *dest, BitBoard *src){
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
  return EMPTY;
}



inline char bitboard_get_pos_nonref(BitBoard board, BitMask pos){
  if(pos & board.w){
    return W;
  } 
  if(pos & board.b){
    return B;
  } 
  return EMPTY;
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



inline int bitboard_piece_diff(BitBoard board){
  return __builtin_popcountll(board.w) - __builtin_popcountll(board.b);
}

inline char bitboard_adj_given_pos(BitBoard *board, BitMask bitmask, char side){
  uint64_t occupation;
  if(side == W){
    occupation = board->w;
  } else {
    occupation = board->b;
  }

  short bitpos = bitmask_to_bitpos(bitmask);
  
  uint64_t dir0 = adj_pos_mask[bitpos][0] & occupation;
  uint64_t dir1 = adj_pos_mask[bitpos][1] & occupation;
  uint64_t dir2 = adj_pos_mask[bitpos][2] & occupation;
  uint64_t dir3 = adj_pos_mask[bitpos][3] & occupation;
  uint64_t dir4 = adj_pos_mask[bitpos][4] & occupation;
  uint64_t dir5 = adj_pos_mask[bitpos][5] & occupation;
  uint64_t dir6 = adj_pos_mask[bitpos][6] & occupation;
  uint64_t dir7 = adj_pos_mask[bitpos][7] & occupation;

  char result = 0;

  if(dir0){
    result |= 0x01;
  }
  if(dir1){
    result |= 0x02;
  }
  if(dir2){
    result |= 0x04;
  }
  if(dir3){
    result |= 0x08;
  }
  if(dir4){
    result |= 0x10;
  }
  if(dir5){
    result |= 0x20;
  }
  if(dir6){
    result |= 0x40;
  }
  if(dir7){
    result |= 0x80;
  }
  
  return result;
}

inline char bitmask_to_bitpos(const BitMask mask){
  return __builtin_clzll(mask);
}

inline BitMask offset_bitmask(const BitMask mask, char offset){
  if(offset > 0){
    return mask >> offset;
  } else {
    return mask << (-offset);
  }
}
