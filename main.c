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

  /*
  void *test = 0x20;
  printf("%lx\n", test + sizeof(int8_t *));
  int8_t *test2 = 0x10;
  printf("%lx\n", (int)((int8_t *)test - test2));
  exit(0);
  */
  
  //printf("elem_size = %d\n", sizeof(((TableValue *)NULL)->flag));

  Player white, black;
  //black = human_player();
  //black = random_player();
  //white = random_player();
  black = mixed_player(12, heuristic_score_4, 21);
  white = mixed_player(12, heuristic_score_4, 21);

  //get_players(&white, &black);
  
  run_game(1, 1, white, black);
  
  //free(white.param);
  //free(black.param);
  exit(0);


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

  int working_cat = 5;
  
  grad_descent(cats[working_cat], cat_sizes[working_cat], working_cat, 10, 0.000000001, 25);
  
  printf("error for cat %d: %lf\n", working_cat, total_error(cats[working_cat], cat_sizes[working_cat]));
  
  //save_all_weights();

  exit(0);
  */
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


  BitState *state = create_initial_bitstate();
  int l;
  for(l = 0; l < 1000000; l++) {
    //srand((long int) 100);
    if(l % 1000 == 0)
      printf("%d done\n", l);
    init_bitstate(state);
    int k;
    for(k = 0; k < 42; k++) {
      int movec;
      BitMask *moves = bitstate_allowed_moves_array(state, &movec);
      if(movec == 0) {
	bitstate_skip_turn(state);
      } else {
	bitstate_place_piece(state, moves[rand() % movec]);
      }
      free(moves);
    }

    int empty_sqr = BOARD_SIZE_SQR -
      (__builtin_popcountll(state->board.b) + __builtin_popcountll(state->board.w));
    struct timeval start, end;
    gettimeofday(&start, NULL);
    count_node = 0;
    double s1 = negamax_end(state, -DBL_MAX, DBL_MAX, NULL, empty_sqr);
    gettimeofday(&end, NULL);
    double elapsed = (double)((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))/(double)1000000;

    printf("s1 complete, elapsed = %lf, count_node = %ld\n", elapsed, count_node);
    double s2 = (double)negamax_end_iterative(state, -65, 65, NULL);

    if(s1 != s2) {
      printf("(error)s1 = %lf, s2 = %lf\n", s1, s2);
      printf("%016lx, %016lx\n", state->board.w, state->board.b);
      printf("depth = %d\n", empty_sqr);
      print_bitstate(state);
      break;
    } else {
      printf("(passed) depth = %d\n", empty_sqr);
    }
    printf("\n");
  }

  exit(0);
  

  /*
  Table *table = table_create(20);

  long int times = 200000000;
  long int freq = 1300000000;

  struct timeval start, end;
  //BitBoard board = new_initial_bitboard();
  BitState *state = create_initial_bitstate();

  TableValue value;
  
  gettimeofday(&start, NULL);
  long int i;
  for(i = 0; i < times; i++){
    //flip_bitboard_w_assembly(0, 0);
    //flip_bitboard_via_pext_w(&board, 0);
    //evaluate_use_avx((BitState *)&board);
    //evaluate(state);
    evaluate(state);
    
    state->board.w = rand() | (uint64_t)rand() << 32;
    state->board.b = (rand() | (uint64_t)rand() << 32) & (~state->board.w);

    //table_write(table, state, value);
    //table_read(table, state);
    //hash_bitstate(state);

    //BitMask mask1, mask2;
    //mask1 = find_moves_bitmask(board, W);
    //mask2 = find_moves_bitmask_avx(board, W);
    //temp1 = (BitBoard) {flipHorizontal(board.w), flipHorizontal(board.b)};
    //temp2 = flipHorizontal_sse(board);

    //temp = (BitBoard) {flipDiagA1H8(board.w), flipDiagA1H8(board.b)};
    //temp = flipDiagA1H8_sse(board);
  }
  gettimeofday(&end, NULL);

  double elapsed = (double)((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))/(double)1000000;
  double cycles = (double)freq * elapsed/(double)times;

  printf("cycles = %lf\n", cycles);
  
  print_bitstate(state);
  
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



