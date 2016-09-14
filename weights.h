#ifndef WEIGHTS_H
#define WEIGHTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <x86intrin.h>

#include "util.h"
#include "bitboard.h"
#include "offset.h"
#include "symmetry_map.h"

#include "confcount.h"

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
void increment_by_bitboard_confcount(Weights *weights, BitBoard board, ConfigCounter *confcount, double increment);





#endif
