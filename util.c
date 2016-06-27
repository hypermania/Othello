#include "util.h"

int ipow(int base, int exp){
  int result = 1;
  while(exp){
    if (exp & 1)
      result *= base;
    exp >>= 1;
    base *= base;
  }
  
  return result;
}

void binarize_items(Pattern *patterns, int *indices, int n){
  if(n<=2){
    int i;
    for(i=0;i<n;i++){
      printf("if(pattern == 0x%016lx) return index_for_config_%02d(config);\n",
	     patterns[i], indices[i]);
    }
    return;
  }

  int half = n/2;
  int best_count = 0;
  unsigned long int best_mask = 0;
  
  int i, j;
  for(i=0;i<1000;i++){
    unsigned long int mask = 0;
    for(j=0;j<64;j++){
      if(!(rand() % 10)){
	mask |= (unsigned long int)1 << j;
      }
    }
    int count = 0;
    for(j=0;j<n;j++){
      if(patterns[j] & mask){
	count++;
      }
    }
    if(abs(best_count - half) > abs(count - half)){
      best_count = count;
      best_mask = mask;
      if(best_count == half)
	break;
    }
  }

  int m = best_count;
  unsigned long int class = best_mask;

  Pattern *left_p = malloc(m * sizeof(Pattern));
  Pattern *right_p = malloc((n-m) * sizeof(Pattern));

  int *left_i = malloc(m * sizeof(int));
  int *right_i = malloc((n-m) * sizeof(int));

  int l = 0; int r = 0;
  
  for(i=0;i<n;i++){
    if(class & patterns[i]){
      left_p[l] = patterns[i];
      left_i[l] = indices[i];
      l++;
    } else {
      right_p[r] = patterns[i];
      right_i[r] = indices[i];
      r++;
    }
  }

  printf("if(pattern & 0x%016lx){\n", class);
  binarize_items(left_p, left_i, m);
  printf("} else {\n");
  binarize_items(right_p, right_i, n-m);
  printf("}\n");

  
  free(left_p);
  free(right_p);
  free(left_i);
  free(right_i);
  
  return;
}
