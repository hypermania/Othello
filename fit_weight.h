#ifndef FIT_WEIGHT_H
#define FIT_WEIGHT_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <pthread.h>
#include <sys/stat.h>
#include <stdbool.h>

//#include "example.h"
#include "pattern.h"
//#include "config.h"

#include "datpt.h"
#include "weights.h"
#include "evaluate.h"
#include "confcount.h"

#include "macro.h"


/* link function related */

double link_function(double x);
double link_function_deriv_relation(double link_function_val);
double link_function_inverse(double g);
double link_function_2nd_deriv_relation(double g_score, double g_deriv);

/* gradient descent related */

// total error computed from the global weights
double total_error(DataPoint *datapoints, long int n_dp);

// evaluate from the global weights, and add the differential to the Weights struct
double grad_descent_step(DataPoint *datapoints, long int n_dp, Weights *weights, double alpha);
double grad_descent_step_mt(DataPoint *datapoints, long int n_dp, Weights *weights, double alpha);

// fit global weights (starting from 0) up to precision = d(total error)/(total error)
void grad_descent(DataPoint *datapoints, long int n_dp, int cat, double alpha, double precision, int chunk);
void grad_descent_mt(DataPoint *datapoints, long int n_dp, int cat, double alpha, double precision, int chunk);

/* fct utilities (deprecated) */ 

/* Returns the weight store in fct for board.
   If the pattern is not active for this board: return 0.
 */
//double get_score_from_fct_list(FlatConfTable *fct_list, int n_f, Config_store board);




#endif
