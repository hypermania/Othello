#include "io.h"

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

int print_board(Board board){
  if(board == NULL)
    return -1;
  //write(1, "\e[1m", 4);
  //writecolor("  0 1 2 3 4 5 6 7 ", "52", "46");
  writecolor("  A B C D E F G H ", "52", "46");
  write(1, "\n", 1);
  int r,c = 0;
  for(r=0;r<BOARD_SIZE;r++){
    char rownum[3] = {'1'+r, ' '};
    writecolor(rownum, "52", "46");
    for(c=0;c<BOARD_SIZE;c++){
      switch(board_get_pos(board, (Pos) {r,c})){
      case 0:
	writecolor("* ", "94", "08");
	break;
      case 1:
	writecolor("W ", "94", "15");
	break;
      case 2:
	writecolor("B ", "94", "00");
	break;
      }
    }
    write(1, "\n", 1);
  }
  return 0;
}

int print_state(State state){
  if(state == NULL)
    return -1;
  
  //printf("state->turn = %d\n", state->turn);
  if(state->turn == W){
    write(1, "(white's turn)\n", 15);
  } else {
    write(1, "(black's turn)\n", 15);
  } 
  print_board(state->board);

  return 0;
}


void print_options(Pos *moves, int movec){
  int i;
  for(i=0;i<(movec+7-1)/7;i++){
    int j = 7*i;
    while(j<movec && j<7*(i+1)){
      printf("%2d:%c%c (%d,%d)  ", j, moves[j].c+'A', moves[j].r+'1', moves[j].r, moves[j].c);
      j++;
    }
    printf("\n");
  }
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

Pos *file_to_seq(char *buff, int n){
  assert(buff != NULL);
  int i;
  for(i=0;i<n/2;i++){
    buff[2*i+0] -= 'A';
    buff[2*i+1] -= '1';
    // swapping adjacent char
    buff[2*i+1] ^= buff[2*i+0];
    buff[2*i+0] ^= buff[2*i+1];
    buff[2*i+1] ^= buff[2*i+0];
  }
  return (Pos *)buff;
}

Pos *randomized_file_to_seq(char *buff, int n){
  assert(buff != NULL);
  int i;
  for(i=0;i<n/2;i++){
    // preprocess
    buff[2*i+0] -= 'A';
    buff[2*i+1] -= '1';
    // swapping adjacent char
    buff[2*i+1] ^= buff[2*i+0];
    buff[2*i+0] ^= buff[2*i+1];
    buff[2*i+1] ^= buff[2*i+0];
  }
  // filp along diagonal at random
  if(rand() % 2){
    for(i=0;i<n/2;i++){
      // swap row and column
      buff[2*i+1] ^= buff[2*i+0];
      buff[2*i+0] ^= buff[2*i+1];
      buff[2*i+1] ^= buff[2*i+0];
    }
  }
  // flip along reverse diagonal at random
  if(rand() % 2){
    for(i=0;i<n/2;i++){
      char temp = BOARD_SIZE - 1 - buff[2*i+1];
      buff[2*i+1] = BOARD_SIZE - 1 - buff[2*i+0];
      buff[2*i+0] = temp;
    }
  }


  if(rand() % 2){
    for(i=0;i<n/2;i++){
      buff[2*i+0] = BOARD_SIZE - 1 - buff[2*i+0];
      buff[2*i+1] = BOARD_SIZE - 1 - buff[2*i+1];
    }
  }


  return (Pos *)buff;
}

int print_config(Config config){
  assert(config != NULL);

  Board board = create_board();
  init_board(board);
  int r, c;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(ATOM(r,c) & config->x){
	board_set_pos(board, (Pos) {r,c}, X);
      } else if(ATOM(r,c) & config->w){
	board_set_pos(board, (Pos) {r,c}, W);	
      } else if(ATOM(r,c) & config->b){
	board_set_pos(board, (Pos) {r,c}, B);
      }
    }
  }
  print_board(board);
  free_board(board);
  
  printf("config->x = %016lx\n", config->x);
  printf("config->w = %016lx\n", config->w);
  printf("config->b = %016lx\n", config->b);
  printf("degree = %d\n",
	 __builtin_popcountl(config->x) +
	 __builtin_popcountl(config->w) +
	 __builtin_popcountl(config->b)
	 );
  return 0;
}

int print_pattern(Pattern pattern){

  Board board = create_board();
  init_board(board);
  int r, c;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(ATOM(r,c) & pattern){
	board_set_pos(board, (Pos) {r,c}, W);
      }
    }
  }
  print_board(board);
  free_board(board);
  printf("pattern = %016lx\n", pattern);
  printf("degree = %d\n", __builtin_popcountl(pattern));

  return 0;
}

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


void *read_dat_from_file(const char *filename, int obj_size, int *count_obj){
  
  //printf("reading data from file %s .....\n", filename);
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
  
  Config data = malloc(lSize);
  fread(data, lSize, 1, fp);

  //printf("read %ld items.\n", lSize/obj_size);
  
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
  size = lSize/sizeof(Example);

  return size;
}
