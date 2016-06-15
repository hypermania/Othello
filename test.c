#include "test.h"

int test_genconf(void){

  int i; int j;
  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      printf("ATOM(%d,%d) = %016lx\n", i, j,  ATOM(i,j));
    }
  }

  printf("init state board and convert it to config:\n");
  State state = create_state();
  init_state(state);
  Config config = create_and_init_config();
  board_to_conf(state->board, config);

  printf("config->x = %016lx\n",config->x);
  printf("config->w = %016lx\n",config->w);
  printf("config->b = %016lx\n",config->b);

  unsigned long int x, w, b;
  x = config->x;
  w = config->w;
  b = config->b;
  
  printf("x&b = %016lx, x&w = %016lx, b&w = %016lx\n", x&b, x&w, b&w);
  printf("x|w|b = %016lx\n", x|w|b);
  printf("x^w^b = %016lx\n", x^w^b);

  int match;
  Config boards = create_and_init_config_list(10);

  board_to_conf(state->board, boards);
  init_config(config);
  config->x = 0x0000000020000000;
  config->b = 0x0000000810000000;
  
  match = match_conf(boards, config, 1);
  printf("match = %d\n", match);

  free_state(state);
  free_config(config);
  free_config(boards);
  
  return 0;
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
  
  
  for(i=0;i<times;i++){
    free_state(naive_table[i]);
  }

  free_table(table);
  return 0;
}

