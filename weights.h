#ifndef WEIGHTS_H
#define WEIGHTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <x86intrin.h>

#include "util.h"
#include "bitboard.h"

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
extern double row_1[CAT_NUM][256][256];
extern double row_2[CAT_NUM][256][256];
extern double row_3[CAT_NUM][256][256];
extern double row_4[CAT_NUM][256][256];

/*
extern double row_1[CAT_NUM][6561];
extern double row_2[CAT_NUM][6561];
extern double row_3[CAT_NUM][6561];
extern double row_4[CAT_NUM][6561];
*/

// anti-diagonal reflect symmetry
extern double diag_8[CAT_NUM][256][256];
extern double diag_7[CAT_NUM][128][128];
extern double diag_6[CAT_NUM][64][64];
extern double diag_5[CAT_NUM][32][32];
extern double diag_4[CAT_NUM][16][16];
/*
extern double diag_8[CAT_NUM][6561];
extern double diag_7[CAT_NUM][2187];
extern double diag_6[CAT_NUM][729];
extern double diag_5[CAT_NUM][243];
extern double diag_4[CAT_NUM][81];
*/

// diagonal reflect symmetry
//extern double corner_33[CAT_NUM][512][512];
extern double corner_33[CAT_NUM][19683];

// no symmetry
//extern double corner_25[CAT_NUM][1024][1024];
extern double corner_25[CAT_NUM][59049];

// center-column reflect symmetry
//extern double edge_xx[CAT_NUM][1024][1024];
extern double edge_xx[CAT_NUM][59049];


typedef struct {
  // center-column reflect symmetry
  double row_1[256][256];
  double row_2[256][256];
  double row_3[256][256];
  double row_4[256][256];

  // anti-diagonal reflect symmetry
  double diag_8[256][256];
  double diag_7[128][128];
  double diag_6[64][64];
  double diag_5[32][32];
  double diag_4[16][16];

  // diagonal reflect symmetry
  double corner_33[19683];

  // no symmetry
  double corner_25[59049];

  // center-column reflect symmetry
  double edge_xx[59049];
} Weights;

//extern Weights weights[CAT_NUM];


// reflection symmetry mapping
extern uint32_t map_reverse_256[256];
extern uint32_t map_reverse_128[128];
extern uint32_t map_reverse_64[64];
extern uint32_t map_reverse_32[32];
extern uint32_t map_reverse_16[16];

extern uint32_t map_corner_33[19683];
extern uint32_t map_edge_xx[59049];




// initialize offsets
void init_offsets(void);

// check the offsets
int check_offsets(void);

// set all weights to zero
void clear_weights(void);

// check for symmetry properties in the weights
int check_weights(void);


// weight modifiers
void increment_256(double table[256][256], uint32_t white, uint32_t black, double increment);
void increment_128(double table[128][128], uint32_t white, uint32_t black, double increment);
void increment_64(double table[64][64], uint32_t white, uint32_t black, double increment);
void increment_32(double table[32][32], uint32_t white, uint32_t black, double increment);
void increment_16(double table[16][16], uint32_t white, uint32_t black, double increment);

void increment_corner_33(double table[19683], uint32_t white, uint32_t black, double increment);
void increment_corner_25(double table[59049], uint32_t white, uint32_t black, double increment);
void increment_edge_xx(double table[59049], uint32_t white, uint32_t black, double increment);

void increment_global_by_bitboard(BitBoard board, double increment);
void increment_by_bitboard(Weights *weights, BitBoard board, double increment);


// initialize maps
void init_maps(void);



#endif
