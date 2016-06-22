#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>

#include "state.h"
#include "genconf.h"

#ifndef FIT_WEIGHT_H
#define FIT_WEIGHT_H

#define CATEGORY_SIZE 4
#define INIT_PIECE_NUM 4
#define CAT_NUM ((BOARD_SIZE_SQR - INIT_PIECE_NUM)/CATEGORY_SIZE)
#define CAT(pieces) (((pieces) - 1 - INIT_PIECE_NUM) / CATEGORY_SIZE)


#define TOTAL_GAMES 117752


typedef struct {
  int n;
  Config c;
  double *w;
} Weight;

typedef Weight EvalFunc[CAT_NUM];

typedef struct{
  Config_store board;
  short score;
} Example;


/* weight fitting utility functions */

// arguments: "weight", the "examples" and its size "N"
// return: write on "hik" according to: hik[i][k] = val(c_i(p_k))
char **compute_hik(Weight weight, Example *examples, int N);
char **compute_symmetric_hik(Weight weight, Example *examples, int N);

double *compute_sum_wi_hik(Weight weight, char **hik, int N);
int *compute_sum_hik(Weight weight, char **hik, int N);
double *compute_delta(Weight weight, Example *examples, int N, char **hik, double *sum_wi_hik, int *sum_hik, double alpha);
// return the number of iterations used
int grad_descent(Weight *weight, Example *examples, int N, double alpha, double precision, bool print_iters);
int sto_grad_descent(Weight *weight, Example *examples, int N, double alpha, double precision, bool print_iters);

double total_error(Weight weight, Example *examples, int N);

/* link function related */

double link_function(double x);
double link_function_deriv_relation(double link_function_val);


/* preprocessors */

// given "examples" and "example_size":
// stores the categorized examples into "categories"
//  stores the number of examples in each cateogry into "category_sizes"
int sort_examples_into_categories(Example *examples, Example **categories, int *cat_sizes, int example_size);
// write to the example ptr all (board,score) pair in the game
int example_from_seq(State state, Pos *seq, Example *example);

Weight init_weight_from_configs(Config configs, int n);
void free_weight(Weight weight);


#endif
