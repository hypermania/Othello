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
      if(match_one_conf(&examples[j].board, &weight.c[i])){
	hik[i][j] = 1;
      } else {
	hik[i][j] = 0;
      }
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
      if(hik[i][j])
	sum_wi_hik[j] += weight.w[i];
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
      if(hik[i][j]){
	sum_hik[i] += 1;
      }
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
int fit_to_precision(Weight *weight, Example *examples, int N, double alpha, double precision, bool print_iters){
  int i;
  
  char **hik = compute_hik(*weight, examples, N);
  int *sum_hik = compute_sum_hik(*weight, hik, N);

  int iter = 0;
  
  while(1){
    iter++;
    double *sum_wi_hik = compute_sum_wi_hik(*weight, hik, N);
    double *delta = compute_delta(*weight, examples, N, hik, sum_wi_hik, sum_hik, alpha);
    double delta_l1_norm = 0;
    for(i=0;i<weight->n;i++){
	delta_l1_norm += fabs(delta[i]);
	weight->w[i] += delta[i];
    }
    
    if(print_iters && (iter % 1 == 0))
      printf("iteration %5d,    delta_l1_norm = %24.20lf\n", iter, delta_l1_norm);

    bool precision_reached = true;

    for(i=0;i<weight->n;i++){
      if(fabs(delta[i]) > precision){
	precision_reached = false;
	break;
      }
    }
    
    if(precision_reached && (iter > 10))
      break;
    
    free(delta);
    free(sum_wi_hik);
  }

  free(sum_hik);  
  for(i=0;i<weight->n;i++){
    free(hik[i]);
  }
  free(hik);

  return 0;
  
}

double *fit_weight_from_examples(Weight *weight, Example *examples, int N, double alpha){
  assert(weight != NULL);
  assert(examples != NULL);
  assert(N>=0);
  assert(alpha>0);
  
  double *delta = malloc(weight->n * sizeof(double));
  int *sum_hik = malloc(weight->n * sizeof(int));
  char *hik = malloc(weight->n * sizeof(char));
  memset(delta, 0, weight->n * sizeof(double));
  memset(sum_hik, 0, weight->n * sizeof(int));
  
  int i;
  for(i=0;i<N;i++){
    double x_score = weighted_score_for_board_info(*weight, &(examples[i].board), hik);
    if(i < 100 && x_score > 0){
	printf("sum_wi_hik[%d] = %30.20lf\n", i, x_score);
    }
    double g_score = link_function(x_score);
  // weighted_score_for_board_info(*weight, &(examples[i].board), hik));
    double g_deriv = link_function_deriv_relation(g_score);
    int j;
    for(j=0;j<weight->n;j++){
      if(hik[j]){
	delta[j] += alpha * 2 * g_deriv
	  * (examples[i].score - g_score);
	sum_hik[j] += 1;
      }
    }
  }

  
  for(i=0;i<weight->n;i++){
    if(sum_hik[i] != 0){
      delta[i] /= sum_hik[i];
      weight->w[i] += delta[i];
    }
    printf("delta[%d] = %30.20lf\n", i, delta[i]);
  }
  free(hik);
  free(sum_hik);
  //free(delta);
  return delta;
}


double weighted_score_for_board(Weight weight, Config board){
  assert(board != NULL);
  assert(check_board_as_config(*board));
  int i;
  double score = 0;
  for(i=0;i<weight.n;i++){
    if(match_one_conf(board, &weight.c[i])){
      score += weight.w[i];
    }
  }
  
  return score;
}

double weighted_score_for_board_nocreate(Weight weight, Config board){
  assert(board != NULL);
  assert(check_board_as_config(*board));
  int i;
  double score = 0;
  for(i=0;i<weight.n;i++){
    if(match_one_conf(board, &weight.c[i])){
      score += weight.w[i];
    }
  }
  
  return score;

}


double weighted_score_for_board_info(Weight weight, Config board, char *hik){
  assert(board != NULL);
  assert(check_board_as_config(*board));
  assert(hik != NULL);

  double score = 0;
  int i;
  for(i=0;i<weight.n;i++){
    if(match_one_conf(board, &weight.c[i])){
      score += weight.w[i];
      hik[i] = 1;
    } else {
      hik[i] = 0;
    }
  }
  
  return score;
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


Config_store reflect_diag(Config_store config){
  int r,c;
  Config_store result;
  result.x = 0;
  result.w = 0;
  result.b = 0;
  
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(ATOM(r,c) & config.x){
	result.x |= ATOM(c,r);
      } else if(ATOM(r,c) & config.b){
	result.b |= ATOM(c,r);
      } else if(ATOM(r,c) & config.w){
	result.w |= ATOM(c,r);
      }
    }
  }
  return result;
}

Config_store reflect_rdiag(Config_store config){
  int r,c;
  Config_store result;
  result.x = 0;
  result.w = 0;
  result.b = 0;
  
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(ATOM(r,c) & config.x){
	result.x |= ATOM(BOARD_SIZE-1-r, BOARD_SIZE-1-c);
      } else if(ATOM(r,c) & config.b){
	result.b |= ATOM(BOARD_SIZE-1-r, BOARD_SIZE-1-c);	
      } else if(ATOM(r,c) & config.w){
	result.w |= ATOM(BOARD_SIZE-1-r, BOARD_SIZE-1-c);	
      }
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
    //categories[i] = malloc((example_size/CAT_NUM + 1) * sizeof(Example));
    //categories[i] = malloc(TOTAL_GAMES * 4 * sizeof(Example));
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
  
  return 0;

}
