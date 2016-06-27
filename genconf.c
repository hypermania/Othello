#include "genconf.h"


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

  /*
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
  */
  
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

  //save_dat_to_file(filename, matches, n_v * sizeof(int));
  
  return matches;
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


