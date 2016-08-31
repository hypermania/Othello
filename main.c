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

FlatConfTable **global_fcts;
int global_n_f;

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
  
  /*
  void read_weight(const char *filename, double *weight){
    FILE *fp;
    fp = fopen(filename, "r");
    fseek(fp, 0L, SEEK_END);
    long int size = ftell(fp);
    rewind(fp);
    fread(weight, size, 1, fp);
    fclose(fp);
  }
  */

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
  int i;
  for(i = 0; i < CAT_NUM; i++){
    printf("initial error = %lf\n", total_error(cats[i], cat_sizes[i]));
    grad_descent(cats[i], cat_sizes[i], i, 0.002, 0.0005, 100);
  }


  save_dat_to_file("./weights/row_1.dat", &row_1[0][0][0], sizeof(row_1));
  save_dat_to_file("./weights/row_2.dat", &row_2[0][0][0], sizeof(row_2));
  save_dat_to_file("./weights/row_3.dat", &row_3[0][0][0], sizeof(row_3));
  save_dat_to_file("./weights/row_4.dat", &row_4[0][0][0], sizeof(row_4));

  save_dat_to_file("./weights/diag_8.dat", &diag_8[0][0][0], sizeof(diag_8));
  save_dat_to_file("./weights/diag_7.dat", &diag_7[0][0][0], sizeof(diag_7));
  save_dat_to_file("./weights/diag_6.dat", &diag_6[0][0][0], sizeof(diag_6));
  save_dat_to_file("./weights/diag_5.dat", &diag_5[0][0][0], sizeof(diag_5));
  save_dat_to_file("./weights/diag_4.dat", &diag_4[0][0][0], sizeof(diag_4));

  save_dat_to_file("./weights/corner_33.dat", &corner_33[0][0], sizeof(corner_33));
  save_dat_to_file("./weights/corner_25.dat", &corner_25[0][0], sizeof(corner_25));
  save_dat_to_file("./weights/edge_xx.dat", &edge_xx[0][0], sizeof(edge_xx));
  */


  /*
  int i;
  for(i = 0; i < CAT_NUM; i++){
    printf("cat_sizes[%d] = %ld\n", i, cat_sizes[i]);
  }

  for(i = 0; i < CAT_NUM; i++){
    double E = total_error(cats[i], cat_sizes[i]);
    printf("E[%d] = %lf\n", i, E);
  }
  */
  /*
  Weights *weights = malloc(sizeof(Weights));
  memset(weights, 0, sizeof(Weights));
    
  double E = total_error(cats[14], cat_sizes[14]);
  printf("E[%d] = %lf\n", 14, E);

  int i;
  int c = 6;
  for(i = 0; i < 1500; i++){
    grad_descent_step(cats[c], cat_sizes[c], weights, 0.0000000003);

    memcpy(row_1[c], weights->row_1, sizeof(row_1[c]));
    memcpy(row_2[c], weights->row_2, sizeof(row_2[c]));
    memcpy(row_3[c], weights->row_3, sizeof(row_3[c]));
    memcpy(row_4[c], weights->row_4, sizeof(row_4[c]));

    memcpy(diag_8[c], weights->diag_8, sizeof(diag_8[c]));
    memcpy(diag_7[c], weights->diag_7, sizeof(diag_7[c]));
    memcpy(diag_6[c], weights->diag_6, sizeof(diag_6[c]));
    memcpy(diag_5[c], weights->diag_5, sizeof(diag_5[c]));
    memcpy(diag_4[c], weights->diag_4, sizeof(diag_4[c]));

    memcpy(corner_33[c], weights->corner_33, sizeof(corner_33[c]));
    memcpy(corner_25[c], weights->corner_25, sizeof(corner_25[c]));
    memcpy(edge_xx[c], weights->edge_xx, sizeof(edge_xx[c]));

    printf("iteration %d done\n", i);
    
    if(i % 10 == 0){
      E = total_error(cats[c], cat_sizes[c]);
      printf("E[%d] = %lf\n", c, E);
    }

  }
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

  /*
  int r,c;
  printf("const char squares_in_dir[BOARD_SIZE_SQR][ADJ_SIZE] = {\n");
  for(r=0;r<8;r++){
    for(c=0;c<8;c++){
      Pos pos = (Pos) {r,c};
      
      printf("{");
      int i, j;
      for(i=-1;i<=1;i++){
	for(j=-1;j<=1;j++){
	  if(i==0 && j==0){
	    continue;
	  }
	  int count = 0;
	  Pos head = (Pos) {r+i, c+j};
	  int direc_h = head.r - pos.r;
	  int direc_v = head.c - pos.c;
	  while(check_pos(head)==0){
	    head.r += direc_h;
	    head.c += direc_v;
	    count++;
	  }
	  printf("%d", count);
	  if(i!=1 || j!= 1){
	    printf(", ");
	  }
	}
      }
      printf("}");
      if(r!=7 || c!=7){
	printf(", \n");
      }
    }
  }
  printf("};\n");
  exit(0);
  */
    
  /*
  printf("const uint64_t rays_to_flip[BOARD_SIZE_SQR][ADJ_SIZE][6] = {\n");
  int r, c;
  for(r=0;r<8;r++){
    for(c=0;c<8;c++){
      printf("{// square (%d,%d), %d\n", r, c, r*8+c);
      for(i=0;i<ADJ_SIZE;i++){
	printf("{");
	uint64_t mask = offset_bitmask(pos_mask[r][c], dir_offset[i]);
	for(j=0;j<6;j++){
	  if(squares_in_dir[8*r+c][i] == 0){
	    mask = 0;
	  }
	  if(squares_in_dir[8*r+c][i] <= j){
	    mask = 0;
	  }

	  printf("0x%016lx", mask);
	  if(j<5){
	    printf(", ");
	  }
	  mask |= offset_bitmask(mask, dir_offset[i]);
	}
	printf("}");
	if(i<7){
	  printf(", \n");
	}
      }
      printf("}");
      if(r<7 || c<7){
	printf(", \n");
      }
    }
  }
  printf("};\n");
  exit(0);
  */
  

  /*
  int n_b;
  Config boards = read_configs_from_file("./dat/boards/boards.dat", &n_b);
  free(boards);
  // temporary variable

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

  global_n_f = n_f;
  global_fcts = fcts;
  */
  
  /*
  int k;
  uint32_t w_index, b_index;
  for(k=0;k<100000;k++){
    w_index = rand() % 512;
    b_index = (rand() % 512) & (~w_index);
    for(cat=0;cat<15;cat++){
      increment_corner_33(corner_33[cat], w_index, b_index, 1);
    }
    
    w_index = rand() % 1024;
    b_index = (rand() % 1024) & (~w_index);
    for(cat=0;cat<15;cat++){
      increment_corner_25(corner_25[cat], w_index, b_index, 1);
    }
    
    w_index = rand() % 1024;
    b_index = (rand() % 1024) & (~w_index);
    for(cat=0;cat<15;cat++){
      increment_edge_xx(edge_xx[cat], w_index, b_index, 1);
    }
  }

  
  BitState *state = create_initial_bitstate();

  state->board.w = (uint64_t)rand() | ((uint64_t)rand() << 32);//(ROW(0) & (~ATOM(0,0))) | ATOM(2,1);
  state->board.b = ((uint64_t)rand() | ((uint64_t)rand() << 32)) & (~state->board.w);
  
  print_bitstate(state);
  printf("score = %lf\n", evaluate(state));
  
  state->board.w = rotate90Clockwise(state->board.w);
  state->board.b = rotate90Clockwise(state->board.b);
  print_bitstate(state);
  printf("score = %lf\n", evaluate(state));
  
  exit(0);
  */

  /*
  struct timeval start;
  struct timeval end;
  gettimeofday(&start, NULL);
  long int i;
  long int times = 200000000;
  long int freq = 1300000000;
  state->board.w = (uint64_t)rand() + ((uint64_t)rand() << 32);
  state->board.b = ((uint64_t)rand() + ((uint64_t)rand() << 32)) & (~state->board.w);
  for(i=0;i<times;i++){
    //state->board.w = (uint64_t)rand() + ((uint64_t)rand() << 32);
    //state->board.b = ((uint64_t)rand() + ((uint64_t)rand() << 32)) & (~state->board.w);
    evaluate(state);
  }
  gettimeofday(&end, NULL);

  print_bitstate(state);
  
  double elapsed = (double)((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))/(double)1000000;
  double cycles = (double)freq * elapsed / (double)times;
  printf("cycles = %lf\n", cycles);

  exit(0);
  */
  
  

  char log_filename[120];
  sprintf(log_filename, "./log/%ld.csv", t.tv_sec);
  log_file = fopen(log_filename, "w");
  
  //Player black = human_player();
  //Player black = random_player();
  Player black = mixed_player(10, heuristic_score_4, 22);
  Player white = mixed_player(10, heuristic_score_4, 22);


  run_game(1, 1, white, black);

  
  free(white.param);
  free(black.param);

  fclose(log_file);

  /*
  for(cat=0;cat<CAT_NUM;cat++){
    for(f=0;f<n_f;f++){
      free_fct_contents(fcts[cat][f]);
    }
    free(fcts[cat]);
  }
  free(fcts);
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

  exit(0);  
}



