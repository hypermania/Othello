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
  int r,c;
  for(r=0;r<BOARD_SIZE;r++){
    char rownum[3] = {'0'+r, ' '};
    writecolor(rownum, "52", "46");
    for(c=0;c<BOARD_SIZE;c++){
      switch(board[r][c]){
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

  if(state->turn == 1){
    write(1, "(white's turn)\n", 15);
  } else {
    write(1, "(black's turn)\n", 15);
  }
  print_board(state->board);

  return 0;
}

