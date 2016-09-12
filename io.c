#include "io.h"

static char filename_templates[12][120] = {
  "./weights/row_1_%02d.dat",
  "./weights/row_2_%02d.dat",
  "./weights/row_3_%02d.dat",
  "./weights/row_4_%02d.dat",

  "./weights/diag_8_%02d.dat",
  "./weights/diag_7_%02d.dat",
  "./weights/diag_6_%02d.dat",
  "./weights/diag_5_%02d.dat",
  "./weights/diag_4_%02d.dat",

  "./weights/corner_33_%02d.dat",
  "./weights/corner_25_%02d.dat",
  "./weights/edge_xx_%02d.dat"
};

void writecolor(const char *str, const char *back, const char *color){
  write(1, "\e[48;5;", 7);
  write(1, back, 2);
  write(1, "m", 1);
  
  write(1, "\e[38;5;", 7);
  write(1, color, 2);
  write(1, "m", 1);

  write(1, str, strlen(str));

  write(1, "\e[48;5;", 7);
  write(1, "00", 2);
  write(1, "m", 1);

  write(1, "\e[38;5;", 7);
  write(1, "46", 2);
  write(1, "m", 1);
}

int print_bitboard(BitBoard board){

  writecolor("  A B C D E F G H ", "52", "46");
  write(1, "\n", 1);
  int r,c = 0;
  for(r=0;r<BOARD_SIZE;r++){
    char rownum[3] = {'1'+r, ' '};
    writecolor(rownum, "52", "46");
    for(c=0;c<BOARD_SIZE;c++){
      switch(bitboard_get_pos(&board, pos_mask[r][c])){
      case EMPTY:
	writecolor("* ", "94", "08");
	break;
      case W:
	writecolor("W ", "94", "15");
	break;
      case B:
	writecolor("B ", "94", "00");
	break;
      }
    }
    write(1, "\n", 1);
  }
  return 0;
}

int print_bitstate(BitState *state){
  if(state == NULL)
    return -1;
  
  //printf("state->turn = %d\n", state->turn);
  if(state->turn == W){
    write(1, "(white's turn)\n", 15);
  } else {
    write(1, "(black's turn)\n", 15);
  } 
  print_bitboard(state->board);

  return 0;
}


void print_options(BitMask *moves, int movec){
  int i;
  for(i=0;i<(movec+7-1)/7;i++){
    int j = 7*i;
    while(j<movec && j<7*(i+1)){
      int clz = __builtin_clzll(moves[j]);
      int r, c;
      r = clz / 8;
      c = clz % 8;

      
      printf("%2d:%c%c (%d,%d)  ", j, c+'A', r+'1', r, c);
      j++;
    }
    printf("\n");
  }
}

void print_move_made(BitMask move, int index){
  int clz = __builtin_clzll(move);
  int r, c;
  r = clz / 8;
  c = clz % 8;
  printf("(makes move at %c%c (%d,%d) (move index %d))\n", c+'A', r+'1', r, c, index);
}

int get_human_response(int movec){
  int response;
  printf("This is your turn. Enter number to place your piece.\n");
  while(1){
    int ret = scanf("%d", &response);
    if(ret < 1){
      printf("Invalid input. Try again.\n");
      continue;
    }
    if(response >= movec){
      printf("Invalid choice. Try again.\n");
      continue;
    }
    break;
  }
  return response;
}


int print_pattern(Pattern pattern){

  BitBoard board = (BitBoard) {pattern, 0};
  print_bitboard(board);
  
  printf("pattern = %016lx\n", pattern);
  printf("degree = %d\n", __builtin_popcountl(pattern));

  return 0;
}

void get_players(Player *white, Player *black){
  char white_choice, black_choice;
  char white_chosen, black_chosen;
  white_chosen = 0;
  black_chosen = 0;
  
  printf("Choose player for white:\n");
  printf("Enter 'c' for computer and 'h' for human: ");

  while(white_chosen == 0){
    int ret = scanf("%c", &white_choice);
    if(ret < 0){
      printf("please enter 'c' or 'h': ");
      continue;
    }
    switch(white_choice){
    case 'c':
      {
	int midgame_depth, endgame_depth;
	midgame_depth = 10;
	endgame_depth = 20;
	printf("Enter the depth for white's midgame search (typically 10): ");
	int ret1 = scanf("%d", &midgame_depth);
	if(ret1 < 0 || midgame_depth <= 0){
	  midgame_depth = 10;
	}
	printf("Enter the depth for white's endgame search (typically 20): ");
	int ret2 = scanf("%d", &endgame_depth);
	if(ret2 < 0 || endgame_depth < 0){
	  endgame_depth = 20;
	}
	*white = mixed_player(midgame_depth, heuristic_score_4, endgame_depth);
	white_chosen = 1;
      }
      break;
    case 'h':
      {
	*white = human_player();
	white_chosen = 1;
      }
      break;
    default:
      {
	printf("please enter 'c' or 'h': ");
	break;
      }
    }
  }

  printf("Choose player for black:\n");
  printf("Enter 'c' for computer and 'h' for human: ");

  while(black_chosen == 0){
    int ret = scanf("%c", &black_choice);
    if(ret < 0){
      printf("please enter 'c' or 'h': ");
      continue;
    }
    switch(black_choice){
    case 'c':
      {
	int midgame_depth, endgame_depth;
	midgame_depth = 10;
	endgame_depth = 20;
	printf("Enter the depth for black's midgame search (typically 10): ");
	int ret1 = scanf("%d", &midgame_depth);
	if(ret1 < 0 || midgame_depth <= 0){
	  midgame_depth = 10;
	}
	printf("Enter the depth for black's endgame search (typically 20): ");
	int ret2 = scanf("%d", &endgame_depth);
	if(ret2 < 0 || endgame_depth < 0){
	  endgame_depth = 20;
	}
	*black = mixed_player(midgame_depth, heuristic_score_4, endgame_depth);
	black_chosen = 1;
      }
      break;
    case 'h':
      {
	*black = human_player();
	black_chosen = 1;
      }
      break;
    default:
      {
	printf("please enter 'c' or 'h': ");
	break;
      }
    }
  }

  
}

/*
Example *read_examples_from_file(const char *filename, int *count_examples){

  printf("reading examples from file %s .....\n", filename);
  FILE *fp;
  if((fp = fopen(filename, "r")) == NULL){
    printf("failed: file access error\n");
    exit(0);
    //return NULL;
  }

  fseek(fp, 0L , SEEK_END);
  long int lSize = ftell(fp);
  rewind(fp);
  if(count_examples != NULL){
    *count_examples = lSize/sizeof(Example);
  }
  
  Example *examples = malloc(lSize);
  fread(examples, lSize, 1, fp);
  
  printf("read %ld examples.\n", lSize/sizeof(Example));

  fclose(fp);

  return examples;
}

Config read_configs_from_file(const char *filename, int *count_configs){

  printf("reading configs from file %s .....\n", filename);
  FILE *fp;
  if((fp = fopen(filename, "r")) == NULL){
    printf("failed: file access error\n");
    exit(0);
  }

  fseek(fp, 0L , SEEK_END);
  long int lSize = ftell(fp);
  rewind(fp);
  if(count_configs != NULL){
    *count_configs = lSize/sizeof(Config_store);
  }
  
  Config configs = malloc(lSize);
  fread(configs, lSize, 1, fp);

  printf("read %ld configs.\n", lSize/sizeof(Config_store));
  
  fclose(fp);

  return configs;
}
*/

void *read_dat_from_file(const char *filename, int obj_size, int *count_obj){
  
  printf("reading data from file %s .....\n", filename);
  FILE *fp;
  if((fp = fopen(filename, "r")) == NULL){
    printf("failed: file access error\n");
    exit(0);
  }

  fseek(fp, 0L , SEEK_END);
  long int lSize = ftell(fp);
  rewind(fp);
  if(count_obj != NULL){
    *count_obj = lSize/obj_size;
  }
  
  void *data = malloc(lSize);
  fread(data, lSize, 1, fp);

  printf("read %ld items.\n", lSize/obj_size);
  
  fclose(fp);

  return data;
}

void save_dat_to_file(const char *file_name, void *dat, int file_size){
  int fd = open(file_name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  printf("writing to file %s: file_size = %d\n", file_name, file_size);
  write(fd, dat, file_size);
  close(fd);
}


int get_file_size(const char *filename, size_t obj_size){

  int size;
  
  FILE *fp;
  if((fp = fopen(filename, "r")) == NULL){
    printf("failed: file access error\n");
    exit(0);
  }

  fseek(fp, 0L , SEEK_END);
  long int lSize = ftell(fp);
  //rewind(fp);
  size = lSize/obj_size;

  return size;
}

void write_flat_weights(const char *filename, double *weights, int bits){

  int size = ipow(2, bits);

  uint32_t *reverse_table;
  switch(size){
  case 16:
    reverse_table = map_reverse_16;
    break;
  case 32:
    reverse_table = map_reverse_32;
    break;
  case 64:
    reverse_table = map_reverse_64;
    break;
  case 128:
    reverse_table = map_reverse_128;
    break;
  case 256:
    reverse_table = map_reverse_256;
    break;
  default:
    reverse_table = map_reverse_256;
    break;
  }

  FILE *fp;
  if((fp = fopen(filename, "w+")) == NULL){
    printf("error calling fopen()\n");
  }

  char *counter = malloc(size * size * sizeof(char));
  memset(counter, 0, size * size * sizeof(char));
  
  uint32_t white, black, rwhite, rblack;
  //uint32_t count = 0;
  for(white = 0; white < size; white++){
    for(black = 0; black < size; black++){
      if(white & black){
	continue;
      }
      if(white == black){
	continue;
      }
      rwhite = reverse_table[white];
      rblack = reverse_table[black];
      if((white == rblack) && (black == rwhite)){
	continue;
      }
      if(counter[white * size + black]){
	continue;
      }
      counter[white * size + black]++;
      counter[black * size + white]++;
      counter[rwhite * size + rblack]++;
      counter[rblack * size + rwhite]++;

      fwrite(weights + white * size + black, sizeof(double), 1, fp);
      
    }
  }
  fclose(fp);
  free(counter);
}

void write_corner_33(const char *filename, double *weights){
  
  int bits = 9;
  
  int array_size = ipow(3, bits);
  int color_size = ipow(2, bits);

  uint32_t *reverse_table;
  reverse_table = map_corner_33;
  
  FILE *fp;
  if((fp = fopen(filename, "w+")) == NULL){
    printf("error calling fopen()\n");
  }

  char *counter = malloc(array_size * sizeof(char));
  memset(counter, 0, array_size * sizeof(char));
  
  uint32_t white, black, rwhite, rblack;

  for(white = 0; white < color_size; white++){
    for(black = 0; black < color_size; black++){
      if(white & black){
	continue;
      }
      if(white == black){
	continue;
      }
      rwhite = reverse_table[white];
      rblack = reverse_table[black];
      if((white == rblack) && (black == rwhite)){
	continue;
      }

      int orig_index = offset_19683[white] + _pext_u32(black, ~white);
      int reverse_index = offset_19683[black] + _pext_u32(white, ~black);
      int reflect_index = offset_19683[rwhite] + _pext_u32(rblack, ~rwhite);
      int both_index = offset_19683[rblack] + _pext_u32(rwhite, ~rblack);
      
      if(counter[orig_index]){
	continue;
      }
      
      counter[orig_index]++;
      counter[reverse_index]++;
      counter[reflect_index]++;
      counter[both_index]++;

      fwrite(&weights[orig_index], sizeof(double), 1, fp);
      
    }
  }
  fclose(fp);
  free(counter);
}

void write_edge_xx(const char *filename, double *weights){
  
  int bits = 10;
  
  int array_size = ipow(3, bits);
  int color_size = ipow(2, bits);

  uint32_t *reverse_table;
  reverse_table = map_edge_xx;
  
  FILE *fp;
  if((fp = fopen(filename, "w+")) == NULL){
    printf("error calling fopen()\n");
  }

  char *counter = malloc(array_size * sizeof(char));
  memset(counter, 0, array_size * sizeof(char));
  
  uint32_t white, black, rwhite, rblack;

  for(white = 0; white < color_size; white++){
    for(black = 0; black < color_size; black++){
      if(white & black){
	continue;
      }
      if(white == black){
	continue;
      }
      rwhite = reverse_table[white];
      rblack = reverse_table[black];
      if((white == rblack) && (black == rwhite)){
	continue;
      }

      int orig_index = offset_59049[white] + _pext_u32(black, ~white);
      int reverse_index = offset_59049[black] + _pext_u32(white, ~black);
      int reflect_index = offset_59049[rwhite] + _pext_u32(rblack, ~rwhite);
      int both_index = offset_59049[rblack] + _pext_u32(rwhite, ~rblack);
      
      if(counter[orig_index]){
	continue;
      }
      
      counter[orig_index]++;
      counter[reverse_index]++;
      counter[reflect_index]++;
      counter[both_index]++;

      fwrite(&weights[orig_index], sizeof(double), 1, fp);
      
    }
  }
  fclose(fp);
  free(counter);
}

void write_corner_25(const char *filename, double *weights){
  
  int bits = 10;
  
  int array_size = ipow(3, bits);
  int color_size = ipow(2, bits);

  FILE *fp;
  if((fp = fopen(filename, "w+")) == NULL){
    printf("error calling fopen()\n");
  }

  char *counter = malloc(array_size * sizeof(char));
  memset(counter, 0, array_size * sizeof(char));
  
  uint32_t white, black;

  for(white = 0; white < color_size; white++){
    for(black = 0; black < color_size; black++){
      if(white & black){
	continue;
      }
      if(white == black){
	continue;
      }
      
      int orig_index = offset_59049[white] + _pext_u32(black, ~white);
      int reverse_index = offset_59049[black] + _pext_u32(white, ~black);
      
      if(counter[orig_index]){
	continue;
      }
      
      counter[orig_index]++;
      counter[reverse_index]++;

      fwrite(&weights[orig_index], sizeof(double), 1, fp);
      
    }
  }
  fclose(fp);
  free(counter);
}


void read_flat_weights(const char *filename, double *weights, int bits){

  int size = ipow(2, bits);

  uint32_t *reverse_table;
  switch(size){
  case 16:
    reverse_table = map_reverse_16;
    break;
  case 32:
    reverse_table = map_reverse_32;
    break;
  case 64:
    reverse_table = map_reverse_64;
    break;
  case 128:
    reverse_table = map_reverse_128;
    break;
  case 256:
    reverse_table = map_reverse_256;
    break;
  default:
    reverse_table = map_reverse_256;
    break;
  }

  FILE *fp;
  if((fp = fopen(filename, "r")) == NULL){
    printf("error calling fopen()\n");
  }

  char *counter = malloc(size * size * sizeof(char));
  memset(counter, 0, size * size * sizeof(char));
  
  uint32_t white, black, rwhite, rblack;
  //uint32_t count = 0;
  for(white = 0; white < size; white++){
    for(black = 0; black < size; black++){
      if(white & black){
	continue;
      }
      if(white == black){
	continue;
      }
      rwhite = reverse_table[white];
      rblack = reverse_table[black];
      if((white == rblack) && (black == rwhite)){
	continue;
      }
      if(counter[white * size + black]){
	continue;
      }
      counter[white * size + black]++;
      counter[black * size + white]++;
      counter[rwhite * size + rblack]++;
      counter[rblack * size + rwhite]++;

      double value;
      fread(&value, sizeof(double), 1, fp);
      *(weights + white * size + black) = value;
      *(weights + black * size + white) = -value;
      *(weights + rwhite * size + rblack) = value;
      *(weights + rblack * size + rwhite) = -value;
      
    }
  }
  fclose(fp);
  free(counter);
}

void read_corner_33(const char *filename, double *weights){
  
  int bits = 9;
  
  int array_size = ipow(3, bits);
  int color_size = ipow(2, bits);

  uint32_t *reverse_table;
  reverse_table = map_corner_33;
  
  FILE *fp;
  if((fp = fopen(filename, "r")) == NULL){
    printf("error calling fopen()\n");
  }

  char *counter = malloc(array_size * sizeof(char));
  memset(counter, 0, array_size * sizeof(char));
  
  uint32_t white, black, rwhite, rblack;

  for(white = 0; white < color_size; white++){
    for(black = 0; black < color_size; black++){
      if(white & black){
	continue;
      }
      if(white == black){
	continue;
      }
      rwhite = reverse_table[white];
      rblack = reverse_table[black];
      if((white == rblack) && (black == rwhite)){
	continue;
      }

      int orig_index = offset_19683[white] + _pext_u32(black, ~white);
      int reverse_index = offset_19683[black] + _pext_u32(white, ~black);
      int reflect_index = offset_19683[rwhite] + _pext_u32(rblack, ~rwhite);
      int both_index = offset_19683[rblack] + _pext_u32(rwhite, ~rblack);
      
      if(counter[orig_index]){
	continue;
      }
      
      counter[orig_index]++;
      counter[reverse_index]++;
      counter[reflect_index]++;
      counter[both_index]++;

      double value;
      fread(&value, sizeof(double), 1, fp);
      weights[orig_index] = value;
      weights[reverse_index] = -value;
      weights[reflect_index] = value;
      weights[both_index] = -value;
      
    }
  }
  fclose(fp);
  free(counter);
}

void read_edge_xx(const char *filename, double *weights){
  
  int bits = 10;
  
  int array_size = ipow(3, bits);
  int color_size = ipow(2, bits);

  uint32_t *reverse_table;
  reverse_table = map_edge_xx;
  
  FILE *fp;
  if((fp = fopen(filename, "r")) == NULL){
    printf("error calling fopen()\n");
  }

  char *counter = malloc(array_size * sizeof(char));
  memset(counter, 0, array_size * sizeof(char));
  
  uint32_t white, black, rwhite, rblack;

  for(white = 0; white < color_size; white++){
    for(black = 0; black < color_size; black++){
      if(white & black){
	continue;
      }
      if(white == black){
	continue;
      }
      rwhite = reverse_table[white];
      rblack = reverse_table[black];
      if((white == rblack) && (black == rwhite)){
	continue;
      }

      int orig_index = offset_59049[white] + _pext_u32(black, ~white);
      int reverse_index = offset_59049[black] + _pext_u32(white, ~black);
      int reflect_index = offset_59049[rwhite] + _pext_u32(rblack, ~rwhite);
      int both_index = offset_59049[rblack] + _pext_u32(rwhite, ~rblack);
      
      if(counter[orig_index]){
	continue;
      }
      
      counter[orig_index]++;
      counter[reverse_index]++;
      counter[reflect_index]++;
      counter[both_index]++;

      double value;
      fread(&value, sizeof(double), 1, fp);
      weights[orig_index] = value;
      weights[reverse_index] = -value;
      weights[reflect_index] = value;
      weights[both_index] = -value;
      
    }
  }
  fclose(fp);
  free(counter);
}

void read_corner_25(const char *filename, double *weights){
  
  int bits = 10;
  
  int array_size = ipow(3, bits);
  int color_size = ipow(2, bits);

  FILE *fp;
  if((fp = fopen(filename, "r")) == NULL){
    printf("error calling fopen()\n");
  }

  char *counter = malloc(array_size * sizeof(char));
  memset(counter, 0, array_size * sizeof(char));
  
  uint32_t white, black;

  for(white = 0; white < color_size; white++){
    for(black = 0; black < color_size; black++){
      if(white & black){
	continue;
      }
      if(white == black){
	continue;
      }

      int orig_index = offset_59049[white] + _pext_u32(black, ~white);
      int reverse_index = offset_59049[black] + _pext_u32(white, ~black);
      
      if(counter[orig_index]){
	continue;
      }
      
      counter[orig_index]++;
      counter[reverse_index]++;

      double value;
      fread(&value, sizeof(double), 1, fp);
      weights[orig_index] = value;
      weights[reverse_index] = -value;
      
    }
  }
  fclose(fp);
  free(counter);
}

void save_all_weights(void){
  int cat;
  char filename[120];

  for(cat = 0; cat < CAT_NUM; cat++){
    sprintf(filename, filename_templates[0], cat);
    write_flat_weights(filename, &row_1[cat][0][0], 8);

    sprintf(filename, filename_templates[1], cat);
    write_flat_weights(filename, &row_2[cat][0][0], 8);

    sprintf(filename, filename_templates[2], cat);
    write_flat_weights(filename, &row_3[cat][0][0], 8);

    sprintf(filename, filename_templates[3], cat);
    write_flat_weights(filename, &row_4[cat][0][0], 8);

    sprintf(filename, filename_templates[4], cat);
    write_flat_weights(filename, &diag_8[cat][0][0], 8);
    
    sprintf(filename, filename_templates[5], cat);
    write_flat_weights(filename, &diag_7[cat][0][0], 7);
    
    sprintf(filename, filename_templates[6], cat);
    write_flat_weights(filename, &diag_6[cat][0][0], 6);
    
    sprintf(filename, filename_templates[7], cat);
    write_flat_weights(filename, &diag_5[cat][0][0], 5);
    
    sprintf(filename, filename_templates[8], cat);
    write_flat_weights(filename, &diag_4[cat][0][0], 4);
    
    sprintf(filename, filename_templates[9], cat);
    write_corner_33(filename, &corner_33[cat][0]);

    sprintf(filename, filename_templates[10], cat);
    write_corner_25(filename, &corner_25[cat][0]);

    sprintf(filename, filename_templates[11], cat);
    write_edge_xx(filename, &edge_xx[cat][0]);
  }

}

void load_all_weights(void){
  int cat;
  char filename[120];

  for(cat = 0; cat < CAT_NUM; cat++){
    sprintf(filename, filename_templates[0], cat);
    read_flat_weights(filename, &row_1[cat][0][0], 8);

    sprintf(filename, filename_templates[1], cat);
    read_flat_weights(filename, &row_2[cat][0][0], 8);

    sprintf(filename, filename_templates[2], cat);
    read_flat_weights(filename, &row_3[cat][0][0], 8);

    sprintf(filename, filename_templates[3], cat);
    read_flat_weights(filename, &row_4[cat][0][0], 8);

    sprintf(filename, filename_templates[4], cat);
    read_flat_weights(filename, &diag_8[cat][0][0], 8);
    
    sprintf(filename, filename_templates[5], cat);
    read_flat_weights(filename, &diag_7[cat][0][0], 7);
    
    sprintf(filename, filename_templates[6], cat);
    read_flat_weights(filename, &diag_6[cat][0][0], 6);
    
    sprintf(filename, filename_templates[7], cat);
    read_flat_weights(filename, &diag_5[cat][0][0], 5);
    
    sprintf(filename, filename_templates[8], cat);
    read_flat_weights(filename, &diag_4[cat][0][0], 4);
    
    sprintf(filename, filename_templates[9], cat);
    read_corner_33(filename, &corner_33[cat][0]);

    sprintf(filename, filename_templates[10], cat);
    read_corner_25(filename, &corner_25[cat][0]);

    sprintf(filename, filename_templates[11], cat);
    read_edge_xx(filename, &edge_xx[cat][0]);
  }

}
