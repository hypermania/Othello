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
  writecolor("  0 1 2 3 4 5 6 7 ", "52", "46");
  write(1, "\n", 1);
  int r,c = 0;
  for(r=0;r<BOARD_SIZE;r++){
    char rownum[3] = {'0'+r, ' '};
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
      printf("%2d:(%d,%d)  ", j, moves[j].r, moves[j].c);
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
    /* swapping adjacent char
    char c;
    c = buff[2*i+1];
    buff[2*i+1] = buff[2*i+0];
    buff[2*i+0] = c;
    */
    buff[2*i+1] ^= buff[2*i+0];
    buff[2*i+0] ^= buff[2*i+1];
    buff[2*i+1] ^= buff[2*i+0];
  }
  return (Pos *)buff;
}

int print_config(Config config){
  assert(config != NULL);
  
  printf("config->x = %016lx\n", config->x);
  printf("config->w = %016lx\n", config->w);
  printf("config->b = %016lx\n", config->b);
  printf("degree = %d\n",
	 __builtin_popcountl(config->x) +
	 __builtin_popcountl(config->w) +
	 __builtin_popcountl(config->b)
	 );
  printf("is_board = %d\n", check_board_as_config(*config));
  
  return 0;
}
