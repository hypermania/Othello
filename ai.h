#ifndef AI_H
#define AI_H

#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <float.h>

#include "state.h"
#include "board.h"
#include "table.h"
#include "fit_weight.h"



#define MAXIMIZE 1
#define MINIMIZE 0 


// does not provide error handling

// heuristic scoring functions
int total_pieces(State state, int side);
int heuristic_score_1(State state, int side, int is_at_final);
double heuristic_score_2(State state);

double get_score_for_move(State state, Pos move,  int param);
double state_score(State state, int my_side, int param);
// state searching algorithms
int best_next_state(State state, Pos *moves, int movec, int param);

// scoring functions
double abpruning(State state, int depth, double a, double b, int side);
int mcts(State state, int width, int my_side);



#endif

