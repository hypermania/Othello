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

/*
  For a configuration represented by (white, black):
  2-D arrays are accessed by array[cat][white][black].
  1-D arrays are accessed by array[cat][offset_xxxx[white] + _pext_u32(black, ~white)].

  Example:
  In configuration:   X O O X O O O -  (where X is black, O is white, - is empty),
  white = (binary)01101110;
  black = (binary)10010000.
 */

// center-column reflect symmetry
extern double row_1[15][256][256];
extern double row_2[15][256][256];
extern double row_3[15][256][256];
extern double row_4[15][256][256];

/*
extern double row_1[15][6561];
extern double row_2[15][6561];
extern double row_3[15][6561];
extern double row_4[15][6561];
*/

// anti-diagonal reflect symmetry
extern double diag_8[15][256][256];
extern double diag_7[15][128][128];
extern double diag_6[15][64][64];
extern double diag_5[15][32][32];
extern double diag_4[15][16][16];
/*
extern double diag_8[15][6561];
extern double diag_7[15][2187];
extern double diag_6[15][729];
extern double diag_5[15][243];
extern double diag_4[15][81];
*/

// diagonal reflect symmetry
//extern double corner_33[15][512][512];
extern double corner_33[15][19683];

// no symmetry
//extern double corner_25[15][1024][1024];
extern double corner_25[15][59049];

// center-column reflect symmetry
//extern double edge_xx[15][1024][1024];
extern double edge_xx[15][59049];



// initialize offsets
void init_offsets(void);

// check the offsets
int check_offsets(void);

// set all weights to zero
void clear_weights(void);

// check for symmetry properties in the weights
int check_weights(void);




#endif
