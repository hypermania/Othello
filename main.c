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


int match_one_config(void);
int process_games_into_examples(Example *examples);

int main(int argc, char **argv){
  // set up random number generator
  struct timeval t;
  gettimeofday(&t, NULL);
  //srand((long int) t.tv_usec);
  srand((long int) 100);

  // temporary variable
  int i, j;

  
  // specifying the weight
  /*
  int i;
  const int n = 32;
  Weight weight;
  weight.n = n;
  weight.c = create_and_init_config_list(n);
  weight.w = malloc(n * sizeof(double));


  long int places[64] = {ATOM(0,0), ATOM(0,1), ATOM(1,0), ATOM(1,1),
			  ATOM(0,7), ATOM(0,6), ATOM(1,7), ATOM(1,6),
			  ATOM(7,0), ATOM(7,1), ATOM(6,0), ATOM(6,1),
			  ATOM(7,7), ATOM(7,6), ATOM(6,7), ATOM(6,6)
  };


  for(i=0;i<n/2;i++){
    weight.c[2*i].w = places[i];
    weight.c[2*i].b = 0;
    weight.c[2*i].x = 0;

    weight.w[2*i] = 0;
    
    weight.c[2*i+1].w = 0;
    weight.c[2*i+1].b = places[i];
    weight.c[2*i+1].x = 0;

    weight.w[2*i+1] = 0;
  }
  */

  // read examples from file and process them into configs
  /*
  int count_examples;
  //Example *examples = read_examples_from_file("./example_dat/randomized_examples.dat", &count_examples);
  Example *examples = read_examples_from_file("./example_dat/cat_14.dat", &count_examples);

  Config boards = malloc(count_examples * sizeof(Config_store));

  for(i=0;i<count_examples;i++){
    boards[i].x = examples[i].board.x;
    boards[i].w = examples[i].board.w;
    boards[i].b = examples[i].board.b;
  }
  */

  /*    
  int *matches = match_variations(variations, boards, n_v, n_b);

  save_dat_to_file("./genconf_dat/corner_variation_matches.dat", matches, n_v * sizeof(int));
  */

  int count_examples;
  Config boards = read_configs_from_file("./genconf_dat/boards.dat", &count_examples);

  int n_v; int n_b = count_examples;
  
  int n_v1, n_v2;
  Config variations_1 =
    list_variations(
		    ATOM(0,0) | ATOM(0,1) | ATOM(0,2) |
		    ATOM(1,0) | ATOM(1,1) | ATOM(1,2) |
		    ATOM(2,0) | ATOM(2,1) | ATOM(2,2)
		    , &n_v1);
  Config variations_2 =
    list_variations(
		    ROW(0)
		    , &n_v2);

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

  for(i=0;i<25;i++){
    print_config(&filtered[rand() % count]);
  }

  printf("count = %d\n", count);


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
    sprintf(filename, "./example_dat/cat_%02d.dat", i);
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
    sprintf(filename, "./example_dat/cat_%02d.dat", i);
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
  /*
  printf("test_board = %d\n", test_board());
  printf("test_state = %d\n", test_state());
  printf("test_table = %d\n", test_table());

  printf("test_genconf = %d\n", test_genconf());
  */

  // run the game
  //run_game(1,1,1,6,6);

  
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



int match_one_config(void){

  FILE *fp;
  fp = fopen("./game_base/all_games.txt", "r");

  fseek( fp , 0L , SEEK_END);
  long int lSize = ftell(fp);
  rewind(fp);
  
  char *buff = calloc(1, lSize+1);
  memset(buff, 0, BUFF_SIZE);

  
  // temporary storage
  State state = create_state();
  Config boards = create_and_init_config_list(100);

  // the config to be tested
  Config config = create_and_init_config();
  config->w = 0x000000000000ffff;
  config->b = 0x0000000000000000;
  config->x = 0x0000000000000000;

  // the percentage aimed for and its standard deviation (for d = 1)
  double q = 0.00001;
  double sd = sqrt(q * (1-q));

  // total match for the config
  int total_match = 0; int total_boards = 0; int total_games = 0;
  while(!feof(fp)){
    // read a line of file
    fgets(buff, BUFF_SIZE, fp);
    Pos *seq = file_to_seq(buff, BUFF_SIZE);
    
    // generate the board in config form from the read line of file
    init_state(state);
    int turns = genconf_from_seq(state, seq, boards);
    // if the generated board is valid, compare it to the config to be tested
    if(turns > 0){
      int matches = match_conf_nocreate(boards, config, turns);
      total_match += matches;
      total_boards += turns;
      total_games += 1;
    }
    if(total_games % 1 == 0){
      // normalized standard deviation
    double z = ((double)total_match)/((double)total_boards) - q;
    z /= sd/sqrt((double)total_boards);
    if(z > +8)
      break;
    if(z < -8)
      break;
    printf("total_games = %d\n", total_games);
    printf("z-score = %lf\n", z);
    printf("percentage = %lf\n\n", (double)total_match/total_boards);
    }
  }
  
  printf("total_games = %d\n", total_games);
  printf("total_boards = %d\n", total_boards);
  printf("total_match = %d\n", total_match);
  printf("percentage = %lf\n\n", (double)total_match/total_boards);
  
  free_state(state);

  return 0;

}
