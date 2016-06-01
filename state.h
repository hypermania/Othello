// implements core game utilities
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#ifndef STATE_H
#define STATE_H

typedef struct {
  Board board;
  int turn; 
} *State, State_store;

clock_t start, end;
static double cpu_time_used;


// return 0 at success, unless otherwise specified
// return -k for error at k-th argument

State create_state(void);
int free_state(State state);
int cpy_state(State dest, State src);
int init_state(State state);

// success: return what it is supposed to get
int state_get_pos(State state, Pos pos);
int state_get_turn(State state);

// get opposite side; return -1 if side is not a side
int opposite_side(int side);

// success: return 0 for no and 1 for yes
int can_place_at(State state, Pos pos, int side);
// return number of allowed moves at success
// is not considered an error if store == NULL
int allowed_moves(State state, Pos *store, int side);

// put a piece for side at pos, flipping other pieces accordingly
// no error check for whether piece is allowed to place there
// will place a piece there anyway in this case
// return # of pieces flipped
int place_piece(State state, Pos pos, int side);
int state_switch_turn(State state);

// return number of pieces given side
// return -2 also if side is neither black or white
int count_pieces(State state, int side);

// return 1 if this is a final state (neither player can move)
// 0 if not
int state_final(State state);


#endif

