#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "state.h"

/* the hash function */
extern unsigned int hash_consts[];

// hash 64 chars pointed by bytes
unsigned int hash_board(Board board);
unsigned int hash_state(State state);
unsigned int hash_mem(char *bytes, size_t size);



#endif
