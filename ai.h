#ifndef AI_H
#define AI_H

#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <float.h>
#include <stdarg.h>

#include "state.h"
#include "board.h"
#include "table.h"
#include "config.h"
#include "fit_weight.h"



// does not provide error handling

// heuristic scoring functions
int total_pieces(State state, int side);
double heuristic_score_0(State state);
double heuristic_score_1(State state);
double heuristic_score_2(State state);


//double get_score_for_move(State state, Pos move,  int param);
//double state_score(State state, int my_side, int param);


//int best_next_state(State state, Pos *moves, int movec, int param);

// move determination functions
int optimizing_move(State state, double (*score_func)(State));
int negamaxing_move(State state, int depth, double (*score_func)(State));
int negamaxing_move_dnstore(State state, int depth, double (*score_func)(State));

int mixed_move_dnstore(State state, int depth_middle, double (*score_func)(State), int depth_end);

// search functions
//double abpruning(State state, int depth, double a, double b, int side);
double negamax(State state, int depth, double alpha, double beta, int *max_move, double (*score_func)(State));
double negamax_dnstore(State state, int depth, double alpha, double beta, int *max_move, double (*score_func)(State));


#endif

