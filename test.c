#include "test.h"

int test_genconf(void){

  int r, c;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      Config_store conf;
      conf.x = ATOM(r, c);
      conf.w = 0;
      conf.b = 0;

      Config_store diag = reflect_diag(conf);
      if(ATOM(c,r) != diag.x){
	printf("reflect error\n");
	return 1;
      }
      
      Config_store rdiag = reflect_rdiag(conf);
      if(ATOM(BOARD_SIZE-r-1, BOARD_SIZE-c-1) != rdiag.x){
	printf("reflect error\n");
	return 1;
      }

      Config_store bdiag = reflect_rdiag(reflect_diag(conf));
      if(ATOM(BOARD_SIZE-c-1, BOARD_SIZE-r-1) != bdiag.x){
	printf("reflect error\n");
	return 1;
      }
    }
  }

  /*
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      printf("ATOM(%d,%d) = %016lx\n", r, c,  ATOM(r,c));
    }
  }
  */
  State state = create_state();
  init_state(state);
  Config config = create_and_init_config();
  board_to_conf(state->board, config);

  if(config->x != 0xffffffe7e7ffffff){
    printf("config->x = %016lx\n",config->x);
    return 1;
  }
  if(config->w != 0x0000001008000000){
    printf("config->w = %016lx\n",config->w);
    return 1;
  }
  if(config->b != 0x0000000810000000){
    printf("config->b = %016lx\n",config->b);
    return 1;
  }
  
  unsigned long int x, w, b;
  x = config->x;
  w = config->w;
  b = config->b;
  if((x&b) != 0 || (x&w) != 0 || (b&w) != 0){
    printf("x&b = %016lx, x&w = %016lx, b&w = %016lx\n", x&b, x&w, b&w);
    return 1;
  }
  if((x|w|b) != 0xffffffffffffffff){
    printf("x|w|b = %016lx\n", x|w|b);
    return 1;
  }
  if((x^w^b) != 0xffffffffffffffff){
    printf("x^w^b = %016lx\n", x^w^b);
    return 1;
  }


  Config boards = create_and_init_config_list(10);

  board_to_conf(state->board, boards);
  init_config(config);
  config->x = 0x0000000020000000;
  config->b = 0x0000000810000000;
  
  int match = match_one_conf(boards, config);
  int symm_match = symmetric_match_one_conf(boards, config);
  
  if(match != 1){
    printf("match = %d\n", match);
    return 1;
  }
  if(symm_match != 4){
    printf("symm_match = %d\n", symm_match);
    return 1;
  }

  int n;
  Config variations = list_variations(0x000000000000000f, &n);
  int i;
  printf("n = %d\n", n);
  for(i=0;i<n;i++){
    print_config(&variations[i]);
  }

  
  free_state(state);
  free_config(config);
  free_config(boards);
  
  return 0;
}



int test_board(void){
  Board board = create_board();
  init_board(board);
  
  int naive_board[BOARD_SIZE][BOARD_SIZE];
  char vals[3] = {X, W, B};
  int i, j;
  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      int r = rand() % 3;
      naive_board[i][j] = vals[r];
    }
  }

  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      if(board_get_pos(board, (Pos) {i,j}) != X)
	return -1;
      board_set_pos(board, (Pos) {i,j}, naive_board[i][j]);
    }
  }
  
  int ret1;
  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      ret1 = board_get_pos(board, (Pos) {i,j});
      if(ret1 != naive_board[i][j])
	return -1;
    }
  }

  //printf("%08x\n" ,hash_board(board));
  //print_board(board);
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


int test_bitboard(void){
  BitBoard board = new_empty_bitboard();

  int naive_board[BOARD_SIZE][BOARD_SIZE];
  char vals[3] = {X, W, B};
  int i, j;
  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      int r = rand() % 3;
      naive_board[i][j] = vals[r];
    }
  }


  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      if(bitboard_get_pos_nonref(board, pos_mask[i][j]) != X)
	return -1;
      bitboard_set_pos(&board, pos_mask[i][j], naive_board[i][j]);
    }
  }

  int ret1;
  for(i=0;i<BOARD_SIZE;i++){
    for(j=0;j<BOARD_SIZE;j++){
      ret1 = bitboard_get_pos_nonref(board, pos_mask[i][j]);
      if(ret1 != naive_board[i][j])
	return -1;
    }
  }

  //print_bitboard(board);
  
  return 0;
}

int test_bitstate(void){
  BitState *state = create_initial_bitstate();

  /*
  long int stage_count[60];
  long int stage_movec[60];

  int stage;
  for(stage=0;stage<60;stage++){
    stage_count[stage] = 0;
    stage_movec[stage] = 0;
  }
  */
  
  int times = 1 << 21;
  int i;
  for(i=0;i<times;i++){
    init_bitstate(state);
    
    while(!bitstate_final(state)){
      int movec;
      bitstate_allowed_moves(state, &movec);

      //stage = __builtin_popcountll(state->board.w) + __builtin_popcountll(state->board.b) - 4;
      //stage_count[stage]++;
      //stage_movec[stage] += movec;
      
      if(movec > 0){
	bitstate_place_piece(state, 0);
      } else {
	bitstate_skip_turn(state);
      }

    }
    //print_bitboard(state->board);
  }

  /*
  for(stage=0;stage<60;stage++){
    printf("%d pieces: avg_movec = %lf\n", stage+4, (double)stage_movec[stage]/(double)stage_count[stage]);
  }
  */
  
  return 0;
}

int test_state(void){
  State state = create_state();

  int times = 1 << 21;
  int i;
  for(i=0;i<times;i++){
    init_state(state);

    while(!state_final(state)){
      int movec;
      allowed_moves_inplace(state, &movec);
      if(movec > 0){
	place_piece_indexed(state, 0);
      } else {
	skip_turn(state);
      }
    }
    //print_state(state);
  }

  /*
  printf("init state\n");
  init_state(state);
  printf("\n");

  printf("basic info: memory plan for State\n");
  printf("board:%ld\n", (long int) ((void *)(state->board) - (void *)(state)));
  printf("turn:%ld\n", (long int) ((void *)&(state->turn) - (void *)(state)));
  printf("control:%ld\n", (long int) ((void *)&(state->control) - (void *)(state)));
  printf("movec:%ld\n", (long int) ((void *)&(state->movec) - (void *)(state)));
  printf("moves:%ld\n", (long int) ((void *)(state->moves) - (void *)(state)));

  printf("positions:%ld\n", (long int) ((void *)(state->positions) - (void *)(state)));
  printf("seq:%ld\n", (long int) ((void *)(state->seq) - (void *)(state)));

  printf("seq_num:%ld\n", (long int) ((void *)&(state->seq_num) - (void *)(state)));
  printf("score:%ld\n", (long int) ((void *)&(state->score) - (void *)(state)));
  
  printf("total size:%ld\n", sizeof(State_store));
  printf("\n");

  printf("pivot size:%ld\n", (sizeof state->board) + (sizeof state->turn));
  */
  

  free_state(state);

  return 0;
}

int test_table(void){
  const int times = 1 << 10;
  const int size = 1 << 14;
  
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
      if((movec = allowed_moves(naive_table[i], alm)) > 0){
	place_piece(naive_table[i], alm[rand() % movec]);
	//state_switch_turn(naive_table[i]);
      } else {
	skip_turn(naive_table[i]);
      }

      if(rand() % 15 == 0){
	break;
      }
    }
  }
  printf("\n");
  
  printf("test hash function given the states\n");
  for(i=0;i<times;i++){
    table_state_bucket_number(table, naive_table[i]);
  }
  printf("\n");

  printf("inserting the random states\n");
  for(i=0;i<times;i++){
    table_insert_state(table, naive_table[i]);
  }
  printf("\n");
  
  printf("check containment of inserted states\n");  
  for(i=0;i<times;i++){
    void * result = table_contains_state(table, naive_table[i]);
    if(result == NULL){
      printf("case %d error\n", i);
      exit(0);
    }
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

  printf("table->total = %d\n", table->total);
  printf("\n");


  printf("deleting states\n\n");
  for(i=0;i<table->size;i++){
    if(table->record[i]){
      Node node = table->buckets[i];
      while(node->next != NULL){
	table_delete_state(table, ((Node)node->next)->state);
      }
    }
  }

  printf("deleted state from table, table->total = %d\n", table->total);

  
  for(i=0;i<times;i++){
    free_state(naive_table[i]);
  }

  free_table(table);



  table = create_and_init_table(size);

  State state = create_state();
  init_state(state);
  
  while(!state_final(state)){
    table_get_state(table, state);
    int movec;
    allowed_moves_inplace(state, &movec);
    if(movec == 0){
      skip_turn(state);
    } else {
      place_piece_indexed(state, rand() % movec);
    }
    if(state->seq_num == 20)
      break;
  }

  State head = 0;
  
  printf("print states\n\n");
  for(i=0;i<table->size;i++){
    if(table->record[i]){
      Node node = table->buckets[i];
      while(node->next != NULL){
	print_state(((Node)node->next)->state);
	head = ((Node)node->next)->state;
	node = node->next;
      }
    }
  }

  printf("head:\n");
  print_state(head);
  
  printf("delete everything before head:\n");
  table_free_nonreachable_state(table, head);

  printf("print states\n\n");
  for(i=0;i<table->size;i++){
    if(table->record[i]){
      printf("record[%d] = %d\n", i, table->record[i]);
      Node node = table->buckets[i];
      while(node->next != NULL){
	print_state(((Node)node->next)->state);
	head = ((Node)node->next)->state;
	node = node->next;
      }
    }
  }
    
  free_state(state);
  free_table(table);

  return 0;
}

