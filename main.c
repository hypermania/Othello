#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "board.h"
#include "io.h"
#include "game.h"
#include "ai.h"

int run_game(int print_endgame_flag, int print_midgame_flag, int human_player_flag, int depthw, int depthb);
int test_board(void);
int test_state(void);

int main(int argc, char **argv){
  // set up random number generator
  struct timeval t;
  gettimeofday(&t, NULL);
  srand((long int) t.tv_usec);
  //srand((long int) 100);

  // run the game
  //run_game(1,1,0,0,5);

  // run tests
  printf("test_board = %d\n", test_board());
  printf("test_state = %d\n", test_state());
  
  exit(0);  
}
int run_game(int print_endgame_flag, int print_midgame_flag, int human_player_flag, int depthw, int depthb){
  
  Game game = create_game();
  init_game(game);
  /*
  int print_endgame_flag = 1;
  int print_midgame_flag = 1;
  int human_player_flag = 0;
  */
  
  int r = 0;
  while(is_end_of_game(game) == 0){
    if(print_midgame_flag){
      printf("Turn %d\n", game->turns);
      print_state(game->current);
    }

    if(require_input(game) == 1){

      if(game->status == W){
	r = best_next_state(game->current, game->allowed_moves, game->allowed_movec, depthw);
	//r = rand() % game->allowed_movec;
      }
      if(game->status == B){

	if(human_player_flag){
	  printf("This is your turn. Enter number to place your piece.\n");
	  
	  int i;
	  for(i=0;i<game->allowed_movec;i++){
	    printf("%d:(%d,%d)\n", i, game->allowed_moves[i].r, game->allowed_moves[i].c);
	  }
	  while(1){
	    int ret = scanf("%d", &r);
	    if(ret < 1){
	      printf("Invalid input. Try again.\n");
	      continue;
	    }
	    if(r>=game->allowed_movec){
	      printf("Invalid choice. Try again.\n");
	      continue;
	    }
	    break;
	  }
	} else {
	  r = best_next_state(game->current, game->allowed_moves, game->allowed_movec, depthb);
	  //r = rand() % game->allowed_movec;
	}

      }
      if(print_midgame_flag)
	printf("(makes move at (%d,%d))\n", game->allowed_moves[r].r, game->allowed_moves[r].c);
      make_move(game, r);
    } else {
      if(print_midgame_flag)
	printf("Turn skipped.\n");
      make_skip(game);
    }
    if(print_midgame_flag)
      write(1, "\n", 1);
  }
  end_game(game);

  
  if(print_midgame_flag)
    print_state(game->current);

  if(print_endgame_flag){
    
    int wp = count_pieces(game->current, W);
    int bp = count_pieces(game->current, B);
    switch(game_result(game)){
    case W:
      printf("White wins: %d - %d\n", wp, bp);
      break;
    case B:
      printf("Black wins: %d - %d\n", wp, bp);
      break;
    case X:
      printf("Draw: %d - %d\n", wp, bp);
      break;
    }
  }
  free_game(game);

  return 0;
}

int test_board(void){
  Board board = create_board();

  int naive_board[BOARD_SIZE][BOARD_SIZE];
  int i, j;
  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      naive_board[i][j] = rand() % 3;
    }
  }
  
  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      if(board_get_pos(board, (Pos) {i,j}) != X)
	return -1;
      if(board_set_pos(board, (Pos) {i,j}, naive_board[i][j]))
	return -1;
    }
  }

  int ret1;
  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      if((ret1 = board_get_pos(board, (Pos) {i,j})) < 0)
	 return -1;
      if(ret1 != naive_board[i][j])
	return -1;
    }
  }



  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      if(adj_sided_pos(board, (Pos) {i,j}, NULL, B) == -1)
	return -1;
    }
  }
  
  //print_board(board);
  free_board(board);
  return 0;
}

int test_state(void){

  State state = create_state();
  init_state(state);

  free_state(state);

  return 0;
}
