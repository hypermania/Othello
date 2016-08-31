#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "io.h"
#include "genconf.h"
#include "game.h"
#include "fit_weight.h"
#include "test.h"
#include "preprocess.h"
#include "util.h"

#include "flip_computation.h"

#include "bitboard.h"
#include "evaluate.h"
#include "weights.h"
#include "datpt.h"


FILE *log_file;

int main(int argc, char **argv){
  // set up random number generator
  struct timeval t;
  gettimeofday(&t, NULL);
  srand((long int) t.tv_usec);
  //srand((long int) 100);

  init_offsets();
  check_offsets();
  init_maps();
  clear_weights();
  
  load_all_weights();

  /*
  FILE *fp = fopen("./game_base/all_games.txt", "r");

  long int n_dp;
  DataPoint *datapoints = datapoints_from_file(fp, &n_dp);
  printf("n_dp = %ld\n", n_dp);

  long int cat_sizes[CAT_NUM];
  
  DataPoint **cats = categorize_datpts(datapoints, n_dp, cat_sizes);

  int i;
  for(i = 0; i < CAT_NUM; i++){
    printf("error for cat %d: %lf\n", i, total_error(cats[i], cat_sizes[i]));
  }
  */

  /*
  char log_filename[120];
  sprintf(log_filename, "./log/%ld.csv", t.tv_sec);
  log_file = fopen(log_filename, "w");
  */
  
  //Player black = human_player();
  //Player black = random_player();
  Player black; // = mixed_player(10, heuristic_score_4, 0);
  Player white; //= mixed_player(10, heuristic_score_4, 0);

  get_players(&white, &black);
  
  run_game(1, 1, white, black);

  
  //free(white.param);
  //free(black.param);

  //fclose(log_file);

  
  exit(0);  
}



