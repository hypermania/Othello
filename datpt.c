#include "datpt.h"

int datapoints_from_seq(char seq[2 * MAX_GAME_LENGTH + 1], DataPoint datapoints[MAX_GAME_LENGTH]){
  BitState *state = create_initial_bitstate();
  int turn_num = 0;
  int valid_game = 1;
  while(!bitstate_final(state)){
    int movec;
    BitMask *allowed_moves = bitstate_allowed_moves(state, &movec);

    if(movec == 0){
      bitstate_skip_turn(state);
      continue;
    } else {
      char col = seq[turn_num * 2] - 'A';
      char row = seq[turn_num * 2 + 1] - '1';
      BitMask pos = ATOM(row, col);

      int move_num;
      int has_move = 0;
      int index;
      for(index = 0; index < movec; index++){
	if(allowed_moves[index] == pos){
	  move_num = index;
	  has_move = 1;
	  break;
	}
      }

      if(has_move == 0){
	valid_game = 0;
	break;
      }
      
      bitstate_place_piece(state, move_num);

      datapoints[turn_num].board = state->board;
      turn_num++;
    }
  }

  if(valid_game == 0){
    return 0;
  }
  
  double score = (double) (__builtin_popcountll(state->board.w) - __builtin_popcountll(state->board.b));

  int i;
  for(i=0;i<turn_num;i++){
    datapoints[i].score = score;
  }
  
  return turn_num;
}

DataPoint *datapoints_from_file(FILE *fp, long int *n_dp){
  char seq[2 * MAX_GAME_LENGTH + 1];
  DataPoint datapoints[MAX_GAME_LENGTH];

  long allocated = 1000;
  DataPoint *result = malloc(allocated * sizeof(DataPoint));
  (*n_dp) = 0;
  
  while(!feof(fp)){
    memset(seq, 0, sizeof(seq));
    memset(datapoints, 0, sizeof(datapoints));

    fgets(seq, sizeof(seq), fp);

    int turns = datapoints_from_seq(seq, datapoints);

    if(allocated - (*n_dp) < MAX_GAME_LENGTH){
      allocated += 10000;
      result = realloc(result, allocated * sizeof(DataPoint));
    }

    memcpy(result + (*n_dp), datapoints, turns * sizeof(DataPoint));

    (*n_dp) += turns;
  }

  result = realloc(result, (*n_dp) * sizeof(DataPoint));
  
  return result;
}
