// implements the game

#ifndef GAME_H
#define GAME_H


#include <stdlib.h>
#include <string.h>


#include "state.h"
#include "player.h"
#include "ai.h"
#include "io.h"
#include "table.h"
#include "genconf.h"
#include "fit_weight.h"


FlatConfTable **global_fcts;


int run_game(int print_endgame_flag, int print_midgame_flag, Player white, Player black);
int run_game_from_seq(State state, Pos *seq, int print_endgame_flag, int print_midgame_flag);

int get_move(State state, Player player);


#endif
