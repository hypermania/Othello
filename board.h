// implements board interface
#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>



#define BOARD_SIZE 8
#define BOARD_SIZE_SQR (BOARD_SIZE * BOARD_SIZE)
#define POS_STORE_SIZE (BOARD_SIZE * BOARD_SIZE / 2)
#define ADJ_SIZE 8
#define X 0
#define W 1
#define B 2

typedef char *Board;//typedef int** Board;

typedef struct {
  char r;
  char c;
} Pos;

// return a new empty board, filled with X
Board create_board(void);

// return 0 at success
int free_board(Board board);
int init_board(Board board);

// return 0 if pos is a position on the board
// -1 otherwise
int check_pos(Pos pos);

// return -1 if val is not valid (not X/W/B)
// 0 otherwise
int check_val(char val);

// return -1 if side is not a side
// 0 otherwise
int check_side(char side);


/* return negative values below changed to assertions */

char board_get_pos(Board board, Pos pos);
int board_set_pos(Board board, Pos pos, char val);

// return number of elems in store at success
int adj_pos(Pos pos, Pos *store);

int adj_empty_pos(Board board, Pos pos, Pos *store);
// return number of elems of side (can be 0) and store them in "store"
// store == NULL is NOT an error
int adj_given_pos(Board board, Pos pos, Pos *store, char side);




#endif
