// implements core game utilities

#ifndef STATE_H
#define STATE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include "board.h"

typedef struct {
  // info that determines the state
  char board[BOARD_SIZE_SQR];
  short turn;

  struct {
    // true iff transposition info are filled accordingly
    bool moves_filled;
    // true iff score has been computed
    bool score_valid;
  } control;
  
  // transposition info (dependent only on board and turn)
  int movec;
  Pos moves[POS_STORE_SIZE];
  //double scores[POS_STORE_SIZE]; 
  char positions[POS_STORE_SIZE][BOARD_SIZE_SQR];

  // previous move data (dependent on external info)
  Pos seq[BOARD_SIZE_SQR];
  int seq_num;

  // score data
  double score;
} *State, State_store;

/* assertions are used for wrong inputs */

// return 0 at success, unless otherwise specified

State create_state(void);
int free_state(State state);
int cpy_state(State dest, State src);
int init_state(State state);
State create_state_from_pivot(Board board, short turn);

int state_eq_seq(State head, State state);

// return number of allowed moves at success
// is not considered an error if store == NULL
int allowed_moves(State state, Pos *store);
Pos *allowed_moves_inplace(State state, int *movec);

// put a piece for side at pos, flipping other pieces accordingly
// no error check for whether piece is allowed to place there
// will place a piece there anyway in this case
// return # of pieces flipped
int place_piece(State state, Pos pos);
int place_piece_indexed(State state, int move_num);
int skip_turn(State state);


// return 1 if this is a final state (neither player can move)
// 0 if not
int state_final(State state);

/* functions below have no error checking */

/* private functions for managing transposition data */
// fill all transposition data
void fill_moves(State state);
// copies board to dest and attempts to place for side at pos
// returns 1 when that positions is placeable
// returns 0 otherwise
// if 0 is returned, there is no guranteed behavior on dest
int try_to_place(Board board, Board dest, Pos pos, int side); 

/* private functions for managing past move data */
void record_seq(State state, Pos pos);

double state_compute_score(State state, double (*score_func)(State state));

#endif

