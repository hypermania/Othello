#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "board.h"
#include "io.h"
//#include "game.h"
#include "ai.h"
#include "table.h"

int run_game(int print_endgame_flag, int print_midgame_flag, int human_player_flag, int depthw, int depthb);
int test_board(void);
int test_state(void);
int test_table(void);
void print_options(Pos *moves, int movec);
int get_human_repsonse(int movec);

int main(int argc, char **argv){
  // set up random number generator
  struct timeval t;
  gettimeofday(&t, NULL);
  //srand((long int) t.tv_usec);
  srand((long int) 100);

  // run the game
  run_game(1,1,1,7,0);
  
  // run tests
  //printf("test_board = %d\n", test_board());
  //printf("test_state = %d\n", test_state());
  //printf("test_table = %d\n", test_table());
  /*
  int i;
  for(i=0;i<100;i++){
    test_board();
  }
  */

  //printf("%lu\n",sizeof(State_store));
  
  exit(0);  
}

void print_options(Pos *moves, int movec){
  int i;
  for(i=0;i<movec;i++){
    printf("%d:(%d,%d)\n", i, moves[i].r, moves[i].c);
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

int run_game(int print_endgame_flag, int print_midgame_flag, int human_player_flag, int depthw, int depthb){

  
  State state = create_state();
  Pos moves[POS_STORE_SIZE]; int movec;
  init_state(state);
  while(!state_final(state)){
    if(print_midgame_flag)
      print_state(state);
    
    movec = allowed_moves(state, moves, state->turn);
    if(movec == 0){
      if(print_midgame_flag)
	printf("Turn skipped.\n");
      state_switch_turn(state);
    } else {
      int r;
      if(human_player_flag){
	if(state->turn == B){
	  print_options(moves, movec);
	  r = get_human_response(movec);
	} else {
	  r = best_next_state(state, moves, movec, depthw);
	}
      } else {
	if(state->turn == B){
	  r = best_next_state(state, moves, movec, depthb);
	} else {
	  r = best_next_state(state, moves, movec, depthw);
	}
      }

      place_piece(state, moves[r], state->turn);
      state_switch_turn(state);
      
      if(print_midgame_flag)
	printf("(makes move at (%d,%d))\n", moves[r].r, moves[r].c);
      
    }

  }
  if(print_midgame_flag)
    print_state(state);

  
  if(print_endgame_flag){
    
    int wp = count_pieces(state, W);
    int bp = count_pieces(state, B);
    if(wp > bp){
      printf("White wins: %d - %d\n", wp, bp);
    } else if(wp < bp){
      printf("Black wins: %d - %d\n", wp, bp);
    } else {
      printf("Draw: %d - %d\n", wp, bp);
    }
  }

  return 0;

  /*
  Game game = create_game();
  init_game(game);
  
  int r = 0;
  while(is_end_of_game(game) == 0){
    if(print_midgame_flag){
      printf("Turn %d\n", game->turns);
      print_state(game->current);
    }

    if(require_input(game) == 1){

      if(game->status == W){
	r = best_next_state(game->current, game->allowed_moves, game->allowed_movec, depthw);
	//r = rand() % game->allowed_movec;
      }
      if(game->status == B){

	if(human_player_flag){
	  printf("This is your turn. Enter number to place your piece.\n");
	  
	  int i;
	  for(i=0;i<game->allowed_movec;i++){
	    printf("%d:(%d,%d)\n", i, game->allowed_moves[i].r, game->allowed_moves[i].c);
	  }
	  while(1){
	    int ret = scanf("%d", &r);
	    if(ret < 1){
	      printf("Invalid input. Try again.\n");
	      continue;
	    }
	    if(r>=game->allowed_movec){
	      printf("Invalid choice. Try again.\n");
	      continue;
	    }
	    break;
	  }
	} else {
	  r = best_next_state(game->current, game->allowed_moves, game->allowed_movec, depthb);
	  //r = rand() % game->allowed_movec;
	}

      }
      make_move(game, r);
    } else {
      make_skip(game);
    }
    if(print_midgame_flag)
      write(1, "\n", 1);
  }
  end_game(game);

  
  if(print_midgame_flag)
    print_state(game->current);

  free_game(game);

  return 0;

  */
}

int test_board(void){
  Board board = create_board();

  int naive_board[BOARD_SIZE][BOARD_SIZE];
  int i, j;
  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      naive_board[i][j] = rand() % 3;
    }
  }
  
  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      if(board_get_pos(board, (Pos) {i,j}) != X)
	return -1;
      if(board_set_pos(board, (Pos) {i,j}, naive_board[i][j]))
	return -1;
    }
  }

  int ret1;
  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      if((ret1 = board_get_pos(board, (Pos) {i,j})) < 0)
	 return -1;
      if(ret1 != naive_board[i][j])
	return -1;
    }
  }

  printf("%08x\n" ,hash_board(board));
  print_board(board);
  /*
  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      if(adj_given_pos(board, (Pos) {i,j}, NULL, B) == -1)
	return -1;
    }
  }
  */
  
  free_board(board);
  return 0;
}

int test_state(void){

  //printf("create state\n");
  State state = create_state();
  //printf("\n");
  
  printf("init state\n");
  init_state(state);
  printf("\n");

  printf("basic info: memory plan for State\n");
  printf("board:%ld\n", (long int) ((void *)(state->board) - (void *)(state)));
  printf("turn:%ld\n", (long int) ((void *)&(state->turn) - (void *)(state)));
  printf("control:%ld\n", (long int) ((void *)&(state->control) - (void *)(state)));
  printf("movec:%ld\n", (long int) ((void *)&(state->movec) - (void *)(state)));
  printf("moves:%ld\n", (long int) ((void *)(state->moves) - (void *)(state)));
  //printf("scores:%ld\n", (long int) ((void *)(state->scores) - (void *)(state)));
  printf("positions:%ld\n", (long int) ((void *)(state->positions) - (void *)(state)));
  printf("seq:%ld\n", (long int) ((void *)(state->seq) - (void *)(state)));

  printf("seq_num:%ld\n", (long int) ((void *)&(state->seq_num) - (void *)(state)));
  printf("total size:%d\n", (int)sizeof(State_store));
  printf("\n");


  printf("test fill_trans:\n");
  fill_trans(state);
  printf("movec = %d\n", state->movec);
  int i;
  for(i=0;i<state->movec;i++){
    printf("moves[%d] = (%d,%d)\n", i, state->moves[i].r, state->moves[i].c);
    print_board(state->positions[i]);
  }

  
  free_state(state);


  
  /*
  int times = 1 << 0;
  int i;
  printf("randomly generating states\n");
  State naive_table[times];
  for(i=0;i<times;i++){
    naive_table[i] = create_state();
    init_state(naive_table[i]);
    Pos alm[32]; int movec;
    //movec = allowed_moves(naive_table[i], alm, naive_table[i]->turn);
    //place_piece(naive_table[i], alm[rand() % movec], naive_table[i]->turn);    

    while(!state_final(naive_table[i])){
      if((movec = allowed_moves(naive_table[i], alm, naive_table[i]->turn)) > 0){
	place_piece(naive_table[i], alm[rand() % movec], naive_table[i]->turn);
	state_switch_turn(naive_table[i]);
      } else {
	state_switch_turn(naive_table[i]);
      }
    }

    print_state(naive_table[i]);
  }

  
  for(i=0;i<times;i++){
    free_state(naive_table[i]);
  }
  */  


  


  return 0;
}

int test_table(void){
  int times = 1 << 18;
  int size = 1 << 22;
  
  printf("create and init table\n");
  Table table = create_and_init_table(size);
  printf("\n");

  printf("basic table info\n");
  printf("table->size = %d\n",table->size);
  printf("table->total = %d\n",table->total);
  printf("\n");

  
  printf("randomly generating states\n");
  int i; State naive_table[times];
  for(i=0;i<times;i++){
    naive_table[i] = create_state();
    init_state(naive_table[i]);
    Pos alm[32]; int movec;
    while(!state_final(naive_table[i])){
      if((movec = allowed_moves(naive_table[i], alm, naive_table[i]->turn)) > 0){
	place_piece(naive_table[i], alm[rand() % movec], naive_table[i]->turn);
	state_switch_turn(naive_table[i]);
      } else {
	state_switch_turn(naive_table[i]);
      }
    }
  }
  /*
  for(i=0;i<times;i++){
    print_state(naive_table[i]);
  }
  */
  printf("\n");
  
  printf("test hash function given the states\n");
  for(i=0;i<times;i++){
    //printf("table state bucket number = %d\n",
    table_state_bucket_number(table, naive_table[i]);
  }
  printf("\n");

  printf("inserting the random states\n");
  for(i=0;i<times;i++){
    //printf("table insert state = %d\n",
    table_insert_state(table, naive_table[i]);
  }
  printf("\n");
  
  printf("check containment of inserted states\n");  
  for(i=0;i<times;i++){
    //printf("table contains state = %lx\n", (long int)
    table_contains_state(table, naive_table[i]);
  }
  printf("\n");

  //int max = 0;
  int total = 0; int count = 0;
  for(i=0;i<size;i++){
    //printf("record[%d] = %d\n", i, (int) table->record[i]);
    if(table->record[i] != 0){
      //max = table->record[i];
      total += table->record[i];
      count ++;
    }
  }
  //printf("max = %d\n", max);
  printf("total = %d\n", total);
  printf("count = %d\n", count);
  printf("avg = %lf\n", ((double)total)/count);
  
  /*
  for(i=0;i<4;i++){
    printf("i=%d:\n", i);
    Node ptr = table->buckets[i];
    while(ptr != NULL){
      printf("(ptr,state,prev,next)=(%lx,%lx,%lx,%lx)   ", (long int) ptr, (long int) ptr->state, (long int) ptr->prev, (long int) ptr->next);
      ptr = ptr->next;
    }
    printf("\n");
  }
  */
  /*  
  printf("delete states\n");
  for(i=0;i<times;i++){
    printf("deleting: hash = %d\n", table_state_bucket_number(table, naive_table[i]));
    printf("(before)table->total = %d\n", table->total);
    printf("table delete state = %d\n", table_delete_state(table, naive_table[i]));
    printf("(after)table->total = %d\n", table->total);
  }
  printf("\n");

  printf("check containment of deleted states\n");
  for(i=0;i<times;i++){
    printf("table contains state = %lx\n", (long int) table_contains_state(table, naive_table[i]));
  }
  printf("\n");

  
  */
  
  for(i=0;i<times;i++){
    free_state(naive_table[i]);
  }

  free_table(table);
  return 0;
}
