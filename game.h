// implements the game

#include <stdlib.h>
#include <string.h>
#include "state.h"
#include "ai.h"
#include "io.h"
#include "table.h"


#ifndef GAME_H
#define GAME_H


int run_game(int print_endgame_flag, int print_midgame_flag, int human_player_flag, int depthw, int depthb);
int run_game_from_seq(State state, Pos *seq, int print_endgame_flag, int print_midgame_flag);



#endif
