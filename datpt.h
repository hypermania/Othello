#ifndef DATPT_H
#define DATPT_H

#include <stdio.h>
#include <stdlib.h>

#include "bitboard.h"
#include "bitstate.h"
#include "macro.h"


typedef struct {
  BitBoard board;
  double score;
} DataPoint;

int datapoints_from_seq(char seq[2 * MAX_GAME_LENGTH + 1], DataPoint datapoints[MAX_GAME_LENGTH]);

DataPoint *datapoints_from_file(FILE *fp, long int *n_dp);

// put datpts into their each category (the number of pieces of the board)
DataPoint **categorize_datpts(DataPoint *datapoints, long int n_dp, long int cat_sizes[CAT_NUM]);

#endif
