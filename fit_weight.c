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
  //memset(weights, 0, sizeof(Weights));

  memcpy(weights->row_1, row_1[cat], sizeof(row_1[cat]));
  memcpy(weights->row_2, row_2[cat], sizeof(row_2[cat]));
  memcpy(weights->row_3, row_3[cat], sizeof(row_3[cat]));
  memcpy(weights->row_4, row_4[cat], sizeof(row_4[cat]));

  memcpy(weights->diag_8, diag_8[cat], sizeof(diag_8[cat]));
  memcpy(weights->diag_7, diag_7[cat], sizeof(diag_7[cat]));
  memcpy(weights->diag_6, diag_6[cat], sizeof(diag_6[cat]));
  memcpy(weights->diag_5, diag_5[cat], sizeof(diag_5[cat]));
  memcpy(weights->diag_4, diag_4[cat], sizeof(diag_4[cat]));

  memcpy(weights->corner_33, corner_33[cat], sizeof(corner_33[cat]));
  memcpy(weights->corner_25, corner_25[cat], sizeof(corner_25[cat]));
  memcpy(weights->edge_xx, edge_xx[cat], sizeof(edge_xx[cat]));

  
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
      //alpha *= 1.02;
    }
    
    if(deriv_diff > 0){
      //alpha /= 1.5;
    }
  }

  //free(hik_abs);
  free(weights);
}

/*
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


*/
