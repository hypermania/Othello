#include "ai.h"

#define ROUNDS 100

int total_pieces(State state, int side){
  return count_pieces(state, side);
}

int consider_corner(State state, int side, int is_at_final){
  //printf("consider_corner\n");
  int result;
  int mypieces = count_pieces(state, side);
  int opp_side = opposite_side(side);
  result = mypieces;
  int opppieces = count_pieces(state, opp_side);

  /*
  if(mypieces + opppieces == BOARD_SIZE * BOARD_SIZE){
    if(mypieces <= opppieces){
      return INT_MIN + 16384 + (mypieces - opppieces);
    }
    if(mypieces > opppieces){
      return INT_MAX - 16384 + (mypieces - opppieces);
    }
  }
  */

  //Pos neighbours[4][3] = {{(Pos) {0,1}, (Pos) {1,0}, (Pos) {1,1}}, {(Pos) {0,BOARD_SIZE-2}, (Pos) {1,BOARD_SIZE-1}, (Pos) {1,BOARD_SIZE-2}}, {(Pos) {BOARD_SIZE-2,0}, (Pos) {BOARD_SIZE-1,1}, (Pos) {BOARD_SIZE-2,1}}, {(Pos) {BOARD_SIZE-1,BOARD_SIZE-2}, (Pos) {BOARD_SIZE-2,BOARD_SIZE-1}, (Pos) {BOARD_SIZE-2,BOARD_SIZE-2}}};

  if(is_at_final){//state_final(state) == 1){
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
    int corner_val = state_get_pos(state, corners[i]);
    if(corner_val == side)
      result += 10;
    if(corner_val == opp_side)
      result -= 10;
    //dangerous optimization using board interface

    //int oppcount = adj_sided_pos(state->board, corners[i], neighbours, opp_side);
    int mycount = adj_sided_pos(state->board, corners[i], NULL, side);
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

int state_score(State state, int my_side, int param){
  //int result = abpruning(state, param, -ROUNDS, ROUNDS, my_side);
  int result = abpruning(state, param, INT_MIN, INT_MAX, my_side);
  //int result = mcts(state, param, my_side);
  return result;
}

// private static function with no error checking
// returns the score my making the move
static int get_score_for_move(State state, Pos move,  int param){
  State hold = create_state();
  cpy_state(hold, state);
  int my_side = hold->turn;
  //printf("gsfm:my_side = %d\n", my_side);
  place_piece(hold, move, my_side);
  state_switch_turn(hold);
  int score = state_score(hold, my_side, param);
  
  free_state(hold);
  return score;
}

State global_state;
Pos *global_moves;
int *global_scores;
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
  /*
  int i;
  for(i=0;i<movec;i++){
    printf("moves:%d:(%d,%d)\n",i, moves[i].r, moves[i].c);
  }
  */
  if(movec == 1)
    return 0;
  
  int scores[TEMP_STORE];
  global_state = state;
  global_moves = moves;
  global_scores = scores;
  global_param = param;

  pthread_t tids[TEMP_STORE];
  int i;
  for(i=0;i<movec;i++){
    pthread_create(&(tids[i]), NULL, store_score, (void *)i);
  }
  for(i=0;i<movec;i++){
      pthread_join(tids[i], NULL);
  }
  
  int max_moves[TEMP_STORE];
  int num_max_moves = 0;
  int max_score = INT_MIN;   int sum_scores = 0;
  for(i=0;i<movec;i++){
    //printf("thread:i=%d, scores[i]=%d, max_score=%d, num_max_moves=%d\n", i, scores[i], max_score, num_max_moves);
    if(scores[i] > max_score){
      num_max_moves = 0;
      max_moves[num_max_moves] = i;
      num_max_moves++;
      max_score = scores[i];
    } else if(scores[i] == max_score){
      max_moves[num_max_moves] = i;
      num_max_moves++;
    }
    //sum_scores += scores[i];
    //printf("move (%d,%d): %lf\n", moves[i].r, moves[i].c, scores[i]/((double)ROUNDS));
  }
  //printf("avg = %lf\n", sum_scores/movec/((double)ROUNDS));
  /*
  for(i=0;i<movec;i++){
    printf("thread:moves[%d] (%d,%d), score = %d\n", i,  moves[i].r, moves[i].c, scores[i]);
  }
  */
  int r = rand() % num_max_moves;
  return max_moves[r];
  
  return 0;
}

//TODO
/*
int strategy_control(State state, Pos *moves, int movec, int param, int side){
  if(side == B){
    return best_next_state(State state, Pos *moves, int movec, int param);
  } else {
    return best_next_state(State state, Pos *moves, int movec, int param);
  }
  return 0;
}
*/

int abpruning(State state, int depth, int a, int b, int side){
  if(state == NULL)
    return -1;
  int is_at_final = 0;
  if((depth == 0) || (is_at_final = (state_final(state) == 1)))
    return consider_corner(state, side, is_at_final);
  
  Pos moves[TEMP_STORE];
  int movec = allowed_moves(state, moves, state->turn);
  State next = create_state();
  int v;
  if(side == state->turn){
    v = INT_MIN;
    
    int i;
    for(i=0;i<movec;i++){
      cpy_state(next, state);
      place_piece(next, moves[i], next->turn);
      state_switch_turn(next);
      int score = abpruning(next, depth-1, a, b, side);
      v = (v > score) ? v : score; // v = max(v, score)
      a = (a > v) ? a : v; // a = max(a, v)
      if(b <= a)
	break;
    }
  } else {
    v = INT_MAX;
    
    int i;
    for(i=0;i<movec;i++){
      cpy_state(next, state);
      place_piece(next, moves[i], next->turn);
      state_switch_turn(next);
      int score = abpruning(next, depth-1, a, b, side);
      v = (v < score) ? v : score; // v = min(v, score)
      b = (b < v) ? b : v; // b = min(b, v)
      if(b <= a)
	break;
    }
  }
  free_state(next);
  return v;
}

int mcts(State state, int width, int my_side){
  State hold = create_state();

  //int my_side = opposite_side(hold->turn);
  int opp_side = opposite_side(my_side);
  
  int final_score = 0;
  Pos moves[TEMP_STORE];
  int movec;
  int i;
  for(i=0;i<width;i++){
    cpy_state(hold, state);
    while(!state_final(hold)){
      movec = allowed_moves(hold, moves, hold->turn);
      if(movec>0){
	place_piece(hold, moves[rand() % movec], hold->turn);
      }
      state_switch_turn(hold);
    }
    
    int my_pieces = count_pieces(hold, my_side);
    int opp_pieces = count_pieces(hold, opp_side);
    /*
    if(my_pieces > opp_pieces){
      final_score++;
    } else if(my_pieces < opp_pieces){
      final_score--;
    }
    */
    final_score += (my_pieces - opp_pieces);
  }

  //printf("final_score = %d\n", final_score);
  free_state(hold);
  return final_score;
}


