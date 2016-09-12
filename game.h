// implements the game

#ifndef GAME_H
#define GAME_H


#include <stdlib.h>
#include <string.h>


#include "player.h"
#include "ai.h"
#include "io.h"
#include "table.h"
#include "fit_weight.h"
#include "player.h"

FlatConfTable **global_fcts;


int run_game(int print_endgame_flag, int print_midgame_flag, Player white, Player black);

int get_move(BitState *state, Player player);


#endif
