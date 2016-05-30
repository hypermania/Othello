#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "board.h"
#include "state.h"

#ifndef IO_H
#define IO_H

static const char white_str[] = "white";
static const char black_str[] = "black";

// return 0 at success
// return -1 if ptr == NULL
int print_board(Board board);
int print_state(State state);

#endif
