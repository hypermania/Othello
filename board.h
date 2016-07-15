// implements board interface
#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "macro.h"

typedef char *Board;

typedef struct {
  char r;
  char c;
} Pos;

// return a new empty board, filled with X
inline Board create_board(void);

// return 0 at success
inline int free_board(Board board);
inline int init_board(Board board);
inline int cpy_board(Board dest, Board src);

// return 0 if pos is a position on the board
// -1 otherwise
inline int check_pos(Pos pos);

// return -1 if val is not valid (not X/W/B)
// 0 otherwise
inline int check_val(char val);

// return -1 if side is not a side
// 0 otherwise
inline int check_side(char side);

// get opposite side; return -1 if side is not a side
inline int opposite_side(char side);


/* return negative values below changed to assertions */

#ifndef BOARD_GET_POS
#define BOARD_GET_POS
extern inline char board_get_pos(Board board, Pos pos){
  return board[BOARD_SIZE * pos.r + pos.c];
}
#endif

#ifndef BOARD_SET_POS
#define BOARD_SET_POS
extern inline void board_set_pos(Board board, Pos pos, char val){
  board[BOARD_SIZE * pos.r + pos.c] =  (char) val;
}
#endif

// return number of elems in store at success
int adj_pos(Pos pos, Pos *store);

int adj_empty_pos(Board board, Pos pos, Pos *store);
// return number of elems of side (can be 0) and store them in "store"
// store == NULL is NOT an error
inline int adj_given_pos(Board board, Pos pos, Pos *store, char side);

// return number of pieces given side (including empty spot)
int count_pieces(Board board, char val);
// return the (number of squares of val1) - (number of squares of val2)

//inline int piece_diff(Board board, char val1, char val2);

#ifndef PIECE_DIFF
#define PIECE_DIFF
extern inline int piece_diff(Board board, char val1, char val2){
  int r, c;
  int count = 0;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      char val = board_get_pos(board, (Pos) {r,c});
      if(val == val1){
	count++;
      } else if(val == val2){
	count--;
      }
    }
  }
  return count;
}
#endif


#endif
