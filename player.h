#ifndef PLAYER_H
#define PLAYER_H

enum PlayerType {HUMAN, RANDOM, AB_PRUNING, NEGAMAX};

typedef struct {
  enum PlayerType type;
  void *param;
} Player;

Player human_player(void);
Player random_player(void);
Player ab_pruning_player(int depth);

#endif
