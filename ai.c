#include "ai.h"

int total_pieces(State state, int side){
  return count_pieces(state, side);
}

int consider_corner(State state, int side){
  int result;
  int mypieces = count_pieces(state, side);
  int opp_side = opposite_side(side);
  result = mypieces;
  int opppieces = count_pieces(state, opp_side);
  
  if(state_final(state) == 1){
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

    /* //(start) original implementation
    Pos neighbours[3];
    adj_pos(corners[i], neighbours);
    int j;
    for(j=0;j<3;j++){
      if(state_get_pos(state, neighbours[j]) == side){
	if(corner_val == side)
	  result += 8;
	if(corner_val == opp_side)
	  result -= 16;
	if(corner_val == X)
	  result -= 8;
      }
    }
    */ //(end) orignal implementation
  }
  
  //Pos store[TEMP_STORE];
  result += allowed_moves(state, NULL, side) * 4;
  //result -= allowed_moves(state, NULL, opp_side) * 1;
  
    
  return result;
}

int state_score(State state, int side, int depth){
  int result = abpruning(state, depth, INT_MIN, INT_MAX, side);
  return result;
}

// private static function with no error checking
// returns the score my making the move
static int get_score_for_move(State state, Pos move,  int param){
  State hold = create_state();
  cpy_state(hold, state);
  int my_side = hold->turn;
  
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
  int max_score = INT_MIN;
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
  }
  /*
  for(i=0;i<num_max_moves;i++){
    printf("thread:max_moves[] = %d, moves[max_moves[%d]] = (%d,%d)\n", max_moves[i], i, moves[max_moves[i]].r, moves[max_moves[i]].c);
  }
  */
  int r = rand() % num_max_moves;
  return max_moves[r];
  
  /* (start) original implementation */
  /*
  int j = 0;
  //int i;
  Pos maxmoves[TEMP_STORE];
  State hold = create_state();  
  int maxscore = INT_MIN;
  int score;
  for(i=0;i<movec;i++){
    cpy_state(hold, state);
    int my_side = hold->turn;
    place_piece(hold, moves[i], hold->turn);
    state_switch_turn(hold);
    score = state_score(hold, my_side, param);

    if(score > maxscore){
      j = 0;
      maxmoves[j] = moves[i];
      j++;
      maxscore = score;
    } else if(score == maxscore){
      maxmoves[j] = moves[i];
      j++;
    }

  }
  free_state(hold);
  
  for(i=0;i<j;i++){
    printf("original:maxmoves:(%d,%d)\n", maxmoves[i].r, maxmoves[i].c);
  }
  */
  /*

  int r = rand() % j;

  for(i=0;i<movec;i++){
    if((maxmoves[r].r == moves[i].r) && (maxmoves[r].c == moves[i].c)){
      return i;
    }
  }
  */
  /* (end) original implementation */

  return 0;
}

int abpruning(State state, int depth, int a, int b, int side){
  if(state == NULL)
    return -1;

  int (*scorer_ptr)(State, int) = consider_corner;
  
  if((depth == 0) || (state_final(state) == 1))
    return (*scorer_ptr)(state, side);
  
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

