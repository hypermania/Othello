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


double fit_weight_from_examples(Weight *weight, Example *examples, int n, double alpha){
  assert(weight != NULL);
  assert(examples != NULL);
  assert(n>=0);
  assert(alpha>0);
  
  double *delta = malloc(weight->n * sizeof(double));
  int *sum_hik = malloc(weight->n * sizeof(int));
  char *hik = malloc(weight->n * sizeof(char));
  memset(delta, 0, weight->n * sizeof(double));
  memset(sum_hik, 0, weight->n * sizeof(int));
  
  int i;
  for(i=0;i<n;i++){
    double g_score = link_function(
	   weighted_score_for_board_info(*weight, &(examples[i].board), hik));
    double g_deriv = link_function_deriv_relation(g_score);
    int j;
    for(j=0;j<weight->n;j++){
      if(hik[j]){
	delta[j] += alpha * 2 * g_deriv
	  * (examples[i].score - g_score);
	sum_hik[j] += 1; // += hik[j];
      }
    }
  }
  
  for(i=0;i<weight->n;i++){
    weight->w[i] += delta[i]/sum_hik[i];
  }
  free(hik);
  free(sum_hik);
  free(delta);
  return 0;
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

