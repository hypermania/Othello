// implements the game
#include <stdlib.h>
#include <string.h>
#include "state.h"
#include "board.h"


// need to support:

// during a game:
// show the player which places to place
// prevent the player from giving invalid move

// after a game:
// the player can revise the game

// reduce repetitive computations for:
// allowed_moves call

// transition graph for game:


#ifndef GAME_H
#define GAME_H

#define MAX_SKIPS 10

typedef struct {
  int status;// 1 for white's move, 2 for black's move, 3, 4 for respective skips
  Pos pos;
} move;

// terms:
// end of game: if at some turn, neither player has allowed move, it is end of game (code 3)
typedef struct {
  int status; // 1 for white's turn, 2 for black's turn, 3 for ended of game
  State state_seq[BOARD_SIZE * BOARD_SIZE + MAX_SKIPS];
  State current;
  move move_seq[BOARD_SIZE * BOARD_SIZE + MAX_SKIPS];
  int allowed_movec;
  Pos allowed_moves[BOARD_SIZE * BOARD_SIZE / 2];
  int turns; // begin from 0
} *Game, Game_store;

// return 0 at success, unless otherwise specified
// return -k for error at k-th argument

Game create_game(void);
int free_game(Game game);
//int cpy_game(Game game);
int init_game(Game game);

// does not change sequence if any error occur
// return -2 if input number is invalid (including no move to play)
// should call make_move only if require_input(game) == 1
int make_move(Game game, int move_num);
// skip the turn for the player if there is no move to play
// return -4 if game has ended
int make_skip(Game game);


// return -2 if already at opening of game
//int go_back_once(Game game);
// return -2 also if turn<0 or turn>game->turns
//int go_back_to(Game game, int turn);

// success: return 0 for no and 1 for yes
// fail: return -2 for other errors
int require_input(Game game);
int is_end_of_game(Game game);
// end the game
int end_game(Game game);


// return side of winner and 0 for draw at success
// return -2 if game hasn't ended yet
int game_result(Game game);

#endif
