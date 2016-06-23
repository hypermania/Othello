#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <fcntl.h>
#include "state.h"
#include "io.h"
#include "genconf.h"
#include "game.h"
#include "fit_weight.h"
#include "test.h"

#define BUFF_SIZE 256


Weight *global_weights;

int process_games_into_examples(Example *examples);

int main(int argc, char **argv){
  // set up random number generator
  struct timeval t;
  gettimeofday(&t, NULL);
  //srand((long int) t.tv_usec);
  srand((long int) 100);

  // temporary variable
  int i, j;
  
  /*    
  int *matches = match_variations(variations, boards, n_v, n_b);

  save_dat_to_file("./genconf_dat/corner_variation_matches.dat", matches, n_v * sizeof(int));
  */

  /*
  int n_v; int n_b;
  Config variations = list_variations(ROW(0) , &n_v);
  Config boards = read_configs_from_file("./genconf_dat/boards.dat", &n_b);

  int *matches = match_variations(variations, boards, n_v, n_b, 0);

  for(i=0;i<25;i++){
      print_config(&variations[i]);
      printf("matches = %d\n", matches[i]);
  }
  
  free(matches);
  */

  //Pattern pattern = ATOM(0,0) | ATOM(0,1) | ATOM(0,2) | ATOM(0,3);
  Pattern pattern = ROW(0) | ROW(1) | ATOM(2,0);
  
  Config_store config;
  config.w = pattern;
  config.b = 0;
  config.x = 0;

  print_config(&config);
  
  int n_v; int n_b;
  int s = __builtin_popcountl(pattern);
  n_v = ipow(3,s);
  Config boards = read_configs_from_file("./dat/boards/boards.dat", &n_b);
  //Config variations = list_variations(pattern, &n_v);
  printf("n_v = %d\n", n_v);

  int *matches = match_std_variation_list(pattern, boards, n_b);

  save_dat_to_file("./dat/test_fast_match_var.dat", matches, n_v * sizeof(int));
  //int *matches_old = match_variations(variations, boards, n_v, n_b, 0);
  
  free(matches);
  /*
  Config_store config;
  for(i=0;i<n_b;i++){
    config = boards[i];
    
    unsigned long int index = index_for_config(pattern, config);
    int valid = match_one_conf_inline(config, variations[index]);
    if(!valid){
      printf("incorrect for:\n");
      printf("i = %ld\n", i);
      printf("index = %ld\n", index);
      print_config(&config);
      print_config(&variations[index]);
    }
  }

  printf("valid\n");
  */
  //printf("correct = %d\n", memcmp(&config, &variations[index], sizeof(Config_store)) == 0);

  
  /*
  int n_b;
  Config boards = read_configs_from_file("./dat/boards/cat_14.dat", &n_b);

  Pattern patterns[64];

  for(i=0;i<BOARD_SIZE_SQR;i++){
    patterns[i] = ((unsigned long int)1) << i;
  }
  */
  //Pattern patterns[64] = {ATOM(0,0), ATOM(0,1), ATOM(0,2), ATOM(0,3), ATOM(0,4)};
  /*
  Pattern patterns[64] = {
    ATOM(0,0), ATOM(0,1), ATOM(0,2), ATOM(0,3),
    ATOM(0,4), ATOM(0,5), ATOM(0,6), ATOM(0,7),
    ATOM(1,0), ATOM(2,0), ATOM(3,0), ATOM(4,0),
    ATOM(5,0), ATOM(6,0), ATOM(7,0), ATOM(7,1),
    ATOM(7,2), ATOM(7,3), ATOM(7,4), ATOM(7,5),
    ATOM(7,6), ATOM(7,7), ATOM(6,7), ATOM(5,7),
    ATOM(4,7), ATOM(3,7), ATOM(2,7), ATOM(1,7),
    ATOM(1,1), ATOM(1,6), ATOM(6,6), ATOM(6,1)
  };
  GeneratedConf gc = genconf_for_patterns(patterns, boards, 32, n_b, 0.000001, 0);

  printf("gc.n = %d\n", gc.n);

  if(true){
  for(i=0;i<200;i++){
    int r = rand() % gc.n;
    print_config(&gc.variations[r]);
    printf("matches = %d, freq = %12.10lf\n", gc.matches[r], (double)gc.matches[r]/n_b);
  }
  }
  */
  
  /*
  int n_v1, n_v2;
  Config variations_1 =
    list_variations(
		    ATOM(0,0),  ATOM(1,0) //| ATOM(1,1) | ATOM(1,2) |
		    //ATOM(2,0) | ATOM(2,1) | ATOM(2,2)
		    , &n_v1);
  Config variations_2 =
    list_variations(
		    ROW(0)
		    , &n_v2);

  */
  
  //int *matches_1 = match_variations(variations_1, boards, n_v1, n_b, 1);
  //printf("match 1 complete\n");
  //int *matches_2 = match_variations(variations_2, boards, n_v2, n_b, 1);
  //printf("match 2 complete\n");
  
  /*
  int *matches_1 = read_dat_from_file("./genconf_dat/corner_variation_matches.dat", sizeof(int), &n_v1);

  int *matches_2 = read_dat_from_file("./genconf_dat/edge_variation_matches.dat", sizeof(int), &n_v2);

  const double threshold = 0.0027; // 3 sigmas
  int count_filtered_1, count_filtered_2;
  Config filtered_1 = filter_variations(variations_1, matches_1, n_v1, n_b, &count_filtered_1, threshold);
  Config filtered_2 = filter_variations(variations_2, matches_2, n_v2, n_b, &count_filtered_2, threshold);
  printf("count_filtered_1 = %d\n", count_filtered_1);
  printf("count_filtered_2 = %d\n", count_filtered_2);
  
  int total;
  Config crossover =
    cross_match(filtered_1, filtered_2,
		count_filtered_1, count_filtered_2,
		&total);
  
  printf("n_v1 = %d\n", n_v1);
  printf("n_v2 = %d\n", n_v2);
  printf("total = %d\n", total);

  n_v = total; int count;


  
  //int *matches = match_variations(crossover, boards, n_v, n_b);
  int *matches = read_dat_from_file("./genconf_dat/corner_row_variation_matches_0.0027.dat", sizeof(int), &n_v);
  
  //save_dat_to_file("./genconf_dat/corner_row_variation_matches_0.0027.dat", matches, n_v * sizeof(int));
  
  Config filtered = filter_variations(crossover, matches, n_v, n_b, &count, threshold);
  
  printf("count = %d\n", count);
  */
  
  // read examples from file

  //int count_examples;
  //Example *examples = read_examples_from_file("./dat/examples/randomized_examples.dat", &count_examples);
  /*
  for(i=0;i<CAT_NUM;i++){
    //i = 14;
    char filename[100];
    sprintf(filename, "./dat/examples/cat_%02d.dat", i);
    Example *examples = read_examples_from_file(filename, &count_examples);
    
    int N = count_examples;
    
    filtered = list_variations(ATOM(0,0), &count);
    Weight weight = init_weight_from_configs(filtered, count);
    grad_descent(&weight, examples, N, 0.0003, 1, true);
    
    for(j=0;j<weight.n;j++){
      printf("weight.w[%d]=%30.20lf\n", j, weight.w[j]);
    }
    
    printf("total error = %30.20lf\n\n\n", total_error(weight, examples, N));

    //sprintf(filename, "./weight_dat/weight_%02d.dat", i);
    //save_dat_to_file(filename, weight.w, weight.n * sizeof(double));
    free(examples);

    }
  */
  
    /*  
  int count = 0;
  for(i=0;i<20;i++){
    if(true){
      print_config(&filtered[i]);
      //printf("freqs[%d] = %12.10lf\n", i, freqs[i]);
      //printf("matches[%d] = %d\n", i, matches[i]);
    }
    count++;
    if(count < 0)
      break;
  }
  */

  
  /*
  double *freqs = malloc(n_v * sizeof(double));
  for(i=0;i<k;i++){
    freqs[i] = (double)matches[i]/n_b;
  }
  */

  /*
  int n_v1, n_v2;
  Config variations_1 =
    list_variations(
		    ATOM(0,0) | ATOM(0,1), &n_v1);
  Config variations_2 =
    list_variations(
		    ATOM(0,0) | ATOM(0,1) | ATOM(0,2), &n_v2);
  */

  
  /*
  // categorizing examples by number of pieces
  Example *categories[CAT_NUM];
  int cat_sizes[CAT_NUM];
  sort_examples_into_categories(examples, categories, cat_sizes, count_examples);

  // free original examples
  free(examples);

  // write categorized examples to file
  for(i=0;i<CAT_NUM;i++){
    char filename[100];
    sprintf(filename, "./dat/examples/cat_%02d.dat", i);
    int fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    printf("writing to file: cat_sizes[%d] = %d\n", i, cat_sizes[i]);
    write(fd, categories[i], cat_sizes[i] * sizeof(Example));
    close(fd);
  }
  */

  // read categorized examples from file
  /*
  Example *categories[CAT_NUM];
  int cat_sizes[CAT_NUM];

  for(i=0;i<CAT_NUM;i++){
    char filename[100];
    sprintf(filename, "./dat/examples/cat_%02d.dat", i);
    categories[i] = read_examples_from_file(filename, &cat_sizes[i]);
  }
  
  // weight fitting
  int cat = 8;
  Example *examples = categories[cat]; int N = cat_sizes[cat];

  grad_descent(&weight, examples, N, 0.00001, 0.00001, true);

  for(i=0;i<weight.n;i++){
    printf("weight.w[%d]=%30.20lf\n", i, weight.w[i]);
  }

  printf("total error = %30.20lf\n", total_error(weight, examples, N));
  
  for(i=0;i<CAT_NUM;i++){
    free(categories[i]);
  }

  free(weight.c);
  free(weight.w);
  */
  
  // run tests

  //printf("test_board = %d\n", test_board());
  //printf("test_state = %d\n", test_state());
  //printf("test_table = %d\n", test_table());
  //printf("test_genconf = %d\n", test_genconf());

  /*
  EvalFunc weights;
  for(i=0;i<CAT_NUM;i++){
    char filename[100];
    sprintf(filename, "./weight_dat/weight_%02d.dat", i);
    weights[i].n = count;
    weights[i].c = filtered;
    weights[i].w = read_dat_from_file(filename, sizeof(double), &count);
  }
  global_weights = weights;

  
  // run the game
  run_game(1,1,1,6,10);
  */
  
  exit(0);  
}



int process_games_into_examples(Example *examples){

  FILE *fp;
  fp = fopen("./game_base/all_games.txt", "r");
  // temporary storage
  State state = create_state();
  char buff[BUFF_SIZE];
  memset(buff, 0, BUFF_SIZE);

  // examples to be loaded
  Example *current = examples;
  int count_games = 0; int count_examples = 0;
  while(!feof(fp)){

    fgets(buff, BUFF_SIZE, fp);
    
    Pos *seq = randomized_file_to_seq(buff, BUFF_SIZE);

    int turns = example_from_seq(state, seq, current);
    if(turns > 0){
      current += turns; 
      count_examples += turns;
      count_games++;
    }
    
    if(count_games % 5000 == 0){
      printf("count_games = %d\n", count_games);
    }
    
    break;
  }

  printf("count_games = %d\n", count_games);
  printf("count_examples = %d\n", count_examples);
  printf("example size = %ld\n",  sizeof(Example));
  
  int fd = open("examples.dat", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  write(fd, examples, count_examples * sizeof(Example));
  close(fd);
  
  fclose(fp);
  
  return count_examples;
}

