#ifndef WEIGHTS_H
#define WEIGHTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <x86intrin.h>

#include "util.h"

// offsets

extern int offset_81[16];
extern int offset_243[32];
extern int offset_729[64];
extern int offset_2187[128];
extern int offset_6561[256];
extern int offset_19683[512];
extern int offset_59049[1024];

// weights

// center-column reflect symmetry
extern double row_1[6561];
extern double row_2[6561];
extern double row_3[6561];
extern double row_4[6561];
// anti-diagonal reflect symmetry
extern double diag_8[6561];
extern double diag_7[2187];
extern double diag_6[729];
extern double diag_5[243];
extern double diag_4[81];
// diagonal reflect symmetry
extern double corner_33[19683];
// no symmetry
extern double corner_25[59049];
// center-column reflect symmetry
extern double edge_xx[59049];


// initialize offsets
void init_offsets(void);

// check the offsets
int check_offsets(void);

// set all weights to zero
void clear_weights(void);

// check for symmetry properties in the weights
int check_weights(void);




#endif
