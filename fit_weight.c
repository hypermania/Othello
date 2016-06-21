#include "fit_weight.h"

int example_from_seq(State state, Pos *seq, Example *example){
  assert(state != NULL);
  assert(seq != NULL);
  assert(example != NULL);
  
  int count = 0;
  Pos moves[POS_STORE_SIZE]; int movec;
  
  init_state(state);
  while(!state_final(state)){
    
    movec = allowed_moves(state, moves, state->turn);
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
	  * (examples[j].score - g_score);
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
  
  char **hik = compute_hik(weight, examples, N);
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


