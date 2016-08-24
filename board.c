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
  assert(board != NULL);
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
  assert(board != NULL);
  memset(board, 0, BOARD_SIZE_SQR * sizeof(char));
  return 0;
}

int cpy_board(Board dest, Board src){
  assert(dest != NULL);
  assert(src != NULL);
  memcpy(dest, src, BOARD_SIZE_SQR * sizeof(char));
  return 0;
}

int check_pos(Pos pos){
  if(pos.r<0 || pos.c< 0 || pos.r>=BOARD_SIZE || pos.c>=BOARD_SIZE)
    return -1;
  return 0;
}

int check_val(char val){
  if(val != EMPTY && val != W && val != B)
    return -1;
  return 0;
}

int check_side(char side){

  if((side != B) && (side != W))
    return -1;

  return 0;
}

int opposite_side(char side){
  assert(check_side(side) >= 0);
  //return 3-side;
  return OPPOSITE_SIDE(side);
}

char board_get_pos(Board board, Pos pos){
  //assert(board != NULL);
  //assert(check_pos(pos) == 0);

  return board[BOARD_SIZE * pos.r + pos.c];
}

void board_set_pos(Board board, Pos pos, char val){
  assert(board != NULL);
  assert(check_pos(pos) == 0);
  assert(check_val(val) == 0);

  board[BOARD_SIZE * pos.r + pos.c] =  (char) val;
}

int adj_pos(Pos pos, Pos *store){
  assert(check_pos(pos) == 0);  
  assert(store != NULL);
  
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
  assert(board != NULL);
  assert(check_pos(pos) == 0);
  assert(store != NULL);

  int count = 0;
  int direc_h, direc_v;
  for(direc_h=-1; direc_h<=1; direc_h++){
    for(direc_v=-1; direc_v<=1; direc_v++){
      if(direc_h != 0 || direc_v != 0){
	Pos temp = pos;
	temp.r += direc_h;
	temp.c += direc_v;
	if((check_pos(temp) >= 0) && (board_get_pos(board, temp) == EMPTY))
	  store[count++] = temp;
      }
    }
  }
  return count;
}

int adj_given_pos(Board board, Pos pos, Pos *store, char val){
  assert(board != NULL);
  assert(check_pos(pos) == 0);
  assert(check_val(val) == 0);

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
	  if((check_pos(temp) >= 0) && (board_get_pos(board, temp) == val))
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
	  if((check_pos(temp) >= 0) && (board_get_pos(board, temp) == val))
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
	if(board[BOARD_SIZE * (r-0) + (c+1)] == val)
	  store[count++] = (Pos) {r-0, c+1};
	if(board[BOARD_SIZE * (r+1) + (c-0)] == val)
	  store[count++] = (Pos) {r+1, c-0};
	if(board[BOARD_SIZE * (r+1) + (c+1)] == val)
	  store[count++] = (Pos) {r+1, c+1};
	
      } else if(condchi){
	if(board[BOARD_SIZE * (r-0) + (c-1)] == val)
	  store[count++] = (Pos) {r-0, c-1};
	if(board[BOARD_SIZE * (r+1) + (c-1)] == val)
	  store[count++] = (Pos) {r+1, c-1};
	if(board[BOARD_SIZE * (r+1) + (c-0)] == val)
	  store[count++] = (Pos) {r+1, c-0};
	
      } else {
	if(board[BOARD_SIZE * (r-0) + (c-1)] == val)
	  store[count++] = (Pos) {r-0, c-1};
	if(board[BOARD_SIZE * (r-0) + (c+1)] == val)
	  store[count++] = (Pos) {r-0, c+1};
	if(board[BOARD_SIZE * (r+1) + (c-1)] == val)
	  store[count++] = (Pos) {r+1, c-1};
	if(board[BOARD_SIZE * (r+1) + (c-0)] == val)
	  store[count++] = (Pos) {r+1, c-0};
	if(board[BOARD_SIZE * (r+1) + (c+1)] == val)
	  store[count++] = (Pos) {r+1, c+1};
	
      }
    } else if(condrhi){
      if(condclow){
	if(board[BOARD_SIZE * (r-1) + (c-0)] == val)
	  store[count++] = (Pos) {r-1, c-0};
	if(board[BOARD_SIZE * (r-1) + (c+1)] == val)
	  store[count++] = (Pos) {r-1, c+1};
	if(board[BOARD_SIZE * (r-0) + (c+1)] == val)
	  store[count++] = (Pos) {r-0, c+1};
	
      } else if(condchi){
	if(board[BOARD_SIZE * (r-1) + (c-1)] == val)
	  store[count++] = (Pos) {r-1, c-1};
	if(board[BOARD_SIZE * (r-1) + (c-0)] == val)
	  store[count++] = (Pos) {r-1, c-0};
	if(board[BOARD_SIZE * (r-0) + (c-1)] == val)
	  store[count++] = (Pos) {r-0, c-1};
	
      } else {
	if(board[BOARD_SIZE * (r-1) + (c-1)] == val)
	  store[count++] = (Pos) {r-1, c-1};
	if(board[BOARD_SIZE * (r-1) + (c-0)] == val)
	  store[count++] = (Pos) {r-1, c-0};
	if(board[BOARD_SIZE * (r-1) + (c+1)] == val)
	  store[count++] = (Pos) {r-1, c+1};
	if(board[BOARD_SIZE * (r-0) + (c-1)] == val)
	  store[count++] = (Pos) {r-0, c-1};
	if(board[BOARD_SIZE * (r-0) + (c+1)] == val)
	  store[count++] = (Pos) {r-0, c+1};
      }
    } else {
      if(condclow){
	if(board[BOARD_SIZE * (r-1) + (c-0)] == val)
	  store[count++] = (Pos) {r-1, c-0};
	if(board[BOARD_SIZE * (r-1) + (c+1)] == val)
	  store[count++] = (Pos) {r-1, c+1};
	if(board[BOARD_SIZE * (r-0) + (c+1)] == val)
	  store[count++] = (Pos) {r-0, c+1};
	if(board[BOARD_SIZE * (r+1) + (c-0)] == val)
	  store[count++] = (Pos) {r+1, c-0};
	if(board[BOARD_SIZE * (r+1) + (c+1)] == val)
	  store[count++] = (Pos) {r+1, c+1};
	
      } else if(condchi){
	if(board[BOARD_SIZE * (r-1) + (c-1)] == val)
	  store[count++] = (Pos) {r-1, c-1};
	if(board[BOARD_SIZE * (r-1) + (c-0)] == val)
	  store[count++] = (Pos) {r-1, c-0};
	if(board[BOARD_SIZE * (r-0) + (c-1)] == val)
	  store[count++] = (Pos) {r-0, c-1};
	if(board[BOARD_SIZE * (r+1) + (c-1)] == val)
	  store[count++] = (Pos) {r+1, c-1};
	if(board[BOARD_SIZE * (r+1) + (c-0)] == val)
	  store[count++] = (Pos) {r+1, c-0};
      } else {
	if(board[BOARD_SIZE * (r-1) + (c-1)] == val)
	  store[count++] = (Pos) {r-1, c-1};
	if(board[BOARD_SIZE * (r-1) + (c-0)] == val)
	  store[count++] = (Pos) {r-1, c-0};
	if(board[BOARD_SIZE * (r-1) + (c+1)] == val)
	  store[count++] = (Pos) {r-1, c+1};
	if(board[BOARD_SIZE * (r-0) + (c-1)] == val)
	  store[count++] = (Pos) {r-0, c-1};
	if(board[BOARD_SIZE * (r-0) + (c+1)] == val)
	  store[count++] = (Pos) {r-0, c+1};
	if(board[BOARD_SIZE * (r+1) + (c-1)] == val)
	  store[count++] = (Pos) {r+1, c-1};
	if(board[BOARD_SIZE * (r+1) + (c-0)] == val)
	  store[count++] = (Pos) {r+1, c-0};
	if(board[BOARD_SIZE * (r+1) + (c+1)] == val)
	  store[count++] = (Pos) {r+1, c+1};
      }
    }
  } else {

    if(condrlow){
      if(condclow){
	if(board[BOARD_SIZE * (r-0) + (c+1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-0)] == val)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c+1)] == val)
	  count++;
	
      } else if(condchi){
	if(board[BOARD_SIZE * (r-0) + (c-1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-0)] == val)
	  count++;
	
      } else {
	if(board[BOARD_SIZE * (r-0) + (c-1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c+1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-0)] == val)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c+1)] == val)
	  count++;
	
      }
    } else if(condrhi){
      if(condclow){
	if(board[BOARD_SIZE * (r-1) + (c-0)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c+1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c+1)] == val)
	  count++;
	
      } else if(condchi){
	if(board[BOARD_SIZE * (r-1) + (c-1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c-0)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c-1)] == val)
	  count++;
	
      } else {
	if(board[BOARD_SIZE * (r-1) + (c-1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c-0)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c+1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c-1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c+1)] == val)
	  count++;
      }
    } else {
      if(condclow){
	if(board[BOARD_SIZE * (r-1) + (c-0)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c+1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c+1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-0)] == val)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c+1)] == val)
	  count++;
	
      } else if(condchi){
	if(board[BOARD_SIZE * (r-1) + (c-1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c-0)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c-1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-0)] == val)
	  count++;
      } else {
	if(board[BOARD_SIZE * (r-1) + (c-1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c-0)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-1) + (c+1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c-1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r-0) + (c+1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-1)] == val)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c-0)] == val)
	  count++;
	if(board[BOARD_SIZE * (r+1) + (c+1)] == val)
	  count++;
      }
    }

  }

  return count;
}

int count_pieces(Board board, char val){
  assert(board != NULL);
  assert(check_val(val) == 0);

  int r, c;
  int count = 0;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(board_get_pos(board, (Pos) {r,c}) == val)
	count++;
    }
  }

  
  return count;
}

int piece_diff(Board board, char val1, char val2){
  assert(board != NULL);
  assert(check_val(val1) == 0);
  assert(check_val(val2) == 0);

  int r, c;
  int count = 0;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      char val = board_get_pos(board, (Pos) {r,c});
      if(val == val1){
	count++;
      } else if(val == val2){
	count--;
      }
    }
  }

  
  return count;


}
