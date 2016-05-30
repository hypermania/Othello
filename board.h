// implements board interface
#include <stdlib.h>

// BOARD_SIZE >= 4 and is even

#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 8
#define ADJ_SIZE 8
#define X 0
#define W 1
#define B 2


typedef int** Board;


typedef struct {
  int r;
  int c;
} Pos;

// return a new empty board, filled with X
Board create_board(void);

// return 0 at success, -1 if board == NULL
int free_board(Board board);
int init_board(Board board);

// return 0 if pos is a position on the board
// -1 otherwise
int check_pos(Pos pos);

// return -1 if val is not valid (not X/W/B)
// 0 otherwise
int check_val(int val);

// return -1 if side is not a side
// 0 otherwise
int check_side(int side);


// return -1, -2, -3 for board, pos, val error, respectively
int board_get_pos(Board board, Pos pos);
int board_set_pos(Board board, Pos pos, int val);

// return number of elems in store at success
// does not malloc new space for store
// return -1, -2 for pos, store error, respectively
int adj_pos(Pos pos, Pos *store);
// return -1, -2, -3 for board, pos, store error, respectively
int adj_empty_pos(Board board, Pos pos, Pos *store);

#endif