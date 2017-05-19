#include "datpt.h"

int datapoints_from_seq(char seq[2 * MAX_GAME_LENGTH + 1], DataPoint datapoints[MAX_GAME_LENGTH]){
  BitState *state = create_initial_bitstate();
  int turn_num = 0;
  int valid_game = 1;
  while(!bitstate_final(state)){
    int movec;
    BitMask moves = bitstate_allowed_moves(state, &movec);

    if(movec == 0){
      bitstate_skip_turn(state);
      continue;
    } else {
      char col = seq[turn_num * 2] - 'A';
      char row = seq[turn_num * 2 + 1] - '1';
      BitMask pos = ATOM(row, col);

      if((pos & moves) == 0){
	valid_game = 0;
	break;
      }
      
      int move_num = 0;
      for(pos = pos >> 1; pos != 0; pos >>= 1){
	if(moves & pos){
	  move_num++;
	}
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

DataPoint **categorize_datpts(DataPoint *datapoints, long int n_dp, long int cat_sizes[CAT_NUM]){

  DataPoint **categories = malloc(CAT_NUM * sizeof(DataPoint *));
  
  const int chunk = 100;

  long int allocated[CAT_NUM];
  int cat;
  for(cat = 0; cat < CAT_NUM; cat++){
    allocated[cat] = chunk;
    categories[cat] = malloc(allocated[cat] * sizeof(DataPoint));
    cat_sizes[cat] = 0;
  }

  long int i;
  int pieces;
  for(i = 0; i < n_dp; i++){
    pieces = __builtin_popcountll(datapoints[i].board.w) +
      __builtin_popcountll(datapoints[i].board.b);
    cat = CAT(pieces);

    if(cat_sizes[cat] == allocated[cat]){
      allocated[cat] += chunk;
      categories[cat] = realloc(categories[cat], allocated[cat] * sizeof(DataPoint));
    }

    categories[cat][cat_sizes[cat]] = datapoints[i];
    cat_sizes[cat]++;
  }

  for(cat = 0; cat < CAT_NUM; cat++){
    categories[cat] = realloc(categories[cat], cat_sizes[cat] * sizeof(DataPoint));
  }

  return categories;
}
