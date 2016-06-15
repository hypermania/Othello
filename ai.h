#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

#include "state.h"
#include "board.h"
#include "table.h"


#ifndef AI_H
#define AI_H


#define MAXIMIZE 1
#define MINIMIZE 0 


// does not provide error handling

// heuristic scoring functions
int total_pieces(State state, int side);
//int consider_corner(State state, int side, int is_at_final);

int strategy_control(State state, Pos *moves, int movec, int param);

// state searching algorithms
int best_next_state(State state, Pos *moves, int movec, int param);

// scoring functions
int abpruning(State state, int depth, int a, int b, int side);
int mcts(State state, int width, int my_side);


#endif

