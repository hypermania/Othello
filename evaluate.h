#ifndef EVALUATE_H
#define EVALUATE_H

#include <stdlib.h>
#include <stdio.h>

#include "bitboard.h"
#include "bitstate.h"
#include "preprocess.h"

#include "macro.h"
#include "weights.h"

BitMask flipVertical(BitMask mask);
BitMask flipHorizontal(BitMask mask);
BitMask flipDiagA1H8(BitMask mask);
BitMask rotate90Clockwise(BitMask mask);
BitMask rotate90CounterClockwise(BitMask mask);
BitMask rotate180(BitMask mask);


double evaluate(BitState *state);

#endif

