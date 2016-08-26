#include "config.h"

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

int match_one_conf_inline(Config_store boards, Config_store config){

  if(((boards.x & config.x)==config.x) &&
     ((boards.w & config.w)==config.w) &&
     ((boards.b & config.b)==config.b)){
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

int symmetric_match_one_conf_inline(Config_store boards, Config_store config){
  int matches = 0;

  Config_store orig = config;
  if(((boards.x & orig.x)==orig.x) &&
     ((boards.w & orig.w)==orig.w) &&
     ((boards.b & orig.b)==orig.b)){
    matches++;
  }
  
  Config_store reflection = reflect_diag(orig);
  if(((boards.x & reflection.x)==reflection.x) &&
     ((boards.w & reflection.w)==reflection.w) &&
     ((boards.b & reflection.b)==reflection.b)){
    matches++;
  }
  
  reflection = reflect_rdiag(orig);
  if(((boards.x & reflection.x)==reflection.x) &&
     ((boards.w & reflection.w)==reflection.w) &&
     ((boards.b & reflection.b)==reflection.b)){
    matches++;
  }
  
  reflection = reflect_bdiag(orig);
  if(((boards.x & reflection.x)==reflection.x) &&
     ((boards.w & reflection.w)==reflection.w) &&
     ((boards.b & reflection.b)==reflection.b)){
    matches++;
  }
  
  return matches;
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
int board_to_conf(Board board, Config config){
  assert(board != NULL);
  assert(config != NULL);

  init_config(config);
  
  int r, c;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(board_get_pos(board, (Pos) {r,c}) == EMPTY){
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
*/
/*
Config_store board_to_conf_nocreate(Board board){
  assert(board != NULL);

  Config_store config;
  
  config.x = 0;
  config.w = 0;
  config.b = 0;
  
  int r, c;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(board_get_pos(board, (Pos) {r,c}) == EMPTY){
	config.x |= ATOM(r,c);
      } else if(board_get_pos(board, (Pos) {r,c}) == W){
	config.w |= ATOM(r,c);
      } else {
	config.b |= ATOM(r,c);
      }
    }
  }
  return config;
}
*/
