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
  //srand((long int) t.tv_usec);
  srand((long int) 100);

  init_offsets();
  init_maps();

  init_flipped_bits();
  init_diags();
  
  clear_weights();
  load_all_weights();

  Player white, black;

  get_players(&white, &black);
  
  run_game(1, 1, white, black);
  
  //free(white.param);
  //free(black.param);


  //Player black = human_player();
  //Player black = random_player();
  //Player black = mixed_player(14, heuristic_score_4, 26);
  //Player white = mixed_player(13, heuristic_score_4, 26);
  
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
  uint64_t int1, int2;

  int1 = 10;
  int2 = 100;
  
  asm (
       "movabs $0xff, %0\n"
       "lea 0x7(%0), %1\n"
       "sar $0x3, %0\n"
       "mov 0x641f40(%0, %1, 1), %0\n"
       :	
       "=r" (int1),
       "=r" (int2)
       );

  printf("int1 = %016lx, int2 = %016lx\n", int1, int2);

  printf("result = %x\n", flip_bitboard_w_assembly(1, 2));
  
  exit(0);
  */


  /*
  BitState *state = create_initial_bitstate();

  int i;
  for(i = 0; i < 10; i++){
    bitstate_fill_moves(state);
    if(state->movec == 0){
      break;
    }
    bitstate_place_piece(state, rand() % state->movec);
  }

  BitState temp1, temp2;
  bitstate_fill_moves(state);
  temp1 = *state;
  temp2 = *state;

  int r = rand() % state->movec;
  BitMask pos = state->moves[r];
  int pos_index = __builtin_clzll(pos);
  

  flip_bitboard_via_pext_b((BitBoard *)&temp1, pos_index);
  flip_bitboard_b[pos_index]((BitBoard *)&temp2);

  print_bitstate(&temp1);
  print_bitstate(&temp2);

  if(temp1.board.w == temp2.board.w && temp1.board.b == temp2.board.b){
    printf("correct\n");
  } else {
    printf("incorrect for w = %016lx, b = %016lx, pos_index = %d\n", state->board.w, state->board.b, pos_index);
  }
  
  free(state);
  
  exit(0);
  */

  /*
  BitBoard board = { 0x0040201c24040000, 0x0000500018180000 };
  BitBoard another = board;

  print_bitboard(board);
  
  int pos_index = 21;

  flip_bitboard_b[pos_index](&board);
  flip_bitboard_via_pext_b(&another, pos_index);
  
  print_bitboard(board);
  print_bitboard(another);

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
  //printf("%d\n", __builtin_clzll(0x1));
  init_flipped_bits();
  init_diags();
  
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



