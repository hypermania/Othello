#include "weights.h"

// defining the weights
/*
double row_1[CAT_NUM][6561];
double row_2[CAT_NUM][6561];
double row_3[CAT_NUM][6561];
double row_4[CAT_NUM][6561];
*/

double row_1[CAT_NUM][256][256];
double row_2[CAT_NUM][256][256];
double row_3[CAT_NUM][256][256];
double row_4[CAT_NUM][256][256];

/*
double diag_8[CAT_NUM][6561];
double diag_7[CAT_NUM][2187];
double diag_6[CAT_NUM][729];
double diag_5[CAT_NUM][243];
double diag_4[CAT_NUM][81];
*/

double diag_8[CAT_NUM][256][256];
double diag_7[CAT_NUM][128][128];
double diag_6[CAT_NUM][64][64];
double diag_5[CAT_NUM][32][32];
double diag_4[CAT_NUM][16][16];

//double corner_33[CAT_NUM][512][512];
double corner_33[CAT_NUM][19683];

//double corner_25[CAT_NUM][1024][1024];
double corner_25[CAT_NUM][59049];

//double edge_xx[CAT_NUM][1024][1024];
double edge_xx[CAT_NUM][59049];


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

  /*
  int check_one_weight_array_flat(int *offset_array, double weight_array[256][256], int num_of_bits){
    
    int array_size = ipow(2, num_of_bits);
  
    int **counter_arr = malloc(array_size * sizeof(int *));
    //memset(counter_arr, 0, array_size * sizeof(int *));

    int sub_arr_i;
    for(sub_arr_i=0;sub_arr_i<array_size;sub_arr_i++){
      counter_arr[sub_arr_i] = malloc(array_size * sizeof(int));
      memset(counter_arr[sub_arr_i], 0, array_size * sizeof(int));
    }
    
    int index_w;
    int index_b;
    for(index_w = 0; index_w < array_size; index_w++){
      for(index_b = 0; index_b < array_size; index_b++){
	if(index_w & index_b){
	  continue;
	}
	
	int white = index_w;
	int black = index_b;
	
	int rwhite = 0;
	int rblack = 0;
	int i;
	for(i = 0; i < num_of_bits; i++){
	  if(white & (1 << i)){
	    rwhite += ipow(2, num_of_bits - i - 1);
	  }
	  if(black & (1 << i)){
	    rblack += ipow(2, num_of_bits - i - 1);
	  }
	}
	
	if(counter_arr[white][black] == 0){
	  printf("point 0, index_w = %d, index_b = %d\n", index_w, index_b);
	  //printf("%016lx\n", weight_array);
	  //printf("%016lx\n", weight_array[0]);
	  if((weight_array[white][black] == weight_array[rwhite][rblack]) &&
	     (weight_array[white][black] == -weight_array[black][white]) &&
	     (weight_array[white][black] == -weight_array[rblack][rwhite])){

	    counter_arr[white][black]++;
	    if(counter_arr[rwhite][rblack] == 0){
	      counter_arr[rwhite][rblack]++;
	    }
	    if(counter_arr[black][white] == 0){
	      counter_arr[black][white]++;
	    }
	    if(counter_arr[rblack][rwhite] == 0){
	      counter_arr[rblack][rwhite]++;
	    }
	
	  } else {
	    printf("error : white = %d, black = %d\n", white, black);
	    return 1;
	  }
	}

      }
    }
    
    int i;
    int j;
    for(i=0;i<array_size;i++){
      for(j=0;j<array_size;j++){
	if(i & j){
	  continue;
	}
	
	if(counter_arr[i][j] != 1){
	  printf("(i,j) = (%d,%d), counter_arr[i] = %d\n", i, j, counter_arr[i]);
	  return 1;
	}
      }
    }
    
    for(i=0;i<array_size;i++){
      free(counter_arr[i]);
    }
    free(counter_arr);
  
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
  */

  /*  
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


  */  
  return 0;

}

void increment_256(double table[256][256], uint32_t white, uint32_t black, double increment){
  if(white & black){
    return;
  }
  if(white == black){
    return;
  }
  
  uint32_t rwhite = map_reverse_256[white];
  uint32_t rblack = map_reverse_256[black];

  if((black == rwhite) && (white == rblack)){
    return;
  }
  
  double new_weight = table[white][black] + increment;  
  table[white][black] = new_weight;
  table[black][white] = -new_weight;
  table[rwhite][rblack] = new_weight;
  table[rblack][rwhite] = -new_weight;
}

void increment_128(double table[128][128], uint32_t white, uint32_t black, double increment){
  if(white & black){
    return;
  }
  if(white == black){
    return;
  }
  
  uint32_t rwhite = map_reverse_128[white];
  uint32_t rblack = map_reverse_128[black];

  if((black == rwhite) && (white == rblack)){
    return;
  }
  
  double new_weight = table[white][black] + increment;  
  table[white][black] = new_weight;
  table[black][white] = -new_weight;
  table[rwhite][rblack] = new_weight;
  table[rblack][rwhite] = -new_weight;
}

void increment_64(double table[64][64], uint32_t white, uint32_t black, double increment){
  if(white & black){
    return;
  }
  if(white == black){
    return;
  }
  
  uint32_t rwhite = map_reverse_64[white];
  uint32_t rblack = map_reverse_64[black];
  
  if((black == rwhite) && (white == rblack)){
    return;
  }
  
  double new_weight = table[white][black] + increment;
  table[white][black] = new_weight;
  table[black][white] = -new_weight;
  table[rwhite][rblack] = new_weight;
  table[rblack][rwhite] = -new_weight;
}

void increment_32(double table[32][32], uint32_t white, uint32_t black, double increment){
  if(white & black){
    return;
  }
  if(white == black){
    return;
  }
  
  uint32_t rwhite = map_reverse_32[white];
  uint32_t rblack = map_reverse_32[black];
  
  if((black == rwhite) && (white == rblack)){
    return;
  }
  
  double new_weight = table[white][black] + increment;
  table[white][black] = new_weight;
  table[black][white] = -new_weight;
  table[rwhite][rblack] = new_weight;
  table[rblack][rwhite] = -new_weight;
}

void increment_16(double table[16][16], uint32_t white, uint32_t black, double increment){
  if(white & black){
    return;
  }
  if(white == black){
    return;
  }
  
  uint32_t rwhite = map_reverse_16[white];
  uint32_t rblack = map_reverse_16[black];
  
  if((black == rwhite) && (white == rblack)){
    return;
  }
  
  double new_weight = table[white][black] + increment;
  table[white][black] = new_weight;
  table[black][white] = -new_weight;
  table[rwhite][rblack] = new_weight;
  table[rblack][rwhite] = -new_weight;
}

void increment_corner_33(double table[19683], uint32_t white, uint32_t black, double increment){
  if(white & black){
    return;
  }
  if(white == black){
    return;
  }
  
  uint32_t rwhite = map_corner_33[white];
  uint32_t rblack = map_corner_33[black];
  
  if((black == rwhite) && (white == rblack)){
    return;
  }

  uint32_t orig_index = offset_19683[white] + _pext_u32(black, ~white);
  uint32_t reverse_index = offset_19683[black] + _pext_u32(white, ~black);
  uint32_t reflect_index = offset_19683[rwhite] + _pext_u32(rblack, ~rwhite);
  uint32_t both_index = offset_19683[rblack] + _pext_u32(rwhite, ~rblack);
  
  double new_weight = table[orig_index] + increment;
  table[orig_index] = new_weight;
  table[reverse_index] = -new_weight;
  table[reflect_index] = new_weight;
  table[both_index] = -new_weight;
}

void increment_corner_25(double table[59049], uint32_t white, uint32_t black, double increment){
  if(white & black){
    return;
  }
  if(white == black){
    return;
  }
  
  uint32_t orig_index = offset_59049[white] + _pext_u32(black, ~white);
  uint32_t reverse_index = offset_59049[black] + _pext_u32(white, ~black);
  
  double new_weight = table[orig_index] + increment;
  table[orig_index] = new_weight;
  table[reverse_index] = -new_weight;
}

void increment_edge_xx(double table[59049], uint32_t white, uint32_t black, double increment){
  if(white & black){
    return;
  }
  if(white == black){
    return;
  }
  
  uint32_t rwhite = map_edge_xx[white];
  uint32_t rblack = map_edge_xx[black];
  
  if((black == rwhite) && (white == rblack)){
    return;
  }

  uint32_t orig_index = offset_59049[white] + _pext_u32(black, ~white);
  uint32_t reverse_index = offset_59049[black] + _pext_u32(white, ~black);
  uint32_t reflect_index = offset_59049[rwhite] + _pext_u32(rblack, ~rwhite);
  uint32_t both_index = offset_59049[rblack] + _pext_u32(rwhite, ~rblack);
  
  double new_weight = table[orig_index] + increment;
  table[orig_index] = new_weight;
  table[reverse_index] = -new_weight;
  table[reflect_index] = new_weight;
  table[both_index] = -new_weight;
}

void increment_global_by_bitboard(BitBoard board, double increment){
  
  int cat = CAT(__builtin_popcountll(board.w) +
		__builtin_popcountll(board.b));
  
  // group theoretic notations for flipped/rotated board:
  // r is for counter-clockwise rotation
  // s is for flip of all columns (flipVertical)

  BitBoard e = board;
  
  BitBoard s = (BitBoard) {flipVertical(e.w),
			   flipVertical(e.b)};
  
  BitBoard r = (BitBoard) {rotate90CounterClockwise(e.w),
			   rotate90CounterClockwise(e.b)};
  
  BitBoard r2 = (BitBoard) {rotate180(e.w),
			    rotate180(e.b)};

  BitBoard r3 = (BitBoard) {rotate90Clockwise(e.w),
			    rotate90Clockwise(e.b)};

  // A1-H8 diagonal flip
  BitBoard sr = (BitBoard) {flipVertical(r.w),
			    flipVertical(r.b)};

  // Horizontal flip
  BitBoard sr2 = (BitBoard) {flipVertical(r2.w),
			     flipVertical(r2.b)};
  // A8-H1 diagonal flip
  BitBoard sr3 = (BitBoard) {flipVertical(r3.w),
			     flipVertical(r3.b)};

  BitBoard *e_ptr = &e;
  //BitBoard *s_ptr = &s;
  //BitBoard *r_ptr = &r;
  //BitBoard *r2_ptr = &r2;
  //BitBoard *r3_ptr = &r3;
  BitBoard *sr_ptr = &sr;
  //BitBoard *sr2_ptr = &sr2;
  //BitBoard *sr3_ptr = &sr3;
  

  // row 1-8
  uint8_t e_w_r1 = *((uint8_t *)e_ptr + 0);
  uint8_t e_w_r2 = *((uint8_t *)e_ptr + 1);
  uint8_t e_w_r3 = *((uint8_t *)e_ptr + 2);
  uint8_t e_w_r4 = *((uint8_t *)e_ptr + 3);
  uint8_t e_w_r5 = *((uint8_t *)e_ptr + 4);
  uint8_t e_w_r6 = *((uint8_t *)e_ptr + 5);
  uint8_t e_w_r7 = *((uint8_t *)e_ptr + 6);
  uint8_t e_w_r8 = *((uint8_t *)e_ptr + 7);

  uint8_t e_b_r1 = *((uint8_t *)e_ptr + 8);
  uint8_t e_b_r2 = *((uint8_t *)e_ptr + 9);
  uint8_t e_b_r3 = *((uint8_t *)e_ptr + 10);
  uint8_t e_b_r4 = *((uint8_t *)e_ptr + 11);
  uint8_t e_b_r5 = *((uint8_t *)e_ptr + 12);
  uint8_t e_b_r6 = *((uint8_t *)e_ptr + 13);
  uint8_t e_b_r7 = *((uint8_t *)e_ptr + 14);
  uint8_t e_b_r8 = *((uint8_t *)e_ptr + 15);

  increment_256(row_1[cat], e_w_r1, e_b_r1, increment);
  increment_256(row_2[cat], e_w_r2, e_b_r2, increment);
  increment_256(row_3[cat], e_w_r3, e_b_r3, increment);
  increment_256(row_4[cat], e_w_r4, e_b_r4, increment);
  increment_256(row_4[cat], e_w_r5, e_b_r5, increment);
  increment_256(row_3[cat], e_w_r6, e_b_r6, increment);
  increment_256(row_2[cat], e_w_r7, e_b_r7, increment);
  increment_256(row_1[cat], e_w_r8, e_b_r8, increment);

  
  // column A-H
  uint8_t sr_w_r1 = *((uint8_t *)sr_ptr + 0);
  uint8_t sr_w_r2 = *((uint8_t *)sr_ptr + 1);
  uint8_t sr_w_r3 = *((uint8_t *)sr_ptr + 2);
  uint8_t sr_w_r4 = *((uint8_t *)sr_ptr + 3);
  uint8_t sr_w_r5 = *((uint8_t *)sr_ptr + 4);
  uint8_t sr_w_r6 = *((uint8_t *)sr_ptr + 5);
  uint8_t sr_w_r7 = *((uint8_t *)sr_ptr + 6);
  uint8_t sr_w_r8 = *((uint8_t *)sr_ptr + 7);

  uint8_t sr_b_r1 = *((uint8_t *)sr_ptr + 8);
  uint8_t sr_b_r2 = *((uint8_t *)sr_ptr + 9);
  uint8_t sr_b_r3 = *((uint8_t *)sr_ptr + 10);
  uint8_t sr_b_r4 = *((uint8_t *)sr_ptr + 11);
  uint8_t sr_b_r5 = *((uint8_t *)sr_ptr + 12);
  uint8_t sr_b_r6 = *((uint8_t *)sr_ptr + 13);
  uint8_t sr_b_r7 = *((uint8_t *)sr_ptr + 14);
  uint8_t sr_b_r8 = *((uint8_t *)sr_ptr + 15);

  increment_256(row_1[cat], sr_w_r1, sr_b_r1, increment);
  increment_256(row_2[cat], sr_w_r2, sr_b_r2, increment);
  increment_256(row_3[cat], sr_w_r3, sr_b_r3, increment);
  increment_256(row_4[cat], sr_w_r4, sr_b_r4, increment);
  increment_256(row_4[cat], sr_w_r5, sr_b_r5, increment);
  increment_256(row_3[cat], sr_w_r6, sr_b_r6, increment);
  increment_256(row_2[cat], sr_w_r7, sr_b_r7, increment);
  increment_256(row_1[cat], sr_w_r8, sr_b_r8, increment);

  
  // diagonals
  uint8_t e_w_d_A1 = _pext_u64(e.w, 0x8040201008040201);
  uint8_t e_w_d_B1 = _pext_u64(e.w, 0x4020100804020100);
  uint8_t e_w_d_C1 = _pext_u64(e.w, 0x2010080402010000);
  uint8_t e_w_d_D1 = _pext_u64(e.w, 0x1008040201000000);
  uint8_t e_w_d_E1 = _pext_u64(e.w, 0x0804020100000000);
  uint8_t e_w_d_A2 = _pext_u64(e.w, 0x0080402010080402);
  uint8_t e_w_d_A3 = _pext_u64(e.w, 0x0000804020100804);
  uint8_t e_w_d_A4 = _pext_u64(e.w, 0x0000008040201008);
  uint8_t e_w_d_A5 = _pext_u64(e.w, 0x0000000080402010);

  uint8_t e_b_d_A1 = _pext_u64(e.b, 0x8040201008040201);
  uint8_t e_b_d_B1 = _pext_u64(e.b, 0x4020100804020100);
  uint8_t e_b_d_C1 = _pext_u64(e.b, 0x2010080402010000);
  uint8_t e_b_d_D1 = _pext_u64(e.b, 0x1008040201000000);
  uint8_t e_b_d_E1 = _pext_u64(e.b, 0x0804020100000000);
  uint8_t e_b_d_A2 = _pext_u64(e.b, 0x0080402010080402);
  uint8_t e_b_d_A3 = _pext_u64(e.b, 0x0000804020100804);
  uint8_t e_b_d_A4 = _pext_u64(e.b, 0x0000008040201008);
  uint8_t e_b_d_A5 = _pext_u64(e.b, 0x0000000080402010);

  increment_256(diag_8[cat], e_w_d_A1, e_b_d_A1, increment);
  increment_128(diag_7[cat], e_w_d_B1, e_b_d_B1, increment);
  increment_128(diag_7[cat], e_w_d_A2, e_b_d_A2, increment);
  increment_64(diag_6[cat], e_w_d_C1, e_b_d_C1, increment);
  increment_64(diag_6[cat], e_w_d_A3, e_b_d_A3, increment);
  increment_32(diag_5[cat], e_w_d_D1, e_b_d_D1, increment);
  increment_32(diag_5[cat], e_w_d_A4, e_b_d_A4, increment);
  increment_16(diag_4[cat], e_w_d_E1, e_b_d_E1, increment);
  increment_16(diag_4[cat], e_w_d_A5, e_b_d_A5, increment);

  
  // anti-diagonals
  uint8_t s_w_d_A1 = _pext_u64(s.w, 0x8040201008040201);
  uint8_t s_w_d_B1 = _pext_u64(s.w, 0x4020100804020100);
  uint8_t s_w_d_C1 = _pext_u64(s.w, 0x2010080402010000);
  uint8_t s_w_d_D1 = _pext_u64(s.w, 0x1008040201000000);
  uint8_t s_w_d_E1 = _pext_u64(s.w, 0x0804020100000000);
  uint8_t s_w_d_A2 = _pext_u64(s.w, 0x0080402010080402);
  uint8_t s_w_d_A3 = _pext_u64(s.w, 0x0000804020100804);
  uint8_t s_w_d_A4 = _pext_u64(s.w, 0x0000008040201008);
  uint8_t s_w_d_A5 = _pext_u64(s.w, 0x0000000080402010);

  uint8_t s_b_d_A1 = _pext_u64(s.b, 0x8040201008040201);
  uint8_t s_b_d_B1 = _pext_u64(s.b, 0x4020100804020100);
  uint8_t s_b_d_C1 = _pext_u64(s.b, 0x2010080402010000);
  uint8_t s_b_d_D1 = _pext_u64(s.b, 0x1008040201000000);
  uint8_t s_b_d_E1 = _pext_u64(s.b, 0x0804020100000000);
  uint8_t s_b_d_A2 = _pext_u64(s.b, 0x0080402010080402);
  uint8_t s_b_d_A3 = _pext_u64(s.b, 0x0000804020100804);
  uint8_t s_b_d_A4 = _pext_u64(s.b, 0x0000008040201008);
  uint8_t s_b_d_A5 = _pext_u64(s.b, 0x0000000080402010);

  increment_256(diag_8[cat], s_w_d_A1, s_b_d_A1, increment);
  increment_128(diag_7[cat], s_w_d_B1, s_b_d_B1, increment);
  increment_128(diag_7[cat], s_w_d_A2, s_b_d_A2, increment);
  increment_64(diag_6[cat], s_w_d_C1, s_b_d_C1, increment);
  increment_64(diag_6[cat], s_w_d_A3, s_b_d_A3, increment);
  increment_32(diag_5[cat], s_w_d_D1, s_b_d_D1, increment);
  increment_32(diag_5[cat], s_w_d_A4, s_b_d_A4, increment);
  increment_16(diag_4[cat], s_w_d_E1, s_b_d_E1, increment);
  increment_16(diag_4[cat], s_w_d_A5, s_b_d_A5, increment);

  
  // corner_33
  uint32_t e_w_c33 = _pext_u64(e.w, 0xE0E0E00000000000);
  uint32_t e_b_c33 = _pext_u64(e.b, 0xE0E0E00000000000);
  uint32_t r_w_c33 = _pext_u64(r.w, 0xE0E0E00000000000);
  uint32_t r_b_c33 = _pext_u64(r.b, 0xE0E0E00000000000);
  uint32_t r2_w_c33 = _pext_u64(r2.w, 0xE0E0E00000000000);
  uint32_t r2_b_c33 = _pext_u64(r2.b, 0xE0E0E00000000000);
  uint32_t r3_w_c33 = _pext_u64(r3.w, 0xE0E0E00000000000);
  uint32_t r3_b_c33 = _pext_u64(r3.b, 0xE0E0E00000000000);

  increment_corner_33(corner_33[cat], e_w_c33, e_b_c33, increment);
  increment_corner_33(corner_33[cat], r_w_c33, r_b_c33, increment);
  increment_corner_33(corner_33[cat], r2_w_c33, r2_b_c33, increment);
  increment_corner_33(corner_33[cat], r3_w_c33, r3_b_c33, increment);
  
  // corner_25
  uint32_t e_w_c25 = _pext_u64(e.w, 0xF8F8000000000000);
  uint32_t e_b_c25 = _pext_u64(e.b, 0xF8F8000000000000);
  uint32_t r_w_c25 = _pext_u64(r.w, 0xF8F8000000000000);
  uint32_t r_b_c25 = _pext_u64(r.b, 0xF8F8000000000000);
  uint32_t r2_w_c25 = _pext_u64(r2.w, 0xF8F8000000000000);
  uint32_t r2_b_c25 = _pext_u64(r2.b, 0xF8F8000000000000);
  uint32_t r3_w_c25 = _pext_u64(r3.w, 0xF8F8000000000000);
  uint32_t r3_b_c25 = _pext_u64(r3.b, 0xF8F8000000000000);
  uint32_t s_w_c25 = _pext_u64(s.w, 0xF8F8000000000000);
  uint32_t s_b_c25 = _pext_u64(s.b, 0xF8F8000000000000);
  uint32_t sr_w_c25 = _pext_u64(sr.w, 0xF8F8000000000000);
  uint32_t sr_b_c25 = _pext_u64(sr.b, 0xF8F8000000000000);
  uint32_t sr2_w_c25 = _pext_u64(sr2.w, 0xF8F8000000000000);
  uint32_t sr2_b_c25 = _pext_u64(sr2.b, 0xF8F8000000000000);
  uint32_t sr3_w_c25 = _pext_u64(sr3.w, 0xF8F8000000000000);
  uint32_t sr3_b_c25 = _pext_u64(sr3.b, 0xF8F8000000000000);

  increment_corner_25(corner_25[cat], e_w_c25, e_b_c25, increment);
  increment_corner_25(corner_25[cat], r_w_c25, r_b_c25, increment);
  increment_corner_25(corner_25[cat], r2_w_c25, r2_b_c25, increment);
  increment_corner_25(corner_25[cat], r3_w_c25, r3_b_c25, increment);
  increment_corner_25(corner_25[cat], s_w_c25, s_b_c25, increment);
  increment_corner_25(corner_25[cat], sr_w_c25, sr_b_c25, increment);
  increment_corner_25(corner_25[cat], sr2_w_c25, sr2_b_c25, increment);
  increment_corner_25(corner_25[cat], sr3_w_c25, sr3_b_c25, increment);
    

  // edge_xx
  uint32_t e_w_xx = _pext_u64(e.w, 0xFF42000000000000);
  uint32_t e_b_xx = _pext_u64(e.b, 0xFF42000000000000);
  uint32_t r_w_xx = _pext_u64(r.w, 0xFF42000000000000);
  uint32_t r_b_xx = _pext_u64(r.b, 0xFF42000000000000);
  uint32_t r2_w_xx = _pext_u64(r2.w, 0xFF42000000000000);
  uint32_t r2_b_xx = _pext_u64(r2.b, 0xFF42000000000000);
  uint32_t r3_w_xx = _pext_u64(r3.w, 0xFF42000000000000);
  uint32_t r3_b_xx = _pext_u64(r3.b, 0xFF42000000000000);

  increment_edge_xx(edge_xx[cat], e_w_xx, e_b_xx, increment);
  increment_edge_xx(edge_xx[cat], r_w_xx, r_b_xx, increment);
  increment_edge_xx(edge_xx[cat], r2_w_xx, r2_b_xx, increment);
  increment_edge_xx(edge_xx[cat], r3_w_xx, r3_b_xx, increment);

}

void increment_by_bitboard(Weights *weights, BitBoard board, double increment){
  
  // group theoretic notations for flipped/rotated board:
  // r is for counter-clockwise rotation
  // s is for flip of all columns (flipVertical)

  BitBoard e = board;
  
  BitBoard s = (BitBoard) {flipVertical(e.w),
			   flipVertical(e.b)};
  
  BitBoard r = (BitBoard) {rotate90CounterClockwise(e.w),
			   rotate90CounterClockwise(e.b)};
  
  BitBoard r2 = (BitBoard) {rotate180(e.w),
			    rotate180(e.b)};

  BitBoard r3 = (BitBoard) {rotate90Clockwise(e.w),
			    rotate90Clockwise(e.b)};

  // A1-H8 diagonal flip
  BitBoard sr = (BitBoard) {flipVertical(r.w),
			    flipVertical(r.b)};

  // Horizontal flip
  BitBoard sr2 = (BitBoard) {flipVertical(r2.w),
			     flipVertical(r2.b)};
  // A8-H1 diagonal flip
  BitBoard sr3 = (BitBoard) {flipVertical(r3.w),
			     flipVertical(r3.b)};

  BitBoard *e_ptr = &e;
  //BitBoard *s_ptr = &s;
  //BitBoard *r_ptr = &r;
  //BitBoard *r2_ptr = &r2;
  //BitBoard *r3_ptr = &r3;
  BitBoard *sr_ptr = &sr;
  //BitBoard *sr2_ptr = &sr2;
  //BitBoard *sr3_ptr = &sr3;
  

  // row 1-8
  uint8_t e_w_r1 = *((uint8_t *)e_ptr + 0);
  uint8_t e_w_r2 = *((uint8_t *)e_ptr + 1);
  uint8_t e_w_r3 = *((uint8_t *)e_ptr + 2);
  uint8_t e_w_r4 = *((uint8_t *)e_ptr + 3);
  uint8_t e_w_r5 = *((uint8_t *)e_ptr + 4);
  uint8_t e_w_r6 = *((uint8_t *)e_ptr + 5);
  uint8_t e_w_r7 = *((uint8_t *)e_ptr + 6);
  uint8_t e_w_r8 = *((uint8_t *)e_ptr + 7);

  uint8_t e_b_r1 = *((uint8_t *)e_ptr + 8);
  uint8_t e_b_r2 = *((uint8_t *)e_ptr + 9);
  uint8_t e_b_r3 = *((uint8_t *)e_ptr + 10);
  uint8_t e_b_r4 = *((uint8_t *)e_ptr + 11);
  uint8_t e_b_r5 = *((uint8_t *)e_ptr + 12);
  uint8_t e_b_r6 = *((uint8_t *)e_ptr + 13);
  uint8_t e_b_r7 = *((uint8_t *)e_ptr + 14);
  uint8_t e_b_r8 = *((uint8_t *)e_ptr + 15);

  increment_256(weights->row_1, e_w_r1, e_b_r1, increment);
  increment_256(weights->row_2, e_w_r2, e_b_r2, increment);
  increment_256(weights->row_3, e_w_r3, e_b_r3, increment);
  increment_256(weights->row_4, e_w_r4, e_b_r4, increment);
  increment_256(weights->row_4, e_w_r5, e_b_r5, increment);
  increment_256(weights->row_3, e_w_r6, e_b_r6, increment);
  increment_256(weights->row_2, e_w_r7, e_b_r7, increment);
  increment_256(weights->row_1, e_w_r8, e_b_r8, increment);

  
  // column A-H
  uint8_t sr_w_r1 = *((uint8_t *)sr_ptr + 0);
  uint8_t sr_w_r2 = *((uint8_t *)sr_ptr + 1);
  uint8_t sr_w_r3 = *((uint8_t *)sr_ptr + 2);
  uint8_t sr_w_r4 = *((uint8_t *)sr_ptr + 3);
  uint8_t sr_w_r5 = *((uint8_t *)sr_ptr + 4);
  uint8_t sr_w_r6 = *((uint8_t *)sr_ptr + 5);
  uint8_t sr_w_r7 = *((uint8_t *)sr_ptr + 6);
  uint8_t sr_w_r8 = *((uint8_t *)sr_ptr + 7);

  uint8_t sr_b_r1 = *((uint8_t *)sr_ptr + 8);
  uint8_t sr_b_r2 = *((uint8_t *)sr_ptr + 9);
  uint8_t sr_b_r3 = *((uint8_t *)sr_ptr + 10);
  uint8_t sr_b_r4 = *((uint8_t *)sr_ptr + 11);
  uint8_t sr_b_r5 = *((uint8_t *)sr_ptr + 12);
  uint8_t sr_b_r6 = *((uint8_t *)sr_ptr + 13);
  uint8_t sr_b_r7 = *((uint8_t *)sr_ptr + 14);
  uint8_t sr_b_r8 = *((uint8_t *)sr_ptr + 15);

  increment_256(weights->row_1, sr_w_r1, sr_b_r1, increment);
  increment_256(weights->row_2, sr_w_r2, sr_b_r2, increment);
  increment_256(weights->row_3, sr_w_r3, sr_b_r3, increment);
  increment_256(weights->row_4, sr_w_r4, sr_b_r4, increment);
  increment_256(weights->row_4, sr_w_r5, sr_b_r5, increment);
  increment_256(weights->row_3, sr_w_r6, sr_b_r6, increment);
  increment_256(weights->row_2, sr_w_r7, sr_b_r7, increment);
  increment_256(weights->row_1, sr_w_r8, sr_b_r8, increment);

  
  // diagonals
  uint8_t e_w_d_A1 = _pext_u64(e.w, 0x8040201008040201);
  uint8_t e_w_d_B1 = _pext_u64(e.w, 0x4020100804020100);
  uint8_t e_w_d_C1 = _pext_u64(e.w, 0x2010080402010000);
  uint8_t e_w_d_D1 = _pext_u64(e.w, 0x1008040201000000);
  uint8_t e_w_d_E1 = _pext_u64(e.w, 0x0804020100000000);
  uint8_t e_w_d_A2 = _pext_u64(e.w, 0x0080402010080402);
  uint8_t e_w_d_A3 = _pext_u64(e.w, 0x0000804020100804);
  uint8_t e_w_d_A4 = _pext_u64(e.w, 0x0000008040201008);
  uint8_t e_w_d_A5 = _pext_u64(e.w, 0x0000000080402010);

  uint8_t e_b_d_A1 = _pext_u64(e.b, 0x8040201008040201);
  uint8_t e_b_d_B1 = _pext_u64(e.b, 0x4020100804020100);
  uint8_t e_b_d_C1 = _pext_u64(e.b, 0x2010080402010000);
  uint8_t e_b_d_D1 = _pext_u64(e.b, 0x1008040201000000);
  uint8_t e_b_d_E1 = _pext_u64(e.b, 0x0804020100000000);
  uint8_t e_b_d_A2 = _pext_u64(e.b, 0x0080402010080402);
  uint8_t e_b_d_A3 = _pext_u64(e.b, 0x0000804020100804);
  uint8_t e_b_d_A4 = _pext_u64(e.b, 0x0000008040201008);
  uint8_t e_b_d_A5 = _pext_u64(e.b, 0x0000000080402010);

  increment_256(weights->diag_8, e_w_d_A1, e_b_d_A1, increment);
  increment_128(weights->diag_7, e_w_d_B1, e_b_d_B1, increment);
  increment_128(weights->diag_7, e_w_d_A2, e_b_d_A2, increment);
  increment_64(weights->diag_6, e_w_d_C1, e_b_d_C1, increment);
  increment_64(weights->diag_6, e_w_d_A3, e_b_d_A3, increment);
  increment_32(weights->diag_5, e_w_d_D1, e_b_d_D1, increment);
  increment_32(weights->diag_5, e_w_d_A4, e_b_d_A4, increment);
  increment_16(weights->diag_4, e_w_d_E1, e_b_d_E1, increment);
  increment_16(weights->diag_4, e_w_d_A5, e_b_d_A5, increment);

  
  // anti-diagonals
  uint8_t s_w_d_A1 = _pext_u64(s.w, 0x8040201008040201);
  uint8_t s_w_d_B1 = _pext_u64(s.w, 0x4020100804020100);
  uint8_t s_w_d_C1 = _pext_u64(s.w, 0x2010080402010000);
  uint8_t s_w_d_D1 = _pext_u64(s.w, 0x1008040201000000);
  uint8_t s_w_d_E1 = _pext_u64(s.w, 0x0804020100000000);
  uint8_t s_w_d_A2 = _pext_u64(s.w, 0x0080402010080402);
  uint8_t s_w_d_A3 = _pext_u64(s.w, 0x0000804020100804);
  uint8_t s_w_d_A4 = _pext_u64(s.w, 0x0000008040201008);
  uint8_t s_w_d_A5 = _pext_u64(s.w, 0x0000000080402010);

  uint8_t s_b_d_A1 = _pext_u64(s.b, 0x8040201008040201);
  uint8_t s_b_d_B1 = _pext_u64(s.b, 0x4020100804020100);
  uint8_t s_b_d_C1 = _pext_u64(s.b, 0x2010080402010000);
  uint8_t s_b_d_D1 = _pext_u64(s.b, 0x1008040201000000);
  uint8_t s_b_d_E1 = _pext_u64(s.b, 0x0804020100000000);
  uint8_t s_b_d_A2 = _pext_u64(s.b, 0x0080402010080402);
  uint8_t s_b_d_A3 = _pext_u64(s.b, 0x0000804020100804);
  uint8_t s_b_d_A4 = _pext_u64(s.b, 0x0000008040201008);
  uint8_t s_b_d_A5 = _pext_u64(s.b, 0x0000000080402010);

  increment_256(weights->diag_8, s_w_d_A1, s_b_d_A1, increment);
  increment_128(weights->diag_7, s_w_d_B1, s_b_d_B1, increment);
  increment_128(weights->diag_7, s_w_d_A2, s_b_d_A2, increment);
  increment_64(weights->diag_6, s_w_d_C1, s_b_d_C1, increment);
  increment_64(weights->diag_6, s_w_d_A3, s_b_d_A3, increment);
  increment_32(weights->diag_5, s_w_d_D1, s_b_d_D1, increment);
  increment_32(weights->diag_5, s_w_d_A4, s_b_d_A4, increment);
  increment_16(weights->diag_4, s_w_d_E1, s_b_d_E1, increment);
  increment_16(weights->diag_4, s_w_d_A5, s_b_d_A5, increment);

  
  // corner_33
  uint32_t e_w_c33 = _pext_u64(e.w, 0xE0E0E00000000000);
  uint32_t e_b_c33 = _pext_u64(e.b, 0xE0E0E00000000000);
  uint32_t r_w_c33 = _pext_u64(r.w, 0xE0E0E00000000000);
  uint32_t r_b_c33 = _pext_u64(r.b, 0xE0E0E00000000000);
  uint32_t r2_w_c33 = _pext_u64(r2.w, 0xE0E0E00000000000);
  uint32_t r2_b_c33 = _pext_u64(r2.b, 0xE0E0E00000000000);
  uint32_t r3_w_c33 = _pext_u64(r3.w, 0xE0E0E00000000000);
  uint32_t r3_b_c33 = _pext_u64(r3.b, 0xE0E0E00000000000);

  increment_corner_33(weights->corner_33, e_w_c33, e_b_c33, increment);
  increment_corner_33(weights->corner_33, r_w_c33, r_b_c33, increment);
  increment_corner_33(weights->corner_33, r2_w_c33, r2_b_c33, increment);
  increment_corner_33(weights->corner_33, r3_w_c33, r3_b_c33, increment);
  
  // corner_25
  uint32_t e_w_c25 = _pext_u64(e.w, 0xF8F8000000000000);
  uint32_t e_b_c25 = _pext_u64(e.b, 0xF8F8000000000000);
  uint32_t r_w_c25 = _pext_u64(r.w, 0xF8F8000000000000);
  uint32_t r_b_c25 = _pext_u64(r.b, 0xF8F8000000000000);
  uint32_t r2_w_c25 = _pext_u64(r2.w, 0xF8F8000000000000);
  uint32_t r2_b_c25 = _pext_u64(r2.b, 0xF8F8000000000000);
  uint32_t r3_w_c25 = _pext_u64(r3.w, 0xF8F8000000000000);
  uint32_t r3_b_c25 = _pext_u64(r3.b, 0xF8F8000000000000);
  uint32_t s_w_c25 = _pext_u64(s.w, 0xF8F8000000000000);
  uint32_t s_b_c25 = _pext_u64(s.b, 0xF8F8000000000000);
  uint32_t sr_w_c25 = _pext_u64(sr.w, 0xF8F8000000000000);
  uint32_t sr_b_c25 = _pext_u64(sr.b, 0xF8F8000000000000);
  uint32_t sr2_w_c25 = _pext_u64(sr2.w, 0xF8F8000000000000);
  uint32_t sr2_b_c25 = _pext_u64(sr2.b, 0xF8F8000000000000);
  uint32_t sr3_w_c25 = _pext_u64(sr3.w, 0xF8F8000000000000);
  uint32_t sr3_b_c25 = _pext_u64(sr3.b, 0xF8F8000000000000);

  increment_corner_25(weights->corner_25, e_w_c25, e_b_c25, increment);
  increment_corner_25(weights->corner_25, r_w_c25, r_b_c25, increment);
  increment_corner_25(weights->corner_25, r2_w_c25, r2_b_c25, increment);
  increment_corner_25(weights->corner_25, r3_w_c25, r3_b_c25, increment);
  increment_corner_25(weights->corner_25, s_w_c25, s_b_c25, increment);
  increment_corner_25(weights->corner_25, sr_w_c25, sr_b_c25, increment);
  increment_corner_25(weights->corner_25, sr2_w_c25, sr2_b_c25, increment);
  increment_corner_25(weights->corner_25, sr3_w_c25, sr3_b_c25, increment);
    

  // edge_xx
  uint32_t e_w_xx = _pext_u64(e.w, 0xFF42000000000000);
  uint32_t e_b_xx = _pext_u64(e.b, 0xFF42000000000000);
  uint32_t r_w_xx = _pext_u64(r.w, 0xFF42000000000000);
  uint32_t r_b_xx = _pext_u64(r.b, 0xFF42000000000000);
  uint32_t r2_w_xx = _pext_u64(r2.w, 0xFF42000000000000);
  uint32_t r2_b_xx = _pext_u64(r2.b, 0xFF42000000000000);
  uint32_t r3_w_xx = _pext_u64(r3.w, 0xFF42000000000000);
  uint32_t r3_b_xx = _pext_u64(r3.b, 0xFF42000000000000);

  increment_edge_xx(weights->edge_xx, e_w_xx, e_b_xx, increment);
  increment_edge_xx(weights->edge_xx, r_w_xx, r_b_xx, increment);
  increment_edge_xx(weights->edge_xx, r2_w_xx, r2_b_xx, increment);
  increment_edge_xx(weights->edge_xx, r3_w_xx, r3_b_xx, increment);
}

// TODO
void increment_by_bitboard_confcount(Weights *weights, BitBoard board, ConfigCounter *confcount, double increment){
  
  // group theoretic notations for flipped/rotated board:
  // r is for counter-clockwise rotation
  // s is for flip of all columns (flipVertical)

  BitBoard e = board;
  
  BitBoard s = (BitBoard) {flipVertical(e.w),
			   flipVertical(e.b)};
  
  BitBoard r = (BitBoard) {rotate90CounterClockwise(e.w),
			   rotate90CounterClockwise(e.b)};
  
  BitBoard r2 = (BitBoard) {rotate180(e.w),
			    rotate180(e.b)};

  BitBoard r3 = (BitBoard) {rotate90Clockwise(e.w),
			    rotate90Clockwise(e.b)};

  // A1-H8 diagonal flip
  BitBoard sr = (BitBoard) {flipVertical(r.w),
			    flipVertical(r.b)};

  // Horizontal flip
  BitBoard sr2 = (BitBoard) {flipVertical(r2.w),
			     flipVertical(r2.b)};
  // A8-H1 diagonal flip
  BitBoard sr3 = (BitBoard) {flipVertical(r3.w),
			     flipVertical(r3.b)};

  BitBoard *e_ptr = &e;
  //BitBoard *s_ptr = &s;
  //BitBoard *r_ptr = &r;
  //BitBoard *r2_ptr = &r2;
  //BitBoard *r3_ptr = &r3;
  BitBoard *sr_ptr = &sr;
  //BitBoard *sr2_ptr = &sr2;
  //BitBoard *sr3_ptr = &sr3;
  

  // row 1-8
  uint8_t e_w_r1 = *((uint8_t *)e_ptr + 0);
  uint8_t e_w_r2 = *((uint8_t *)e_ptr + 1);
  uint8_t e_w_r3 = *((uint8_t *)e_ptr + 2);
  uint8_t e_w_r4 = *((uint8_t *)e_ptr + 3);
  uint8_t e_w_r5 = *((uint8_t *)e_ptr + 4);
  uint8_t e_w_r6 = *((uint8_t *)e_ptr + 5);
  uint8_t e_w_r7 = *((uint8_t *)e_ptr + 6);
  uint8_t e_w_r8 = *((uint8_t *)e_ptr + 7);

  uint8_t e_b_r1 = *((uint8_t *)e_ptr + 8);
  uint8_t e_b_r2 = *((uint8_t *)e_ptr + 9);
  uint8_t e_b_r3 = *((uint8_t *)e_ptr + 10);
  uint8_t e_b_r4 = *((uint8_t *)e_ptr + 11);
  uint8_t e_b_r5 = *((uint8_t *)e_ptr + 12);
  uint8_t e_b_r6 = *((uint8_t *)e_ptr + 13);
  uint8_t e_b_r7 = *((uint8_t *)e_ptr + 14);
  uint8_t e_b_r8 = *((uint8_t *)e_ptr + 15);

  increment_256(weights->row_1, e_w_r1, e_b_r1, increment/confcount->row_1[e_w_r1][e_b_r1]);
  increment_256(weights->row_2, e_w_r2, e_b_r2, increment/confcount->row_2[e_w_r2][e_b_r2]);
  increment_256(weights->row_3, e_w_r3, e_b_r3, increment/confcount->row_3[e_w_r3][e_b_r3]);
  increment_256(weights->row_4, e_w_r4, e_b_r4, increment/confcount->row_4[e_w_r4][e_b_r4]);
  increment_256(weights->row_4, e_w_r5, e_b_r5, increment/confcount->row_4[e_w_r5][e_b_r5]);
  increment_256(weights->row_3, e_w_r6, e_b_r6, increment/confcount->row_3[e_w_r6][e_b_r6]);
  increment_256(weights->row_2, e_w_r7, e_b_r7, increment/confcount->row_2[e_w_r7][e_b_r7]);
  increment_256(weights->row_1, e_w_r8, e_b_r8, increment/confcount->row_1[e_w_r8][e_b_r8]);

  
  // column A-H
  uint8_t sr_w_r1 = *((uint8_t *)sr_ptr + 0);
  uint8_t sr_w_r2 = *((uint8_t *)sr_ptr + 1);
  uint8_t sr_w_r3 = *((uint8_t *)sr_ptr + 2);
  uint8_t sr_w_r4 = *((uint8_t *)sr_ptr + 3);
  uint8_t sr_w_r5 = *((uint8_t *)sr_ptr + 4);
  uint8_t sr_w_r6 = *((uint8_t *)sr_ptr + 5);
  uint8_t sr_w_r7 = *((uint8_t *)sr_ptr + 6);
  uint8_t sr_w_r8 = *((uint8_t *)sr_ptr + 7);

  uint8_t sr_b_r1 = *((uint8_t *)sr_ptr + 8);
  uint8_t sr_b_r2 = *((uint8_t *)sr_ptr + 9);
  uint8_t sr_b_r3 = *((uint8_t *)sr_ptr + 10);
  uint8_t sr_b_r4 = *((uint8_t *)sr_ptr + 11);
  uint8_t sr_b_r5 = *((uint8_t *)sr_ptr + 12);
  uint8_t sr_b_r6 = *((uint8_t *)sr_ptr + 13);
  uint8_t sr_b_r7 = *((uint8_t *)sr_ptr + 14);
  uint8_t sr_b_r8 = *((uint8_t *)sr_ptr + 15);

  increment_256(weights->row_1, sr_w_r1, sr_b_r1, increment/confcount->row_1[sr_w_r1][sr_b_r1]);
  increment_256(weights->row_2, sr_w_r2, sr_b_r2, increment/confcount->row_2[sr_w_r2][sr_b_r2]);
  increment_256(weights->row_3, sr_w_r3, sr_b_r3, increment/confcount->row_3[sr_w_r3][sr_b_r3]);
  increment_256(weights->row_4, sr_w_r4, sr_b_r4, increment/confcount->row_4[sr_w_r4][sr_b_r4]);
  increment_256(weights->row_4, sr_w_r5, sr_b_r5, increment/confcount->row_4[sr_w_r5][sr_b_r5]);
  increment_256(weights->row_3, sr_w_r6, sr_b_r6, increment/confcount->row_3[sr_w_r6][sr_b_r6]);
  increment_256(weights->row_2, sr_w_r7, sr_b_r7, increment/confcount->row_2[sr_w_r7][sr_b_r7]);
  increment_256(weights->row_1, sr_w_r8, sr_b_r8, increment/confcount->row_1[sr_w_r8][sr_b_r8]);

  
  // diagonals
  uint8_t e_w_d_A1 = _pext_u64(e.w, 0x8040201008040201);
  uint8_t e_w_d_B1 = _pext_u64(e.w, 0x4020100804020100);
  uint8_t e_w_d_C1 = _pext_u64(e.w, 0x2010080402010000);
  uint8_t e_w_d_D1 = _pext_u64(e.w, 0x1008040201000000);
  uint8_t e_w_d_E1 = _pext_u64(e.w, 0x0804020100000000);
  uint8_t e_w_d_A2 = _pext_u64(e.w, 0x0080402010080402);
  uint8_t e_w_d_A3 = _pext_u64(e.w, 0x0000804020100804);
  uint8_t e_w_d_A4 = _pext_u64(e.w, 0x0000008040201008);
  uint8_t e_w_d_A5 = _pext_u64(e.w, 0x0000000080402010);

  uint8_t e_b_d_A1 = _pext_u64(e.b, 0x8040201008040201);
  uint8_t e_b_d_B1 = _pext_u64(e.b, 0x4020100804020100);
  uint8_t e_b_d_C1 = _pext_u64(e.b, 0x2010080402010000);
  uint8_t e_b_d_D1 = _pext_u64(e.b, 0x1008040201000000);
  uint8_t e_b_d_E1 = _pext_u64(e.b, 0x0804020100000000);
  uint8_t e_b_d_A2 = _pext_u64(e.b, 0x0080402010080402);
  uint8_t e_b_d_A3 = _pext_u64(e.b, 0x0000804020100804);
  uint8_t e_b_d_A4 = _pext_u64(e.b, 0x0000008040201008);
  uint8_t e_b_d_A5 = _pext_u64(e.b, 0x0000000080402010);

  increment_256(weights->diag_8, e_w_d_A1, e_b_d_A1, increment/confcount->diag_8[e_w_d_A1][e_b_d_A1]);
  increment_128(weights->diag_7, e_w_d_B1, e_b_d_B1, increment/confcount->diag_7[e_w_d_B1][e_b_d_B1]);
  increment_128(weights->diag_7, e_w_d_A2, e_b_d_A2, increment/confcount->diag_7[e_w_d_A2][e_b_d_A2]);
  increment_64(weights->diag_6, e_w_d_C1, e_b_d_C1, increment/confcount->diag_6[e_w_d_C1][e_b_d_C1]);
  increment_64(weights->diag_6, e_w_d_A3, e_b_d_A3, increment/confcount->diag_6[e_w_d_A3][e_b_d_A3]);
  increment_32(weights->diag_5, e_w_d_D1, e_b_d_D1, increment/confcount->diag_5[e_w_d_D1][e_b_d_D1]);
  increment_32(weights->diag_5, e_w_d_A4, e_b_d_A4, increment/confcount->diag_5[e_w_d_A4][e_b_d_A4]);
  increment_16(weights->diag_4, e_w_d_E1, e_b_d_E1, increment/confcount->diag_4[e_w_d_E1][e_b_d_E1]);
  increment_16(weights->diag_4, e_w_d_A5, e_b_d_A5, increment/confcount->diag_4[e_w_d_A5][e_b_d_A5]);

  
  // anti-diagonals
  uint8_t s_w_d_A1 = _pext_u64(s.w, 0x8040201008040201);
  uint8_t s_w_d_B1 = _pext_u64(s.w, 0x4020100804020100);
  uint8_t s_w_d_C1 = _pext_u64(s.w, 0x2010080402010000);
  uint8_t s_w_d_D1 = _pext_u64(s.w, 0x1008040201000000);
  uint8_t s_w_d_E1 = _pext_u64(s.w, 0x0804020100000000);
  uint8_t s_w_d_A2 = _pext_u64(s.w, 0x0080402010080402);
  uint8_t s_w_d_A3 = _pext_u64(s.w, 0x0000804020100804);
  uint8_t s_w_d_A4 = _pext_u64(s.w, 0x0000008040201008);
  uint8_t s_w_d_A5 = _pext_u64(s.w, 0x0000000080402010);

  uint8_t s_b_d_A1 = _pext_u64(s.b, 0x8040201008040201);
  uint8_t s_b_d_B1 = _pext_u64(s.b, 0x4020100804020100);
  uint8_t s_b_d_C1 = _pext_u64(s.b, 0x2010080402010000);
  uint8_t s_b_d_D1 = _pext_u64(s.b, 0x1008040201000000);
  uint8_t s_b_d_E1 = _pext_u64(s.b, 0x0804020100000000);
  uint8_t s_b_d_A2 = _pext_u64(s.b, 0x0080402010080402);
  uint8_t s_b_d_A3 = _pext_u64(s.b, 0x0000804020100804);
  uint8_t s_b_d_A4 = _pext_u64(s.b, 0x0000008040201008);
  uint8_t s_b_d_A5 = _pext_u64(s.b, 0x0000000080402010);

  increment_256(weights->diag_8, s_w_d_A1, s_b_d_A1, increment/confcount->diag_8[s_w_d_A1][s_b_d_A1]);
  increment_128(weights->diag_7, s_w_d_B1, s_b_d_B1, increment/confcount->diag_7[s_w_d_B1][s_b_d_B1]);
  increment_128(weights->diag_7, s_w_d_A2, s_b_d_A2, increment/confcount->diag_7[s_w_d_A2][s_b_d_A2]);
  increment_64(weights->diag_6, s_w_d_C1, s_b_d_C1, increment/confcount->diag_6[s_w_d_C1][s_b_d_C1]);
  increment_64(weights->diag_6, s_w_d_A3, s_b_d_A3, increment/confcount->diag_6[s_w_d_A3][s_b_d_A3]);
  increment_32(weights->diag_5, s_w_d_D1, s_b_d_D1, increment/confcount->diag_5[s_w_d_D1][s_b_d_D1]);
  increment_32(weights->diag_5, s_w_d_A4, s_b_d_A4, increment/confcount->diag_5[s_w_d_A4][s_b_d_A4]);
  increment_16(weights->diag_4, s_w_d_E1, s_b_d_E1, increment/confcount->diag_4[s_w_d_E1][s_b_d_E1]);
  increment_16(weights->diag_4, s_w_d_A5, s_b_d_A5, increment/confcount->diag_4[s_w_d_A5][s_b_d_A5]);

  
  // corner_33
  uint32_t e_w_c33 = _pext_u64(e.w, 0xE0E0E00000000000);
  uint32_t e_b_c33 = _pext_u64(e.b, 0xE0E0E00000000000);
  uint32_t r_w_c33 = _pext_u64(r.w, 0xE0E0E00000000000);
  uint32_t r_b_c33 = _pext_u64(r.b, 0xE0E0E00000000000);
  uint32_t r2_w_c33 = _pext_u64(r2.w, 0xE0E0E00000000000);
  uint32_t r2_b_c33 = _pext_u64(r2.b, 0xE0E0E00000000000);
  uint32_t r3_w_c33 = _pext_u64(r3.w, 0xE0E0E00000000000);
  uint32_t r3_b_c33 = _pext_u64(r3.b, 0xE0E0E00000000000);

  increment_corner_33(weights->corner_33, e_w_c33, e_b_c33, increment/confcount->corner_33[offset_19683[e_w_c33] + _pext_u32(e_b_c33, ~e_w_c33)]);
  increment_corner_33(weights->corner_33, r_w_c33, r_b_c33, increment/confcount->corner_33[offset_19683[r_w_c33] + _pext_u32(r_b_c33, ~r_w_c33)]);
  increment_corner_33(weights->corner_33, r2_w_c33, r2_b_c33, increment/confcount->corner_33[offset_19683[r2_w_c33] + _pext_u32(r2_b_c33, ~r2_w_c33)]);
  increment_corner_33(weights->corner_33, r3_w_c33, r3_b_c33, increment/confcount->corner_33[offset_19683[r3_w_c33] + _pext_u32(r3_b_c33, ~r3_w_c33)]);
  
  // corner_25
  uint32_t e_w_c25 = _pext_u64(e.w, 0xF8F8000000000000);
  uint32_t e_b_c25 = _pext_u64(e.b, 0xF8F8000000000000);
  uint32_t r_w_c25 = _pext_u64(r.w, 0xF8F8000000000000);
  uint32_t r_b_c25 = _pext_u64(r.b, 0xF8F8000000000000);
  uint32_t r2_w_c25 = _pext_u64(r2.w, 0xF8F8000000000000);
  uint32_t r2_b_c25 = _pext_u64(r2.b, 0xF8F8000000000000);
  uint32_t r3_w_c25 = _pext_u64(r3.w, 0xF8F8000000000000);
  uint32_t r3_b_c25 = _pext_u64(r3.b, 0xF8F8000000000000);
  uint32_t s_w_c25 = _pext_u64(s.w, 0xF8F8000000000000);
  uint32_t s_b_c25 = _pext_u64(s.b, 0xF8F8000000000000);
  uint32_t sr_w_c25 = _pext_u64(sr.w, 0xF8F8000000000000);
  uint32_t sr_b_c25 = _pext_u64(sr.b, 0xF8F8000000000000);
  uint32_t sr2_w_c25 = _pext_u64(sr2.w, 0xF8F8000000000000);
  uint32_t sr2_b_c25 = _pext_u64(sr2.b, 0xF8F8000000000000);
  uint32_t sr3_w_c25 = _pext_u64(sr3.w, 0xF8F8000000000000);
  uint32_t sr3_b_c25 = _pext_u64(sr3.b, 0xF8F8000000000000);

  increment_corner_25(weights->corner_25, e_w_c25, e_b_c25, increment/confcount->corner_25[offset_59049[e_w_c25] + _pext_u32(e_b_c25, ~e_w_c25)]);
  increment_corner_25(weights->corner_25, r_w_c25, r_b_c25, increment/confcount->corner_25[offset_59049[r_w_c25] + _pext_u32(r_b_c25, ~r_w_c25)]);
  increment_corner_25(weights->corner_25, r2_w_c25, r2_b_c25, increment/confcount->corner_25[offset_59049[r2_w_c25] + _pext_u32(r2_b_c25, ~r2_w_c25)]);
  increment_corner_25(weights->corner_25, r3_w_c25, r3_b_c25, increment/confcount->corner_25[offset_59049[r3_w_c25] + _pext_u32(r3_b_c25, ~r3_w_c25)]);
  increment_corner_25(weights->corner_25, s_w_c25, s_b_c25, increment/confcount->corner_25[offset_59049[s_w_c25] + _pext_u32(s_b_c25, ~s_w_c25)]);
  increment_corner_25(weights->corner_25, sr_w_c25, sr_b_c25, increment/confcount->corner_25[offset_59049[sr_w_c25] + _pext_u32(sr_b_c25, ~sr_w_c25)]);
  increment_corner_25(weights->corner_25, sr2_w_c25, sr2_b_c25, increment/confcount->corner_25[offset_59049[sr2_w_c25] + _pext_u32(sr2_b_c25, ~sr2_w_c25)]);
  increment_corner_25(weights->corner_25, sr3_w_c25, sr3_b_c25, increment/confcount->corner_25[offset_59049[sr3_w_c25] + _pext_u32(sr3_b_c25, ~sr3_w_c25)]);
    

  // edge_xx
  uint32_t e_w_xx = _pext_u64(e.w, 0xFF42000000000000);
  uint32_t e_b_xx = _pext_u64(e.b, 0xFF42000000000000);
  uint32_t r_w_xx = _pext_u64(r.w, 0xFF42000000000000);
  uint32_t r_b_xx = _pext_u64(r.b, 0xFF42000000000000);
  uint32_t r2_w_xx = _pext_u64(r2.w, 0xFF42000000000000);
  uint32_t r2_b_xx = _pext_u64(r2.b, 0xFF42000000000000);
  uint32_t r3_w_xx = _pext_u64(r3.w, 0xFF42000000000000);
  uint32_t r3_b_xx = _pext_u64(r3.b, 0xFF42000000000000);

  increment_edge_xx(weights->edge_xx, e_w_xx, e_b_xx, increment/confcount->edge_xx[offset_59049[e_w_xx] + _pext_u32(e_b_xx, ~e_w_xx)]);
  increment_edge_xx(weights->edge_xx, r_w_xx, r_b_xx, increment/confcount->edge_xx[offset_59049[r_w_xx] + _pext_u32(r_b_xx, ~r_w_xx)]);
  increment_edge_xx(weights->edge_xx, r2_w_xx, r2_b_xx, increment/confcount->edge_xx[offset_59049[r2_w_xx] + _pext_u32(r2_b_xx, ~r2_w_xx)]);
  increment_edge_xx(weights->edge_xx, r3_w_xx, r3_b_xx, increment/confcount->edge_xx[offset_59049[r3_w_xx] + _pext_u32(r3_b_xx, ~r3_w_xx)]);

}
