#ifndef DATPT_H
#define DATPT_H

#include <stdio.h>
#include <stdlib.h>

#include "bitboard.h"
#include "bitstate.h"
#include "macro.h"
#include "io.h"


typedef struct {
  BitBoard board;
  double score;
} DataPoint;

int datapoints_from_seq(char seq[2 * MAX_GAME_LENGTH + 1], DataPoint datapoints[MAX_GAME_LENGTH]);

DataPoint *datapoints_from_file(FILE *fp, long int *n_dp);

#endif
