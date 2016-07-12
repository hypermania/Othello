#include "ai.h"

Table global_table;
FlatConfTable **global_fcts;
int global_n_f;

State temp_state;

// heuristic scoring functions

int count_0 = 0;
int count_1 = 0;
int count_2 = 0;
int count_3 = 0;

double heuristic_score_0(State state){
  //return (double) (count_pieces(state->board, W) - count_pieces(state->board, B));
  count_0++;
  //printf("count_0 = %d\n", count_0);
  return (double) piece_diff(state->board, W, B);
  //Config_store board = board_to_conf_nocreate(state->board);
  //return __builtin_popcountl(board.w) - __builtin_popcountl(board.b);
}

double heuristic_score_1(State state){
  //printf("heuristic_score_1\n");

  count_1++;
  int side = W;
  int is_at_final = state_final(state);
  
  double result;
  int mypieces = count_pieces(state->board, side);
  int opp_side = opposite_side(side);
  int opppieces = count_pieces(state->board, opp_side);
  
  result = (double)mypieces;
  
  if(is_at_final){
    if(mypieces <= opppieces){
      return INT_MIN + 16384 + (mypieces - opppieces);
    }
    if(mypieces > opppieces){
      return INT_MAX - 16384 + (mypieces - opppieces);
    }
  }

  Pos corners[4] = {(Pos) {0,0}, (Pos) {0,BOARD_SIZE-1}, (Pos) {BOARD_SIZE-1,0}, (Pos) {BOARD_SIZE-1,BOARD_SIZE-1}};  
  int i;
  for(i=0;i<4;i++){
    int corner_val = board_get_pos(state->board, corners[i]);
    if(corner_val == side)
      result += 10;
    if(corner_val == opp_side)
      result -= 10;


    int mycount = adj_given_pos(state->board, corners[i], NULL, side);
    if(corner_val == side) {
      result += 8*mycount;
    } else if(corner_val == opp_side){
      result -= 16*mycount;
    } else {
      result -= 8*mycount;
    }
  }  

  return result;
}



double heuristic_score_2(State state){
  count_2++;
  
  Config_store board = board_to_conf_nocreate(state->board);
  int cat = CAT(BOARD_SIZE_SQR - __builtin_popcountl(board.x));
  /*
  if(state_final(state)){
    return link_function_inverse(heuristic_score_0(state));
  }
  */
  
  return get_score_from_fct_list(global_fcts[cat], global_n_f, board);
}

double heuristic_score_3(State state){
  count_3++;
  
  int movec;
  allowed_moves_inplace(state, &movec);
  
  return -(double)movec;
}


int optimizing_move(State state, double (*score_func)(State)){
  int side = state->turn;
  
  int movec;
  allowed_moves_inplace(state, &movec);
  State pivot = create_state();

  double max_score = -DBL_MAX;
  int max_move = 0;
  
  int i;
  for(i=0;i<movec;i++){
    cpy_state(pivot, state);
    place_piece_indexed(pivot, i);
    double score = ((side == W) ? 1 : (-1)) * 
      state_compute_score(pivot, score_func); // min(a,b) = -max(-a,-b)
    if(score > max_score){
      max_move = i;
      max_score = score;
    }
  }
  free_state(pivot);
  return max_move;
}

int count_node = 0;
int max_count_node = 0;
double max_t = 0;

#define SHOW_STAT

int negamaxing_move(State state, int depth, double (*score_func)(State)){
  assert(state != NULL);

#ifdef SHOW_STAT  
  struct timeval start;
  struct timeval end;
  
  gettimeofday(&start, NULL);
#endif

  count_node = 0;
  int move_num = 0;
  negamax(state, depth, -DBL_MAX, DBL_MAX, &move_num, score_func);

#ifdef SHOW_STAT

  gettimeofday(&end, NULL);
  double elapsed = (double)((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))/(double)1000000;

  max_count_node = MAX(max_count_node, count_node);
  max_t = MAX(elapsed, max_t);
  
  printf("time = %lfs\n", elapsed);
  printf("max_t = %lfs\n", max_t);
  
  printf("count_node = %d\n", count_node);
  printf("max_count_node = %d\n", max_count_node);
  
  printf("node/s = %lf\n", (double)count_node/elapsed);
#endif
  
  return move_num;
}


int mixed_move(State state, int depth_middle, double (*score_func)(State), int depth_end){
  assert(state != NULL);

  
#ifdef SHOW_STAT  
  struct timeval start;
  struct timeval end;
  
  gettimeofday(&start, NULL);
#endif

  count_0 = 0;
  count_1 = 0;
  count_2 = 0;
  count_3 = 0;
  
  count_node = 0;
  
  Config_store board = board_to_conf_nocreate(state->board);
  int empty_sqr = __builtin_popcountl(board.x);
  
  int move_num = 0;
  
  if(empty_sqr > depth_end){
    negamax(state, depth_middle, -DBL_MAX, DBL_MAX, &move_num, score_func);
  } else {
    int remaining = count_pieces(state->board, X);
    double score = negamax_end(state, -DBL_MAX, DBL_MAX, &move_num, heuristic_score_0, remaining);
    printf("end game: score = %lf\n", score);
  }

#ifdef SHOW_STAT

  gettimeofday(&end, NULL);
  double elapsed = (double)((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))/(double)1000000;

  max_count_node = MAX(max_count_node, count_node);
  max_t = MAX(elapsed, max_t);
  
  printf("time = %lfs\n", elapsed);
  printf("max_t = %lfs\n", max_t);
  
  printf("count_node = %d\n", count_node);
  printf("max_count_node = %d\n", max_count_node);

  printf("node/s = %lf\n", (double)count_node/elapsed);

  printf("count_0 = %d, count_2 = %d\n", count_0, count_2);
  
#endif

  
  return move_num;
}





double negamax(State state, int depth, double alpha, double beta, int *max_move, double (*score_func)(State)){
  assert(state != NULL);

  count_node++;

  /* check if this is a leaf */
  int side = state->turn;
  if(depth == 0 || state_final(state)){
    return ((side == W) ? 1 : (-1)) * state_compute_score(state, score_func);
  }

  /* get basic state info */
  int movec;
  allowed_moves_inplace(state, &movec);


  /* logic for turn skipping */
  if(movec == 0){
    skip_turn(state);
    return (-1) * negamax(state, depth-1, -beta, -alpha, NULL, score_func);
  }

  /* move ordering */
  char order[POS_STORE_SIZE]; int m;
  for(m=0;m<movec;m++){
    order[m] = m;
  }

  if(depth >= 4){
    order_moves(state, order, movec, 1, heuristic_score_2);
  }
  
  /* logic for move making */

  State pivot = create_state();
  
  double best_score = -DBL_MAX;
  int best_move_num = 0;
  
  int i;
  for(i=0;i<movec;i++){
    cpy_state(pivot, state);
    place_piece_indexed(pivot, order[i]);
    double score = (-1) * negamax(pivot, depth-1, -beta, -alpha, NULL, score_func);
    if(score >= best_score){
      best_score = score;
      best_move_num = order[i];
    }
    alpha = MAX(alpha, score);
    if(alpha >= beta){
      break;
    }
  }

  if(max_move != NULL){
    *max_move = best_move_num;
  }

  free(pivot);
  return best_score;
}

double negamax_dnorder(State state, int depth, double alpha, double beta, int *max_move, double (*score_func)(State)){
  assert(state != NULL);

  count_node++;
  
  int side = state->turn;
  if(depth == 0 || state_final(state)){
    return ((side == W) ? 1 : (-1)) * state_compute_score(state, score_func);
  }

  double best_score = -DBL_MAX;
  int best_move_num = 0;
  
  int movec;
  allowed_moves_inplace(state, &movec);

  if(movec == 0){
    skip_turn(state);
    return (-1) * negamax(state, depth-1, -beta, -alpha, NULL, score_func);
  }
  
  State pivot = create_state();
  
  int i;
  for(i=0;i<movec;i++){
    cpy_state(pivot, state);
    place_piece_indexed(pivot, i);
    double score = (-1) * negamax(pivot, depth-1, -beta, -alpha, NULL, score_func);
    if(score >= best_score){
      best_score = score;
      best_move_num = i;
    }
    alpha = MAX(alpha, score);
    if(alpha >= beta){
      break;
    }
  }

  if(max_move != NULL){
    *max_move = best_move_num;
  }

  free(pivot);
  return best_score;
}


double negamax_end(State state, double alpha, double beta, int *max_move, double (*score_func)(State), int remaining){
  assert(state != NULL);

  count_node++;
  
  int side = state->turn;
  if(state_final(state)){
    return ((side == W) ? 1 : (-1)) * state_compute_score(state, score_func);
  }

  double best_score = -DBL_MAX;
  int best_move_num = 0;
  
  int movec;
  allowed_moves_inplace(state, &movec);

  if(movec == 0){
    skip_turn(state);
    return (-1) * negamax_end(state, -beta, -alpha, NULL, score_func, remaining);
  }

  char order[POS_STORE_SIZE]; int m;
  for(m=0;m<movec;m++){
    order[m] = m;
  }


  if(remaining > 9){
    order_moves(state, order, movec, 1, heuristic_score_2);
  }

  
  State pivot = create_state();
  
  int i;
  for(i=0;i<movec;i++){
    cpy_state(pivot, state);
    place_piece_indexed(pivot, order[i]);
    double score = (-1) * negamax_end(pivot, -beta, -alpha, NULL, score_func, remaining-1);
    if(score > best_score){
      best_score = score;
      best_move_num = order[i];
    }
    alpha = MAX(alpha, score);
    if(alpha >= beta){
      break;
    }
  }

  if(max_move != NULL){
    *max_move = best_move_num;
  }

  free(pivot);
  return best_score;
}

/*
double negamax_dep_lim(State state, int depth, double alpha, double beta, double *move_scores, int *id_node_count, double (*score_func)(State)){
  assert(state != NULL);
  assert(id_node_count != NULL);

  (*id_node_count)++;

  int side = state->turn;
  if(depth == 0 || state_final(state)){
    return ((side == W) ? 1 : (-1)) * state_compute_score(state, score_func);
  }

  int movec;
  allowed_moves_inplace(state, &movec);

  if(movec == 0){
    skip_turn(state);
    return (-1) * negamax_dep_lim(state, depth-1, -beta, -alpha, NULL, );
  }

  char order[POS_STORE_SIZE]; int m;
  for(m=0;m<movec;m++){
    order[m] = m;
  }

  State pivot = create_state();

  int i;
  for(i=0;i<movec;i++){
    cpy_state(pivot, state);
    place_piece_indexed(pivot, order[i]);
    double score = (-1) * negamax_dep_lim(pivot, depth-1, -beta, -alpha, NULL, score_func, remaining-1);
    if(score > best_score){
      best_score = score;
      best_move_num = order[i];
    }
    alpha = MAX(alpha, score);
    if(alpha >= beta){
      break;
    }
  }
}
*/

/*
double iterative_deepening(State state, int node_limit, double (*score_func)(State)){
  int id_node_count = 0;

  // the scores for each move
  double move_scores[POS_STORE_SIZE];
  
  // Condition on the number of non-empty squares on the board.
  // A turn skipped does not appear in the principal_move.
  char principal_move[BOARD_SIZE_SQR] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  int depth = 1;
  while(1){
    double alpha = -DBL_MAX; double beta = DBL_MAX;
    negamax_dep_lim(state, depth, alpha, beta, move_scores, &id_node_count, score_func);
  }
  int movec = 0;
  allowed_moves_inplace(state, &movec);

  double max_score = -DBL_MAX;
  char max_move = 0;
}
*/

void order_moves(State state, char *order, int movec, int depth, double (*score_func)(State)){

  int cmp(const void*move1, const void*move2){
    State temp = create_state();
    
    cpy_state(temp, state);
    place_piece_indexed(temp, *(char *)move1);  
    double score1 = negamax_dnorder(temp, depth-1, -DBL_MAX, DBL_MAX, NULL, score_func);
    
    cpy_state(temp, state);
    place_piece_indexed(temp, *(char *)move2);
    double score2 = negamax_dnorder(temp, depth-1, -DBL_MAX, DBL_MAX, NULL, score_func);
    
    free(temp);
    
    if(score1 > score2){
      return 1;
    } else {
      return -1;
    }
  }

  qsort(order, movec, sizeof(char), cmp);

}

