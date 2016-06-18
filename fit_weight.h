#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "state.h"
#include "genconf.h"

#ifndef FIT_WEIGHT_H
#define FIT_WEIGHT_H

#define CATEGORY_SIZE 4
#define INIT_PIECE_NUM 4
#define CAT_NUM ((BOARD_SIZE_SQR - INIT_PIECE_NUM)/CATEGORY_SIZE)

#define TOTAL_GAMES 117752


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
// arguments: "weight", the "examples" and its size "N"
// return: write on "hik" according to: hik[i][k] = val(c_i(p_k))
char **compute_hik(Weight weight, Example *examples, int N);
double *compute_sum_wi_hik(Weight weight, char **hik, int N);
int *compute_sum_hik(Weight weight, char **hik, int N);
double *compute_delta(Weight weight, Example *examples, int N, char **hik, double *sum_wi_hik, int *sum_hik, double alpha);
// eturn the number of iterations used
int fit_to_precision(Weight *weight, Example *examples, int N, double alpha, double precision, bool print_iters);

// perform one iteration of weight-fitting using examples
// n is the total number of examples to be fitted to
// return the averaged error
double *fit_weight_from_examples(Weight *weight, Example *examples, int N, double alpha);

double weighted_score_for_board(Weight weight, Config board);// deprecated
double weighted_score_for_board_nocreate(Weight weight, Config board);
double weighted_score_for_board_info(Weight weight, Config board, char *hik);

double link_function(double x);
double link_function_deriv_relation(double link_function_val);

/* given "examples" and "example_size":
   stores the categorized examples into "categories"
   stores the number of examples in each cateogry into "category_sizes"
*/
int sort_examples_into_categories(Example *examples, Example **categories, int *cat_sizes, int example_size);

/*
Weight symmetrize_weight(Weight *weight);

Config_store reflect_diag(Config_store config);
Config_store reflect_rdiag(Config_store config);
*/

#endif
