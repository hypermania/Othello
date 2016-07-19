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
#include "preprocess.h"

#include "bitboard.h"

FlatConfTable **global_fcts;
int global_n_f;

int main(int argc, char **argv){
  // set up random number generator
  struct timeval t;
  gettimeofday(&t, NULL);
  srand((long int) t.tv_usec);
  //srand((long int) 100);

  int i, j;

  /*
  BitBoard bitboard = new_initial_bitboard();
  Board board = create_board();
  BitBoard temp;
  
  long int k;
  volatile char n;
  //for(k=0;k<10000000000;k++){
  for(k=0;k<1000000000;k++){
    //bitboard_set_pos(&bitboard, pos_mask[1][k%8], W);
    //n = bitboard_get_pos(&bitboard, pos_mask[1][k%8]);
    
    //board_set_pos(board, (Pos){1, k%8}, W);
    //n = board_get_pos(board, (Pos) {1, k%8});

    //bitboard_set_pos(&bitboard, ATOM(1, k%8), W);
    //temp = bitboard_set_pos_nonref(bitboard, pos_mask[1][k%8], W);
    //n = bitboard_get_pos_nonref(bitboard, pos_mask[1][k%8]);
    //board_set_pos(board, (Pos){1, k%8}, W);
  }
  print_board(board);
  print_bitboard(bitboard);
  print_bitboard(temp);
  printf("%d\n",n);
  
  exit(0);
  */

  /*
  for(i=0;i<3000000;i++){
  //for(i=0;i<10000000;i++){
    if(test_bitboard()){
      printf("failed\n");
    }
  }
  exit(0);
  */
  
  /*
  BitBoard board = new_initial_bitboard();
  int r,c;
  for(r=0;r<8;r++){
    for(c=0;c<8;c++){
  

  BitMask bitmask = pos_mask[r][c];
  BitMask store[8];
  int count = bitboard_adj_given_pos(&board, bitmask, store, B);

  printf("(%d,%d), count = %d\n", r, c, count);

    }}
  print_bitboard(board);
  exit(0);
  */

  /*
  BitState *state = create_initial_bitstate();

  int movec;
  BitMask *moves;
  
  print_bitboard(state->board);
  
  //moves = bitstate_allowed_moves(state, &movec); 
  //bitstate_place_piece(state, 0);
  //print_bitboard(state->board);

  BitMask move_mask = find_moves_bitmask(state->board, state->turn);

  print_bitboard((BitBoard) {move_mask, 0});

  exit(0);
  */
  

  struct timeval start;
  struct timeval end;
  
  gettimeofday(&start, NULL);
  
  test_bitstate();
  
  gettimeofday(&end, NULL);

  double elapsed = (double)((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))/(double)1000000;

  printf("game/s = %lf\n", (double)(1 << 20)/elapsed);

  exit(0);



  
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
  printf("const uint64_t adj_pos_mask[BOARD_SIZE_SQR][ADJ_SIZE] = {\n");
  int r, c;
  for(r=0;r<8;r++){
    for(c=0;c<8;c++){
      printf("{");
      for(i=0;i<ADJ_SIZE;i++){
	uint64_t mask = offset_bitmask(pos_mask[r][c], dir_offset[i]);
	if(squares_in_dir[8*r+c][i] == 0){
	  mask = 0;
	}
	printf("0x%016lx", mask);
	if(i<7){
	  printf(", ");
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
  
  //fit_fct_for_categories();
  //exit(0);
  //printf("test_table = %d\n", test_table());
  //printf("test_state = %d\n", test_state());
  

  /*
  int n_e = 0;
  Example *examples = malloc(0);
  //examples = append_filed_games_to_examples(examples, &n_e, "./game_base/all_games.txt");
  examples = append_random_games_to_examples(examples, &n_e, 50000);
  Config boards_random = create_and_init_config_list(n_e);
  for(i=0;i<n_e;i++){
    boards_random[i] = examples[i].board;
  }
  
  save_dat_to_file("./dat/boards/boards_random.dat", boards_random, n_e * sizeof(Config_store));
  

  Example *categories[CAT_NUM];
  int cat_sizes[CAT_NUM];

  sort_examples_into_categories(examples, categories, cat_sizes, n_e);
  

  for(i=0;i<10;i++){
    int cat = rand() % CAT_NUM;
    int r = rand() % cat_sizes[cat];
    print_config(&categories[cat][r].board);
    printf("cat = %d, score = %d\n", cat, categories[cat][r].score);
  }


  //fit_fct_for_categories(categories, cat_sizes);

  free(examples);
  
  exit(0);
  */
  
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
  /*
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
  */
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
  global_n_f = n_f;
  global_fcts = fcts;


  //Player black = human_player();
  //Player black = random_player();
  Player black = mixed_player(10, heuristic_score_2, 21);
  Player white = mixed_player(10, heuristic_score_2, 21);

  //for(i=0;i<1000;i++){
  run_game(1, 1, white, black);
  //}

  free(white.param);
  free(black.param);
  

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

  
  // run tests

  //printf("test_board = %d\n", test_board());

  //printf("test_table = %d\n", test_table());
  //printf("test_genconf = %d\n", test_genconf());


  exit(0);  
}



