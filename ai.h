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
#include "bitboard.h"
#include "bitstate.h"
#include "table.h"
#include "config.h"
#include "fit_weight.h"

// does not provide error handling

// heuristic scoring functions
double heuristic_score_0(BitState *state);
double heuristic_score_1(BitState *state);
double heuristic_score_2(BitState *state);
double heuristic_score_3(BitState *state);

// move determination functions
int optimizing_move(BitState *state, double (*score_func)(BitState *));
int negamaxing_move(BitState *state, int depth, double (*score_func)(BitState *));
int mixed_move(BitState *state, int depth_middle, double (*score_func)(BitState *), int depth_end);

// search functions
//double abpruning(BitState *state, int depth, double a, double b, int side);
double negamax(BitState *state, int depth, double alpha, double beta, int *max_move, double (*score_func)(BitState *));

double negamax_dnorder(BitState *state, int depth, double alpha, double beta, int *max_move, double (*score_func)(BitState *));

double negamax_end(BitState *state, double alpha, double beta, int *max_move, int remaining);

//double negamax_iterative(BitState *state, int depth, double alpha, double beta, int *max_move, double (*score_func)(BitState *));

/* Negamax search up to a certain depth, used by iterative_deepening.

   id_node_count must not be NULL. At the start of each call to this function, id_node_count is increased by 1.

   move_scores is ignored if it is NULL.
   If move_scores is not NULL:
   During search, when a child branch is completed, store the final score for that child (searched to depth-1) at move_scores[move_num], where move_num is ordered by the call to allowed_moves_inplace(state,...).
 */
double negamax_dep_lim(BitState *state, int depth, double alpha, double beta, double *move_scores, int *id_node_count, double (*score_func)(BitState *));
// return the 
double iterative_deepening(BitState *state, int node_limit, double (*score_func)(BitState *));


/* move ordering
   Perform search with score_func up to depth, 
   and sort the moves in descending order.
 */
void order_moves_fastest_first(BitState *state, char *order, int movec, BitMask *opp_move_masks);


#endif

