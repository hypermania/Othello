#include "fit_weight.h"

double link_function(double x){
  return 2*BOARD_SIZE_SQR/(1+exp((-1)*x)) - BOARD_SIZE_SQR;
  //return x;
}

double link_function_deriv_relation(double link_function_val){
  return  (link_function_val + BOARD_SIZE_SQR) * (BOARD_SIZE_SQR - link_function_val) / (2*BOARD_SIZE_SQR);
  //return 1;
}

double link_function_inverse(double g){
  return (-1) * log((2 * BOARD_SIZE_SQR)/(BOARD_SIZE_SQR + g) - 1);
}

double link_function_2nd_deriv_relation(double g_score, double g_deriv){
  return 2 * g_deriv * g_deriv / (g_score + BOARD_SIZE) - g_deriv;
}


double total_error(DataPoint *datapoints, long int n_dp){
  double E = 0;
  
  long int i;
  for(i = 0; i < n_dp; i++){
    double x_score = evaluate((BitState *)(&datapoints[i].board));
    double g_score = link_function(x_score);
    double sqr_diff = (g_score - datapoints[i].score);
    sqr_diff *= sqr_diff;
    E += sqr_diff;
  }
  
  E /= (double)n_dp;
  return E;
}

ConfigCounter *hik_abs;

double grad_descent_step(DataPoint *datapoints, long int n_dp, Weights *weights, double alpha){
  double total_deriv = 0;
  
  long int i;
  for(i = 0; i < n_dp; i++){
    double x_score = evaluate((BitState *)(&datapoints[i].board));
    double g_score = link_function(x_score);
    double g_deriv = link_function_deriv_relation(g_score);
    double deriv = 2 * g_deriv * (datapoints[i].score - g_score) / (double)n_dp;
    double delta = deriv * alpha;
    total_deriv += deriv * deriv;
    
    increment_by_bitboard(weights, datapoints[i].board, delta);
  }

  total_deriv = sqrt(total_deriv);
  return total_deriv;
}

DataPoint *global_datapoints;
long int *global_bounds;
double *global_deriv_sqr;
long int global_n_dp;
double global_alpha;

void *grad_descent_step_thread(void *ptr){
  long int start = *(long int*)ptr;
  long int end = *(((long int*)ptr) + 1);
  int th = ((long int)ptr - (long int)global_bounds) / sizeof(long int);
  
  double total_deriv = 0;

  Weights *my_weights = malloc(sizeof(Weights));
  memset(my_weights, 0, sizeof(Weights));
  
  long int i;
  for(i = start; i < end; i++){
    double x_score = evaluate((BitState *)(&global_datapoints[i].board));
    double g_score = link_function(x_score);
    double g_deriv = link_function_deriv_relation(g_score);
    double deriv = 2 * g_deriv * (global_datapoints[i].score - g_score) / (double)global_n_dp;
    double delta = deriv * global_alpha;
    total_deriv += deriv * deriv;
    
    increment_by_bitboard(my_weights, global_datapoints[i].board, delta);
  }

  global_deriv_sqr[th] = total_deriv;
  //total_deriv = sqrt(total_deriv);
  return (void *)my_weights;
}


double grad_descent_step_mt(DataPoint *datapoints, long int n_dp, Weights *weights, double alpha){

  long int bounds[TH_NUM + 1];

  int th; int interval = n_dp/4;
  for(th = 0; th < TH_NUM; th++){
    bounds[th] = interval * th;
  }
  bounds[th] = n_dp;

  double deriv_sqr[TH_NUM];
  
  global_datapoints = datapoints;
  global_bounds = bounds;
  global_deriv_sqr = deriv_sqr;
  global_n_dp = n_dp;
  global_alpha = alpha;

  pthread_t tids[TH_NUM];
  Weights *section_delta[TH_NUM];
  for(th = 0; th < TH_NUM; th++){
    pthread_create(&(tids[th]), NULL, grad_descent_step_thread, &bounds[th]);
  }
  for(th = 0; th < TH_NUM; th++){
    pthread_join(tids[th], (void *)&section_delta[th]);
  }

  for(th = 0; th < TH_NUM; th++){
    uint32_t white, black;
    for(white = 0; white < 256; white++){
      for(black = 0; black < 256; black++){
	if(white & black){
	  continue;
	}
	weights->row_1[white][black] += section_delta[th]->row_1[white][black];
	weights->row_2[white][black] += section_delta[th]->row_2[white][black];
	weights->row_3[white][black] += section_delta[th]->row_3[white][black];
	weights->row_4[white][black] += section_delta[th]->row_4[white][black];

	weights->diag_8[white][black] += section_delta[th]->diag_8[white][black];
      }
    }
    for(white = 0; white < 128; white++){
      for(black = 0; black < 128; black++){
	if(white & black){
	  continue;
	}
	weights->diag_7[white][black] += section_delta[th]->diag_7[white][black];
      }
    }
    for(white = 0; white < 64; white++){
      for(black = 0; black < 64; black++){
	if(white & black){
	  continue;
	}
	weights->diag_6[white][black] += section_delta[th]->diag_6[white][black];
      }
    }
    for(white = 0; white < 32; white++){
      for(black = 0; black < 32; black++){
	if(white & black){
	  continue;
	}
	weights->diag_5[white][black] += section_delta[th]->diag_5[white][black];
      }
    }
    for(white = 0; white < 16; white++){
      for(black = 0; black < 16; black++){
	if(white & black){
	  continue;
	}
	weights->diag_4[white][black] += section_delta[th]->diag_4[white][black];
      }
    }
    for(white = 0; white < 512; white++){
      for(black = 0; black < 512; black++){
	if(white & black){
	  continue;
	}
	int index = offset_19683[white] + _pext_u32(black, ~white);
	weights->corner_33[index] += section_delta[th]->corner_33[index];
      }
    }
    for(white = 0; white < 1024; white++){
      for(black = 0; black < 1024; black++){
	if(white & black){
	  continue;
	}
	int index = offset_59049[white] + _pext_u32(black, ~white);
	weights->corner_25[index] += section_delta[th]->corner_25[index];
	weights->edge_xx[index] += section_delta[th]->edge_xx[index];
      }
    }
  }

  for(th = 0; th < TH_NUM; th++){
    free(section_delta[th]);
  }
  
  double total_deriv = 0;
  for(th = 0; th < TH_NUM; th++){
    total_deriv += global_deriv_sqr[th];
  }
  total_deriv = sqrt(total_deriv);

  return total_deriv;
}



void grad_descent(DataPoint *datapoints, long int n_dp, int cat, double alpha, double precision, int chunk){
  Weights *weights = malloc(sizeof(Weights));
  memset(weights, 0, sizeof(Weights));
  
  double deriv, last_deriv;
  double error, last_error;
  deriv = DBL_MAX;
  last_deriv = DBL_MAX;
  error = DBL_MAX;
  last_error = DBL_MAX;
  
  int iter = 0;  
  while(1){
    iter++;
    deriv = grad_descent_step_mt(datapoints, n_dp, weights, alpha);

    memcpy(row_1[cat], weights->row_1, sizeof(row_1[cat]));
    memcpy(row_2[cat], weights->row_2, sizeof(row_2[cat]));
    memcpy(row_3[cat], weights->row_3, sizeof(row_3[cat]));
    memcpy(row_4[cat], weights->row_4, sizeof(row_4[cat]));

    memcpy(diag_8[cat], weights->diag_8, sizeof(diag_8[cat]));
    memcpy(diag_7[cat], weights->diag_7, sizeof(diag_7[cat]));
    memcpy(diag_6[cat], weights->diag_6, sizeof(diag_6[cat]));
    memcpy(diag_5[cat], weights->diag_5, sizeof(diag_5[cat]));
    memcpy(diag_4[cat], weights->diag_4, sizeof(diag_4[cat]));

    memcpy(corner_33[cat], weights->corner_33, sizeof(corner_33[cat]));
    memcpy(corner_25[cat], weights->corner_25, sizeof(corner_25[cat]));
    memcpy(edge_xx[cat], weights->edge_xx, sizeof(edge_xx[cat]));

    double deriv_diff = (deriv - last_deriv)/last_deriv;
    last_deriv = deriv;
    double error_diff;

    printf("iteration %d: deriv = %lf, deriv_diff = %lf, alpha = %lf\n", iter, deriv, deriv_diff, alpha);
    
    if(iter % chunk == 0){
      error = total_error(datapoints, n_dp);
      error_diff = (error - last_error)/last_error;
      last_error = error;
      printf("total error = %lf, error_diff = %lf\n", error, error_diff);
      if(error_diff < 0 && fabs(error_diff) < precision){
	break;
      }
    }
    
    if(deriv_diff < 0 && fabs(deriv_diff) < 0.01){
      alpha *= 1.02;
    }
    
    if(deriv_diff > 0){
      alpha /= 1.5;
    }
  }

  //free(hik_abs);
  free(weights);
}
/*
char **compute_hik(Weight weight, Example *examples, int N){
  assert(examples != NULL);
  assert(N >= 0);

  char **hik = malloc(weight.n * sizeof(char *));
  
  int i; int j;
  for(i=0;i<weight.n;i++){
    hik[i] = malloc(N * sizeof(char));
    for(j=0;j<N;j++){
      hik[i][j] = match_one_conf_inline(examples[j].board, weight.c[i]);
    }
  }

  return hik;
}

char **compute_symmetric_hik(Weight weight, Example *examples, int N){
  assert(examples != NULL);
  assert(N >= 0);

  char **hik = malloc(weight.n * sizeof(char *));
  
  int i; int j;
  for(i=0;i<weight.n;i++){
    hik[i] = malloc(N * sizeof(char));
    for(j=0;j<N;j++){
      hik[i][j] = symmetric_match_one_conf_inline(examples[j].board, weight.c[i]);
    }
  }

  return hik;
}

double *compute_sum_wi_hik(Weight weight, char **hik, int N){
  assert(hik != NULL);

  double *sum_wi_hik = malloc(N * sizeof(double));
  memset(sum_wi_hik, 0, N * sizeof(double));
  
  int i; int j;
  for(i=0;i<weight.n;i++){
    for(j=0;j<N;j++){
      //if(hik[i][j])
      sum_wi_hik[j] += weight.w[i] * hik[i][j];
    }
  }
  return sum_wi_hik;
}

int *compute_sum_hik(Weight weight, char **hik, int N){
  assert(hik != NULL);
  
  int *sum_hik = malloc(weight.n * sizeof(double));
  memset(sum_hik, 0, weight.n * sizeof(double));
  
  int i; int j;
  for(i=0;i<weight.n;i++){
    for(j=0;j<N;j++){
      sum_hik[i] += hik[i][j];
    }
  }
  return sum_hik;
}

double *compute_delta(Weight weight, Example *examples, int N, char **hik, double *sum_wi_hik, int *sum_hik, double alpha){
  assert(examples != NULL);
  assert(hik != NULL);
  assert(sum_wi_hik != NULL);
  assert(sum_hik != NULL);
  
  double *delta = malloc(weight.n * sizeof(double));
  memset(delta, 0, weight.n * sizeof(double));

  int i; int j;
  for(i=0;i<weight.n;i++){
    for(j=0;j<N;j++){
      if(hik[i][j]){
	double g_score = link_function(sum_wi_hik[j]);
	double g_deriv = link_function_deriv_relation(g_score);
	delta[i] += alpha * 2 * g_deriv
	  * (examples[j].score - g_score) * hik[i][j];
      }
    }
    if(sum_hik[i]){
      delta[i] /= sum_hik[i];
    }
  }
  
  return delta;
}

*/

/*

double get_weight_from_fct(FlatConfTable fct, Config_store board){
  unsigned long int index = index_for_config(fct.pattern, board);
  if(fct.valid[index]){
    return fct.weights[index];
  } else {
    return 0;
  }
  return 0;
}

int **global_sum_hik_fct;
int **global_indices;
*/

/*
double fit_fct_list(FlatConfTable *fct_list, Example *examples, int n_f, int n_e, double alpha, double precision, int chunk){
  // temporary variables, denoting index for fct_list and examples
  int f, e;
  // pre-computing indexes for each example for each FlatConfTable
  int **indices = malloc(n_e * sizeof(int *));
  global_indices = indices;
  for(e=0;e<n_e;e++){
    indices[e] = malloc(n_f * sizeof(int));
    for(f=0;f<n_f;f++){
      indices[e][f] =
	index_for_config(fct_list[f].pattern, examples[e].board);
    }
  }
  // pre-computing, for each FlatConfTable, the number of active occurences
  // in the examples
  int **sum_hik_fct = malloc(n_f * sizeof(int *));
  global_sum_hik_fct = sum_hik_fct;
  for(f=0;f<n_f;f++){
    sum_hik_fct[f] = malloc(fct_list[f].n * sizeof(int));
    memset(sum_hik_fct[f], 0, fct_list[f].n * sizeof(int));
  }
  for(e=0;e<n_e;e++){
    for(f=0;f<n_f;f++){
      unsigned long int index = indices[e][f];
      if(fct_list[f].valid[index]){
	sum_hik_fct[f][index]++;
      }
    }
  }

  double deriv = DBL_MAX;
  double last_deriv = DBL_MAX;
  double last_total_error = DBL_MAX;
  int iter = 0;
  
  printf("starting condition:\n");
  printf("total error = %20.15lf\n",
	 total_error_fct_list(fct_list, examples, n_f, n_e));
  while(1){
    deriv = iterate_descent_for_fct_list_mt(fct_list, examples, n_f, n_e, alpha);
    double change_deriv = (deriv - last_deriv)/last_deriv;
    printf("iteration %4d:  deriv = %17.15lf,  change_deriv = %17.15lf,  alpha = %17.15lf\n", iter++, deriv, change_deriv, alpha);
    
    if(iter % chunk == 0){
      double total_error = total_error_fct_list(fct_list, examples, n_f, n_e);
      double change = (total_error - last_total_error)/last_total_error;
      printf("total error = %20.15lf, change = %20.15lf\n", total_error, change);
      last_total_error = total_error;
      if(change < 0 && fabs(change) < precision)
	break;
    }
    
    if(change_deriv < 0 && fabs(change_deriv) < 0.01){
      alpha *= 1.01;
    }
    if(change_deriv > 0){
      alpha /= 1.5;
    }
    last_deriv = deriv;
      
  }

  for(e=0;e<n_e;e++){
    free(indices[e]);
  }
  free(indices);
  
  for(f=0;f<n_f;f++){
    free(sum_hik_fct[f]);
  }
  free(sum_hik_fct);
  
  return 0;
}
*/

/*
FlatConfTable *global_fct_list;
Example *global_examples;
void *global_bounds;
int global_n_f;
int global_n_e;

struct {
  double **deriv_fct_list;
  //double sum_hik;
} th_results[TH_NUM];

void *iterate_descent_fct_thread(void *bounds){

  int start = ((int *)bounds)[0];
  int end = ((int *)bounds)[1];
  
  int n_f = global_n_f;
  
  double **deriv_fct_list = malloc(n_f * sizeof(double *));
  
  int e, f;  
  for(f=0;f<n_f;f++){
    deriv_fct_list[f] = malloc(global_fct_list[f].n * sizeof(double));
    memset(deriv_fct_list[f], 0, global_fct_list[f].n * sizeof(double));
  }
  
  for(e = start; e < end; e++){
    double x_score = 0;
    for(f=0;f<n_f;f++){
      unsigned long int index = global_indices[e][f];
      
      if(global_fct_list[f].valid[index]){
	x_score += global_fct_list[f].weights[index];
      }
    }

    double g_score = link_function(x_score);
    double g_deriv = link_function_deriv_relation(g_score);
    for(f=0;f<n_f;f++){
      unsigned long int index = global_indices[e][f];
      if(global_fct_list[f].valid[index]){
	double tot_chi_deriv =
	  2 * g_deriv * (global_examples[e].score - g_score);
	deriv_fct_list[f][index] += tot_chi_deriv;
      }
    }
  }
  
  int th = (bounds - global_bounds)/sizeof(int);
  th_results[th].deriv_fct_list = deriv_fct_list;

  return NULL;
}


double iterate_descent_for_fct_list(FlatConfTable *fct_list, Example *examples, int n_f, int n_e, double alpha){

  int e, f;
  double **deriv_fct_list = malloc(n_f * sizeof(double *));
  
  for(f=0;f<n_f;f++){
    deriv_fct_list[f] = malloc(fct_list[f].n * sizeof(double));
    memset(deriv_fct_list[f], 0, fct_list[f].n * sizeof(double));
  }
  
  unsigned long int *indices = malloc(n_f * sizeof(unsigned long int));

  for(e=0;e<n_e;e++){
    double x_score = 0;
    for(f=0;f<n_f;f++){
      unsigned long int index =
	index_for_config(fct_list[f].pattern, examples[e].board);
      indices[f] = index;
      if(fct_list[f].valid[index]){
	x_score += fct_list[f].weights[index];
      }
    }

    double g_score = link_function(x_score);
    double g_deriv = link_function_deriv_relation(g_score);
    for(f=0;f<n_f;f++){
      unsigned long int index = indices[f];
      if(fct_list[f].valid[index]){
	double tot_chi_deriv =
	  2 * g_deriv * (examples[e].score - g_score); // / n_e;
	deriv_fct_list[f][index] += tot_chi_deriv;
      }
    }
  }

  double deriv = 0;  
  for(f=0;f<n_f;f++){
    int i;
    for(i=0;i<fct_list[f].n;i++){
      if(fct_list[f].valid[i]){
	double delta = alpha * deriv_fct_list[f][i];

	fct_list[f].weights[i] += delta / n_e;
	deriv += fabs(delta) * fabs(delta);
      }
    }
    
  }
  
  for(f=0;f<n_f;f++){
    free(deriv_fct_list[f]);
  }
  free(deriv_fct_list);
  free(indices);
  deriv = sqrt(deriv) / alpha / n_e;
  return deriv;
}



double iterate_descent_for_fct_list_mt(FlatConfTable *fct_list, Example *examples, int n_f, int n_e, double alpha){


  int bounds[TH_NUM + 1];
  
  int th; int interval = n_e/4;
  for(th=0;th<TH_NUM;th++){
    bounds[th] = interval * th;
  }
  bounds[th] = n_e;

  global_fct_list = fct_list;
  global_examples = examples;
  global_bounds = bounds;
  global_n_f = n_f;
  global_n_e = n_e;
  
  pthread_t tids[TH_NUM];
  for(th=0;th<TH_NUM;th++){
    pthread_create(&(tids[th]), NULL, iterate_descent_fct_thread, &bounds[th]);
  }
  for(th=0;th<TH_NUM;th++){
    pthread_join(tids[th], NULL);
  }

  double deriv = 0;    
  int f;
  for(f=0;f<n_f;f++){
    int i;
    for(i=0;i<fct_list[f].n;i++){
      if(fct_list[f].valid[i]){
	double delta = 0;
	for(th=0;th<TH_NUM;th++){
	  delta += alpha * th_results[th].deriv_fct_list[f][i];
	}
	if(global_sum_hik_fct[f][i]){
	  fct_list[f].weights[i] += delta / global_sum_hik_fct[f][i];// / n_e;
	}
	deriv += fabs(delta) * fabs(delta);
      }
    }
  }

  for(th=0;th<TH_NUM;th++){
    for(f=0;f<n_f;f++){
      free(th_results[th].deriv_fct_list[f]);
    }
    free(th_results[th].deriv_fct_list);
  }
  
  deriv = sqrt(deriv) / alpha / n_e;
  return deriv;
}
*/

/*
double total_error_fct_list(FlatConfTable *fct_list, Example *examples, int n_f, int n_e){
  assert(fct_list != NULL);
  assert(examples != NULL);

  double total_error = 0;
  
  int e, f;
  for(e=0;e<n_e;e++){
    double x_score = 0;
    for(f=0;f<n_f;f++){
      x_score += get_weight_from_fct(fct_list[f], examples[e].board);
    }
    double g_score = link_function(x_score);
    double case_error = examples[e].score - g_score;
    case_error *= case_error;
    total_error += case_error;
  }
  
  return total_error/n_e;
}
*/


double get_score_from_fct_list(FlatConfTable *fct_list, int n_f, Config_store board){
  double score = 0;
  
  int f;
  for(f=0;f<n_f;f++){
    //unsigned long int index = index_for_config(fct_list[f].pattern, board);
    unsigned long int index = index_for_config_array[f](board);
    score += fct_list[f].weights[index];

  }
  
  return score;
}


