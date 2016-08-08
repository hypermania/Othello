#ifndef EVALUATE_H
#define EVALUATE_H

#include <stdlib.h>
#include <stdio.h>

#include "bitboard.h"
//#include "bitstate.h"
//#include "preprocess.h"

//#include "macro.h"
#include "weights.h"

BitMask flipVertical(BitMask mask);
BitMask flipDiagA1H8(BitMask mask);

#endif
