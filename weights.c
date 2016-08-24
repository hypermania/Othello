#include "weights.h"

// defining the weights
double row_1[6561];
double row_2[6561];
double row_3[6561];
double row_4[6561];

double diag_8[6561];
double diag_7[2187];
double diag_6[729];
double diag_5[243];
double diag_4[81];

double corner_33[19683];
double corner_25[59049];

double edge_xx[59049];

// defining the offsets
int offset_81[16];
int offset_243[32];
int offset_729[64];
int offset_2187[128];
int offset_6561[256];
int offset_19683[512];
int offset_59049[1024];


void init_offsets(void){

  void init_one_offset_array(int *array, int num_of_bits){
    int n = 0;
    int index;
    int array_length = ipow(2, num_of_bits);
    for(index = 0; index < array_length; index++){
      int num_of_remaining_bits = num_of_bits - __builtin_popcountl(index);
      int section_size = ipow(2, num_of_remaining_bits);
      array[index] = n;
      n += section_size;
    }
  }

  init_one_offset_array(offset_81, 4);
  init_one_offset_array(offset_243, 5);
  init_one_offset_array(offset_729, 6);
  init_one_offset_array(offset_2187, 7);
  init_one_offset_array(offset_6561, 8);
  init_one_offset_array(offset_19683, 9);
  init_one_offset_array(offset_59049, 10);

}

int check_offsets(void){

  // check those arrays with center reflect symmetry
  int check_one_offset_array_flat(int *array, int num_of_bits){

    int array_size = ipow(3, num_of_bits);
    
    int *counter = malloc(array_size * sizeof(int));
    memset(counter, 0, array_size * sizeof(int));
  
    int index;
    for(index = 0; index < array_size; index++){
      int n = index;
      int white = 0;
      int black = 0;
      int i;
      for(i = 0; i < num_of_bits; i++){
	int ternary_bit = n % 3;
	n = n/3;
	if(ternary_bit == 1){
	  white += ipow(2, i);
	} else if(ternary_bit == 2){
	  black += ipow(2, i);
	}
      }

      if(white & black){
	printf("error: index = %d\n", index);
	return 1;
      }

      counter[array[white] + _pext_u64(black, (~white))]++;
    }

    int i;
    for(i=0;i<array_size;i++){
      if(counter[i] != 1){
	printf("unexpected counter[%d] value: %d\n", i, counter[i]);
	printf("num_of_bits = %d\n", num_of_bits);
	
	return 1;
      }
    }

    free(counter);
    return 0;
  }

  if(check_one_offset_array_flat(offset_81, 4) != 0){
    return 1;
  }
  if(check_one_offset_array_flat(offset_243, 5) != 0){
    return 1;
  }
  if(check_one_offset_array_flat(offset_729, 6) != 0){
    return 1;
  }
  if(check_one_offset_array_flat(offset_2187, 7) != 0){
    return 1;
  }
  if(check_one_offset_array_flat(offset_6561, 8) != 0){
    return 1;
  }
  if(check_one_offset_array_flat(offset_19683, 9) != 0){
    return 1;
  }
  if(check_one_offset_array_flat(offset_59049, 10) != 0){
    return 1;
  }
  
  return 0;
}

void clear_weights(void){
  memset(row_1, 0, sizeof(row_1));
  memset(row_2, 0, sizeof(row_2));
  memset(row_3, 0, sizeof(row_3));
  memset(row_4, 0, sizeof(row_4));
  
  memset(diag_8, 0, sizeof(diag_8));
  memset(diag_7, 0, sizeof(diag_7));
  memset(diag_6, 0, sizeof(diag_6));
  memset(diag_5, 0, sizeof(diag_5));
  memset(diag_4, 0, sizeof(diag_4));
  
  memset(corner_33, 0, sizeof(corner_33));
  memset(corner_25, 0, sizeof(corner_25));
  
  memset(edge_xx, 0, sizeof(edge_xx));
}

int check_weights(void){
    
  int check_one_weight_array_flat(int *offset_array, double *weight_array, int num_of_bits){
    
    int array_size = ipow(3, num_of_bits);
  
    int *counter = malloc(array_size * sizeof(int));
    memset(counter, 0, array_size * sizeof(int));
  
    int index;
    for(index = 0; index < array_size; index++){
      int n = index;
      int white = 0;
      int black = 0;
      int rwhite = 0;
      int rblack = 0;
      int i;
      for(i = 0; i < num_of_bits; i++){
	int ternary_bit = n % 3;
	n = n/3;
	if(ternary_bit == 1){
	  white += ipow(2, i);
	  rwhite += ipow(2, num_of_bits - i - 1);
	} else if(ternary_bit == 2){
	  black += ipow(2, i);
	  rblack += ipow(2, num_of_bits - i - 1);
	}
      }
    
      int orig_index = offset_array[white] + _pext_u64(black, (~white));
      int reflect_index = offset_array[rwhite] + _pext_u64(rblack, (~rwhite));
      int reverse_index = offset_array[black] + _pext_u64(white, (~black));
      int both_index = offset_array[rblack] + _pext_u64(rwhite, (~rblack));

      if(counter[orig_index] == 0){
    
	if((weight_array[orig_index] == weight_array[reflect_index]) &&
	   (weight_array[orig_index] == -weight_array[reverse_index]) &&
	   (weight_array[orig_index] == -weight_array[both_index])){
	
	  counter[orig_index]++;
	  if(counter[reflect_index] == 0){
	    counter[reflect_index]++;
	  }
	  if(counter[reverse_index] == 0){
	    counter[reverse_index]++;
	  }
	  if(counter[both_index] == 0){
	    counter[both_index]++;
	  }
	
	} else {
	  printf("error : index = %d, orig_index = %d\n", index, orig_index);
	  return 1;
	}
      }
    }

    int i;
    for(i=0;i<array_size;i++){
      if(counter[i] != 1){
	printf("i = %d, counter[i] = %d\n", i, counter[i]);
	return 1;
      }
    }
    free(counter);
  
    return 0;
  }

  if(check_one_weight_array_flat(offset_6561, row_1, 8) != 0){
    return 1;
  }
  if(check_one_weight_array_flat(offset_6561, row_2, 8) != 0){
    return 1;
  }
  if(check_one_weight_array_flat(offset_6561, row_3, 8) != 0){
    return 1;
  }
  if(check_one_weight_array_flat(offset_6561, row_4, 8) != 0){
    return 1;
  }
  
  if(check_one_weight_array_flat(offset_6561, diag_8, 8) != 0){
    return 1;
  }
  if(check_one_weight_array_flat(offset_2187, diag_7, 7) != 0){
    return 1;
  }
  if(check_one_weight_array_flat(offset_729, diag_6, 6) != 0){
    return 1;
  }
  if(check_one_weight_array_flat(offset_243, diag_5, 5) != 0){
    return 1;
  }
  if(check_one_weight_array_flat(offset_81, diag_4, 4) != 0){
    return 1;
  }

  int check_one_weight_array_33(int *offset_array, double *weight_array){

    int num_of_bits = 9;
    int array_size = ipow(3, num_of_bits);
  
    int *counter = malloc(array_size * sizeof(int));
    memset(counter, 0, array_size * sizeof(int));
  
    int index;
    for(index = 0; index < array_size; index++){
      int n = index;
      int white = 0;
      int black = 0;
      int rwhite = 0;
      int rblack = 0;
      int i;
      for(i = 0; i < num_of_bits; i++){
	int ternary_bit = n % 3;
	n = n/3;
	if(ternary_bit == 1){
	  white += ipow(2, i);
	  rwhite += ipow(2, 3 * (i%3) + (i/3));
	} else if(ternary_bit == 2){
	  black += ipow(2, i);
	  rblack += ipow(2, 3 * (i%3) + (i/3));
	}
      }
    
      int orig_index = offset_array[white] + _pext_u64(black, (~white));
      int reflect_index = offset_array[rwhite] + _pext_u64(rblack, (~rwhite));
      int reverse_index = offset_array[black] + _pext_u64(white, (~black));
      int both_index = offset_array[rblack] + _pext_u64(rwhite, (~rblack));

      if(counter[orig_index] == 0){
    
	if((weight_array[orig_index] == weight_array[reflect_index]) &&
	   (weight_array[orig_index] == -weight_array[reverse_index]) &&
	   (weight_array[orig_index] == -weight_array[both_index])){
	
	  counter[orig_index]++;
	  if(counter[reflect_index] == 0){
	    counter[reflect_index]++;
	  }
	  if(counter[reverse_index] == 0){
	    counter[reverse_index]++;
	  }
	  if(counter[both_index] == 0){
	    counter[both_index]++;
	  }
	
	} else {
	  printf("error : index = %d, orig_index = %d\n", index, orig_index);
	  return 1;
	}
      }
    }

    int i;
    for(i=0;i<array_size;i++){
      if(counter[i] != 1){
	printf("i = %d, counter[i] = %d\n", i, counter[i]);
	return 1;
      }
    }
    free(counter);
  
    return 0;
  }

  
  if(check_one_weight_array_33(offset_19683, corner_33) != 0){
    return 1;
  }

  // no check for corner_25, since there is no inner symmetry  

  int check_one_weight_array_xx(int *offset_array, double *weight_array){

    int num_of_bits = 10;
    int array_size = ipow(3, num_of_bits);
  
    int *counter = malloc(array_size * sizeof(int));
    memset(counter, 0, array_size * sizeof(int));
  
    int index;
    for(index = 0; index < array_size; index++){
      int n = index;
      int white = 0;
      int black = 0;
      int rwhite = 0;
      int rblack = 0;
      int i;
      for(i = 0; i < num_of_bits; i++){
	int ternary_bit = n % 3;
	n = n/3;
	if(ternary_bit == 1){
	  white += ipow(2, i);
	  rwhite += ipow(2, (i<2) ? (1-i) : (11-i));
	} else if(ternary_bit == 2){
	  black += ipow(2, i);
	  rblack += ipow(2, (i<2) ? (1-i) : (11-i));
	}
      }
    
      int orig_index = offset_array[white] + _pext_u64(black, (~white));
      int reflect_index = offset_array[rwhite] + _pext_u64(rblack, (~rwhite));
      int reverse_index = offset_array[black] + _pext_u64(white, (~black));
      int both_index = offset_array[rblack] + _pext_u64(rwhite, (~rblack));

      if(counter[orig_index] == 0){
    
	if((weight_array[orig_index] == weight_array[reflect_index]) &&
	   (weight_array[orig_index] == -weight_array[reverse_index]) &&
	   (weight_array[orig_index] == -weight_array[both_index])){
	
	  counter[orig_index]++;
	  if(counter[reflect_index] == 0){
	    counter[reflect_index]++;
	  }
	  if(counter[reverse_index] == 0){
	    counter[reverse_index]++;
	  }
	  if(counter[both_index] == 0){
	    counter[both_index]++;
	  }
	
	} else {
	  printf("error : index = %d, orig_index = %d\n", index, orig_index);
	  return 1;
	}
      }
    }

    int i;
    for(i=0;i<array_size;i++){
      if(counter[i] != 1){
	printf("i = %d, counter[i] = %d\n", i, counter[i]);
	return 1;
      }
    }
    free(counter);
  
    return 0;
  }


  if(check_one_weight_array_xx(offset_59049, edge_xx) != 0){
    return 1;
  }


  
  return 0;
}

