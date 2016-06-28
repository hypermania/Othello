#ifndef PLAYER_H
#define PLAYER_H

enum PlayerType {HUMAN, RANDOM, AB_PRUNING, NEGAMAX};

typedef struct {
  enum PlayerType type;
  void *param;
} Player;


#endif
