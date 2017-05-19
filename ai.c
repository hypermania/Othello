#include "ai.h"

#define SHOW_STAT

#ifdef SHOW_STAT
static long int count_leaf = 0;

static long int count_movec = 0;

long int count_node = 0;
static long int max_count_node = 0;

static double max_t = 0;
static double sum_t = 0;

static long int best_move_order_histogram[POS_STORE_SIZE];

static Table *table;

FILE *log_file;
#endif

static inline int cmp_mobility(const void *move1, const void *move2, void *opp_mobility);
static inline int cmp_mobility_2(const void *move1, const void *move2, void *cmp_info);
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
  int movec = __builtin_popcountll(find_moves_bitmask_avx(state->board, state->turn));
  
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
  BitMask max_move = 0;
  
  int i;
  for(i = 0; i < movec; i++) {
    cpy_bitstate(pivot, state);
    bitstate_place_piece(pivot, i);
    double score = ((side == W) ? 1 : (-1)) * 
      score_func(pivot);
    if(score > max_score) {
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
  BitMask max_move = 0;
  negamax(state, depth, -DBL_MAX, DBL_MAX, &max_move, score_func);

  int movec = 0;
  BitMask *moves_array = bitstate_allowed_moves_array(state, &movec);
  int i;
  for(i = 0; i < movec; i++) {
    if(moves_array[i] == max_move) {
      move_num = i;
      break;
    }
  }
  free(moves_array);
  
  return move_num;
}


int mixed_move(BitState *state, int depth_middle, double (*score_func)(BitState *), int depth_end){
  assert(state != NULL);

  //if(table == NULL)
  //table = table_create(25);


#ifdef SHOW_STAT  

  count_leaf = 0;
  
  count_node = 0;
  count_movec = 0;
  
  memset(best_move_order_histogram, 0, sizeof(best_move_order_histogram));

  struct timeval start;
  struct timeval end;
  
  gettimeofday(&start, NULL);
#endif
  
  int empty_sqr = BOARD_SIZE_SQR -
    (__builtin_popcountll(state->board.b) + __builtin_popcountll(state->board.w));

  int movec = 0;
  int move_num = 0;
  BitMask max_move = 0;
  
  if(empty_sqr > depth_end){
    double score = negamax(state, depth_middle, -DBL_MAX, DBL_MAX, &max_move, score_func);
    printf("mid game: score = %lf\n", link_function(score));
  } else {
    double score = negamax_end(state, -DBL_MAX, DBL_MAX, &max_move, empty_sqr);
    printf("end game: score = %lf\n", score);
  }

  BitMask *moves_array = bitstate_allowed_moves_array(state, &movec);
  int i;
  for(i = 0; i < movec; i++) {
    if(moves_array[i] == max_move) {
      move_num = i;
      break;
    }
  }
  free(moves_array);
  
#ifdef SHOW_STAT

  gettimeofday(&end, NULL);
  double elapsed = (double)((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))/(double)1000000;

  max_count_node = MAX(max_count_node, count_node);
  max_t = MAX(elapsed, max_t);
  sum_t += elapsed;
  
  printf("time = %lfs\n", elapsed);
  
  printf("max time = %lfs\n", max_t);

  printf("sum time = %lfs\n", sum_t);
  
  printf("count_node = %ld\n", count_node);
  
  printf("node/s = %lf k/s\n", (double)count_node/elapsed/(double)1000);
  
  /*
  printf("best_move_order_histogram:\n");

  long int sum_histogram = 0;
  long int sum_front = 0;
  for(i = 0; i < POS_STORE_SIZE; i++) {
    printf("%ld ", best_move_order_histogram[i]);
    sum_histogram += best_move_order_histogram[i];
    if(i < 1)
      sum_front += best_move_order_histogram[i];
  }
  printf("\n");

  double percentage = (double)sum_front/sum_histogram;
  
  printf("percentage = %lf\n", percentage);
  */
  
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
  /*
  if(empty_sqr > depth_end) {
    table_free(table);
    table = NULL;
  }
  */
  //table_free(table);
  return move_num;
}

char init_order[POS_STORE_SIZE] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
  21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
};


double negamax(BitState *state, int depth, double alpha, double beta, BitMask *max_move, double (*score_func)(BitState *)){

  double alpha_orig = alpha;
  TableValue *value = NULL;

  /*
  if(depth >= 3) {
    value = table_read(table, state);
    if(value != NULL) {

      if(value->flag == EXACT) {
	return value->score;
      } else if(value->flag == LOWERBOUND) {
	alpha = MAX(alpha, value->score);
      } else if(value->flag == UPPERBOUND) {
	beta = MIN(beta, value->score);
      }

      if(alpha >= beta)
	return value->score;
    }
  }
  */
  
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

  /* get basic state info */
  int movec;
  BitMask moves = bitstate_allowed_moves(state, &movec);

#ifdef SHOW_STAT
  count_movec += movec;
#endif

  /* logic for turn skipping */
  if(movec == 0){
    BitState pivot = *state;
    bitstate_skip_turn(&pivot);
    return (-1) * negamax(&pivot, depth-1, -beta, -alpha, NULL, score_func);
  }
  
  /* move ordering */
  char order[POS_STORE_SIZE];
  memcpy(order, init_order, sizeof(order));
  
  int i;  
  BitMask moves_array[POS_STORE_SIZE];
  BitState next_states[POS_STORE_SIZE];
  
  for(i = 0; moves != 0; moves = my_blsr_u64(moves)) {
    BitMask pos = my_blsi_u64(moves);
    moves_array[i++] = pos;
  }
  
  if(depth >= 3) {
    char opp_side = OPPOSITE_SIDE(state->turn);
    char opp_mobility[POS_STORE_SIZE];

    for(i = 0; i < movec; i++) {
      BitState temp = *state;
      bitstate_place_piece(&temp, moves_array[i]);
      next_states[i] = temp;
      BitMask opp_moves = find_moves_bitmask_avx(temp.board, opp_side);
      opp_mobility[i] = __builtin_popcountll(opp_moves);
    }
    qsort_r(order, movec, sizeof(char), cmp_mobility, opp_mobility);
  }

  
  /* logic for move making */

  BitState pivot_bitstate;
  BitState *pivot = &pivot_bitstate;
  
  double best_score = -DBL_MAX;
  BitMask best_move = 0;

  for(i = 0; i < movec; i++){
    int j = order[i];
    BitMask pos = moves_array[j];

    if(depth >= 3) {
      *pivot = next_states[j];
    } else {
      memcpy(pivot, state, sizeof(BitState));
      bitstate_place_piece(pivot, pos);
    }
    
    double score = (-1) * negamax(pivot, depth-1, -beta, -alpha, NULL, score_func);
    
    if(score > best_score){
      best_score = score;
      best_move = pos;
    }
    alpha = MAX(alpha, score);
    if(alpha >= beta){
      break;
    }

  }
  
  if(max_move != NULL){
    *max_move = best_move;
  }

  /*
  if(depth >= 3) {
    TableValue value_temp;
    value_temp.score = best_score;
    if(best_score <= alpha_orig) {
      value_temp.flag = UPPERBOUND;
    } else if(best_score >= beta) {
      value_temp.flag = LOWERBOUND;
    } else {
      value_temp.flag = EXACT;
    }
    table_write(table, state, value_temp);
  }
  */
  
  return best_score;
}

double negamax_end(BitState *state, double alpha, double beta, BitMask *max_move, int remaining){

  double alpha_orig = alpha;
  TableValue *value = NULL;

  /*
  if(remaining >= 7) {
    value = table_read(table, state);
    if(value != NULL) {

      if(value->flag == EXACT) {
	return value->score;
      } else if(value->flag == LOWERBOUND) {
	alpha = MAX(alpha, value->score);
      } else if(value->flag == UPPERBOUND) {
	beta = MIN(beta, value->score);
      }

      if(alpha >= beta)
	return value->score;
    }
  }
  */

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
    }
  } else if(bitstate_final(state)){
    return ((side == W) ? 1 : (-1)) * heuristic_score_0(state);
  }

  int movec;
  BitMask moves = bitstate_allowed_moves(state, &movec);

#ifdef SHOW_STAT
  count_movec += movec;
#endif
  
  if(movec == 0) {
    BitState pivot = *state;
    bitstate_skip_turn(&pivot);
    return (-1) * negamax_end(&pivot, -beta, -alpha, NULL, remaining);
  }
  
  char order[POS_STORE_SIZE];
  memcpy(order, init_order, POS_STORE_SIZE * sizeof(char));

  int i;  
  BitMask moves_array[POS_STORE_SIZE];
  BitState next_states[POS_STORE_SIZE];
  
  for(i = 0; moves != 0; moves = my_blsr_u64(moves)) {
    BitMask pos = my_blsi_u64(moves);
    moves_array[i++] = pos;
  }

  bool ordered = false;
  if(remaining > 5) {
    ordered = true;
    char opp_side = OPPOSITE_SIDE(state->turn);
    char opp_mobility[POS_STORE_SIZE];

    for(i = 0; i < movec; i++) {
      BitState temp = *state;
      bitstate_place_piece(&temp, moves_array[i]);
      next_states[i] = temp;
      BitMask opp_moves = find_moves_bitmask_avx(temp.board, opp_side);
      opp_mobility[i] = __builtin_popcountll(opp_moves);
    }
    qsort_r(order, movec, sizeof(char), cmp_mobility, opp_mobility);
  }

  double best_score = -DBL_MAX;
  BitMask best_move = 0;
  
  BitState pivot_bitstate;
  BitState *pivot = &pivot_bitstate;
  
  for(i = 0; i < movec; i++){
    int j = order[i];
    BitMask pos = moves_array[j];

    if(ordered) {
      pivot_bitstate = next_states[j];
    } else {
      memcpy(pivot, state, sizeof(BitState));
      bitstate_place_piece(pivot, pos);
    }
    
    double score = (-1) * negamax_end(pivot, -beta, -alpha, NULL, remaining-1);

    best_score = MAX(best_score, score);
    if(alpha < score) {
      alpha = score;
      best_move = pos;
    }

    if(alpha >= beta) {
      break;
    }
    
  }

  if(max_move != NULL){
    *max_move = best_move;
  }

  /*
  if(remaining >= 7) {
    TableValue value_temp;
    value_temp.score = best_score;
    if(best_score <= alpha_orig) {
      value_temp.flag = UPPERBOUND;
    } else if(best_score >= beta) {
      value_temp.flag = LOWERBOUND;
    } else {
      value_temp.flag = EXACT;
    }
    table_write(table, state, value_temp);
  }
  */

  return best_score;
}

#define SCORE_MAX 65

int negamax_end_iterative(BitState *state, int alpha, int beta, BitMask *max_move) {

  int empty_sqr = BOARD_SIZE_SQR -
    (__builtin_popcountll(state->board.b) + __builtin_popcountll(state->board.w));
  //int side = state->turn;

  // Corner case.
  if(empty_sqr == 0) {
    return ((state->turn == W) ? 1 : (-1)) * (int)heuristic_score_0(state);
  }
  
  // Game tree data definition.
  struct {
    int16_t alpha;
    int16_t beta;
  } bounds[GAME_LENGTH];// __attribute__ ((aligned(8)));
  int16_t scores[GAME_LENGTH];  //__attribute__ ((aligned(8)));
  BitState states[GAME_LENGTH]; //__attribute__ ((aligned(8)));
  BitMask moves[GAME_LENGTH];  //__attribute__ ((aligned(8)));
  bool moves_allocated[GAME_LENGTH]; //__attribute__ ((aligned(8)));
  int16_t moves_index[GAME_LENGTH]; //__attribute__ ((aligned(8)));
  int8_t moves_stack[GAME_LENGTH * 16]; //__attribute__ ((aligned(8)));


  // Placeholder variable.
  int movec;  

  // Game tree data initialization.
  memset(bounds, 0, sizeof(bounds));
  memset(states, 0, sizeof(states));
  memset(moves, 0, sizeof(moves));
  memset(moves_index, 0, sizeof(moves_index));
  memset(moves_stack, 0, sizeof(moves_stack));
  memset(moves_allocated, 0, sizeof(moves_allocated));
  int i;
  for(i = 0; i < GAME_LENGTH; i++) {
    scores[i] = -SCORE_MAX;
  }

  bounds[0].alpha = alpha;
  bounds[0].beta = beta;
  states[0] = *state;
  moves[0] = bitstate_allowed_moves(&states[0], &movec);

  // Profiling.
  struct timeval start, end;
  gettimeofday(&start, NULL);
  long int count = 0;

  // Game loop.
  int stack_top = 0;
  while(stack_top >= 0) {
    
    /*    
    printf("stack_top = %d\n", stack_top);
    int j;
    for(j = 0; j < GAME_LENGTH; j++) {
      printf("%d:(%d,%d,%d) ", j, bounds[j].alpha, bounds[j].beta, scores[j]);
      //printf("%d ", moves_index[j]);
    }

    printf("\n");
    for(j = 0; j < GAME_LENGTH; j++) {
      printf("%d ", moves_stack[j]);
    }
    printf("\n");
    */
    
    // Special treatment for case (remaining == 1) for speed.
    int remaining = BOARD_SIZE_SQR - (__builtin_popcountll(states[stack_top].board.b) + __builtin_popcountll(states[stack_top].board.w));
    
    if(remaining == 1) {
      scores[stack_top] = (int16_t)negamax_end_with_1_empty(&states[stack_top]);
      stack_top--;
      count += 2;
      continue;
    }

    // Update score of current node based on result for child node.
    if(scores[stack_top+1] > -SCORE_MAX) {
      scores[stack_top] = MAX(scores[stack_top], -scores[stack_top+1]);
      bounds[stack_top].alpha = MAX(bounds[stack_top].alpha, -scores[stack_top+1]);
      scores[stack_top+1] = -SCORE_MAX;

      if(bounds[stack_top].alpha >= bounds[stack_top].beta) {
	stack_top--;
	count++;
	continue;
      }

    }

    if(moves_allocated[stack_top] == true) {
      if((stack_top == 0 && moves_index[stack_top] > 0) ||
	 (stack_top > 0 && moves_index[stack_top] > moves_index[stack_top-1])) {
	BitMask move = ((uint64_t)1) << moves_stack[moves_index[stack_top]-1];
	moves_index[stack_top]--;
	states[stack_top+1] = states[stack_top];
	bitstate_place_piece(&states[stack_top+1], move);
	moves[stack_top+1] = bitstate_allowed_moves(&states[stack_top+1], &movec);
	bounds[stack_top+1].alpha = -bounds[stack_top].beta;
	bounds[stack_top+1].beta = -bounds[stack_top].alpha;
	moves_allocated[stack_top+1] = false;
	moves_index[stack_top+1] = moves_index[stack_top];
	stack_top++;
	continue;
      }
    }

    
    // Branch if there are moves left.
    if(moves[stack_top] != 0) {

      /*
      BitMask move = my_blsi_u64(moves[stack_top]);
      moves[stack_top] = my_blsr_u64(moves[stack_top]);
      states[stack_top+1] = states[stack_top];
      bitstate_place_piece(&states[stack_top+1], move);
      moves[stack_top+1] = bitstate_allowed_moves(&states[stack_top+1], &movec);
      bounds[stack_top+1].alpha = -bounds[stack_top].beta;
      bounds[stack_top+1].beta = -bounds[stack_top].alpha;
      moves_allocated[stack_top+1] = false;
      moves_index[stack_top+1] = moves_index[stack_top];

      stack_top++;
      */
      while(moves[stack_top] != 0) {
	int pos = __builtin_ctzll(my_blsi_u64(moves[stack_top]));
	moves[stack_top] = my_blsr_u64(moves[stack_top]);
	moves_stack[moves_index[stack_top]] = pos;
	moves_index[stack_top]++;
      }
      if(remaining > 6) {
	int index_start = stack_top == 0 ? 0 : moves_index[stack_top-1];
	int move_count = moves_index[stack_top] - index_start;
	char opp_side = OPPOSITE_SIDE(states[stack_top].turn);
	
	struct {
	  int8_t *start;
	  int8_t opp_mobility[POS_STORE_SIZE];
	} cmp_info;
	
	cmp_info.start = &moves_stack[index_start];

	int j;
	for(j = 0; j < move_count; j++) {
	  BitState temp = states[stack_top];
	  bitstate_place_piece(&temp, 1 << moves_stack[index_start+j]);
	  cmp_info.opp_mobility[j] = __builtin_popcountll(find_moves_bitmask_avx(temp.board, opp_side));
	}
	/*
	for(j = 0; j < move_count; j++) {
	  printf("%d ", cmp_info.opp_mobility[j]);
	}
	printf("\n");
	*/
	
	qsort_r(&moves_stack[index_start], move_count, sizeof(int8_t), cmp_mobility_2, &cmp_info);
      }
      moves_allocated[stack_top] = true;
    } else {
      // Case: game ended.
      if(bitstate_final(&states[stack_top])) {
	scores[stack_top] = ((states[stack_top].turn == W) ? 1 : (-1)) * (short)heuristic_score_0(&states[stack_top]);
	stack_top--;
	count++;
	continue;
      }
      
      // Case: turn skipped.
      if(scores[stack_top] == -SCORE_MAX) {
	states[stack_top+1] = states[stack_top];
	bitstate_skip_turn(&states[stack_top+1]);
	moves[stack_top+1] = bitstate_allowed_moves(&states[stack_top+1], &movec);
	bounds[stack_top+1].alpha = -bounds[stack_top].beta;
	bounds[stack_top+1].beta = -bounds[stack_top].alpha;
	moves_allocated[stack_top+1] = false;
	moves_index[stack_top+1] = moves_index[stack_top];
 
	stack_top++;
	continue;
      } else {
	stack_top--;
	count++;
      }
    }
  }
  
  gettimeofday(&end, NULL);

  double elapsed = (double)((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))/(double)1000000;
  printf("count = %ld\n", count);
  printf("elapsed = %lf s\n", elapsed);
  printf("speed = %lf k/s\n", count/elapsed/1000);

  
  return scores[0];
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
    BitMask flipped = flip_bitboard_via_pext_w(&board, pos_index);
    if(flipped == 0){
      flip_bitboard_via_pext_b(&board, pos_index);
    }
  } else {
    BitMask flipped = flip_bitboard_via_pext_b(&board, pos_index);
    if(flipped == 0){
      flip_bitboard_via_pext_w(&board, pos_index);
    }
  }


  return ((side == W) ? 1 : (-1)) * (double) (__builtin_popcountll(board.w) - __builtin_popcountll(board.b));
}

// TODO
double negamax_end_with_2_empty(BitState *state){
#ifdef SHOW_STAT
  count_node += 3;
#endif

  return 0;
}


static inline int cmp_mobility(const void *move1, const void *move2, void *opp_mobility) {
  return ((char *)opp_mobility)[(int)*(char *)move1] - ((char *)opp_mobility)[(int)*(char *)move2];
}
 
static inline int cmp_mobility_2(const void *move1, const void *move2, void *cmp_info) {
  int8_t *start = *(int8_t **)cmp_info;
  int8_t *opp_mobility = (int8_t *)(cmp_info + sizeof(int8_t *));

  int ret = ((int8_t *)opp_mobility)[(int)((int8_t *)move2 - start)] -
    ((int8_t *)opp_mobility)[(int)((int8_t *)move1 - start)];
  
  return ret;
}
