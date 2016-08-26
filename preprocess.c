#include "preprocess.h"

/*
int example_from_seq(State state, Pos *seq, Example *example){
  assert(state != NULL);
  assert(seq != NULL);
  assert(example != NULL);
  
  int count = 0;
  Pos moves[POS_STORE_SIZE]; int movec;
  
  init_state(state);
  while(!state_final(state)){
    
    movec = allowed_moves(state, moves);
    if(movec == 0){
      skip_turn(state);
    } else {
      int i; int moved = 0;
      for(i=0;i<movec;i++){
	if(moves[i].r == seq[count].r && moves[i].c == seq[count].c){
	  place_piece(state, seq[count]);
	  //state_switch_turn(state);
	  moved = 1;
	  break;
	}
      }
      if(moved == 0){
	count = 0;
	break;
      }
      board_to_conf(state->board, &(example[count].board));
      count++;
    }
  }
  int i;
  int score = count_pieces(state->board, W) - count_pieces(state->board, B);
  for(i=0;i<count;i++){
    example[i].score = score;
  }
  return count;
}
*/

int sort_examples_into_categories(Example *examples, Example **categories, int *cat_sizes, int example_size){

  const int chunk = 10;
  
  int allocated[CAT_NUM];
  int i;
  for(i=0;i<CAT_NUM;i++){
    allocated[i] = chunk;
    categories[i] = malloc(allocated[i] * sizeof(Example));
    cat_sizes[i] = 0;
  }

  for(i=0;i<example_size;i++){
    int pieces = BOARD_SIZE_SQR - __builtin_popcountl(examples[i].board.x);
    int cat = ((pieces - INIT_PIECE_NUM) - 1) / CATEGORY_SIZE;

    if(cat_sizes[cat] == allocated[cat]){
      allocated[cat] += chunk;
      categories[cat] = realloc(categories[cat], allocated[cat] * sizeof(Example));
    }
    
    categories[cat][cat_sizes[cat]] = examples[i];
    cat_sizes[cat]++;
  }

  int cat;
  for(cat=0;cat<CAT_NUM;cat++){
    categories[cat] = realloc(categories[cat], cat_sizes[cat] * sizeof(Example));
  }
  
  return 0;

}


/*
Example *append_filed_games_to_examples(Example *examples, int *n_e, const char *filename){
  
  printf("begin appending games from file %s to examples\n", filename);
  
  FILE *fp;
  fp = fopen(filename, "r");
  // temporary storage
  State state = create_state();
  char buff[BUFF_SIZE];

  // examples to be loaded
  int allocated = *n_e;
  
  int count_games = 0;
  while(!feof(fp)){
    memset(buff, 0, BUFF_SIZE);
    fgets(buff, BUFF_SIZE, fp);
    
    Pos *seq = randomized_file_to_seq(buff, BUFF_SIZE);

    if(allocated - (*n_e) < 100){
      allocated += 10000;
      examples = realloc(examples, allocated * sizeof(Example));
    }

    Example *current = examples + (*n_e);
    int turns = example_from_seq(state, seq, current);
    
    if(turns > 0){
      (*n_e) += turns;
      count_games++;
    }
    
    if(count_games % 5000 == 0){
      printf("count_games = %d\n", count_games);
    }
  }
  
  printf("...complete. n_e = %d\n", (*n_e));
  examples = realloc(examples, (*n_e) * sizeof(Example));
  
  fclose(fp);
  
  return examples;
}
*/

/*
Example *append_random_games_to_examples(Example *examples, int *n_e, int n_g){

  printf("begin appending random games to examples\n");
  
  // temporary storage
  State state = create_state();

  int allocated = *n_e;

  int i;
  for(i=0;i<n_g;i++){
    init_state(state);
    Config_store boards[60];
    while(!state_final(state)){
      int movec;
      allowed_moves_inplace(state, &movec);
      if(movec == 0){
	skip_turn(state);
      } else {
	place_piece_indexed(state, rand() % movec);
      }
      boards[state->seq_num - 1] = board_to_conf_nocreate(state->board);
    }

    short score  = piece_diff(state->board, W, B);
    
    if(allocated - (*n_e) < 100){
      allocated += 1000;
      examples = realloc(examples, allocated * sizeof(Example));
    }
    
    int j;
    for(j=0;j<state->seq_num;j++){
      Example pt;
      pt.board = boards[j];
      //print_config(&boards[j]);
      pt.score = score;
      examples[(*n_e)++] = pt;
    }
    if(i % 5000 == 0){
      printf("count_games = %d\n", i);
    }
  }

  free_state(state);
  
  printf("...complete. n_e = %d\n", (*n_e));
  
  examples = realloc(examples, (*n_e) * sizeof(Example));
  
  return examples;
}
*/


/*
Example *append_mixed_games_to_examples(Example *examples, int *n_e, int n_g){

  printf("begin appending mixed games to examples\n");
  
  // temporary storage
  State state = create_state();

  int allocated = *n_e;

  int i;
  for(i=0;i<n_g;i++){
    init_state(state);
    Config_store boards[60];
    while(!state_final(state)){
      int movec;
      allowed_moves_inplace(state, &movec);
      if(movec == 0){
	skip_turn(state);
      } else {
	int m = negamaxing_move(state, 1, heuristic_score_0);
	place_piece_indexed(state, m);
      }
      boards[state->seq_num - 1] = board_to_conf_nocreate(state->board);
    }

    short score  = piece_diff(state->board, W, B);
    
    if(allocated - (*n_e) < 100){
      allocated += 1000;
      examples = realloc(examples, allocated * sizeof(Example));
    }
    
    int j;
    for(j=0;j<state->seq_num;j++){
      Example pt;
      pt.board = boards[j];
      //print_config(&boards[j]);
      pt.score = score;
      examples[(*n_e)++] = pt;
    }
    if(i % 5000 == 0){
      printf("count_games = %d\n", i);
    }
  }

  free_state(state);
  
  printf("...complete. n_e = %d\n", (*n_e));
  
  examples = realloc(examples, (*n_e) * sizeof(Example));
  
  return examples;
}

*/
