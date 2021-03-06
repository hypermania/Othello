#ifndef EVALUATE_H
#define EVALUATE_H

#include <x86intrin.h>

#include <stdlib.h>
#include <stdio.h>

#include "bitboard.h"
#include "bitstate.h"
//#include "preprocess.h"

#include "macro.h"
#include "weights.h"


double evaluate(BitState *state);
double evaluate_use_avx(BitState *state);

double evaluate_0(BitState *state);

#endif

