#ifndef EVALUATE_H
#define EVALUATE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <pthread.h>
#include <sys/stat.h>

#include "bitboard.h"
#include "preprocess.h"

#include "macro.h"

BitMask flipVertical(BitMask mask);
BitMask flipDiagA1H8(BitMask mask);

#endif
