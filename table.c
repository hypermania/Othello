#include "table.h"

Table *table_create(int log_size) {
  size_t total_size = sizeof(Table) + (1 << log_size) * ELEM_SIZE;
  Table *table = (Table *)malloc(total_size);
  table->log_size = log_size;
  table->mask = (1 << log_size) - 1;
  table->write_count = 0;
  table->hit_count = 0;
  table->evict_count = 0;
  table->occupied = 0;
  memset(table->list, 0, (1 << log_size) * ELEM_SIZE);
  return table;
}

void table_clear(Table *table) {
  table->write_count = 0;
  table->hit_count = 0;
  table->evict_count = 0;
  table->occupied = 0;
  memset(table->list, 0, (1 << table->log_size) * ELEM_SIZE);
}

inline void table_write(Table *table, BitState *state, TableValue value) {
  table->write_count++;
  uint64_t hash = hash_bitstate(state);
  uint64_t index = hash & table->mask;
  BitState read = table->list[index].state;
  //if(table->list[index].hash != 0) {
  if(read.board.w != 0) {

    if(read.board.w != state->board.w ||
       read.board.b != state->board.b ||
       read.turn != state->turn) {

      //if(table->list[index].hash != hash) {
      table->evict_count++;
    } 
  } else {
    table->occupied++;
  }
  
  table->list[index].state = *state;
  //table->list[index].hash = hash;
  table->list[index].value = value;
}

inline TableValue *table_read(Table *table, BitState *state) {
  uint64_t hash = hash_bitstate(state);
  uint64_t index = hash & table->mask;

  BitState read = table->list[index].state;
  if(read.board.w == state->board.w &&
     read.board.b == state->board.b &&
     read.turn == state->turn) {

    //if(table->list[index].hash == hash) {
    table->hit_count++;
    return &table->list[index].value;
  }

  return NULL;
}

void table_free(Table *table) {
  printf("table stat: write_count = %ld; hit_count = %ld; evict_count = %ld; occupied = %ld; rate = %lf\n",
	 table->write_count, table->hit_count, table->evict_count, table->occupied, table->occupied/(double)(1 << table->log_size));
  free(table);
}
