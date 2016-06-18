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

  // creating examples and write to file
  /*
  Example *examples = malloc(TOTAL_GAMES * 60 * sizeof(Example));
  process_games_into_examples(examples);
  */

  const int n = 32;
  Weight weight;
  weight.n = n;
  weight.c = create_and_init_config_list(n);
  weight.w = malloc(n * sizeof(double));

  long int corners[16] = {ATOM(0,0), ATOM(0,1), ATOM(1,0), ATOM(1,1),
			  ATOM(0,7), ATOM(0,6), ATOM(1,7), ATOM(1,6),
			  ATOM(7,0), ATOM(7,1), ATOM(6,0), ATOM(6,1),
			  ATOM(7,7), ATOM(7,6), ATOM(6,7), ATOM(6,6)
  };
  
  int i;
  for(i=0;i<n/2;i++){
    weight.c[2*i].w = corners[i];
    weight.c[2*i].b = 0;
    weight.c[2*i].x = 0;

    weight.w[2*i] = 0;
    
    weight.c[2*i+1].w = 0;
    weight.c[2*i+1].b = corners[i];
    weight.c[2*i+1].x = 0;

    weight.w[2*i+1] = 0;
  }

  /*
  int count_examples;
  Example *examples = read_examples_from_file("./example_dat/randomized_examples.dat", &count_examples);

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

  fit_to_precision(&weight, examples, N, 0.0003, 0.00000001, true);

  for(i=0;i<weight.n;i++){
    printf("weight.w[%d]=%30.20lf\n", i, weight.w[i]);
  }
  
  for(i=0;i<CAT_NUM;i++){
    free(categories[i]);
  }

  free(weight.c);
  free(weight.w);

  for(i=0;i<CAT_NUM;i++){
    free(categories[i]);
  }

  
  // weight fitting
  /*
  int cat = 8;
  while(1){
    
    double *delta = fit_weight_from_examples(&weight, categories[cat], cat_sizes[cat], 0.0001);

    for(i=0;i<n;i++){
      printf("w[%d]=%30.20lf\n", i, weight.w[i]);
    }
    double delta_l1_norm = 0;
    for(i=0;i<weight.n;i++){
      delta_l1_norm += fabs(delta[i]);
    }
    printf("delta_l1_norm = %30.20lf\n", delta_l1_norm);
    if(delta_l1_norm < 0.00000001){
      free(delta);
      break;
    }
    free(delta);
    printf("\n");
    break;
  }

  for(i=0;i<CAT_NUM;i++){
    free(categories[i]);
  }

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
      int matches = match_conf(boards, config, turns);
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
