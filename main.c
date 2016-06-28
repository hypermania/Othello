#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "state.h"
#include "io.h"
#include "genconf.h"
#include "game.h"
#include "fit_weight.h"
#include "test.h"

FlatConfTable **global_fcts;

int process_games_into_examples(Example *examples);
void fit_fct_for_categories(void);


void fit_fct_for_categories(void){
  int i, j;
  const int pattern_set_size = 12; // max 12
  Pattern patterns[20] =
    {
      DIAG(0),
      
      ATOM(0,1)|ATOM(1,2)|ATOM(2,3)|ATOM(3,4)|ATOM(4,5)|ATOM(5,6)|ATOM(6,7),
      
      ATOM(0,2)|ATOM(1,3)|ATOM(2,4)|ATOM(3,5)|ATOM(4,6)|ATOM(5,7),
      
      ATOM(0,3)|ATOM(1,4)|ATOM(2,5)|ATOM(3,6)|ATOM(4,7),
      
      ATOM(0,4)|ATOM(1,5)|ATOM(2,6)|ATOM(3,7),
      
      ROW(0),
      
      ROW(1),
      
      ROW(2),
      
      ROW(3),

      ROW(0)|ATOM(1,1)|ATOM(1,6),
      
      ATOM(0,0)|ATOM(0,1)|ATOM(0,2)|
      ATOM(1,0)|ATOM(1,1)|ATOM(1,2)|
      ATOM(2,0)|ATOM(2,1)|ATOM(2,2),

      ATOM(0,0)|ATOM(0,1)|ATOM(0,2)|ATOM(0,3)|ATOM(0,4)|
      ATOM(1,0)|ATOM(1,1)|ATOM(1,2)|ATOM(1,3)|ATOM(1,4)  
    };


  int n_f;
  Pattern *completion = complete_pattern_set(patterns, pattern_set_size, &n_f);
  printf("n_f = %d\n", n_f);

  
  int n_b;
  Config boards = read_configs_from_file("./dat/boards/boards.dat", &n_b);

  const int threshold = 10;
  
  char filename[120];
  
  int cat;

  for(cat=0;cat<CAT_NUM;cat++){
  
  sprintf(filename, "./dat/examples/cat_%02d.dat", cat);
  int n_e;
  Example *examples = read_examples_from_file(filename, &n_e);

  int count_weights = 0; int count_valid = 0;
  FlatConfTable *fct_list = malloc(n_f * sizeof(FlatConfTable));
  for(i=0;i<n_f;i++){
    fct_list[i] = genconf_single_pattern(completion[i], boards, n_b, threshold);
    init_weights_for_fct(&fct_list[i]);
    //print_pattern(fct_list[i].pattern);
    printf("fct_list[%d].n = %d\n", i, fct_list[i].n);
    count_weights += fct_list[i].n;
    for(j=0;j<fct_list[i].n;j++){
      if(fct_list[i].valid[j]){
	count_valid++;
      }
    }
  }
  
  printf("count_weights = %d\n", count_weights);
  printf("count_valid = %d\n", count_valid);

  fit_fct_list(fct_list, examples, n_f, n_e, 0.00001, 0.001, 100);


  sprintf(filename, "./dat/fcts/raw_cat_%02d", cat);
  mkdir(filename, 0700);
  for(i=0;i<n_f;i++){
    sprintf(filename, "./dat/fcts/raw_cat_%02d/%02d", cat, i);
    mkdir(filename, 0700);
    
    sprintf(filename, "./dat/fcts/raw_cat_%02d/%02d/fct.dat", cat, i);
    save_dat_to_file(filename, &fct_list[i], sizeof(FlatConfTable));

    sprintf(filename, "./dat/fcts/raw_cat_%02d/%02d/valid.dat", cat, i);
    save_dat_to_file(filename, fct_list[i].valid, fct_list[i].n * sizeof(char));

    sprintf(filename, "./dat/fcts/raw_cat_%02d/%02d/variations.dat", cat, i);
    save_dat_to_file(filename, fct_list[i].variations, fct_list[i].n * sizeof(Config_store));

    sprintf(filename, "./dat/fcts/raw_cat_%02d/%02d/matches.dat", cat, i);
    save_dat_to_file(filename, fct_list[i].matches, fct_list[i].n * sizeof(int));

    sprintf(filename, "./dat/fcts/raw_cat_%02d/%02d/weights.dat", cat, i);
    save_dat_to_file(filename, fct_list[i].weights, fct_list[i].n * sizeof(double));
  }
  
  for(i=0;i<n_f;i++){
    free_fct_contents(fct_list[i]);
  }
  free(fct_list);
  free(examples);

  }
}

int main(int argc, char **argv){
  // set up random number generator
  struct timeval t;
  gettimeofday(&t, NULL);
  //srand((long int) t.tv_usec);
  srand((long int) 100);
  

  
  //printf("test_table = %d\n", test_table());
  //printf("test_state = %d\n", test_state());
  
  
  int n_b;
  Config boards = read_configs_from_file("./dat/boards/boards.dat", &n_b);
  
  // temporary variable
  int i, j;
  int cat;  int f;
  int n_f = 50;
  FlatConfTable **fcts = malloc(CAT_NUM * sizeof(FlatConfTable *));
  for(cat=0;cat<CAT_NUM;cat++){
    fcts[cat] = malloc(n_f * sizeof(FlatConfTable));
    char filename[120];
    for(f=0;f<n_f;f++){
      sprintf(filename, "./dat/fcts/raw_cat_%02d/%02d/fct.dat", cat, f);
      FlatConfTable *fct =
	read_dat_from_file(filename, sizeof(FlatConfTable), NULL);
      fcts[cat][f] = *fct;
      
      sprintf(filename, "./dat/fcts/raw_cat_%02d/%02d/valid.dat", cat, f);
      char *valid =
	read_dat_from_file(filename, sizeof(char), NULL);
      fcts[cat][f].valid = valid;

      sprintf(filename, "./dat/fcts/raw_cat_%02d/%02d/variations.dat", cat, f);
      Config variations =
	read_dat_from_file(filename, sizeof(Config_store), NULL);
      fcts[cat][f].variations = variations;

      sprintf(filename, "./dat/fcts/raw_cat_%02d/%02d/matches.dat", cat, f);
      int *matches =
	read_dat_from_file(filename, sizeof(int), NULL);
      fcts[cat][f].matches = matches;

      sprintf(filename, "./dat/fcts/raw_cat_%02d/%02d/weights.dat", cat, f);
      double *weights =
	read_dat_from_file(filename, sizeof(double), NULL);
      fcts[cat][f].weights = weights;

      free(fct);
    }
  }

  for(cat=0;cat<CAT_NUM;cat++){
    for(f=0;f<n_f;f++){
      FlatConfTable fct = fcts[cat][f];
      for(i=0;i<fct.n;i++){
	if(fct.valid[i]){
	  if(fct.matches[i] < 5){
	    fct.weights[i] *= (double)fct.matches[i]/5;
	  }
	}
      }
    }
  }
  /*
  for(i=0;i<10000;i++){
    cat = rand() % CAT_NUM;
    f = rand() % n_f;
    FlatConfTable fct = fcts[cat][f];
    int index = rand() % fct.n;
    if(fct.valid[index] && fabs(fct.weights[index]) > 1){
      print_config(&fct.variations[index]);
      printf("cat = %d, matches = %d, weight = %20.15lf\n", cat, fct.matches[index], fct.weights[index]);
    }
  }
  */
  /*
  printf("printing examples weights for examples:\n");
  for(i=0;i<100;i++){
    Config_store board = boards[rand() % n_b];
    cat = CAT(BOARD_SIZE_SQR - __builtin_popcountl(board.x));
    double score = get_score_from_fct_list(fcts[cat], n_f, board);
    if(fabs(score) > 0.5){
      print_config(&board);    
      printf("score = %30.20lf\n", score);
    }
  }
  */
  global_fcts = fcts;

  Player white = ab_pruning_player(7);
  Player black = human_player();
  
  run_game(1, 1, white, black);
  
  for(cat=0;cat<CAT_NUM;cat++){
    for(f=0;f<n_f;f++){
      free_fct_contents(fcts[cat][f]);
    }
    free(fcts[cat]);
  }
  free(fcts);


  /*
  int *indices = malloc(n_f * sizeof(int));
  for(i=0;i<n_f;i++){
    indices[i] = i;
  }
  binarize_items(completion, indices, n_f);
  */

  
  /*
  printf("printing example weights:\n");
  for(i=0;i<10;i++){
    FlatConfTable fct = fct_list[rand() % n_f];
    int r = rand() % fct.n;
    if(fct.valid[r] && fabs(fct.weights[r]) > 0.01){
      print_config(&fct.variations[r]);
      printf("weight = %20.15lf\n", fct.weights[r]);
    }
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
  
  // categorizing examples by number of pieces
  /*
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
  */    
  
  // run tests

  //printf("test_board = %d\n", test_board());

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
  */
  
  // run the game



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

