#include "fit_weight.h"

int example_from_seq(State state, Pos *seq, Example *example){
  assert(state != NULL);
  assert(seq != NULL);
  assert(example != NULL);
  
  int count = 0;
  Pos moves[POS_STORE_SIZE]; int movec;
  
  init_state(state);
  while(!state_final(state)){
    
    movec = allowed_moves(state, moves);
    if(movec == 0){
      state_switch_turn(state);
    } else {
      int i; int moved = 0;
      for(i=0;i<movec;i++){
	if(moves[i].r == seq[count].r && moves[i].c == seq[count].c){
	  place_piece(state, seq[count], state->turn);
	  state_switch_turn(state);
	  moved = 1;
	  break;
	}
      }
      if(moved == 0){
	count = 0;
	break;
      }
      board_to_conf(state->board, &(example[count].board));
      count++;
    }
  }
  int i;
  int score = count_pieces(state, W) - count_pieces(state, B);
  for(i=0;i<count;i++){
    example[i].score = score;
  }
  return count;
}

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

int grad_descent(Weight *weight, Example *examples, int N, double alpha, double precision, bool print_iters){
  int i;
  
  char **hik = compute_symmetric_hik(*weight, examples, N);
  int *sum_hik = compute_sum_hik(*weight, hik, N);

  int iter = 0;
  
  double last_deriv_norm = DBL_MAX;
  double delta_norm = 0;
  double deriv_norm = 0;

  double *last_delta = malloc(weight->n * sizeof(double));
  memset(last_delta, 0, weight->n * sizeof(double));

  int count_seq = 0;
  
  while(1){
    iter++;
    double *sum_wi_hik = compute_sum_wi_hik(*weight, hik, N);
    double *delta = compute_delta(*weight, examples, N, hik, sum_wi_hik, sum_hik, alpha);
    delta_norm = 0;
    for(i=0;i<weight->n;i++){
	delta_norm += fabs(delta[i]) * fabs(delta[i]);
	weight->w[i] += delta[i] + 0.5 * last_delta[i];
    }
    delta_norm = sqrt(delta_norm);
    deriv_norm = delta_norm / alpha;

    double quotient = (deriv_norm - last_deriv_norm)/last_deriv_norm;
    
    if(print_iters)
      printf("iteration %5d,    deriv_norm = %12.10lf,   alpha = %12.10lf,   quotient = %12.20lf\n",
	     iter,
	     deriv_norm,
	     alpha,
	     quotient);
    //printf("total error = %30.20lf\n", total_error(*weight, examples, N));

    if(count_seq >= 10 && quotient < 0 && quotient > -0.002){
      alpha *= 1.5;
      count_seq = 0;
    } else if(quotient > 0) {
      alpha /= 10;
    } else {
      count_seq++;
    }
    
    if(deriv_norm < precision){
      free(delta);
      free(sum_wi_hik);
      break;
    }

    memcpy(last_delta, delta, weight->n * sizeof(double));
    
    last_deriv_norm = deriv_norm;
    
    free(delta);
    free(sum_wi_hik);
  }

  free(sum_hik);  
  for(i=0;i<weight->n;i++){
    free(hik[i]);
  }
  free(hik);

  return iter;
  
}

int sto_grad_descent(Weight *weight, Example *examples, int N, double alpha, double precision, bool print_iters){

  char **hik = compute_hik(*weight, examples, N);
  int *sum_hik = compute_sum_hik(*weight, hik, N);


  double *sum_wi_hik_init = compute_sum_wi_hik(*weight, hik, N);
  double *total_delta_init = compute_delta(*weight, examples, N, hik, sum_wi_hik_init, sum_hik, 1);
  
  double init_deriv = 0;
  int w_index;
  for(w_index = 0; w_index < weight->n; w_index++){
    init_deriv += fabs(total_delta_init[w_index]) * fabs(total_delta_init[w_index]);
  }
  init_deriv = sqrt(init_deriv);

  free(sum_wi_hik_init);
  free(total_delta_init);
  
  int iter = 0;
  double alpha_now = alpha;
  double alpha_min = alpha;
  
  while(1){
    iter++;

    int w_index;
    int e_index = rand() % N;

    // compute sum_wi_hik
    double sum_wi_hik = 0;
    for(w_index = 0; w_index < weight->n; w_index++){
      if(hik[w_index][e_index]){
	sum_wi_hik += weight->w[w_index];
      }
    }

    // compute link function values
    double g_score = link_function(sum_wi_hik);
    double g_deriv = link_function_deriv_relation(g_score);

    // compute delta and update weight
    short game_score = examples[e_index].score;    
    for(w_index = 0; w_index < weight->n; w_index++){
      if(hik[w_index][e_index]){
	weight->w[w_index] += g_deriv * (game_score - g_score) * alpha_now;
      }
    }
    
    // check how good is the weight every 10000 iteration
    if(iter % 1000000 == 0){
      // compute total derivative
      double *sum_wi_hik = compute_sum_wi_hik(*weight, hik, N);
      double *total_delta = compute_delta(*weight, examples, N, hik, sum_wi_hik, sum_hik, 1);
      
      double deriv_norm = 0;
      for(w_index = 0; w_index < weight->n; w_index++){
	deriv_norm += fabs(total_delta[w_index]) * fabs(total_delta[w_index]);
      }

      deriv_norm = sqrt(deriv_norm);
      printf("iteration %5d,    deriv_norm = %12.10lf,   alpha = %24.20lf\n",
	     iter,
	     deriv_norm,
	     alpha_now);

      free(sum_wi_hik);
      free(total_delta);
      
      //alpha_now = pow(deriv_norm / init_deriv, 1) * alpha ;
      if(alpha_min < alpha_now){
	alpha_now = alpha_min;
      } else {
	alpha_min = alpha_now;
      }
      
      if(deriv_norm < precision)
	break;
    }

  }
    

  int i;
  for(i=0;i<weight->n;i++){
    free(hik[i]);
  }
  free(sum_hik);
  free(hik);

  return iter;
}


double total_error(Weight weight, Example *examples, int N){

  assert(examples != NULL);
  assert(N > 0);
  
  char **hik = compute_symmetric_hik(weight, examples, N);
  double *sum_wi_hik = compute_sum_wi_hik(weight, hik, N);

  double total_error = 0;
  
  int i;
  for(i=0;i<N;i++){
    double error = examples[i].score - link_function(sum_wi_hik[i]);
    error *= error;
    total_error += error;
  }

  total_error /= N;
  
  free(sum_wi_hik);
  for(i=0;i<weight.n;i++){
    free(hik[i]);
  }
  free(hik);

  return total_error;
}


double link_function(double x){
  return 2*BOARD_SIZE_SQR/(1+exp((-1)*x)) - BOARD_SIZE_SQR;
}

double link_function_deriv_relation(double link_function_val){
  return  (link_function_val + BOARD_SIZE_SQR) * (BOARD_SIZE_SQR - link_function_val) / (2*BOARD_SIZE_SQR);
}

double link_function_2nd_deriv_relation(double g_score, double g_deriv){
  return 2 * g_deriv * g_deriv / (g_score + BOARD_SIZE) - g_deriv;
}

/*
// TODO
Weight symmetrize_weight(Weight *weight){
  assert(weight != NULL);
  
  char *processed = malloc(weight->n * sizeof(char));
  memset(processed, 0, weight->n * sizeof(char));

  Weight result;
  result.c = malloc(4 * weight->n * sizeof(Config_store));
  result.w = malloc(4 * weight->n * sizeof(double));

  int count = 0;
  
  int i; int j;
  for(i=0;i<weight->n;i++){
    if(processed[i])
      continue;
    
    Config_store diag = reflect_diag(weight->c[i]);
    char has_diag = 0; int diag_index = 0;
    Config_store rdiag = reflect_rdiag(weight->c[i]);
    char has_rdiag = 0; int rdiag_index = 0;
    Config_store diag_rdiag = reflect_rdiag(reflect_diag(weight->c[i]));
    char has_diag_rdiag = 0; int diag_rdiag_index = 0;
    
    for(j=i+1;j<weight->n;j++){
      if(memcmp(&diag, &weight->c[j], sizeof(Config_store)) == 0){
	has_diag = 1;
	diag_index = j;
	processed[j] = 1;
      }
      if(memcmp(&rdiag, &weight->c[j], sizeof(Config_store)) == 0){
	has_rdiag = 1;
	rdiag_index = j;
	processed[j] = 1;
      }
      if(memcmp(&diag_rdiag, &weight->c[j], sizeof(Config_store)) == 0){
	has_diag_rdiag = 1;
	diag_rdiag_index = j;
	processed[j] = 1;
      }
    }
    char sum_has = 1 + has_diag + has_rdiag + has_diag_rdiag;
    double sum_weights = weight->w[i] +
      has_diag * weight->w[diag_index] +
      has_rdiag * weight->w[rdiag_index] +
      has_diag_rdiag * weight->w[diag_rdiag_index];
    double avg_weight = sum_weights/sum_has;


    char symm, rsymm = 0;
    if(memcmp(&diag, &weight->c[i], sizeof(Config_store)) == 0)
      symm = 1;
    if(memcmp(&rdiag, &weight->c[i], sizeof(Config_store)) == 0)
      rsymm = 1;

    if((!symm) && (!rsymm)){
      result.c[count] = weight->c[i];
      result.c[count+1] = diag;
      result.c[count+2] = rdiag;
      result.c[count+3] = diag_rdiag;
      result.w[count] = avg_weight;
      result.w[count+1] = avg_weight;
      result.w[count+2] = avg_weight;
      result.w[count+3] = avg_weight;
      
      result.n += 4;
      count += 4;
    } else if(symm){
      result.c[count] = weight->c[i];
      result.c[count+1] = rdiag;
      result.w[count] = avg_weight;
      result.w[count+1] = avg_weight;
      
      result.n += 2;
      count += 2;
    } else if(rsymm){
      result.c[count] = weight->c[i];
      result.c[count+1] = diag;
      result.w[count] = avg_weight;
      result.w[count+1] = avg_weight;
      
      result.n += 2;
      count += 2;
    }
    
  }    
  return result;
}



*/


int sort_examples_into_categories(Example *examples, Example **categories, int *cat_sizes, int example_size){

  const int chunk = 10;
  
  int allocated[CAT_NUM];
  int i;
  for(i=0;i<CAT_NUM;i++){
    allocated[i] = chunk;
    categories[i] = malloc(allocated[i] * sizeof(Example));
    cat_sizes[i] = 0;
  }

  for(i=0;i<example_size;i++){
    int pieces = BOARD_SIZE_SQR - __builtin_popcountl(examples[i].board.x);
    int cat = ((pieces - INIT_PIECE_NUM) - 1) / CATEGORY_SIZE;

    if(cat_sizes[cat] == allocated[cat]){
      allocated[cat] += chunk;
      categories[cat] = realloc(categories[cat], allocated[cat] * sizeof(Example));
    }
    
    categories[cat][cat_sizes[cat]] = examples[i];
    cat_sizes[cat]++;
  }
  // the following were added without testing
  int cat;
  for(cat=0;cat<CAT_NUM;cat++){
    categories[cat] = realloc(categories[cat], cat_sizes[cat] * sizeof(Example));
  }
  
  return 0;

}

Weight init_weight_from_configs(Config configs, int n){
  Weight weight;
  weight.n = n;
  weight.c = malloc(n * sizeof(Config_store));
  weight.w = malloc(n * sizeof(double));

  memcpy(weight.c, configs, n * sizeof(Config_store));
  memset(weight.w, 0, n * sizeof(double));
  
  return weight;
}

void free_weight(Weight weight){
  free(weight.c);
  free(weight.w);
}


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

double get_score_from_fct_list(FlatConfTable *fct_list, int n_f, Config_store board){
  double score = 0;
  
  int f;
  for(f=0;f<n_f;f++){
    unsigned long int index = index_for_config(fct_list[f].pattern, board);
    if(fct_list[f].valid[index]){
      score += fct_list[f].weights[index];
    }
  }
  
  return score;
}
