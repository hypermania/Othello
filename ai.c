#include "ai.h"

int total_pieces(State state, int side){
  return count_pieces(state, side);
}

int consider_corner(State state, int side){
  int result;
  
  int mypieces = count_pieces(state, side);
  result = mypieces;

  int opp_side = opposite_side(side);
  
  Pos corners[4] = {(Pos) {0,0}, (Pos) {0,BOARD_SIZE-1}, (Pos) {BOARD_SIZE-1,0}, (Pos) {BOARD_SIZE-1,BOARD_SIZE-1}};
  Pos neighbours[3];
  int i;
  for(i=0;i<4;i++){
    int corner_val = state_get_pos(state, corners[i]);
    if(corner_val == side)
      result += 10;
    if(corner_val == opp_side)
      result -= 10;
    adj_pos(corners[i], neighbours);
    int j;
    for(j=0;j<3;j++){
      if(state_get_pos(state, neighbours[j]) == side)
	result -= 8;
    }
  }
  
  //Pos store[TEMP_STORE];
  result += allowed_moves(state, NULL, side) * 4;
  
  if(state_final(state) == 1){
    int opppieces = count_pieces(state, opp_side);
    if(mypieces < opppieces)
      return INT_MIN;      
    if(mypieces > opppieces)
      return INT_MAX;
  }
    
  return result;
}

int state_score(State state, int side, int depth){
  int result = abpruning(state, depth, INT_MIN, INT_MAX, side);
  return result;
}

int best_next_state(State state, Pos *moves, int movec, int param){
  if(state == NULL)
    return -1;
  if(moves == NULL)
    return -2;
  // should try to eliminate error conditions
  State hold = create_state();
  
  int i,j = 0; Pos maxmoves[TEMP_STORE];
  //memset(maxmoves, 0, TEMP_STORE * sizeof(Pos));
  
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

