#include "game.h"


int run_game(int print_endgame_flag, int print_midgame_flag, int human_player_flag, int depthw, int depthb){

  State state = create_state();
  Pos moves[POS_STORE_SIZE]; int movec;
  init_state(state);
  int turn = 0;
  while(!state_final(state)){
    if(print_midgame_flag){
      printf("(Turn %d)\n", turn);
      print_state(state);

      /*
      Config_store board = board_to_conf_nocreate(state->board);
      int cat = CAT(BOARD_SIZE_SQR - __builtin_popcountl(board.x));
      int n_f = 50;
      double score = get_score_from_fct_list(global_fcts[cat], n_f, board);
      printf("score = %30.20lf\n", score);
      */
    }
    
    movec = allowed_moves(state, moves);
    if(movec == 0){
      if(print_midgame_flag)
	printf("Turn skipped.\n");
      skip_turn(state);
    } else {
      int r;
      if(human_player_flag){
	if(state->turn == B){
	  print_options(moves, movec);
	  r = get_human_response(movec);
	} else {
	  r = best_next_state(state, moves, movec, depthw);
	}
      } else {
	if(state->turn == B){
	  r = best_next_state(state, moves, movec, depthb);
	} else {
	  r = best_next_state(state, moves, movec, depthw);
	}
      }

      place_piece(state, moves[r]);
      //state_switch_turn(state);
      
      if(print_midgame_flag)
	printf("(makes move at (%d,%d))\n", moves[r].r, moves[r].c);
      
    }
    turn++;
  }
  if(print_midgame_flag){
    printf("(end of game)\n");
    print_state(state);
  }

  
  if(print_endgame_flag){
    
    int wp = count_pieces(state->board, W);
    int bp = count_pieces(state->board, B);
    if(wp > bp){
      printf("White wins: %d - %d\n", wp, bp);
    } else if(wp < bp){
      printf("Black wins: %d - %d\n", wp, bp);
    } else {
      printf("Draw: %d - %d\n", wp, bp);
    }
  }

  return 0;

}

int run_game_from_seq(State state, Pos *seq, int print_endgame_flag, int print_midgame_flag){
  assert(state != NULL);
  int turn = 0;
  
  //State state = create_state();
  Pos moves[POS_STORE_SIZE]; int movec; 
  //init_state(state);
  while(!state_final(state)){
    if(print_midgame_flag){
      printf("(Turn %d)\n", turn);
      print_state(state);
    }
    movec = allowed_moves(state, moves);
    if(movec == 0){
      if(print_midgame_flag)
	printf("Turn skipped.\n");
      skip_turn(state);
    } else {
      int i; int moved = 0;
      for(i=0;i<movec;i++){
	if(moves[i].r == seq[turn].r && moves[i].c == seq[turn].c){
	  place_piece(state, seq[turn]);
	  //state_switch_turn(state);
	  moved = 1;
	}
      }
      if(moved == 0){
	//printf("incomplete game\n");
	return -1;
      }
      if(print_midgame_flag)
	printf("(makes move at (%d,%d))\n", seq[turn].r, seq[turn].c);

      turn++;
    }

  }
  
  if(print_midgame_flag){
    printf("(end of game)\n");
    print_state(state);
  }
  
  if(print_endgame_flag){
    
    int wp = count_pieces(state->board, W);
    int bp = count_pieces(state->board, B);
    if(wp > bp){
      printf("White wins: %d - %d\n", wp, bp);
    } else if(wp < bp){
      printf("Black wins: %d - %d\n", wp, bp);
    } else {
      printf("Draw: %d - %d\n", wp, bp);
    }
  }

  return 0;

}
