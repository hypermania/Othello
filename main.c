#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "board.h"
#include "io.h"
#include "game.h"
#include "ai.h"

int main(int argc, char **argv){

  struct timeval t;
  gettimeofday(&t, NULL);
  srand((long int) t.tv_usec);
  //srand((long int) 102);

  Game game = create_game();
  init_game(game);

  int print_midgame_flag = 0;
  int human_player_flag = 0;
  
  while(is_end_of_game(game) == 0){
    if(print_midgame_flag){
      printf("Turn %d\n", game->turns);
      print_state(game->current);
    }

    if(require_input(game) == 1){
      int r;
      if(game->status == B)
	r = best_next_state(game->current, game->allowed_moves, game->allowed_movec, 2);
      if(game->status == W){

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
	  //r = best_next_state(game->current, game->allowed_moves, game->allowed_movec, 0);
	  r = rand() % game->allowed_movec;
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


  free_game(game);
  
  /*
  State state = create_state();
  init_state(state);
  Pos store[10];
  int x = adj_sided_pos(state->board, (Pos) {2,4}, store, B);
  printf("x = %d\n",x);
  free_state(state);
  */
  
  exit(0);  
  

}
