#include "board.h"


// board[r][c]
// 0 for empty, 1 for white, 2 for black

Board create_board(void){
  /*
  Board board = malloc(BOARD_SIZE * sizeof(int *));
  int r;
  for(r=0;r<BOARD_SIZE;r++){
    board[r] = malloc(BOARD_SIZE * sizeof(int));
  }
  */
  Board board = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(char));
  return board;
}

int free_board(Board board){
  if(board == NULL)
    return -1;
  /*
  int r;
  for(r=0;r<BOARD_SIZE;r++){
    free(board[r]);
  }
  */
  free(board);
  return 0;
}

int init_board(Board board){
  if(board == NULL)
    return -1;
  /*
  int i;
  for(i=0;i<BOARD_SIZE_SQR;i++){
    board[i] = X;
  }
  */
  memset(board, 0, BOARD_SIZE_SQR * sizeof(char));
  return 0;
}

int check_pos(Pos pos){
  if(pos.r<0 || pos.c< 0 || pos.r>=BOARD_SIZE || pos.c>=BOARD_SIZE)
    return -1;
  return 0;
}

int check_val(char val){
  if(val != X && val != W && val != B)
    return -1;
  return 0;
}

int check_side(char side){

  if((side != B) && (side != W))
    return -1;

  return 0;
}


char board_get_pos(Board board, Pos pos){

  if(board == NULL){
    //printf("board == NULL\n");
    return -1;
  }

  if(check_pos(pos)<0){
    //printf("check_pos(pos) < 0, pos = (%d,%d)\n", pos.r, pos.c);
    return -2;
  }

  return board[BOARD_SIZE * pos.r + pos.c];
}

int board_set_pos(Board board, Pos pos, char val){
  if(board == NULL)
    return -1;
  if(check_pos(pos)<0)
    return -2;
  if(check_val(val)<0)
    return -3;
  //if(val == W)
  board[BOARD_SIZE * pos.r + pos.c] =  (char) val;
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

  int count = 0;
  int direc_h, direc_v;
  for(direc_h=-1; direc_h<=1; direc_h++){
    for(direc_v=-1; direc_v<=1; direc_v++){
      if(direc_h != 0 || direc_v != 0){
	Pos temp = pos;
	temp.r += direc_h;
	temp.c += direc_v;
	if((check_pos(temp) >= 0) && (board_get_pos(board, temp) == X))
	  store[count++] = temp;
      }
    }
  }
  return count;
}

int adj_given_pos(Board board, Pos pos, Pos *store, char side){
  if(board == NULL)
    return -1;
  if(check_pos(pos)<0)
    return -2;
  /*
  if(store == NULL)
    return -3;
  */
  /*
  if(check_side(side) < 0)
    return -4;
  */

  int count = 0;
  /*
  int direc_h, direc_v;
  Pos temp;
  if(store == NULL){
    for(direc_h=-1; direc_h<=1; direc_h++){
      for(direc_v=-1; direc_v<=1; direc_v++){
	if(direc_h != 0 || direc_v != 0){
	  temp = pos;
	  temp.r += direc_h;
	  temp.c += direc_v;
	  if((check_pos(temp) >= 0) && (board_get_pos(board, temp) == side))
	    count++;
	}
      }
    }
  } else {
    for(direc_h=-1; direc_h<=1; direc_h++){
      for(direc_v=-1; direc_v<=1; direc_v++){
	if(direc_h != 0 || direc_v != 0){
	  temp = pos;
	  temp.r += direc_h;
	  temp.c += direc_v;
	  if((check_pos(temp) >= 0) && (board_get_pos(board, temp) == side))
	    store[count++] = temp;
	}
      }
    }
  }

  */

  int r = pos.r; int c = pos.c;
  int condrlow = r==0; int condclow = c==0; int condrhi = r==BOARD_SIZE-1; int condchi = c==BOARD_SIZE-1;

  if(store != NULL){
    if(condrlow){
      if(condclow){
	if(board[BOARD_SIZE * (r-0) + (c+1)] == side)
	  store[count++] = (Pos) {r-0, c+1};
	if(board[BOARD_SIZE * (r+1) + (c-0)] == side)
	  store[count++] = (Pos) {r+1, c-0};
	if(board[BOARD_SIZE * (r+1) + (c+1)] == side)
	  store[count++] = (Pos) {r+1, c+1};
	
      } else if(condchi){
	if(board[BOARD_SIZE * (r-0) + (c-1)] == side)
	  store[count++] = (Pos) {r-0, c-1};
	if(board[BOARD_SIZE * (r+1) + (c-1)] == side)
	  store[count++] = (Pos) {r+1, c-1};
	if(board[BOARD_SIZE * (r+1) + (c-0)] == side)
	  store[count++] = (Pos) {r+1, c-0};
	
      } else {
	if(board[BOARD_SIZE * (r-0) + (c-1)] == side)
	  store[count++] = (Pos) {r-0, c-1};
	if(board[BOARD_SIZE * (r-0) + (c+1)] == side)
	  store[count++] = (Pos) {r-0, c+1};
	if(board[BOARD_SIZE * (r+1) + (c-1)] == side)
	  store[count++] = (Pos) {r+1, c-1};
	if(board[BOARD_SIZE * (r+1) + (c-0)] == side)
	  store[count++] = (Pos) {r+1, c-0};
	if(board[BOARD_SIZE * (r+1) + (c+1)] == side)
	  store[count++] = (Pos) {r+1, c+1};
	
      }
    } else if(condrhi){
      if(condclow){
	if(board[BOARD_SIZE * (r-1) + (c-0)] == side)
	  store[count++] = (Pos) {r-1, c-0};
	if(board[BOARD_SIZE * (r-1) + (c+1)] == side)
	  store[count++] = (Pos) {r-1, c+1};
	if(board[BOARD_SIZE * (r-0) + (c+1)] == side)
	  store[count++] = (Pos) {r-0, c+1};
	
      } else if(condchi){
	if(board[BOARD_SIZE * (r-1) + (c-1)] == side)
	  store[count++] = (Pos) {r-1, c-1};
	if(board[BOARD_SIZE * (r-1) + (c-0)] == side)
	  store[count++] = (Pos) {r-1, c-0};
	if(board[BOARD_SIZE * (r-0) + (c-1)] == side)
	  store[count++] = (Pos) {r-0, c-1};
	
      } else {
	if(board[BOARD_SIZE * (r-1) + (c-1)] == side)
	  store[count++] = (Pos) {r-1, c-1};
	if(board[BOARD_SIZE * (r-1) + (c-0)] == side)
	  store[count++] = (Pos) {r-1, c-0};
	if(board[BOARD_SIZE * (r-1) + (c+1)] == side)
	  store[count++] = (Pos) {r-1, c+1};
	if(board[BOARD_SIZE * (r-0) + (c-1)] == side)
	  store[count++] = (Pos) {r-0, c-1};
	if(board[BOARD_SIZE * (r-0) + (c+1)] == side)
	  store[count++] = (Pos) {r-0, c+1};
      }
    } else {
      if(condclow){
	if(board[BOARD_SIZE * (r-1) + (c-0)] == side)
	  store[count++] = (Pos) {r-1, c-0};
	if(board[BOARD_SIZE * (r-1) + (c+1)] == side)
	  store[count++] = (Pos) {r-1, c+1};
	if(board[BOARD_SIZE * (r-0) + (c+1)] == side)
	  store[count++] = (Pos) {r-0, c+1};
	if(board[BOARD_SIZE * (r+1) + (c-0)] == side)
	  store[count++] = (Pos) {r+1, c-0};
	if(board[BOARD_SIZE * (r+1) + (c+1)] == side)
	  store[count++] = (Pos) {r+1, c+1};
	
      } else if(condchi){
	if(board[BOARD_SIZE * (r-1) + (c-1)] == side)
	  store[count++] = (Pos) {r-1, c-1};
	if(board[BOARD_SIZE * (r-1) + (c-0)] == side)
	  store[count++] = (Pos) {r-1, c-0};
	if(board[BOARD_SIZE * (r-0) + (c-1)] == side)
	  store[count++] = (Pos) {r-0, c-1};
	if(board[BOARD_SIZE * (r+1) + (c-1)] == side)
	  store[count++] = (Pos) {r+1, c-1};
	if(board[BOARD_SIZE * (r+1) + (c-0)] == side)
	  store[count++] = (Pos) {r+1, c-0};
      } else {
	if(board[BOARD_SIZE * (r-1) + (c-1)] == side)
	  store[count++] = (Pos) {r-1, c-1};
	if(board[BOARD_SIZE * (r-1) + (c-0)] == side)
	  store[count++] = (Pos) {r-1, c-0};
	if(board[BOARD_SIZE * (r-1) + (c+1)] == side)
	  store[count++] = (Pos) {r-1, c+1};
	if(board[BOARD_SIZE * (r-0) + (c-1)] == side)
	  store[count++] = (Pos) {r-0, c-1};
	if(board[BOARD_SIZE * (r-0) + (c+1)] == side)
	  store[count++] = (Pos) {r-0, c+1};
	if(board[BOARD_SIZE * (r+1) + (c-1)] == side)
	  store[count++] = (Pos) {r+1, c-1};
	if(board[BOARD_SIZE * (r+1) + (c-0)] == side)
	  store[count++] = (Pos) {r+1, c-0};
	if(board[BOARD_SIZE * (r+1) + (c+1)] == side)
	  store[count++] = (Pos) {r+1, c+1};
      }
    }
  } else {

    if(condrlow){
      if(condclow){
	if(board[BOARD_SIZE * (r-0) + (c+1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-0)] == side)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c+1)] == side)
	  count++;
	
      } else if(condchi){
	if(board[BOARD_SIZE * (r-0) + (c-1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-0)] == side)
	  count++;
	
      } else {
	if(board[BOARD_SIZE * (r-0) + (c-1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c+1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-0)] == side)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c+1)] == side)
	  count++;
	
      }
    } else if(condrhi){
      if(condclow){
	if(board[BOARD_SIZE * (r-1) + (c-0)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c+1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c+1)] == side)
	  count++;
	
      } else if(condchi){
	if(board[BOARD_SIZE * (r-1) + (c-1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c-0)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c-1)] == side)
	  count++;
	
      } else {
	if(board[BOARD_SIZE * (r-1) + (c-1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c-0)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c+1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c-1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c+1)] == side)
	  count++;
      }
    } else {
      if(condclow){
	if(board[BOARD_SIZE * (r-1) + (c-0)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c+1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c+1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-0)] == side)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c+1)] == side)
	  count++;
	
      } else if(condchi){
	if(board[BOARD_SIZE * (r-1) + (c-1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c-0)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c-1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-0)] == side)
	  count++;
      } else {
	if(board[BOARD_SIZE * (r-1) + (c-1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c-0)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c+1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c-1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c+1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-1)] == side)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-0)] == side)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c+1)] == side)
	  count++;
      }
    }

  }

  return count;
}

