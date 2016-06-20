#include "genconf.h"
#include "const.h"

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
  int i;
  /*
  for(i=0;i<n;i++){
    assert(check_board_as_config(boards[i]));
  }
  */
  assert(config != NULL);

  Config board = create_and_init_config();
  
  int count = 0;
  for(i=0;i<n;i++){
    memcpy(board, &boards[i], sizeof(Config_store));
    board->x &= config->x;
    board->w &= config->w;
    board->b &= config->b;

    if((board->x==config->x) && (board->w==config->w) && (board->b==config->b)){
      count++;
    }

  }
  free(board);
  return count;
}

int match_conf_nocreate(Config boards, Config config, int n){
  assert(boards != NULL);
  int i;
  assert(config != NULL);
  
  int count = 0;
  for(i=0;i<n;i++){
    if(((boards[i].x & config->x)==config->x) &&
       ((boards[i].w & config->w)==config->w) &&
       ((boards[i].b & config->b)==config->b)){
      count++;
    }

  }
  return count;
}

int match_one_conf(Config boards, Config config){
  assert(boards != NULL);
  assert(config != NULL);
  if(((boards->x & config->x)==config->x) &&
     ((boards->w & config->w)==config->w) &&
     ((boards->b & config->b)==config->b)){
    return 1;

  }
  return 0;
}

int symmetric_match_one_conf(Config boards, Config config){
  assert(boards != NULL);
  assert(config != NULL);

  int matches = 0;

  Config_store orig = *config;
  if(((boards->x & orig.x)==orig.x) &&
     ((boards->w & orig.w)==orig.w) &&
     ((boards->b & orig.b)==orig.b)){
    matches++;
  }
  
  Config_store reflection = reflect_diag(orig);
  if(((boards->x & reflection.x)==reflection.x) &&
     ((boards->w & reflection.w)==reflection.w) &&
     ((boards->b & reflection.b)==reflection.b)){
    matches++;
  }
  
  reflection = reflect_rdiag(orig);
  if(((boards->x & reflection.x)==reflection.x) &&
     ((boards->w & reflection.w)==reflection.w) &&
     ((boards->b & reflection.b)==reflection.b)){
    matches++;
  }
  
  reflection = reflect_bdiag(orig);
  if(((boards->x & reflection.x)==reflection.x) &&
     ((boards->w & reflection.w)==reflection.w) &&
     ((boards->b & reflection.b)==reflection.b)){
    matches++;
  }
  
  return matches;
}

Config list_variations(Pattern pattern, int *n_var){
  assert(n_var != NULL);
  int s = __builtin_popcountl(pattern);

  if(s == 0){
    Config base_variation = malloc(sizeof(Config_store));
    base_variation->x = 0;
    base_variation->w = 0;
    base_variation->b = 0;
    *n_var = 1;
    return base_variation;
  }

  long int mask = 1;
  while((mask & pattern) == 0){
    mask <<= 1;
  }

  Pattern sub_pattern = mask ^ pattern;
  int sub_n = 1;
  Config sub_variations = list_variations(sub_pattern, &sub_n);

  int N = 3 * sub_n;
  *n_var = N;
  Config variations = malloc(N * sizeof(Config_store));
  memcpy(variations, sub_variations, sub_n * sizeof(Config_store));
  memcpy(variations + sub_n, sub_variations, sub_n * sizeof(Config_store));
  memcpy(variations + 2*sub_n, sub_variations, sub_n * sizeof(Config_store));
  free(sub_variations);
  int i;
  for(i=0;i<sub_n;i++){
    variations[i].x |= mask;
  }
  for(i=0;i<sub_n;i++){
    variations[i+sub_n].w |= mask;
  }
  for(i=0;i<sub_n;i++){
    variations[i+2*sub_n].b |= mask;
  }
  
  return variations;
}

int *match_variations(Config variations, Config boards, int n_v, int n_b){
  assert(variations != NULL);
  assert(boards != NULL);
  assert(n_v >= 0);
  assert(n_b >= 0);

  int *matches = malloc(n_v * sizeof(int));
  memset(matches, 0, n_v * sizeof(int));
  int v; int b;
  for(b=0;b<n_b;b++){
    /*
    if(b % 10000 == 0)
      printf("b = %d\n", b);
    */
    for(v=0;v<n_v;v++){
      Config board = &boards[b];
      Config config = &variations[v];
      matches[v] += symmetric_match_one_conf(board, config);
    }
  }

  return matches;
}


int genconf_from_seq(State state, Pos *seq, Config boards){
  assert(state != NULL);
  assert(seq != NULL);
  assert(boards != NULL);
  
  int turn = 0;
  board_to_conf(state->board, &boards[turn]);
  Pos moves[POS_STORE_SIZE]; int movec; 
  init_state(state);
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
	  break;
	}
      }
      if(moved == 0){
	turn = 0;
	break;
      }
      turn++;
      board_to_conf(state->board, &boards[turn]);
    }
  }
  return turn;
}

Config_store reflect_diag(Config_store config){

  Config_store result;
  result.x = 0;
  result.w = 0;
  result.b = 0;

  result.x |= row_diag[(config.x & ROW(7)) >> 0] << 0;
  result.x |= row_diag[(config.x & ROW(6)) >> 8] << 1;
  result.x |= row_diag[(config.x & ROW(5)) >> 16] << 2;
  result.x |= row_diag[(config.x & ROW(4)) >> 24] << 3;
  result.x |= row_diag[(config.x & ROW(3)) >> 32] << 4;
  result.x |= row_diag[(config.x & ROW(2)) >> 40] << 5;
  result.x |= row_diag[(config.x & ROW(1)) >> 48] << 6;
  result.x |= row_diag[(config.x & ROW(0)) >> 56] << 7;

  result.w |= row_diag[(config.w & ROW(7)) >> 0] << 0;
  result.w |= row_diag[(config.w & ROW(6)) >> 8] << 1;
  result.w |= row_diag[(config.w & ROW(5)) >> 16] << 2;
  result.w |= row_diag[(config.w & ROW(4)) >> 24] << 3;
  result.w |= row_diag[(config.w & ROW(3)) >> 32] << 4;
  result.w |= row_diag[(config.w & ROW(2)) >> 40] << 5;
  result.w |= row_diag[(config.w & ROW(1)) >> 48] << 6;
  result.w |= row_diag[(config.w & ROW(0)) >> 56] << 7;

  result.b |= row_diag[(config.b & ROW(7)) >> 0] << 0;
  result.b |= row_diag[(config.b & ROW(6)) >> 8] << 1;
  result.b |= row_diag[(config.b & ROW(5)) >> 16] << 2;
  result.b |= row_diag[(config.b & ROW(4)) >> 24] << 3;
  result.b |= row_diag[(config.b & ROW(3)) >> 32] << 4;
  result.b |= row_diag[(config.b & ROW(2)) >> 40] << 5;
  result.b |= row_diag[(config.b & ROW(1)) >> 48] << 6;
  result.b |= row_diag[(config.b & ROW(0)) >> 56] << 7;

  /*
  int r,c;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(ATOM(r,c) & config.x){
	result.x |= ATOM(c,r);
      } else if(ATOM(r,c) & config.b){
	result.b |= ATOM(c,r);
      } else if(ATOM(r,c) & config.w){
	result.w |= ATOM(c,r);
      }
    }
  }
  */
  
  return result;
}

Config_store reflect_rdiag(Config_store config){
  
  Config_store result;
  result.x = 0;
  result.w = 0;
  result.b = 0;

  result.x |= row_rdiag[(config.x & ROW(7)) >> 0] >> 0;
  result.x |= row_rdiag[(config.x & ROW(6)) >> 8] >> 1;
  result.x |= row_rdiag[(config.x & ROW(5)) >> 16] >> 2;
  result.x |= row_rdiag[(config.x & ROW(4)) >> 24] >> 3;
  result.x |= row_rdiag[(config.x & ROW(3)) >> 32] >> 4;
  result.x |= row_rdiag[(config.x & ROW(2)) >> 40] >> 5;
  result.x |= row_rdiag[(config.x & ROW(1)) >> 48] >> 6;
  result.x |= row_rdiag[(config.x & ROW(0)) >> 56] >> 7;

  result.w |= row_rdiag[(config.w & ROW(7)) >> 0] >> 0;
  result.w |= row_rdiag[(config.w & ROW(6)) >> 8] >> 1;
  result.w |= row_rdiag[(config.w & ROW(5)) >> 16] >> 2;
  result.w |= row_rdiag[(config.w & ROW(4)) >> 24] >> 3;
  result.w |= row_rdiag[(config.w & ROW(3)) >> 32] >> 4;
  result.w |= row_rdiag[(config.w & ROW(2)) >> 40] >> 5;
  result.w |= row_rdiag[(config.w & ROW(1)) >> 48] >> 6;
  result.w |= row_rdiag[(config.w & ROW(0)) >> 56] >> 7;

  result.b |= row_rdiag[(config.b & ROW(7)) >> 0] >> 0;
  result.b |= row_rdiag[(config.b & ROW(6)) >> 8] >> 1;
  result.b |= row_rdiag[(config.b & ROW(5)) >> 16] >> 2;
  result.b |= row_rdiag[(config.b & ROW(4)) >> 24] >> 3;
  result.b |= row_rdiag[(config.b & ROW(3)) >> 32] >> 4;
  result.b |= row_rdiag[(config.b & ROW(2)) >> 40] >> 5;
  result.b |= row_rdiag[(config.b & ROW(1)) >> 48] >> 6;
  result.b |= row_rdiag[(config.b & ROW(0)) >> 56] >> 7;

  
  /*  
      int r,c;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(ATOM(r,c) & config.x){
	result.x |= ATOM(BOARD_SIZE-1-c, BOARD_SIZE-1-r);
      } else if(ATOM(r,c) & config.b){
	result.b |= ATOM(BOARD_SIZE-1-c, BOARD_SIZE-1-r);	
      } else if(ATOM(r,c) & config.w){
	result.w |= ATOM(BOARD_SIZE-1-c, BOARD_SIZE-1-r);	
      }
    }
  }
  */
  return result;
}

Config_store reflect_bdiag(Config_store config){
 Config_store result;
  result.x = 0;
  result.w = 0;
  result.b = 0;

  result.x |= row_bdiag[(config.x & ROW(7)) >> 0] >> 0*8;
  result.x |= row_bdiag[(config.x & ROW(6)) >> 8] >> 1*8;
  result.x |= row_bdiag[(config.x & ROW(5)) >> 16] >> 2*8;
  result.x |= row_bdiag[(config.x & ROW(4)) >> 24] >> 3*8;
  result.x |= row_bdiag[(config.x & ROW(3)) >> 32] >> 4*8;
  result.x |= row_bdiag[(config.x & ROW(2)) >> 40] >> 5*8;
  result.x |= row_bdiag[(config.x & ROW(1)) >> 48] >> 6*8;
  result.x |= row_bdiag[(config.x & ROW(0)) >> 56] >> 7*8;

  result.w |= row_bdiag[(config.w & ROW(7)) >> 0] >> 0*8;
  result.w |= row_bdiag[(config.w & ROW(6)) >> 8] >> 1*8;
  result.w |= row_bdiag[(config.w & ROW(5)) >> 16] >> 2*8;
  result.w |= row_bdiag[(config.w & ROW(4)) >> 24] >> 3*8;
  result.w |= row_bdiag[(config.w & ROW(3)) >> 32] >> 4*8;
  result.w |= row_bdiag[(config.w & ROW(2)) >> 40] >> 5*8;
  result.w |= row_bdiag[(config.w & ROW(1)) >> 48] >> 6*8;
  result.w |= row_bdiag[(config.w & ROW(0)) >> 56] >> 7*8;

  result.b |= row_bdiag[(config.b & ROW(7)) >> 0] >> 0*8;
  result.b |= row_bdiag[(config.b & ROW(6)) >> 8] >> 1*8;
  result.b |= row_bdiag[(config.b & ROW(5)) >> 16] >> 2*8;
  result.b |= row_bdiag[(config.b & ROW(4)) >> 24] >> 3*8;
  result.b |= row_bdiag[(config.b & ROW(3)) >> 32] >> 4*8;
  result.b |= row_bdiag[(config.b & ROW(2)) >> 40] >> 5*8;
  result.b |= row_bdiag[(config.b & ROW(1)) >> 48] >> 6*8;
  result.b |= row_bdiag[(config.b & ROW(0)) >> 56] >> 7*8;

  return result;
  
}

/*
00 00000000
00 00000000
00 00000000
00 00000000
28 00101000
65 01100101
82 10000010
b8 10111000

diag

00000011
00000100
00001101
00000001
00001001
00000100
00000010
00000100

rdiag_diag

00011101 1d
01000001 41
10100110 a6
00010100 14
00000000
00000000
00000000
00000000
*/
