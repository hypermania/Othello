#include "ai.h"

#define SHOW_STAT

#ifdef SHOW_STAT
static long int count_leaf = 0;

static long int count_movec = 0;

static long int count_node = 0;
static long int max_count_node = 0;
static double max_t = 0;

FILE *log_file;
#endif

// heuristic scoring functions

inline double heuristic_score_0(BitState *state){
#ifdef SHOW_STAT
  count_leaf++;
#endif
  return __builtin_popcountll(state->board.w) - __builtin_popcountll(state->board.b);
}

inline double heuristic_score_3(BitState *state){
#ifdef SHOW_STAT
  count_leaf++;
#endif
  int movec = __builtin_popcountll(find_moves_bitmask(state->board, state->turn));
  
  return ((state->turn == W) ? 1 : (-1)) * (double)movec;
}

inline double heuristic_score_4(BitState *state){
#ifdef SHOW_STAT
  count_leaf++;
#endif
  return evaluate(state);
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

  count_leaf = 0;
  
  count_node = 0;
  count_movec = 0;
#endif
  
  int empty_sqr = BOARD_SIZE_SQR -
    (__builtin_popcountll(state->board.b) + __builtin_popcountll(state->board.w));
  
  int move_num = 0;
  
  if(empty_sqr > depth_end){
    double score = negamax(state, depth_middle, -DBL_MAX, DBL_MAX, &move_num, score_func);
    printf("mid game: score = %lf\n", link_function(score));
  } else {
    double score = negamax_end(state, -DBL_MAX, DBL_MAX, &move_num, empty_sqr);
    printf("end game: score = %lf\n", score);
  }

#ifdef SHOW_STAT

  gettimeofday(&end, NULL);
  double elapsed = (double)((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))/(double)1000000;

  max_count_node = MAX(max_count_node, count_node);
  max_t = MAX(elapsed, max_t);
  
  printf("time = %lfs\n", elapsed);
  
  printf("count_node = %ld\n", count_node);

  printf("node/s = %lf k/s\n", (double)count_node/elapsed/(double)1000);

  //printf("count_leaf/count_node = %lf\n", (double)count_leaf/(double)count_node);
  //printf("avg movec = %lf\n", (double)count_movec/((double)count_node - (double)count_leaf));

  // is_endgame, count_leaf, count_node, elapsed
  /*
  fprintf(log_file, "%d, %ld, %ld, %ld, %lf\n",
	  (empty_sqr <= depth_end),
	  count_node, count_leaf, count_movec,
	  elapsed);
  */
  
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

#ifdef SHOW_STAT
  count_movec += movec;
#endif


  /* logic for turn skipping */
  if(movec == 0){
    bitstate_skip_turn(state);
    return (-1) * negamax(state, depth-1, -beta, -alpha, NULL, score_func);
  }

  /* move ordering */
  char order[POS_STORE_SIZE];
  memcpy(order, init_order, POS_STORE_SIZE * sizeof(char));
  
  BitMask opp_move_masks[POS_STORE_SIZE];
  bool ordered = false;
  if(depth >= 4){
    order_moves_fastest_first(state, order, movec, opp_move_masks);
    ordered = true;
  }

  
  /* logic for move making */

  BitState pivot_bitstate;
  BitState *pivot = &pivot_bitstate;

  
  double best_score = -DBL_MAX;
  char best_movec = 0;
  char best_moves[POS_STORE_SIZE];

  int opp_side = OPPOSITE_SIDE(state->turn);  
  int i;
  for(i=0;i<movec;i++){

    pivot->board = state->positions[(int)order[i]];
    pivot->turn = opp_side;
    pivot->control.moves_filled = false;

    pivot->move_mask = opp_move_masks[(int)order[i]];
    pivot->control.move_mask_filled = ordered;
    
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
    *max_move = best_moves[r];
  }

  return best_score;
}


double negamax_end(BitState *state, double alpha, double beta, int *max_move, int remaining){
  
#ifdef SHOW_STAT
  count_node++;
#endif
  
  int side = state->turn;
  if(remaining <= 1){
    switch(remaining){
    case 0:
      return ((side == W) ? 1 : (-1)) * heuristic_score_0(state);
      break;
    case 1:
      return negamax_end_with_1_empty(state);
      break;
    case 2:
      return negamax_end_with_2_empty(state);
      break;
    }
  } else if(bitstate_final(state)){
    return ((side == W) ? 1 : (-1)) * heuristic_score_0(state);
  }

  double best_score = -DBL_MAX;
  int best_move_num = 0;

  // since movec is guranteed to be computed before here,
  // we read movec from the state directly to speed up
  int movec = state->movec;
  //bitstate_allowed_moves(state, &movec);

#ifdef SHOW_STAT
  count_movec += movec;
#endif
  
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
  
  int opp_side = OPPOSITE_SIDE(state->turn);
  int i;
  for(i=0;i<movec;i++){

    pivot->board = state->positions[(int)order[i]];
    pivot->turn = opp_side;
    pivot->control.moves_filled = false;

    pivot->move_mask = opp_move_masks[(int)order[i]];
    pivot->control.move_mask_filled = ordered;

    double score = (-1) * negamax_end(pivot, -beta, -alpha, NULL, remaining-1);

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

  return best_score;
}

double negamax_end_with_1_empty(BitState *state){
#ifdef SHOW_STAT
      count_node++;
#endif
  
  int side = state->turn;
  
  BitMask pos = ~(state->board.w | state->board.b);
  int pos_index = __builtin_clzll(pos);
  
  BitBoard board = state->board;

  if(side == W){
    flip_bitboard_via_pext_w(&board, pos_index);
    if(board.w == state->board.w){
      flip_bitboard_via_pext_b(&board, pos_index);
    }
  } else {
    flip_bitboard_via_pext_b(&board, pos_index);
    if(board.w == state->board.w){
      flip_bitboard_via_pext_w(&board, pos_index);
    }
  }

  return ((side == W) ? 1 : (-1)) * (double) (__builtin_popcountll(board.w) - __builtin_popcountll(board.b));
}

// TODO
double negamax_end_with_2_empty(BitState *state){
  /*
  char side = state->turn;

  BitMask empty = ~(state->board.w | state->board.b);
  BitMask pos1 = my_blsi_u64(empty);
  BitMask pos2 = (~pos1) & empty;
  int pos_index1 = __builtin_clzll(pos1);
  int pos_index2 = __builtin_clzll(pos2);
  
  BitBoard board1 = state->board;

  double score1, score2;
  */

  /*  
  if(side == W){
    flip_bitboard_via_pext_w(&board1, pos_index1);
    if(board1.w == state->board.w){
      BitMask last_white = board1.w;
      flip_bitboard_via_pext_b(&board1, pos_index1);
      if(last_white == board1.w){

      } else {
	BitState temp_state;
	temp_state.board = board1;
	temp_state.side = B;
	score1 = negamax_end_with_1_empty(&temp_state);
      }
    } else {
      BitState temp_state;
      temp_state.board = board1;
      temp_state.side = B;
      score1 = negamax_end_with_1_empty(&temp_state);
    }
  }
  */
  
  //return ((side == W) ? 1 : (-1)) * (double) (__builtin_popcountll(board.w) - __builtin_popcountll(board.b));
  
  return 0;
  
}



int opp_mobility[POS_STORE_SIZE];

int cmp_mobility(const void*move1, const void*move2){
  return opp_mobility[(int)*(char *)move1] - opp_mobility[(int)*(char *)move2];
}

inline void order_moves_fastest_first(BitState *state, char *order, int movec, BitMask *opp_move_masks){

  int i;
  int opp_side = OPPOSITE_SIDE(state->turn);

  for(i=0;i<movec;i++){
    opp_move_masks[i] = find_moves_bitmask(state->positions[i], opp_side);
    opp_mobility[i] = __builtin_popcountll(opp_move_masks[i]);
  }
  
  qsort(order, movec, sizeof(char), cmp_mobility);

}

