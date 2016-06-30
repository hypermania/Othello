#include "player.h"

Player human_player(void){
  Player player;
  player.type = HUMAN;
  return player;
}

Player random_player(void){
  Player player;
  player.type = RANDOM;
  return player;
}

Player optimizing_player(double (*score_func)(State)){
  Player player;
  player.type = IMMEDIATE;
  player.param = score_func;
  return player;
}


Player negamaxing_player(int depth, double (*score_func)(State)){
  Player player;
  player.type = NEGAMAX;

  NegamaxConf *conf = malloc(sizeof(NegamaxConf));
  player.param = conf;
  conf->depth = depth;
  conf->score_func = score_func;
  
  return player;
}

Player negamaxing_dnstore_player(int depth, double (*score_func)(State)){
  Player player;
  player.type = NEGAMAX_DNSTORE;

  NegamaxConf *conf = malloc(sizeof(NegamaxConf));
  player.param = conf;
  
  conf->depth = depth;
  conf->score_func = score_func;
  
  return player;
}


Player mixed_dnstore_player(int depth_middle, double (*score_func)(State), int depth_end){
  Player player;
  player.type = MIXED_DNSTORE;

  MixedConf *conf = malloc(sizeof(MixedConf));
  player.param = conf;
  
  conf->depth_middle = depth_middle;
  conf->score_func = score_func;
  conf->depth_end = depth_end;

  return player;
}
