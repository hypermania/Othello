// implements core game utilities



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "board.h"

#ifndef STATE_H
#define STATE_H


typedef struct {
  // info that determines the state
  char board[BOARD_SIZE_SQR];
  short turn;

  struct {
    // true when transposition info are filled accordingly
    bool trans_filled;
    // true when previous move data exists (dependent on external info)
    bool seq_valid; // seems useless, should delete
  } control;
  
  // transposition info (dependent only on board and turn)
  int movec;
  Pos moves[POS_STORE_SIZE];
  //double scores[POS_STORE_SIZE]; 
  char positions[POS_STORE_SIZE][BOARD_SIZE_SQR];

  // previous move data (dependent on external info)
  Pos seq[BOARD_SIZE_SQR];
  int seq_num;
} *State, State_store;

/* assertions for wrong inputs */

// return 0 at success, unless otherwise specified

State create_state(void);
int free_state(State state);
int cpy_state(State dest, State src);
int init_state(State state);

// success: return what it is supposed to get
int state_get_pos(State state, Pos pos);
int state_get_turn(State state);

// get opposite side; return -1 if side is not a side
int opposite_side(int side);

// return number of allowed moves at success
// is not considered an error if store == NULL
int allowed_moves(State state, Pos *store, int side);

// put a piece for side at pos, flipping other pieces accordingly
// no error check for whether piece is allowed to place there
// will place a piece there anyway in this case
// return # of pieces flipped
int place_piece(State state, Pos pos, int side);
int state_switch_turn(State state);

// return number of pieces given side (including empty spot)
int count_pieces(State state, int val);

// return 1 if this is a final state (neither player can move)
// 0 if not
int state_final(State state);

/* functions below have no error checking */

/* private functions for managing transposition data */
// fill all transposition data
void fill_trans(State state);
// copies board to dest and attempts to place for side at pos
// returns 1 when that positions is placeable
// returns 0 otherwise
// if 0 is returned, there is no guranteed behavior on dest
int try_to_place(Board board, Board dest, Pos pos, int side); 



/* private functions for managing past move data */
void record_seq(State state, Pos pos);


/* old private functions */

// success: return 0 for no and 1 for yes
int can_place_at(State state, Pos pos, int side);


#endif

