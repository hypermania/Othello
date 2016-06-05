#include "state.h"

State create_state(void){

  State state = malloc(sizeof(State_store));
  state->board = create_board();
  return state;
}

int free_state(State state){
  if(state == NULL)
    return -1;
  free_board(state->board);
  free(state);
  return 0;
}

int cpy_state(State dest, State src){
  if(dest == NULL)
    return -1;
  if(src == NULL)
    return -2;
  
  int r,c;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      Pos pos = {r,c};
      board_set_pos(dest->board, pos, board_get_pos(src->board, pos));
    }
  }
  dest->turn = src->turn;
  
  return 0;
}


int init_state(State state){
  if(state == NULL)
    return -1;

  Board board = state->board;
  init_board(board);
  state->turn = B;

  int r = BOARD_SIZE/2;
  board_set_pos(board, (Pos) {r-1,r-1}, W);
  board_set_pos(board, (Pos) {r,r}, W);
  board_set_pos(board, (Pos) {r,r-1}, B);
  board_set_pos(board, (Pos) {r-1,r}, B);
  
  return 0;
}


int state_get_pos(State state, Pos pos){
  if(state == NULL)
    return -1;
  if(check_pos(pos) < 0)
    return -2;
  return board_get_pos(state->board, pos);
}

int state_get_turn(State state){
  if(state == NULL)
    return -1;
  return state->turn;
}

int opposite_side(int side){
  if(check_side(side) < 0)
    return -1;
  return 3-side;
}

int can_place_at(State state, Pos pos, int side){
 
  if(state == NULL)
    return -1;
  if(check_pos(pos) < 0)
    return -2;
  if(check_val(side) < 0)
    return -3;

  if(board_get_pos(state->board, pos) != X){
    return 0;
  }

  Board board = state->board;
  int opp_side = opposite_side(side);
  Pos adjs[ADJ_SIZE];
  int adjc = adj_sided_pos(board, pos, adjs, opp_side);
  int i;
  for(i=0;i<adjc;i++){
    /*
    if(board_get_pos(board, adjs[i]) != opp_side)
      continue;
    */
    Pos head = adjs[i];
    int direc_h = adjs[i].r - pos.r;
    int direc_v = adjs[i].c - pos.c;
    head.r += direc_h;
    head.c += direc_v;
    while(board_get_pos(board, head) == opp_side){
      head.r += direc_h;
      head.c += direc_v;
    }
    /*
    if(check_pos(head) < 0)
      continue;
    */
    if(board_get_pos(board, head) == side)
      return 1;
  }


  return 0;
}


int allowed_moves(State state, Pos *store, int side){

  int need_to_store = 0;
  if(state == NULL)
    return -1;
  if(store != NULL)
    need_to_store = 1;
  if(check_val(side) < 0)
    return -3;

  Board board = state->board;
  int count = 0;
  int r,c;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(board_get_pos(board, (Pos) {r,c}) != X)
	continue;
      if(can_place_at(state, (Pos) {r,c}, side)){
	if(need_to_store)
	  store[count] = (Pos) {r,c};
	count++;
      }
    }
  }


  return count;
}



int place_piece(State state, Pos pos, int side){

  
  if(state == NULL)
    return -1;
  if(check_pos(pos) < 0)
    return -2;
  if(check_val(side) < 0)
    return -3;

  Board board = state->board;
  int opp_side = opposite_side(side);
  Pos adjs[ADJ_SIZE];
  int adjc = adj_pos(pos, adjs);

  board_set_pos(board, pos, side);
  
  int i, count = 0;
  for(i=0;i<adjc;i++){
    if(board_get_pos(board, adjs[i]) != opp_side)
      continue;

    Pos head = adjs[i];
    int direc_h = adjs[i].r - pos.r;
    int direc_v = adjs[i].c - pos.c;
    while((check_pos(head) == 0) && (board_get_pos(board, head) == opp_side)){
      head.r += direc_h;
      head.c += direc_v;
    }

    if(check_pos(head) < 0)
      continue;
    
    if(board_get_pos(board, head) == side){
      head.r -= direc_h;
      head.c -= direc_v;
      while(board_get_pos(board, head) == opp_side){
	board_set_pos(board, head, side);
	count++;
	head.r -= direc_h;
	head.c -= direc_v;
      }
    }
  }



  return count;
}


int state_switch_turn(State state){
  if(state == NULL)
    return -1;
  state->turn = opposite_side(state->turn);
}


int count_pieces(State state, int side){

  if(state == NULL)
    return -1;
  if(check_val(side) < 0)
    return -2;
  if(side == X)
    return -2;

  Board board = state->board;
  int r, c;
  int count = 0;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(board[r][c] == side)
	count++;
    }
  }

  
  return count;
}

int state_final(State state){
  if(state == NULL)
    return -1;
  if((allowed_moves(state, NULL, W) == 0) && (allowed_moves(state, NULL, B) == 0))
    return 1;
  return 0;
}
