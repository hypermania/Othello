/* A hash table for storing game State information,
   as well as an interface for reading/writing information
   to the table.
   

 */

#include <stdlib.h>
#include "state.h"
#include <string.h>

#ifndef TABLE_H
#define TABLE_H

typedef struct {
  State state;
  void *prev;
  void *next;
} *Node, Node_store;

// bucket and record here are indexed by the board of the state only
typedef struct {
  //  int max; // maximum number of states storable
  int size; // total number of buckets
  
  int total; // total number of states stored
  Node *buckets; // the sequence of buckets
  char *record; // each char records the number of states at that bucket
} *Table, Table_store;


/* public interface */
Table create_and_init_table(int table_size);//, int max_states); 
int free_table(Table table);  // free the table and its associated states
int table_get_state(Table table, State state, State addr); 
int table_store_state_info(Table table, State state, int *movec, Pos *moves, double *scores);
int table_free_useless_state(Table table, State state);


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
Node table_contains_state(Table table, State state);

// returns 1 if state already exists
int table_insert_state(Table table, State state);
// returns 0 and do nothing if state does not exist
int table_delete_state(Table table, State state);


/* the hash function */
extern unsigned int hash_consts[];

// hash 64 chars pointed by bytes
unsigned int hash_board(char *bytes);



//int table_insert_node(Table table, State state);


//int table_search_(Table table, State state, State addr);
//int table_delete_state(Table table, State state);


#endif
