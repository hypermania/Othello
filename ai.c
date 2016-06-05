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
    //Pos neighbours[3];
    int mycount = adj_sided_pos(state->board, corners[i], NULL, side);
    //int oppcount = adj_sided_pos(state->board, corners[i], neighbours, opp_side);
    if(corner_val == side) {
      result += 8*mycount;
    } else if(corner_val == opp_side){
      result -= 16*mycount;
    } else {
      result -= 8*mycount;
    }
    
    /*

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
    */
  }
  
  //Pos store[TEMP_STORE];
  result += allowed_moves(state, NULL, side) * 4;
  result -= allowed_moves(state, NULL, opp_side) * 1;
  
    
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
  int scores[TEMP_STORE];
  global_state = state; global_moves = moves; global_param = param;
  global_scores = scores;
  pthread_t tids[TEMP_STORE];
  /*
int i; int j;
  for(j=0;j<(movec+3)/4;j++){
    for(i=0;i<4;i++){
      //scores[i] = get_score_for_move(state, moves[i], param);
      if(4*j+i < movec)
	pthread_create(&(tids[i]), NULL, store_score, (void *)(4*j+i));
    }
    for(i=0;i<4;i++){
      if(4*j+i < movec)
	pthread_join(tids[4*j+i], NULL);
    }
  }
  */
  int i;
  for(i=0;i<movec;i++){
    pthread_create(&(tids[i]), NULL, store_score, (void *)(i));
  }
  for(i=0;i<movec;i++){
      pthread_join(tids[i], NULL);
  }

  int max_moves[TEMP_STORE];
  int num_max_moves = 0;
  int max_score = INT_MIN;
  for(i=0;i<movec;i++){
    if(scores[i] > max_score){
      max_score = scores[i];
      max_moves[num_max_moves++] = i;
    } else if(scores[i] == max_score){
      max_moves[num_max_moves++] = i;
    }
  }
  if(num_max_moves == 0)
    return 0;
  int r = rand() % num_max_moves;
  return max_moves[r];
  //memset(maxmoves, 0, TEMP_STORE * sizeof(Pos));
  /*
  int i,j = 0; Pos maxmoves[TEMP_STORE];
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
      maxmoves[j++] = moves[i];
      maxscore = score;
    } 
    if(score == maxscore)
      maxmoves[j++] = moves[i];
  }
  free_state(hold);

  
  int r = rand() % j;

  for(i=0;i<movec;i++){
    if((maxmoves[r].r == moves[i].r) && (maxmoves[r].c == moves[i].c))
      return i;
  }
  */  
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

