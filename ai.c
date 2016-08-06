#include "ai.h"

#define SHOW_STAT

FlatConfTable **global_fcts;
int global_n_f;

#ifdef SHOW_STAT
static long int count_0 = 0;
static long int count_1 = 0;
static long int count_2 = 0;
static long int count_3 = 0;

static long int count_node = 0;
static long int max_count_node = 0;
static double max_t = 0;
#endif

// heuristic scoring functions

inline double heuristic_score_0(BitState *state){
#ifdef SHOW_STAT
  count_0++;
#endif
  //return (double) piece_diff(state->board, W, B);
  //Config_store board = board_to_conf_nocreate(state->board);
  return __builtin_popcountll(state->board.w) - __builtin_popcountll(state->board.b);
}
/*
double heuristic_score_1(BitState *state){
  //printf("heuristic_score_1\n");

  count_1++;
  int side = W;
  int is_at_final = bitstate_final(state);
  
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
*/


inline double heuristic_score_2(BitState *state){
#ifdef SHOW_STAT
  count_2++;
#endif
  
  Config_store board;
  board.w = state->board.w;
  board.b = state->board.b;
  board.x = ~(board.w | board.b);
  
  int cat = CAT(BOARD_SIZE_SQR - __builtin_popcountll(board.x));
  
  return get_score_from_fct_list(global_fcts[cat], global_n_f, board);
}

inline double heuristic_score_3(BitState *state){
#ifdef SHOW_STAT
  count_3++;
#endif
  
  int movec = __builtin_popcountll(find_moves_bitmask(state->board, state->turn));
  //bitstate_allowed_moves(state, &movec);
  
  return ((state->turn == W) ? 1 : (-1)) * (double)movec;
}

int optimizing_move(BitState *state, double (*score_func)(BitState *)){
  int side = state->turn;
  
  int movec;
  bitstate_allowed_moves(state, &movec);
  BitState *pivot = create_initial_bitstate();

  double max_score = -DBL_MAX;
  int max_move = 0;
  
  int i;
  for(i=0;i<movec;i++){
    cpy_bitstate(pivot, state);
    bitstate_place_piece(pivot, i);
    double score = ((side == W) ? 1 : (-1)) * 
      score_func(pivot);//state_compute_score(pivot, score_func); // min(a,b) = -max(-a,-b)
    if(score > max_score){
      max_move = i;
      max_score = score;
    }
  }
  free_bitstate(pivot);
  return max_move;
}


int negamaxing_move(BitState *state, int depth, double (*score_func)(BitState *)){
  assert(state != NULL);

  int move_num = 0;
  negamax(state, depth, -DBL_MAX, DBL_MAX, &move_num, score_func);

  
  return move_num;
}


int mixed_move(BitState *state, int depth_middle, double (*score_func)(BitState *), int depth_end){
  assert(state != NULL);

  
#ifdef SHOW_STAT  
  struct timeval start;
  struct timeval end;
  
  gettimeofday(&start, NULL);

  count_0 = 0;
  count_1 = 0;
  count_2 = 0;
  count_3 = 0;
  
  count_node = 0;
#endif
  
  int empty_sqr = BOARD_SIZE_SQR -
    (__builtin_popcountll(state->board.b) + __builtin_popcountll(state->board.w));
  
  int move_num = 0;
  
  if(empty_sqr > depth_end){
    negamax(state, depth_middle, -DBL_MAX, DBL_MAX, &move_num, score_func);
  } else {
    double score = negamax_end(state, -DBL_MAX, DBL_MAX, &move_num, empty_sqr);
    //double score = negamax(state, empty_sqr, -DBL_MAX, DBL_MAX, &move_num, heuristic_score_0);
    printf("end game: score = %lf\n", score);
  }

#ifdef SHOW_STAT

  gettimeofday(&end, NULL);
  double elapsed = (double)((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))/(double)1000000;

  max_count_node = MAX(max_count_node, count_node);
  max_t = MAX(elapsed, max_t);
  
  printf("time = %lfs\n", elapsed);
  printf("max_t = %lfs\n", max_t);
  
  printf("count_node = %ld\n", count_node);
  printf("max_count_node = %ld\n", max_count_node);

  printf("node/s = %lf k/s\n", (double)count_node/elapsed/(double)1000);

  printf("count_0/count_node = %lf\n", (double)count_0/(double)count_node);
  printf("count_2/count_node = %lf\n", (double)count_2/(double)count_node);
  //printf("count_3/count_node = %lf\n", (double)count_3/(double)count_node);  
#endif

  
  return move_num;
}

char init_order[POS_STORE_SIZE] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
  21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
};


double negamax(BitState *state, int depth, double alpha, double beta, int *max_move, double (*score_func)(BitState *)){
  
#ifdef SHOW_STAT
  count_node++;
#endif
  
  /* check if this is a leaf */
  int side = state->turn;
  int is_end = 0;
  if(depth == 0 || (is_end = bitstate_final(state))){
    if(is_end){
      return ((side == W) ? 100000 : (-100000)) * heuristic_score_0(state);  
    } else {
      return ((side == W) ? 1 : (-1)) * score_func(state);
    }
  } 
  //


  /* get basic state info */
  // since movec is guranteed to be computed before here,
  // we read movec from the state directly to speed up
  int movec = state->movec;
  //bitstate_allowed_moves(state, &movec);


  /* logic for turn skipping */
  if(movec == 0){
    bitstate_skip_turn(state);
    return (-1) * negamax(state, depth-1, -beta, -alpha, NULL, score_func);
  }

  /* move ordering */
  char order[POS_STORE_SIZE];
  memcpy(order, init_order, POS_STORE_SIZE * sizeof(char));
  
  BitMask opp_move_masks[POS_STORE_SIZE];
  if(depth >= 4){
    order_moves_fastest_first(state, order, movec, opp_move_masks);
  }

  
  /* logic for move making */

  //BitState *pivot = create_initial_bitstate();
  BitState pivot_bitstate;
  BitState *pivot = &pivot_bitstate;

  
  double best_score = -DBL_MAX;
  char best_movec = 0;
  char best_moves[POS_STORE_SIZE];

  int opp_side = opposite_side(state->turn);  
  int i;
  for(i=0;i<movec;i++){
    //cpy_bitstate(pivot, state);
    //bitstate_place_piece(pivot, order[i]);

    pivot->board = state->positions[(int)order[i]];
    pivot->turn = opp_side;
    pivot->control.moves_filled = false;

    if(depth >= 4){
      pivot->move_mask = opp_move_masks[(int)order[i]];
      pivot->control.move_mask_filled = true;
    } else {
      pivot->control.move_mask_filled = false;
    }

    
    double score = (-1) * negamax(pivot, depth-1, -beta, -alpha, NULL, score_func);
    
    if(score > best_score){
      best_score = score;
      best_movec = 0;
      best_moves[(int)(best_movec++)] = order[i];
    } else if(score == best_score){
      best_moves[(int)(best_movec++)] = order[i];
    }
    alpha = MAX(alpha, score);
    if(alpha >= beta){
      break;
    }
  }

  int r = rand() % best_movec;
  if(max_move != NULL){
    *max_move = best_moves[r];//best_move_num;
  }

  //free(pivot);
  return best_score;
}


double negamax_end(BitState *state, double alpha, double beta, int *max_move, int remaining){
  
#ifdef SHOW_STAT
  count_node++;
#endif
  
  int side = state->turn;
  if((remaining == 0) || bitstate_final(state)){
    return ((side == W) ? 1 : (-1)) * heuristic_score_0(state);
  }

  double best_score = -DBL_MAX;
  int best_move_num = 0;

  // since movec is guranteed to be computed before here,
  // we read movec from the state directly to speed up
  int movec = state->movec;
  //bitstate_allowed_moves(state, &movec);

  if(movec == 0){
    bitstate_skip_turn(state);
    return (-1) * negamax_end(state, -beta, -alpha, NULL, remaining);
  }

  
  char order[POS_STORE_SIZE];
  memcpy(order, init_order, POS_STORE_SIZE * sizeof(char));

  BitMask opp_move_masks[POS_STORE_SIZE];
  bool ordered = false;
  if(remaining > 5){
    order_moves_fastest_first(state, order, movec, opp_move_masks);
    ordered = true;
  }

  BitState pivot_bitstate;
  BitState *pivot = &pivot_bitstate;

  //long int last_count = 0;
  
  int opp_side = opposite_side(state->turn);
  int i;
  for(i=0;i<movec;i++){

    pivot->board = state->positions[(int)order[i]];
    pivot->turn = opp_side;
    pivot->control.moves_filled = false;

    //if(ordered){
    pivot->move_mask = opp_move_masks[(int)order[i]];
    pivot->control.move_mask_filled = ordered;
      //} else {
      //pivot->control.move_mask_filled = false;
      //}

    double score = (-1) * negamax_end(pivot, -beta, -alpha, NULL, remaining-1);

    /*
    if(remaining == 21){
      printf("count_node for %d-th branch = %ld\n", i, count_node - last_count);
      last_count = count_node;
    }
    */
    
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

  //free(pivot);
  return best_score;
}

/*
double iterative_deepening(BitState *state, int node_limit, double (*score_func)(BitState *)){
  int id_node_count = 0;

  // the scores for each move
  double move_scores[POS_STORE_SIZE];
  
  // Condition on the number of non-empty squares on the board.
  // A turn skipped does not appear in the principal_move.
  char principal_move[BOARD_SIZE_SQR] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  int depth = 1;
  while(1){
    double alpha = -DBL_MAX; double beta = DBL_MAX;
    negamax(state, depth, alpha, beta, move_scores, &id_node_count, score_func);
  }
  int movec = 0;
  bitstate_allowed_moves(state, &movec);

  double max_score = -DBL_MAX;
  char max_move = 0;
}
*/

//static BitState temp_bitstate;

int opp_mobility[POS_STORE_SIZE];

inline void order_moves_fastest_first(BitState *state, char *order, int movec, BitMask *opp_move_masks){

  int i;
  int opp_side = opposite_side(state->turn);

  for(i=0;i<movec;i++){
    opp_move_masks[i] = find_moves_bitmask(state->positions[i], opp_side);
    opp_mobility[i] = __builtin_popcountll(opp_move_masks[i]);
  }
  
  int cmp(const void*move1, const void*move2){
    return opp_mobility[(int)*(char *)move1] - opp_mobility[(int)*(char *)move2];
  }
  
  qsort(order, movec, sizeof(char), cmp);

}
