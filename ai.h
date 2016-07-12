#ifndef AI_H
#define AI_H

#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <float.h>
#include <stdarg.h>
#include <sys/time.h>

#include "state.h"
#include "board.h"
#include "table.h"
#include "config.h"
#include "fit_weight.h"

// does not provide error handling

// heuristic scoring functions
double heuristic_score_0(State state);
double heuristic_score_1(State state);
double heuristic_score_2(State state);
double heuristic_score_3(State state);

// move determination functions
int optimizing_move(State state, double (*score_func)(State));
int negamaxing_move(State state, int depth, double (*score_func)(State));
int mixed_move(State state, int depth_middle, double (*score_func)(State), int depth_end);

// search functions
//double abpruning(State state, int depth, double a, double b, int side);
double negamax(State state, int depth, double alpha, double beta, int *max_move, double (*score_func)(State));
double negamax_dnorder(State state, int depth, double alpha, double beta, int *max_move, double (*score_func)(State));
double negamax_end(State state, double alpha, double beta, int *max_move, double (*score_func)(State), int remaining);

/* Negamax search up to a certain depth, used by iterative_deepening.

   id_node_count must not be NULL. At the start of each call to this function, id_node_count is increased by 1.

   move_scores is ignored if it is NULL.
   If move_scores is not NULL:
   During search, when a child branch is completed, store the final score for that child (searched to depth-1) at move_scores[move_num], where move_num is ordered by the call to allowed_moves_inplace(state,...).
 */
double negamax_dep_lim(State state, int depth, double alpha, double beta, double *move_scores, int *id_node_count, double (*score_func)(State));
// return the 
double iterative_deepening(State state, int node_limit, double (*score_func)(State));


/* move ordering
   Perform search with score_func up to depth, 
   and sort the moves in descending order.
 */
void order_moves(State state, char *order, int movec, int depth, double (*score_func)(State));


#endif

