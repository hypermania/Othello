#include "state.h"

inline State create_state(void){

  State state = malloc(sizeof(State_store));

  return state;
}

inline int free_state(State state){
  assert(state != NULL);
  free(state);
  return 0;
}

inline int cpy_state(State dest, State src){
  assert(dest != NULL);
  assert(src != NULL);
  
  memcpy((void *)dest, (void *)src, sizeof(State_store));
  
  return 0;
}

inline int init_state(State state){
  if(state == NULL)
    return -1;

  memset(state, 0, sizeof(State_store));
  
  Board board = state->board;
  init_board(board);
  state->turn = B;

  const int r = BOARD_SIZE/2;
  board_set_pos(board, (Pos) {r-1,r-1}, W);
  board_set_pos(board, (Pos) {r,r}, W);
  board_set_pos(board, (Pos) {r,r-1}, B);
  board_set_pos(board, (Pos) {r-1,r}, B);
  
  return 0;
}

inline State create_state_from_pivot(Board board, short turn){
  State state = malloc(sizeof(State_store));
  memset(state, 0, sizeof(State_store));
  memcpy(state->board, board, BOARD_SIZE_SQR * sizeof(char));
  state->turn = turn;
  return state;
}


inline int state_eq_seq(State head, State state){
  assert(head != NULL);
  assert(state != NULL);

  if(head->seq_num > state->seq_num){
    return 1;
  }
  
  return memcmp(head->seq, state->seq, head->seq_num * sizeof(Pos));
}

inline int allowed_moves(State state, Pos *store){
  assert(state != NULL);

  if(state->control.moves_filled == false){
    fill_moves(state);
  }
  
  if(store != NULL){
    memcpy(store, state->moves, state->movec * sizeof(Pos));
  }
  return state->movec;
  
}

inline Pos *allowed_moves_inplace(State state, int *movec){
  assert(state != NULL);

  if(state->control.moves_filled == false){
    fill_moves(state);
  }

  *movec = state->movec;
 
  return state->moves;
}


inline int place_piece(State state, Pos pos){
  assert(state != NULL);
  assert(check_pos(pos) == 0);

  if(state->control.moves_filled == false){
    fill_moves(state);
  }
  
  int i;
  for(i=0;i<state->movec;i++){
    if(pos.r == state->moves[i].r && pos.c == state->moves[i].c){
      cpy_board(state->board, state->positions[i]);
      state->turn = opposite_side(state->turn);
      record_seq(state, pos);
      state->control.moves_filled = false;
      state->control.score_valid = false;
      return 0;
    }
  }

  return -1;
}

inline int place_piece_indexed(State state, int move_num){
  assert(state != NULL);
  assert(state->control.moves_filled);
  assert(move_num < state->movec);

  cpy_board(state->board, state->positions[move_num]);
  state->turn = opposite_side(state->turn);
  record_seq(state, state->moves[move_num]);
  state->control.moves_filled = false;
  state->control.score_valid = false;
	
  return 0;
}

inline int skip_turn(State state){
  assert(state != NULL);
  assert(state->control.moves_filled);
  assert(state->movec == 0);
  
  state->turn = opposite_side(state->turn);
  state->control.moves_filled = false;
  state->control.score_valid = false;
  
  return 0;
}

State_store temp_state_store;

inline int state_final(State state){
  assert(state != NULL);

  if(allowed_moves(state, NULL) > 0){
    return 0;
  } 


  /* no available move: 
     skip the turn and check for opponent's moves
  */
  cpy_board((&temp_state_store)->board, state->board);
  temp_state_store.turn = opposite_side(state->turn);
  temp_state_store.control.moves_filled = false;
  
  int movec = allowed_moves((&temp_state_store), NULL);
  if(movec > 0){
    return 0;
  }

  /*
  State temp = create_state();

  cpy_board(temp->board, state->board);
  temp->turn = opposite_side(state->turn);
  temp->control.moves_filled = false;
  
  int movec = allowed_moves(temp, NULL);
  free_state(temp);
  if(movec > 0){
    return 0;
  }
  */
  
  return 1;
}


/* below are internal function: no error checking */

inline void fill_moves(State state){
  assert(state != NULL);
  
  if(state->control.moves_filled == false){
    Board board = state->board;
    int movec = 0;
    char r,c;
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
    
    state->control.moves_filled = true;
  }

}


inline int try_to_place(Board board, Board dest, Pos pos, int side){
  assert(board != NULL);
  assert(dest != NULL);
  assert(check_pos(pos) == 0);
  assert(check_side(side) == 0);
  
  cpy_board(dest, board);

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

inline void record_seq(State state, Pos pos){
  assert(state != NULL);
  assert(check_pos(pos) == 0);
  
  state->seq[state->seq_num++] = pos;
}

inline double state_compute_score(State state, double (*score_func)(State state)){
  assert(state != NULL);
  if(state->control.score_valid){
    return state->score;
  }

  state->score = score_func(state);
  state->control.score_valid = true;
  return state->score;
}
