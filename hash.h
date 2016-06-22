#include <stdlib.h>
//#include "state.h"
#include <string.h>

#ifndef HASH_H
#define HASH_H


/* the hash function */
extern unsigned int hash_consts[];

// hash 64 chars pointed by bytes
unsigned int hash_board(char *bytes);
unsigned int hash_mem(char *bytes, size_t size);



#endif
