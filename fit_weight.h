#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "state.h"
#include "genconf.h"

#ifndef FIT_WEIGHT_H
#define FIT_WEIGHT_H


typedef struct {
  int n;
  Config c;
  double *w;
} Weight;

typedef struct{
  Config_store board;
  short score;
} Example;

// write to the example ptr all (board,score) pair in the game
int example_from_seq(State state, Pos *seq, Example *example);

// perform one iteration of weight-fitting using examples
// n is the total number of examples to be fitted to
// return the averaged error
double fit_weight_from_examples(Weight *weight, Example *examples, int n, double alpha);

double weighted_score_for_board(Weight weight, Config board);// deprecated
double weighted_score_for_board_nocreate(Weight weight, Config board);
double weighted_score_for_board_info(Weight weight, Config board, char *hik);

double link_function(double x);
double link_function_deriv_relation(double link_function_val);


#endif
