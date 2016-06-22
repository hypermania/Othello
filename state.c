#include "state.h"

State create_state(void){

  State state = malloc(sizeof(State_store));
  //state->board = create_board();
  return state;
}

int free_state(State state){
  if(state == NULL)
    return -1;
  //free_board(state->board);
  free(state);
  return 0;
}

int cpy_state(State dest, State src){
  if(dest == NULL)
    return -1;
  if(src == NULL)
    return -2;
  /*
  memcpy((void *)dest->board, (void *)src->board, BOARD_SIZE_SQR * sizeof(char));
  dest->turn = src->turn;
  dest->control = src->control;
  dest->movec = src->movec;
  */
  memcpy((void *)dest, (void *)src, sizeof(State_store));
  
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

  memset((void *)&(state->control), 0, sizeof(State_store) - ((void *)&(state->control) - (void *)state));
  
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
  /*
  if(state == NULL)
    return -1;
  if(check_pos(pos) < 0)
    return -2;
  if(check_val(side) < 0)
    return -3;

  if(board_get_pos(state->board, pos) != X){
    return 0;
  }
  */
  
  Board board = state->board;
  int opp_side = opposite_side(side);
  Pos adjs[ADJ_SIZE];
  int adjc = adj_given_pos(board, pos, adjs, opp_side);
  int i;
  for(i=0;i<adjc;i++){

    Pos head = adjs[i];
    int direc_h = adjs[i].r - pos.r;
    int direc_v = adjs[i].c - pos.c;
    head.r += direc_h;
    head.c += direc_v;
    while((check_pos(head) == 0) && (board_get_pos(board, head) == opp_side)){
      head.r += direc_h;
      head.c += direc_v;
    }

    if(check_pos(head) < 0)
      continue;

    if(board_get_pos(board, head) == side)
      return 1;
  }
  return 0;
}


int allowed_moves(State state, Pos *store, int side){
  assert(state != NULL);
  assert(check_side(side) == 0);
  
  if(side == state->turn){
    if(state->control.trans_filled == false){
      fill_trans(state);
    }
    if(store != NULL){
      memcpy(store, state->moves, state->movec * sizeof(Pos));
    }
    return state->movec;
  } else {

    int need_to_store = 0;
    if(state == NULL){
      printf("state == NULL\n");
      return -1;
    }
    if(store != NULL){
      //printf("store == NULL\n");
      need_to_store = 1;
    }
    if(check_val(side) < 0){
      printf("check_val < 0\n");
      return -3;
    }
    
    Board board = state->board;
    int count = 0;
    int r,c;
    if(need_to_store){
      for(r=0;r<BOARD_SIZE;r++){
	for(c=0;c<BOARD_SIZE;c++){
	  if(board_get_pos(board, (Pos) {r,c}) != X)
	    continue;
	  if(can_place_at(state, (Pos) {r,c}, side)){
	    store[count] = (Pos) {r,c};
	    count++;
	  }
	}
      }
    } else {
      for(r=0;r<BOARD_SIZE;r++){
	for(c=0;c<BOARD_SIZE;c++){
	  if(board_get_pos(board, (Pos) {r,c}) != X)
	    continue;
	  if(can_place_at(state, (Pos) {r,c}, side)){
	    count++;
	  }
	}
      }
    }
    
    return count;
  }
}


int place_piece(State state, Pos pos, int side){
  assert(state != NULL);
  assert(check_pos(pos) == 0);
  assert(check_side(side) == 0);

  if(state->control.trans_filled && (side == state->turn)){
    int i;
    for(i=0;i<state->movec;i++){
      if(pos.r == state->moves[i].r && pos.c == state->moves[i].c){
	memcpy(state->board, state->positions[i], BOARD_SIZE_SQR * sizeof(char));
	state->control.trans_filled = false;
	record_seq(state, pos);
	return 0;
      }
    }
  }
  
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
  record_seq(state, pos);
  return count;
}


int state_switch_turn(State state){
  assert(state != NULL);
  state->turn = opposite_side(state->turn);
  return 0;
}


int count_pieces(State state, int val){
  assert(state != NULL);
  assert(check_val(val) == 0);

  Board board = state->board;
  int r, c;
  int count = 0;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(board_get_pos(board, (Pos) {r,c}) == val)
	count++;
    }
  }

  
  return count;
}

int state_final(State state){
  assert(state != NULL);

  if((allowed_moves(state, NULL, W) == 0) && (allowed_moves(state, NULL, B) == 0))
    return 1;
  return 0;
}


/* below are internal function: no error checking */

void fill_trans(State state){
  assert(state != NULL);
  
  if(state->control.trans_filled == false){
    Board board = state->board;
    int movec = 0;
    int r,c;
    for(r=0;r<BOARD_SIZE;r++){
      for(c=0;c<BOARD_SIZE;c++){
	if(board_get_pos(board, (Pos) {r,c}) != X)
	  continue;
	if(try_to_place(board, state->positions[movec], (Pos) {r,c}, state->turn) > 0){
	  state->moves[movec++] = (Pos) {r,c};
	}
      }
    }
    state->movec = movec;
  }
}


int try_to_place(Board board, Board dest, Pos pos, int side){
  assert(board != NULL);
  assert(dest != NULL);
  assert(check_pos(pos) == 0);
  assert(check_side(side) == 0);
  
  memcpy(dest, board, BOARD_SIZE_SQR * sizeof(char));

  int opp_side = opposite_side(side);
  Pos adjs[ADJ_SIZE];
  int adjc = adj_given_pos(dest, pos, adjs, opp_side);

  board_set_pos(dest, pos, side);
  
  int i;
  int count = 0;
  for(i=0;i<adjc;i++){
    Pos head = adjs[i];
    int direc_h = adjs[i].r - pos.r;
    int direc_v = adjs[i].c - pos.c;
    while((check_pos(head) == 0) && (board_get_pos(dest, head) == opp_side)){
      head.r += direc_h;
      head.c += direc_v;
    }

    if(check_pos(head) < 0)
      continue;
    
    if(board_get_pos(dest, head) == side){
      head.r -= direc_h;
      head.c -= direc_v;
      while(board_get_pos(dest, head) == opp_side){
	board_set_pos(dest, head, side);
	head.r -= direc_h;
	head.c -= direc_v;
      }
      count++;
    }
  }
  
  if(count>0)
    return 1;
  
  return 0;
}

void record_seq(State state, Pos pos){
  assert(state != NULL);
  assert(check_pos(pos) == 0);
  
  state->seq[state->seq_num++] = pos;
}

