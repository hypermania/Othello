#ifndef EVALUATE_H
#define EVALUATE_H

#include <x86intrin.h>

#include <stdlib.h>
#include <stdio.h>

#include "bitboard.h"
#include "bitstate.h"
#include "preprocess.h"

#include "macro.h"
#include "weights.h"


double evaluate(BitState *state);

#endif

