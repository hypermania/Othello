#include "ai.h"

Table global_table;
FlatConfTable **global_fcts;
int global_n_f;

// heuristic scoring functions
int total_pieces(State state, int side){
  return count_pieces(state->board, side)
    - count_pieces(state->board, opposite_side(side));
}

double heuristic_score_0(State state){
  //return (double) (count_pieces(state->board, W) - count_pieces(state->board, B));
  return (double) piece_diff(state->board, W, B);
  //Config_store board = board_to_conf_nocreate(state->board);
  
  //return __builtin_popcountl(board.w) - __builtin_popcountl(board.b);
}


double heuristic_score_1(State state){
  //printf("heuristic_score_1\n");

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
  Config_store board = board_to_conf_nocreate(state->board);
  int cat = CAT(BOARD_SIZE_SQR - __builtin_popcountl(board.x));
  /*
  if(board.w == 0){
    return -DBL_MAX;
  }
  if(board.b == 0){
    return DBL_MAX;
  }
  */
  if(state_final(state)){
    return heuristic_score_0(state);
  }
  
  return get_score_from_fct_list(global_fcts[cat], global_n_f, board);
}


/*
double state_score(State state, int my_side, int param){
  //int result = abpruning(state, param, -ROUNDS, ROUNDS, my_side);
  double result = abpruning(state, param, -DBL_MAX, DBL_MAX, my_side);

  return result;
}

// private static function with no error checking
// returns the score my making the move
double get_score_for_move(State state, Pos move,  int param){
  State hold = create_state();
  cpy_state(hold, state);
  int my_side = hold->turn;

  place_piece(hold, move);
  double score = state_score(hold, my_side, param);
  
  free_state(hold);
  return score;
}

State global_state;
Pos *global_moves;
double *global_scores;
int global_param;

static void *store_score(void *vargp){

  global_scores[(long int)vargp] = get_score_for_move(global_state, global_moves[(long int)vargp], global_param);

  return NULL;
}



int best_next_state(State state, Pos *moves, int movec, int param){
  if(state == NULL)
    return -1;
  if(moves == NULL)
    return -2;
  // should try to eliminate error conditions
  if(movec == 1)
    return 0;
  
  double scores[POS_STORE_SIZE];
  global_state = state;
  global_moves = moves;
  global_scores = scores;
  global_param = param;

  pthread_t tids[POS_STORE_SIZE];
  int i;
  for(i=0;i<movec;i++){
    pthread_create(&(tids[i]), NULL, store_score, (void *)i);
  }
  for(i=0;i<movec;i++){
      pthread_join(tids[i], NULL);
  }

  int max_moves[POS_STORE_SIZE];
  int num_max_moves = 0;
  double max_score = -DBL_MAX;
  for(i=0;i<movec;i++){
    if(scores[i] > max_score){
      num_max_moves = 0;
      max_moves[num_max_moves] = i;
      num_max_moves++;
      max_score = scores[i];
    } else if(scores[i] == max_score){
      max_moves[num_max_moves] = i;
      num_max_moves++;
    }
  }
  
  int r = rand() % num_max_moves;

  int result = max_moves[r];

  return result;
  //return max_moves[r];
  
  //return 0;
}
*/


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
    State info = table_get_state(global_table, pivot);
    double score = ((side == W) ? 1 : (-1)) * 
      state_compute_score(info, score_func); // min(a,b) = -max(-a,-b)
    if(score > max_score){
      max_move = i;
      max_score = score;
    }

  }
  free_state(pivot);
  return max_move;
}

int count_node = 0;

int negamaxing_move(State state, int depth, double (*score_func)(State)){
  assert(state != NULL);

  int move_num = 0;
  negamax(state, depth, -DBL_MAX, DBL_MAX, &move_num, score_func);
  
  return move_num;
}

int negamaxing_move_dnstore(State state, int depth, double (*score_func)(State)){
  assert(state != NULL);

  //count_node = 0;
  
  int move_num = 0;
  negamax_dnstore(state, depth, -DBL_MAX, DBL_MAX, &move_num, score_func);

  //printf("count_node = %d\n", count_node);
  
  return move_num;
}

int mixed_move_dnstore(State state, int depth_middle, double (*score_func)(State), int depth_end){
  assert(state != NULL);

  //count_node = 0;
  Config_store board = board_to_conf_nocreate(state->board);
  int empty_spot = __builtin_popcountl(board.x);
  
  int move_num = 0;

  double node_val;
  
  if(empty_spot > depth_end){
    node_val = negamax_dnstore(state, depth_middle, -DBL_MAX, DBL_MAX, &move_num, score_func);
    printf("score = %lf\n", link_function(node_val));
  } else {
    node_val = negamax_dnstore(state, INT_MAX, -DBL_MAX, DBL_MAX, &move_num, heuristic_score_0);
    printf("score = %lf\n", node_val);
  }

  //
  
  return move_num;
}


/*
double abpruning(State state, int depth, double a, double b, int side){
  
  if(state == NULL)
    return -1;
  int is_at_final = 0;
  if((depth == 0) || (is_at_final = (state_final(state) == 1))){
    return heuristic_score_1(state, side, is_at_final);
    //return heuristic_score_2(state) * ((side == W) ? 1 : (-1) );
  }


  Pos moves[POS_STORE_SIZE];
  int movec = allowed_moves(state, moves);
  State next = create_state();

  double v;
  if(side == state->turn){

    v = -DBL_MAX;
    int i;
    
    for(i=0;i<movec;i++){
      cpy_state(next, state);
      place_piece(next, moves[i]);
      //state_switch_turn(next);
      double score = abpruning(next, depth-1, a, b, side);
      v = (v > score) ? v : score; // v = max(v, score)
      a = (a > v) ? a : v; // a = max(a, v)
      if(b <= a)
	break;


    }
  } else {

    v = DBL_MAX;
    int i;
    for(i=0;i<movec;i++){
      cpy_state(next, state);
      place_piece(next, moves[i]);
      //state_switch_turn(next);
      double score = abpruning(next, depth-1, a, b, side);
      v = (v < score) ? v : score; // v = min(v, score)
      b = (b < v) ? b : v; // b = min(b, v)
      if(b <= a)
	break;
    }
  }

  free_state(next);
  return v;
}
*/

double negamax(State state, int depth, double alpha, double beta, int *max_move, double (*score_func)(State)){
  assert(state != NULL);

  State root = table_get_state(global_table, state);
  
  int side = root->turn;
  if(depth == 0 || state_final(root)){
    return ((side == W) ? 1 : (-1)) * state_compute_score(root, score_func);
  }

  double best_score = -DBL_MAX;
  int best_move_num = 0;
  
  int movec;
  allowed_moves_inplace(root, &movec);

  State pivot = create_state();
  
  int i;
  for(i=0;i<movec;i++){
    cpy_state(pivot, root);
    place_piece_indexed(pivot, i);
    double score = (-1) * negamax(pivot, depth-1, -beta, -alpha, NULL, score_func);
    if(score > best_score){
      best_score = score;
      best_move_num = i;
    }
    alpha = MAX(alpha, score);
    if(alpha >= beta)
      break;
    
  }

  if(max_move != NULL){
    *max_move = best_move_num;
  }

  free(pivot);
  return best_score;
}

double negamax_dnstore(State state, int depth, double alpha, double beta, int *max_move, double (*score_func)(State)){
  assert(state != NULL);

  count_node++;
  
  State root = state;
  
  int side = root->turn;
  if(depth == 0 || state_final(root)){
    return ((side == W) ? 1 : (-1)) * state_compute_score(root, score_func);
  }

  double best_score = -DBL_MAX;
  int best_move_num = 0;
  
  int movec;
  allowed_moves_inplace(root, &movec);

  if(movec == 0){
    skip_turn(state);
    return (-1) * negamax_dnstore(state, depth-1, -beta, -alpha, NULL, score_func);
  }
  
  State pivot = create_state();
  
  int i;
  for(i=0;i<movec;i++){
    cpy_state(pivot, root);
    place_piece_indexed(pivot, i);
    double score = (-1) * negamax_dnstore(pivot, depth-1, -beta, -alpha, NULL, score_func);
    if(score > best_score){
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

