#include "game.h"

FlatConfTable **global_fcts;
int global_n_f;

int run_game(int print_endgame_flag, int print_midgame_flag, Player white, Player black){
  BitState *state = create_initial_bitstate();
  init_bitstate(state);

  int turn = 0;
  if(print_midgame_flag){
    printf("(Turn %d)\n", turn);
    print_bitstate(state);
  }

  while(!bitstate_final(state)){

    int movec;    
    bitstate_allowed_moves(state, &movec);
    
    if(movec == 0){
      if(print_midgame_flag)
	printf("Turn skipped.\n");
      bitstate_skip_turn(state);
    } else {
      
      int move_num;
      if(state->turn == B){
	move_num = get_move(state, black);
      } else {
	move_num = get_move(state, white);
      }

      uint64_t move_made = state->moves[move_num];
      
      bitstate_place_piece(state, move_num);

      if(print_midgame_flag)
	print_move_made(move_made, move_num);
      
    }

    turn++;
    
    if(print_midgame_flag){
      printf("\n(Turn %d)\n", turn);
      print_bitstate(state);

    }
  }
  
  if(print_midgame_flag){
    printf("(end of game)\n");
  }

  if(print_endgame_flag){
    
    int wp = __builtin_popcountll(state->board.w);
    int bp = __builtin_popcountll(state->board.b);
    if(wp > bp){
      printf("White wins: %d - %d\n", wp, bp);
    } else if(wp < bp){
      printf("Black wins: %d - %d\n", wp, bp);
    } else {
      printf("Draw: %d - %d\n", wp, bp);
    }
  }

  free_bitstate(state);
  return 0;

}

/*
int run_game_from_seq(BitState *state, BitMask *seq, int print_endgame_flag, int print_midgame_flag){
  assert(state != NULL);
  int turn = 0;
  
  //BitState *state = create_initial_bitstate();
  BitMask moves[POS_STORE_SIZE]; int movec; 
  //init_bitstate(state);

  if(print_midgame_flag){
    printf("(Turn %d)\n", turn);
    print_bitstate(state);
  }

  while(!bitstate_final(state)){
    movec = allowed_moves(state, moves);
    if(movec == 0){
      if(print_midgame_flag)
	printf("Turn skipped.\n");
      bitstate_skip_turn(state);
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

    if(print_midgame_flag){
      printf("\n(Turn %d)\n", turn);
      print_bitstate(state);
    }

  }
  
  if(print_midgame_flag){
    printf("(end of game)\n");
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
*/

int get_move(BitState *state, Player player){

  int move_num;
  int movec;
  BitMask *moves = bitstate_allowed_moves(state, &movec);
  switch(player.type){
  case HUMAN:
    print_options(moves, movec);
    move_num = get_human_response(movec);
    break;
  case RANDOM:
    move_num = rand() % movec;
    break;
  case IMMEDIATE:
    move_num = optimizing_move(state, player.param);
    break;
  case NEGAMAX:
    move_num =
      negamaxing_move(state,
		      ((NegamaxConf *)(player.param))->depth,
		      ((NegamaxConf *)(player.param))->score_func);
    break;
  case MIXED:
    move_num =
      mixed_move(state,
		 ((MixedConf *)(player.param))->depth_middle,
		 ((MixedConf *)(player.param))->score_func,
		 ((MixedConf *)(player.param))->depth_end);
    break;
  default:
    move_num = 0;
    break;
  }

  return move_num;
}
