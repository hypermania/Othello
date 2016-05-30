#include "ai.h"

int consider_corner(State state, int side, int cor_param){
  int result = count_pieces(state, side);

  if(state_get_pos(state, (Pos) {0,0}) == side)
    result += 6;
  if(state_get_pos(state, (Pos) {0,BOARD_SIZE-1}) == side)
    result += 6;
  if(state_get_pos(state, (Pos) {BOARD_SIZE-1,0}) == side)
    result += 6;
  if(state_get_pos(state, (Pos) {BOARD_SIZE-1, BOARD_SIZE-1}) == side)
    result += 6;
  
  Pos store[32];
  result += allowed_moves(state, store, state->turn) * cor_param;
  return result;
}

int state_score(State state, int side){
  int result = count_pieces(state, side);

  if(state_get_pos(state, (Pos) {0,0}) == side)
    result += 6;
  if(state_get_pos(state, (Pos) {0,BOARD_SIZE-1}) == side)
    result += 6;
  if(state_get_pos(state, (Pos) {BOARD_SIZE-1,0}) == side)
    result += 6;
  if(state_get_pos(state, (Pos) {BOARD_SIZE-1, BOARD_SIZE-1}) == side)
    result += 6;
  
  Pos store[32];
  result += allowed_moves(state, store, state->turn) * 3;
  state_switch_turn(state);
  result -= allowed_moves(state, store, state->turn) * 2;
  return result;
}


int best_next_state(State state, Pos *moves, int movec){

  State hold = create_state();
  
  int i,j = 0; Pos maxmoves[30];
  memset(maxmoves, 0, 30 * sizeof(Pos));
  
  int maxscore = -1000000;
  int score;
  for(i=0;i<movec;i++){
    cpy_state(hold, state);
    place_piece(hold, moves[i], hold->turn);
    score = state_score(hold, hold->turn);
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

