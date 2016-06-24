#include "genconf.h"
#include "const.h"
#include "io.h"

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
  unsigned long int mask = 1;
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

static Config global_boards;
static Config global_variations;
static int *global_matches;
static int global_n_b;

static void *match_variations_thread_symmetrize(void *i){
  int begin = ((int *)i)[0];
  int end = ((int *)i)[1];
  int v; int b;
  for(v=begin;v<end;v++){
    Config config = &global_variations[v];
    int match = 0;
    for(b=0;b<global_n_b;b++){
      Config board = &global_boards[b];
      match += symmetric_match_one_conf_inline(*board, *config);
    }
    global_matches[v] = match;
  }
  return 0;
}

static void *match_variations_thread(void *i){
  int begin = ((int *)i)[0];
  int end = ((int *)i)[1];
  int v; int b;
  for(v=begin;v<end;v++){
    Config config = &global_variations[v];
    int match = 0;
    for(b=0;b<global_n_b;b++){
      Config board = &global_boards[b];
      if(match_one_conf_inline(*board, *config)){
	match += 1;//match_one_conf_inline(*board, *config);
      }
    }
    global_matches[v] = match;
  }
  return 0;
}


int *match_variations(Config variations, Config boards, int n_v, int n_b, int symmetrize){
  assert(variations != NULL);
  assert(boards != NULL);
  assert(n_v >= 0);
  assert(n_b >= 0);
  
  unsigned int hash_variations =
    hash_mem((char *)variations, n_v * sizeof(Config_store));

  unsigned int hash_boards =
    hash_mem((char *)boards, n_b * sizeof(Config_store));
  
  char filename[200];
  sprintf(filename, "./dat/match_variations/%x_%x_%x.dat", hash_variations, hash_boards, symmetrize);

  if(access(filename, F_OK | R_OK) == 0){
    printf("saved data exists, reading from file %s ...\n", filename);
    int *matches = read_dat_from_file(filename, sizeof(int), &n_v);
    return matches;
  }

  
  int *matches = malloc(n_v * sizeof(int));
  memset(matches, 0, n_v * sizeof(int));

  pthread_t tids[4];
  global_boards = boards;
  global_variations = variations;
  global_matches = matches;
  global_n_b = n_b;

  int bounds[5];
  int i; int interval = n_v/4;
  for(i=0;i<4;i++){
    bounds[i] = interval * i;
  }
  bounds[4] = n_v;
  
  for(i=0;i<4;i++){
    if(symmetrize){
      pthread_create(&(tids[i]), NULL, match_variations_thread_symmetrize, &bounds[i]);
    } else {
      pthread_create(&(tids[i]), NULL, match_variations_thread, &bounds[i]);
    }
  }
  for(i=0;i<4;i++){
      pthread_join(tids[i], NULL);
  }

  save_dat_to_file(filename, matches, n_v * sizeof(int));
  
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


Config filter_variations(Config variations, int *matches, int n_v, int n_b, int *k, double threshold){
  assert(variations != NULL);
  assert(matches != NULL);
  assert(k != NULL);
  assert(n_v >= 0);
  assert(n_b >= 0);

  int allocated = 10;
  Config result = malloc(allocated * sizeof(Config_store));

  int count = 0;
  int v;
  for(v=0;v<n_v;v++){
    double freq = (double)matches[v] / (double)n_b;
    if(freq > threshold){
      if(allocated == count){
	allocated += 10;
	result = realloc(result, allocated * sizeof(Config_store));
      }
      result[count++] = variations[v];
    }
  }
  result = realloc(result, count * sizeof(Config_store));
  *k = count;
  return result;
}

Config_store config_join(Config_store config_1, Config_store config_2){
  Config_store sum = config_1;
  sum.x |= config_2.x;
  sum.w |= config_2.w;
  sum.b |= config_2.b;

  return sum;
}

Config cross_match(Config variations_1, Config variations_2, int n_v1, int n_v2, int *total){
  assert(variations_1 != NULL);
  assert(variations_2 != NULL);
  assert(n_v1 >= 0);
  assert(n_v2 >= 0);
  assert(total != NULL);

  int allocated = 100;
  Config result = malloc(allocated * sizeof(Config_store));
  
  int v1, v2; int count = 0;
  for(v1=0;v1<n_v1;v1++){
    for(v2=0;v2<n_v2;v2++){
      Config var1 = &variations_1[v1];
      Config var2 = &variations_2[v2];

      if(match_pair_conf(*var1, *var2)){
	if(allocated == count){
	  allocated += 100;
	  result = realloc(result, allocated * sizeof(Config_store));
	}
	result[count++] = config_join(*var1, *var2);
      }
      
    }
  }
  *total = count;
  result = realloc(result, count * sizeof(Config_store));
  return result;
}

int match_pair_conf(Config_store config_1, Config_store config_2){
  unsigned long int xw = config_1.x & config_2.w;
  unsigned long int xb = config_1.x & config_2.b;
  unsigned long int wx = config_1.w & config_2.x;
  unsigned long int wb = config_1.w & config_2.b;
  unsigned long int bx = config_1.b & config_2.x;
  unsigned long int bw = config_1.b & config_2.w;
  if(xw | xb | wx | wb | bx | bw)
    return 0;
  return 1;
}


GeneratedConf genconf_for_patterns(Pattern *patterns, Config boards, int n_p, int n_b, double threshold, int symmetrize){
  assert(patterns != NULL);
  assert(threshold >= 0);
  
  Pattern empty = 0;
  
  int n_v;
  Config variations = list_variations(empty, &n_v);


  int i;
  for(i=0;i<n_p;i++){
    // compute variations

    int new_n_v;
    Config new_variations = list_variations(patterns[i], &new_n_v);

    // find matches and filter new variations
    int *new_matches =
      match_variations(new_variations, boards, new_n_v, n_b, symmetrize);
    int filtered_num;  
    Config filtered =
      filter_variations(new_variations, new_matches,
			new_n_v, n_b, &filtered_num, threshold);

    // cross-matching known variations with variations of the new known pattern
    int cross_num;
    Config cross =
      cross_match(variations, filtered, n_v, filtered_num, &cross_num);

    // match the joined variations
    int *joined_matches =
      match_variations(cross, boards, cross_num, n_b, symmetrize);
    int joined_filtered_num; 
    Config joined_filtered =
      filter_variations(cross, joined_matches,
			cross_num, n_b,
			&joined_filtered_num, threshold);


    // free redundant info
    free(new_variations); 
    free(new_matches);
    free(filtered);
    free(cross);
    free(variations);
    n_v = joined_filtered_num;
    variations = joined_filtered;

    printf("phase %d finished\ncurrent number of variations: %d\n\n", i, n_v);
    
  }
  
  int *matches = match_variations(variations, boards, n_v, n_b, symmetrize);  

  GeneratedConf gc;
  gc.n = n_v;
  gc.variations = variations;
  gc.matches = matches;

  return gc;
  
}

const int pow3[20] = {
  1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049,
  177147, 531441, 1594323, 4782969
};

const unsigned long int row_0_squares[8] = {
  ATOM(0,0), ATOM(0,1), ATOM(0,2), ATOM(0,3), 
  ATOM(0,4), ATOM(0,5), ATOM(0,6), ATOM(0,7)
};

unsigned long int index_for_config(Pattern pattern, Config_store config){

  if(pattern == ROW(0)){
    unsigned long int index = 0;
    int i;
    for(i=0;i<8;i++){
      if(config.w & row_0_squares[i]){
	index += pow3[i];
      } else if(config.b & row_0_squares[i]){
	index += 2 * pow3[i];
      }
    }
    return index;
  }

  unsigned long int mask;
  unsigned long int result = 0;
  for(mask = 1; mask != 0; mask <<= 1){
    if(mask & pattern){
      result *= 3;
      if(config.x & mask){
	result += 0;
      } else if(config.w & mask){
	result += 1;
      } else {
	result += 2;
      }
    }
  }
  return result;
}

int ipow(int base, int exp){
  int result = 1;
  while(exp){
    if (exp & 1)
      result *= base;
    exp >>= 1;
    base *= base;
  }
  
  return result;
}

int *match_std_variation_list(Pattern pattern, Config boards, int n_b){
  int s = __builtin_popcountl(pattern);
  int n_v = ipow(3,s);
  int *matches = malloc(n_v * sizeof(int));
  memset(matches, 0, n_v * sizeof(int));
  
  int b;
  for(b=0;b<n_b;b++){
    matches[index_for_config(pattern, boards[b])]++;
  }
  
  return matches;
}


FlatConfTable genconf_single_pattern(Pattern pattern, Config boards, int n_b, int threshold){
  FlatConfTable fct;
  
  int n_v;
  Config variations = list_variations(pattern, &n_v);
  int *matches = match_std_variation_list(pattern, boards, n_b);

  fct.n = n_v;
  fct.pattern = pattern;
  fct.variations = variations;
  fct.matches = matches;
  fct.valid = malloc(n_v * sizeof(char));
  memset(fct.valid, 0, n_v * sizeof(char));
  int i;
  for(i=0;i<n_v;i++){
    if(matches[i] > threshold){
      fct.valid[i] = 1;
    }
  }
  return fct;
}

int init_weights_for_fct(FlatConfTable *fct){
  assert(fct != NULL);
  fct->weights = malloc(fct->n * sizeof(double));
  memset(fct->weights, 0, fct->n * sizeof(double));
  return 0;
}

// TODO
Pattern *complete_pattern_set(Pattern *pattern, int n_p, int *n_c){
  int allocated = 10;
  Pattern *result = malloc(allocated * sizeof(Pattern));

  int count = 0;
  int p;
  for(p=0;p<n_p;p++){
    Pattern e = pattern[p];
    Pattern r = pattern_rotate_90(e);
    Pattern rr = pattern_rotate_180(e);
    Pattern rrr = pattern_rotate_270(e);

    Pattern s = pattern_reflect_diag(e);
    Pattern sr = pattern_reflect_diag(r);
    Pattern srr = pattern_reflect_diag(rr);
    Pattern srrr = pattern_reflect_diag(rrr);

    Pattern list[8] = {e, r, rr, rrr, s, sr, srr, srrr};
    int l;
    for(l=0;l<8;l++){
      int i; char is_in_result = 0;
      for(i=0;i<count;i++){
	if(list[l] == result[i]){
	  is_in_result = 1;
	  break;
	}
      }
      if(is_in_result)
	continue;

      if(allocated == count){
	allocated += 10;
	result = realloc(result, allocated * sizeof(Pattern));
      }
      result[count++] = list[l];
    }
  }
  *n_c = count;
  
  return result;
}

Pattern pattern_reflect_diag(Pattern pattern){
  Pattern result = 0;

  result |= row_diag[(pattern & ROW(7)) >> 0] << 0;
  result |= row_diag[(pattern & ROW(6)) >> 8] << 1;
  result |= row_diag[(pattern & ROW(5)) >> 16] << 2;
  result |= row_diag[(pattern & ROW(4)) >> 24] << 3;
  result |= row_diag[(pattern & ROW(3)) >> 32] << 4;
  result |= row_diag[(pattern & ROW(2)) >> 40] << 5;
  result |= row_diag[(pattern & ROW(1)) >> 48] << 6;
  result |= row_diag[(pattern & ROW(0)) >> 56] << 7;

  return result;
}

Pattern pattern_rotate_90(Pattern pattern){
  Pattern result = 0;
  int r;
  int c;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(ATOM(r,c) & pattern){
	result |= ATOM(BOARD_SIZE - 1 - c, r);
      }
    }
  }
  return result;
}

Pattern pattern_rotate_180(Pattern pattern){
  return pattern_rotate_90(pattern_rotate_90(pattern));
}

Pattern pattern_rotate_270(Pattern pattern){
  return pattern_rotate_90(pattern_rotate_90(pattern_rotate_90(pattern)));
}
