/* A hash table for storing game State information,
   as well as an interface for reading/writing information
   to the table.
 */

#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "hash.h"
#include "state.h"


#ifndef TABLE_H
#define TABLE_H

typedef struct {
  State state;
  void *prev;
  void *next;
} *Node, Node_store;

// indexed by state->board and state->turn
typedef struct {
  //  int max; // maximum number of states storable
  int size; // total number of buckets
  
  int total; // total number of states stored
  Node *buckets; // the sequence of buckets
  char *record; // each char records the number of states at that bucket
} *Table, Table_store;

sem_t *mutex;

/* public interface */
Table create_and_init_table(int table_size);//, int max_states);

// free the table and its associated states
int free_table(Table table);

// Return the address of the state stored in the table.
// If the state is not in the table, it will be created and stored in the table.
// The pivotal information from the returned state should not be modified
State table_get_state(Table table, State state);
int table_free_nonreachable_state(Table table, State state);


/* The following should be private */

/* node operations */
// create new node and let it point to a newly created state (with copied data)
Node create_node_from_state(State state);
int append_node_from_state(Node node, State state);
// delete node and free corresponding state
int delete_node(Node node);

/* internal table */
// returns the bucket number for state
int table_state_bucket_number(Table table, State state);
// returns Node of the stored state if it does exist
// otherwise return NULL
Node table_contains_state(Table table, State state);

// returns 1 if state already exists
int table_insert_state(Table table, State state);
// returns 0 and do nothing if state does not exist
int table_delete_state(Table table, State state);





#endif
