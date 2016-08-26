#include "test.h"

int test_bitboard(void){
  BitBoard board = new_empty_bitboard();

  int naive_board[BOARD_SIZE][BOARD_SIZE];
  char vals[3] = {EMPTY, W, B};
  int i, j;
  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      int r = rand() % 3;
      naive_board[i][j] = vals[r];
    }
  }


  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      if(bitboard_get_pos_nonref(board, pos_mask[i][j]) != EMPTY)
	return -1;
      bitboard_set_pos(&board, pos_mask[i][j], naive_board[i][j]);
    }
  }

  int ret1;
  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      ret1 = bitboard_get_pos_nonref(board, pos_mask[i][j]);
      if(ret1 != naive_board[i][j])
	return -1;
    }
  }

  //print_bitboard(board);
  
  return 0;
}

int test_bitstate(void){
  BitState *state = create_initial_bitstate();

  /*
  long int stage_count[60];
  long int stage_movec[60];

  int stage;
  for(stage=0;stage<60;stage++){
    stage_count[stage] = 0;
    stage_movec[stage] = 0;
  }
  */
  
  int times = 1 << 21;
  int i;
  for(i=0;i<times;i++){
    init_bitstate(state);
    
    while(!bitstate_final(state)){
      int movec;
      bitstate_allowed_moves(state, &movec);

      //stage = __builtin_popcountll(state->board.w) + __builtin_popcountll(state->board.b) - 4;
      //stage_count[stage]++;
      //stage_movec[stage] += movec;
      
      if(movec > 0){
	bitstate_place_piece(state, 0);
      } else {
	bitstate_skip_turn(state);
      }

    }
    //print_bitboard(state->board);
  }

  /*
  for(stage=0;stage<60;stage++){
    printf("%d pieces: avg_movec = %lf\n", stage+4, (double)stage_movec[stage]/(double)stage_count[stage]);
  }
  */
  
  return 0;
}

