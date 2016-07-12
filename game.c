#include "game.h"

Table global_table;
FlatConfTable **global_fcts;
int global_n_f;

int run_game(int print_endgame_flag, int print_midgame_flag, Player white, Player black){
  State state = create_state();
  init_state(state);

  const int size = 1 << 2;
  Table table = create_and_init_table(size);
  global_table = table;
  int turn = 0;
  if(print_midgame_flag){
    printf("(Turn %d)\n", turn);
    print_state(state);
  }

  while(!state_final(state)){

    int movec;    
    Pos *moves = allowed_moves_inplace(state, &movec);
    
    if(movec == 0){
      if(print_midgame_flag)
	printf("Turn skipped.\n");
      skip_turn(state);
    } else {
      
      int move_num;
      if(state->turn == B){
	move_num = get_move(state, black);
      } else {
	move_num = get_move(state, white);
      }
      
      place_piece_indexed(state, move_num);

      if(print_midgame_flag)
	printf("(makes move at %c%c (%d,%d) (move index %d))\n", moves[move_num].c+'A', moves[move_num].r+'1', moves[move_num].r, moves[move_num].c, move_num);
    }
    
    turn++;

    table_free_nonreachable_state(table, state);


    //printf("table->total = %d\n", table->total);
    
    if(print_midgame_flag){
      printf("\n(Turn %d)\n", turn);
      print_state(state);

      /*
      Config_store board = board_to_conf_nocreate(state->board);
      int cat = CAT(BOARD_SIZE_SQR - __builtin_popcountl(board.x));
      int n_f = global_n_f;
      double score = get_score_from_fct_list(global_fcts[cat], n_f, board);
      printf("score = %30.20lf\n", score);
      */
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

  free_table(table);
  free_state(state);
  return 0;

}

int run_game_from_seq(State state, Pos *seq, int print_endgame_flag, int print_midgame_flag){
  assert(state != NULL);
  int turn = 0;
  
  //State state = create_state();
  Pos moves[POS_STORE_SIZE]; int movec; 
  //init_state(state);

  if(print_midgame_flag){
    printf("(Turn %d)\n", turn);
    print_state(state);
  }

  while(!state_final(state)){
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

    if(print_midgame_flag){
      printf("\n(Turn %d)\n", turn);
      print_state(state);
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

int get_move(State state, Player player){

  int move_num;
  int movec;
  Pos *moves = allowed_moves_inplace(state, &movec);
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
