#ifndef PLAYER_H
#define PLAYER_H

#include "state.h"
#include "bitstate.h"

enum PlayerType {HUMAN, RANDOM, IMMEDIATE, NEGAMAX, MIXED};

typedef struct {
  enum PlayerType type;
  void *param;
} Player;

Player human_player(void);
Player random_player(void);
Player optimizing_player(double (*score_func)(BitState *));

typedef struct {
  int depth;
  double (*score_func)(BitState *);
} NegamaxConf;

Player negamaxing_player(int depth, double (*score_func)(BitState *));
//Player negamaxing_dnstore_player(int depth, double (*score_func)(BitState *));

typedef struct {
  int depth_middle;
  double (*score_func)(BitState *);
  int depth_end;
} MixedConf;


Player mixed_player(int depth_middle, double (*score_func)(BitState *), int depth_end);

//Player ab_pruning_player(int depth);

#endif
