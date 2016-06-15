#include "genconf.h"

Config create_and_init_config(void){
  Config config = (Config) malloc(sizeof(Config_store));
  config->x = 0;
  config->w = 0;
  config->b = 0;
  return config;
}

Config create_and_init_config_list(int length){
  assert(length >= 0);
  
  Config config = (Config) malloc(length * sizeof(Config_store));
  memset(config, 0, length * sizeof(Config_store));
  
  return config;
}

int init_config(Config config){
  assert(config != NULL);
  config->x = 0;
  config->w = 0;
  config->b = 0;
  return 0;
}

int free_config(Config config){
  assert(config != NULL);
  free(config);
  return 0;
}

int check_board_as_config(Config_store conf){
  if((conf.x ^ conf.w ^ conf.b) == 0xffffffffffffffff)
    return 1;
  return 0;
}

int board_to_conf(Board board, Config config){
  assert(board != NULL);
  assert(config != NULL);

  init_config(config);
  
  int r, c;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(board_get_pos(board, (Pos) {r,c}) == X){
	config->x |= ATOM(r,c);
      } else if(board_get_pos(board, (Pos) {r,c}) == W){
	config->w |= ATOM(r,c);
      } else {
	config->b |= ATOM(r,c);
      }
    }
  }
  return 0;
  
}

int match_conf(Config boards, Config config, int n){
  assert(boards != NULL);
  assert(config != NULL);

  Config board = create_and_init_config();
  
  int i;
  int count = 0;
  for(i=0;i<n;i++){
    memcpy(board, &boards[i], sizeof(Config_store));
    board->x &= config->x;
    board->w &= config->w;
    board->b &= config->b;

    if(board->x==config->x && board->w==config->w && board->b==config->b){
      count++;
    }

  }
  return count;
}


int genconf_from_seq(State state, Pos *seq, Config boards){
  assert(state != NULL);
  assert(seq != NULL);
  assert(boards != NULL);
  
  int turn = 0;
  board_to_conf(state->board, &boards[turn]);
  Pos moves[POS_STORE_SIZE]; int movec; 
  //init_state(state);
  while(!state_final(state)){
    movec = allowed_moves(state, moves, state->turn);
    if(movec == 0){
      state_switch_turn(state);
    } else {
      int i; int moved = 0;
      for(i=0;i<movec;i++){
	if(moves[i].r == seq[turn].r && moves[i].c == seq[turn].c){
	  place_piece(state, seq[turn], state->turn);
	  state_switch_turn(state);
	  moved = 1;
	}
      }
      if(moved == 0){
	break;
      }
      turn++;
      board_to_conf(state->board, &boards[turn]);
    }
  }
  return turn;
}

