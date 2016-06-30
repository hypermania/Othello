#include "table.h"

Node create_node_from_state(State state){
  Node node = malloc(sizeof(Node_store));
  node->state = state;//create_state();
  //cpy_state(node->state, state);
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
  assert(node != NULL);
  assert(state != NULL);
  
  while(node->next != NULL){
    node = node->next;
  }
  Node next = create_node_from_state(state);
  node->next = next;
  next->prev = node;
  return 0;
}

int delete_node(Node node){
  assert(node != NULL);

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

  /*
  sem_t P;
  sem_init(&P, 0, 1);
  mutex = &P;
  */
  
  return table;
}

int free_table(Table table){
  assert(table != NULL);

  // iterate over table
  int i;
  for(i=0;i<table->size;i++){
    int number_of_state = table->record[i];
    //iterate over node
    while((number_of_state--) > 0){
      delete_node(table->buckets[i]->next);
    }
    //delete_node(table->buckets[i]);
    free(table->buckets[i]);
  }
  free(table->buckets);
  free(table->record);
  free(table);
  return 0;
}

int table_state_bucket_number(Table table, State state){
  assert(table != NULL);
  assert(state != NULL);

  return hash_state(state) % table->size;
}

Node table_contains_state(Table table, State state){
  assert(table != NULL);
  assert(state != NULL);

  int bucket_num = table_state_bucket_number(table, state);

  if(table->record[bucket_num] == 0){
    return 0;
  } else {
    Node ptr = table->buckets[bucket_num]->next;
    while(1){
      int diff =
	memcmp(state, ptr->state, BOARD_SIZE_SQR * sizeof(char) + sizeof(short));
      if(diff){
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
  assert(table != NULL);
  assert(state != NULL);


  int bucket_num;
  if(table_contains_state(table, state)){
    return 1;
  } else {
    bucket_num = table_state_bucket_number(table, state);
    append_node_from_state(table->buckets[bucket_num], state);
    (table->record[bucket_num])++;
    table->total++;	    
  }

  
  return 0;
}


int table_delete_state(Table table, State state){
  assert(table != NULL);
  assert(state != NULL);

  Node ptr;
  if((ptr = table_contains_state(table, state))){

    int bucket_num = table_state_bucket_number(table, state);
    delete_node(ptr);
    table->record[bucket_num]--;
    table->total--;
  }

  return 0;
}


State table_get_state(Table table, State pivot){
  
  //sem_wait(mutex);
  
  Node node = table_contains_state(table, pivot);
  if(node != NULL){
    return node->state;
  }
  State state = create_state();
  cpy_state(state, pivot);
  table_insert_state(table, state);
  
  //sem_post(mutex);  
  return state;
}


int table_free_nonreachable_state(Table table, State head){
  int i;

  //sem_wait(mutex);
  for(i=0;i<table->size;i++){
    if(table->record[i] == 0)
      continue;

    Node node = table->buckets[i];
    while(node->next != NULL){
      State state = ((Node)node->next)->state;
      if(state_eq_seq(head, state)){
	table_delete_state(table, state);
	continue;
      } else {
	node = (Node)node->next;
      }
    }
  }

  //sem_post(mutex);
  return 0;
}
