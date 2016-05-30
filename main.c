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

  Game game = create_game();
  init_game(game);

  while(is_end_of_game(game) == 0){
    printf("Turn %d\n", game->turns);
    print_state(game->current);
    
    //printf("%d pieces on board\n", count_pieces(game->current, W) + count_pieces(game->current, B));
    if(require_input(game) == 1){
      int r;
      if(game->status == W)
	//r = rand() % game->allowed_movec;
	r = best_next_state(game->current, game->allowed_moves, game->allowed_movec);
      if(game->status == B){
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
      }
      printf("(makes move at (%d,%d))\n", game->allowed_moves[r].r, game->allowed_moves[r].c);
      make_move(game, r);
    } else {
      make_skip(game);
      printf("Turn skipped.\n");
    }
    write(1, "\n", 1);
  }
  end_game(game);

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

  exit(0);  
  /*      
      // my turn!

*/

}
