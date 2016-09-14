#ifndef OFFSET_H
#define OFFSET_H

#include <stdlib.h>

#include "util.h"

// offsets

extern int offset_81[16];
extern int offset_243[32];
extern int offset_729[64];
extern int offset_2187[128];
extern int offset_6561[256];
extern int offset_19683[512];
extern int offset_59049[1024];


// initialize offsets
void init_offsets(void);

// check the offsets
int check_offsets(void);


#endif
