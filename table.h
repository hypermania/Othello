/*
  A hash table for storing midgame search results.
  Entries are in the form (state, score)
*/
#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "bitstate.h"

typedef struct {
  enum {EXACT, LOWERBOUND, UPPERBOUND} flag;
  uint8_t depth;
  uint8_t move;
  double score;
} TableValue;

typedef struct {
  int log_size;
  uint64_t mask;
  long int write_count;
  long int hit_count;
  long int evict_count;
  long int occupied;
  struct {
    BitState state;
    //uint64_t hash;
    TableValue value;
  } list[0];
} Table;

#define ELEM_SIZE (sizeof(((Table *)NULL)->list[0]))

Table *table_create(int log_size);
void table_clear(Table *table);
void table_write(Table *table, BitState *state, TableValue value);
TableValue *table_read(Table *table, BitState *state);
void table_free(Table *table);


#endif
