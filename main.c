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
#include "game.h"
#include "fit_weight.h"
#include "test.h"
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
  //srand((long int) t.tv_usec);
  srand((long int) 100);

  init_offsets();
  init_maps();

  init_flipped_bits();
  init_diags();
  
  clear_weights();
  load_all_weights();


  Player white, black;
  
  //black = human_player();
  //white = random_player();
  black = mixed_player(10, heuristic_score_4, 22);
  white = mixed_player(10, heuristic_score_4, 22);

  //get_players(&white, &black);
  
  run_game(1, 1, white, black);
  
  //free(white.param);
  //free(black.param);
  exit(0);


  /*
  memset(row_1[14], 0, sizeof(row_1[14]));
  memset(row_2[14], 0, sizeof(row_2[14]));
  memset(row_3[14], 0, sizeof(row_3[14]));
  memset(row_4[14], 0, sizeof(row_4[14]));

  memset(diag_8[14], 0, sizeof(diag_8[14]));
  memset(diag_7[14], 0, sizeof(diag_7[14]));
  memset(diag_6[14], 0, sizeof(diag_6[14]));
  memset(diag_5[14], 0, sizeof(diag_5[14]));
  memset(diag_4[14], 0, sizeof(diag_4[14]));

  memset(corner_33[14], 0, sizeof(corner_33[14]));
  memset(corner_25[14], 0, sizeof(corner_25[14]));

  memset(edge_xx[14], 0, sizeof(edge_xx[14]));
  */

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

  exit(0);
  int working_cat = 12;
  
  grad_descent(cats[working_cat], cat_sizes[working_cat], working_cat, 0.0002, 0.00000001, 25);
  
  printf("error for cat %d: %lf\n", working_cat, total_error(cats[working_cat], cat_sizes[working_cat]));
  
  //save_all_weights();



		  
  /*
  uint64_t int1, int2;

  int1 = 10;
  int2 = 100;

  asm (
       "movabs $0xff, %0\n"
       "lea 0x7(%0), %1\n"
       "sar $0x3, %0\n"
       "mov 0x641f40(%0, %1, 1), %0\n"
       "movq $100, %mm0\n"
       :	
       "=r" (int1),
       "=r" (int2)
       );
  */
  /*
  asm (
       "movq $100, %rax\n"
       "movq %rax, %mm0\n"
       "movq %mm0, %rdx\n"
       );
  
  printf("int1 = %016lx, int2 = %016lx\n", int1, int2);

  
  exit(0);
  */



  /*
  long int times = 100000000;
  long int freq = 1300000000;

  struct timeval start, end;
  BitBoard board;
  
  gettimeofday(&start, NULL);
  long int i;
  for(i = 0; i < times; i++){
    //flip_bitboard_w_assembly(0, 0);
    //flip_bitboard_via_pext_w(&board, 0);
    flip_bitboard_via_pext_w_00(&board, 0);
  }
  gettimeofday(&end, NULL);

  double elapsed = (double)((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))/(double)1000000;
  double cycles = (double)freq * elapsed/(double)times;

  printf("cycles = %lf\n", cycles);

  exit(0);
  */


  /*
  char log_filename[120];
  sprintf(log_filename, "./log/%ld.csv", t.tv_sec);
  log_file = fopen(log_filename, "my");
  */
  
  

  //fclose(log_file);

  
  exit(0);  
}



