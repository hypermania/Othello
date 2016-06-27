#include "pattern.h"

Pattern pattern_reflect_diag(Pattern pattern){
  Pattern result = 0;

  result |= row_diag[(pattern & ROW(7)) >> 0] << 0;
  result |= row_diag[(pattern & ROW(6)) >> 8] << 1;
  result |= row_diag[(pattern & ROW(5)) >> 16] << 2;
  result |= row_diag[(pattern & ROW(4)) >> 24] << 3;
  result |= row_diag[(pattern & ROW(3)) >> 32] << 4;
  result |= row_diag[(pattern & ROW(2)) >> 40] << 5;
  result |= row_diag[(pattern & ROW(1)) >> 48] << 6;
  result |= row_diag[(pattern & ROW(0)) >> 56] << 7;

  return result;
}

Pattern pattern_rotate_90(Pattern pattern){
  Pattern result = 0;
  int r;
  int c;
  for(r=0;r<BOARD_SIZE;r++){
    for(c=0;c<BOARD_SIZE;c++){
      if(ATOM(r,c) & pattern){
	result |= ATOM(BOARD_SIZE - 1 - c, r);
      }
    }
  }
  return result;
}

Pattern pattern_rotate_180(Pattern pattern){
  return pattern_rotate_90(pattern_rotate_90(pattern));
}

Pattern pattern_rotate_270(Pattern pattern){
  return pattern_rotate_90(pattern_rotate_90(pattern_rotate_90(pattern)));
}


Pattern *complete_pattern_set(Pattern *pattern, int n_p, int *n_c){
  int allocated = 10;
  Pattern *result = malloc(allocated * sizeof(Pattern));

  int count = 0;
  int p;
  for(p=0;p<n_p;p++){
    Pattern e = pattern[p];
    Pattern r = pattern_rotate_90(e);
    Pattern rr = pattern_rotate_180(e);
    Pattern rrr = pattern_rotate_270(e);

    Pattern s = pattern_reflect_diag(e);
    Pattern sr = pattern_reflect_diag(r);
    Pattern srr = pattern_reflect_diag(rr);
    Pattern srrr = pattern_reflect_diag(rrr);

    Pattern list[8] = {e, r, rr, rrr, s, sr, srr, srrr};
    int l;
    for(l=0;l<8;l++){
      int i; char is_in_result = 0;
      for(i=0;i<count;i++){
	if(list[l] == result[i]){
	  is_in_result = 1;
	  break;
	}
      }
      if(is_in_result)
	continue;

      if(allocated == count){
	allocated += 10;
	result = realloc(result, allocated * sizeof(Pattern));
      }
      result[count++] = list[l];
    }
  }
  *n_c = count;
  
  return result;
}

