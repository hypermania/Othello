#include "game.h"


Game create_game(void){
  Game game = malloc(sizeof(Game_store));
  return game;
  
}

int free_game(Game game){
  if(game == NULL)
    return -1;

  int i;
  //printf("game->turns = %d\n", game->turns);
  //printf("game->stauts = %d\n", game->status);
  for(i=0;i<=game->turns;i++){
    //printf("freeing game->state_seq[%d], move_seq[%d].status = %d\n", i, i, game->move_seq[i].status);
    free_state(game->state_seq[i]);
  }
  free(game);
  return 0;
}

int init_game(Game game){
  if(game == NULL)
    return -1;

  memset(game, 0, sizeof(Game_store));
  
  State opening = create_state();
  init_state(opening);
  game->state_seq[0] = opening;
  game->current = opening;

  game->status = B;
  game->allowed_movec = allowed_moves(opening, game->allowed_moves, B);
  return 0;
}

// make a move without error checking
void unsafe_make_move(Game game, int move_num){
  game->move_seq[game->turns] = (move) {game->current->turn, game->allowed_moves[move_num]};

  State next = create_state();
  cpy_state(next, game->current);

  place_piece(next, game->allowed_moves[move_num], game->status);
  state_switch_turn(next);
  
  game->state_seq[++game->turns] = next;
  game->current = next;
  game->status = next->turn;
  
  game->allowed_movec = allowed_moves(next, game->allowed_moves, next->turn);
}
// no need to consider skipping 
int make_move(Game game, int move_num){
  if(game == NULL)
    return -1;
  if(move_num >= game->allowed_movec || move_num < 0)
    return -2;
  
  unsafe_make_move(game, move_num);
  return 0;
}

int make_skip(Game game){
  if(game == NULL)
    return -1;
  if(game->status == 3)
    return -4;

  game->move_seq[game->turns] = (move) {game->current->turn + 2, (Pos) {0,0}};
  
  State next = create_state();
  cpy_state(next, game->current);
  state_switch_turn(next);
  
  game->state_seq[++game->turns] = next;
  game->current = next;
  game->status = next->turn;
  
  game->allowed_movec = allowed_moves(next, game->allowed_moves, next->turn);
  return 0;

}

int go_back_once(Game game){
  if(game == NULL)
    return -1;
  if(game->turns == 0)
    return -2;

  free_state(game->current);
  game->turns--;
  int status = game->move_seq[game->turns].status;
  game->status = (status > 2) ? status - 2 : status;

  game->allowed_movec = allowed_moves(game->current, game->allowed_moves, game->status);
  
  return 0;
}

int require_input(Game game){
  if(game == NULL)
    return -1;
  if(game->status == 3)
    return 0;
  if(game->allowed_movec == 0)
    return 0;
  return 1;
}

// does not change state of variable game
int is_end_of_game(Game game){
  if(game == NULL)
    return -1;
  if(game->status == 3)
    return 1;
  
  int opp_side;
  if((opp_side = opposite_side(game->status)) == -1)
    return -2;
  
  if((game->allowed_movec == 0) && (allowed_moves(game->current, NULL, opp_side) == 0))
    return 1;

  return 0;
}

int end_game(Game game){
  if(game == NULL)
    return -1;

  game->status = 3;
  return 0;
}

int game_result(Game game){
  if(game == NULL)
    return -1;

  if(game->status != 3)
    return -2;

  int wp = count_pieces(game->current, W);
  int bp = count_pieces(game->current, B);
  if(wp<bp){
    return B;
  }
  if(wp==bp){
    return X;
  }
  if(wp>bp){
    return W;
  }
  return 0;
}
