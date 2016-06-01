#include <stdlib.h>
#include <limits.h>

#include "state.h"
#include "game.h"

#define TEMP_STORE (BOARD_SIZE*BOARD_SIZE/2)
#define MAXIMIZE 1
#define MINIMIZE 0 

#ifndef AI_H
#define AI_H

// does not provide error handling

// scoring functions (given state)
int total_pieces(State state, int side);
int consider_corner(State state, int side);

// state searching algorithms
int best_next_state(State state, Pos *moves, int movec);
int abpruning(State state, int depth, int a, int b, int side);



#endif

