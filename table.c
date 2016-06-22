#include "table.h"

Node create_node_from_state(State state){
  Node node = malloc(sizeof(Node_store));
  node->state = create_state();
  cpy_state(node->state, state);
  //node->prev = node;
  node->next = NULL;
  return node;
}

Node create_head_node(void){
  Node node = malloc(sizeof(Node_store));
  node->state = NULL;
  node->prev = node;
  node->next = NULL;
  return node;
}


int append_node_from_state(Node node, State state){
  if(node == NULL)
    return -1;

  while(node->next != NULL){
    node = node->next;
  }
  Node next = create_node_from_state(state);
  node->next = next;
  next->prev = node;
  return 0;
}

int delete_node(Node node){
  if(node == NULL)
    return -1;
  
  free_state(node->state);

  Node prev, next;
  prev = (Node) node->prev;
  next = (Node) node->next;
  
  if(node->next == NULL){
    prev->next = NULL;
    free(node);
    return 0;
  } else {
    prev->next = (void *)next;
    next->prev = (void *)prev;
    free(node);
    return 0;
  }
  return 0;
}

Table create_and_init_table(int table_size){
  Table table = (Table) malloc(sizeof(Table_store));
  //table->max = max_states;
  table->size = table_size;
  
  table->total = 0;
  table->buckets = (Node *) malloc(table_size * sizeof(Node_store));
  int i;
  for(i=0;i<table_size;i++){
    table->buckets[i] = create_head_node();
  }
  table->record = (char *) malloc(table_size * sizeof(char));
  memset(table->record, 0, table_size * sizeof(char));
  return table;
}

int free_table(Table table){
  if(table == NULL)
    return -1;

  // iterate over table
  int i;
  for(i=0;i<table->size;i++){
    int number_of_state = table->record[i];
    //iterate over node
    while((number_of_state--) > 0){
      delete_node(table->buckets[i]->next);
    }
    delete_node(table->buckets[i]);
  }
  free(table->buckets);
  free(table->record);
  free(table);
  return 0;
}

int table_state_bucket_number(Table table, State state){
  if(table == NULL)
    return -1;
  if(state == NULL)
    return -2;

  return hash_board(state->board) % table->size;
}

Node table_contains_state(Table table, State state){
  if(table == NULL || state == NULL)
    return NULL;
  /*
  if(state == NULL)
  return NULL; */
  //printf("table contains state error message:\n");
  /*
  int i;
  for(i=0;i<4;i++){
    //printf("i=%d:\n", i);
    Node ptr = table->buckets[i];
    while(ptr != NULL){
      //printf("(ptr,state,prev,next)=(%lx,%lx,%lx,%lx)   ", (long int) ptr, (long int) ptr->state, (long int) ptr->prev, (long int) ptr->next);
      ptr = ptr->next;
    }
    // printf("\n");
  }
  */
  int bucket_num = table_state_bucket_number(table, state);

  if(table->record[bucket_num] == 0){
    return 0;
  } else {
    Node ptr = table->buckets[bucket_num]->next;
    while(1){
      //printf("ptr = %016lx\n", (long int) ptr);
      //printf("memcmp = %d\n", memcmp(state->board, ptr->state->board, BOARD_SIZE_SQR * sizeof(char)));
      //printf("Point 1\n");
      if(memcmp(state->board, ptr->state->board, BOARD_SIZE_SQR * sizeof(char))){
	ptr = (Node) (ptr->next);
	if(ptr == NULL)
	  break;
      } else {
	return ptr;
      }
    }
  }
  return NULL;
}

int table_insert_state(Table table, State state){
  if(table == NULL)
    return -1;
  if(state == NULL)
    return -2;

  int bucket_num;
  if(table_contains_state(table, state)){
    return 1;
  } else {
    bucket_num = table_state_bucket_number(table, state);
    append_node_from_state(table->buckets[bucket_num], state);
    (table->record[bucket_num])++;
    table->total++;	    
  }
  //printf("table->record[%d] = %d\n", bucket_num,(int) table->record[bucket_num]);  
  return 0;
}


int table_delete_state(Table table, State state){
  if(table == NULL)
    return -1;
  if(state == NULL)
    return -2;

  Node ptr;
  if((ptr = table_contains_state(table, state))){

    int bucket_num = table_state_bucket_number(table, state);
    delete_node(ptr);
    table->record[bucket_num]--;
    table->total--;
  } 
  return 0;
}

