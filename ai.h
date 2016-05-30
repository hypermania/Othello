#include <stdlib.h>

#include "state.h"
#include "game.h"

#ifndef AI_H
#define AI_H

// scoring functions (given state)
int total_pieces(State state, int side);
int consider_corner(State state, int side, int cor_param);

// state searching algorithms
int best_next_state(State state, Pos *moves, int movec);
int abpruning(State state, Pos *moves, int movec, int a, int b);



#endif

