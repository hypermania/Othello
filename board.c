#include "board.h"


// board[r][c]
// 0 for empty, 1 for white, 2 for black

Board create_board(void){
  Board board = malloc(BOARD_SIZE * sizeof(int *));
  int r;
  for(r=0;r<BOARD_SIZE;r++){
    board[r] = malloc(BOARD_SIZE * sizeof(int));
  }
  return board;
}

int free_board(Board board){
  if(board == NULL)
    return -1;
  int r;
  for(r=0;r<BOARD_SIZE;r++){
    free(board[r]);
  }
  free(board);
  return 0;
}

int init_board(Board board){
  if(board == NULL)
    return -1;
  int r, c;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      board[r][c] = X;
    }
  }
  return 0;
}

int check_pos(Pos pos){
  if(pos.r<0 || pos.c< 0 || pos.r>=BOARD_SIZE || pos.c>=BOARD_SIZE)
    return -1;
  return 0;
}

int check_val(int val){
  if(val != X && val != W && val != B)
    return -1;
  return 0;
}

int check_side(int side){
  if(!(side == B || side == W))
    return -1;
  return 0;
}


int board_get_pos(Board board, Pos pos){
  if(board == NULL)
    return -1;
  if(check_pos(pos)<0)
    return -2;
  return board[pos.r][pos.c];
}

int board_set_pos(Board board, Pos pos, int val){
  if(board == NULL)
    return -1;
  if(check_pos(pos)<0)
    return -2;
  if(check_val(val)<0)
    return -3;
  board[pos.r][pos.c] = val;
  return 0;
}

int adj_pos(Pos pos, Pos *store){
  if(check_pos(pos)<0)
    return -1;
  if(store == NULL)
    return -2;
  
  int count = 0;
  int direc_h, direc_v;
  for(direc_h=-1; direc_h<=1; direc_h++){
    for(direc_v=-1; direc_v<=1; direc_v++){
      if(direc_h != 0 || direc_v != 0){
	Pos temp = pos;
	temp.r += direc_h;
	temp.c += direc_v;
	if(check_pos(temp) >= 0)
	  store[count++] = temp;
      }
    }
  }
  return count;
}

int adj_empty_pos(Board board, Pos pos, Pos *store){
  if(board == NULL)
    return -1;
  if(check_pos(pos) < 0)
    return -2;
  if(store == NULL)
    return -3;

  Pos adjs[ADJ_SIZE];
  int num = adj_pos(pos, adjs);
  int i, count = 0;
  for(i=0;i<num;i++){
    if(board_get_pos(board, adjs[i]) == X)
      store[count++] = adjs[i];
  }
  return count;
}
