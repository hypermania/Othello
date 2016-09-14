#include "offset.h"

// defining the offsets
int offset_81[16];
int offset_243[32];
int offset_729[64];
int offset_2187[128];
int offset_6561[256];
int offset_19683[512];
int offset_59049[1024];


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


void init_offsets(void){


  init_one_offset_array(offset_81, 4);
  init_one_offset_array(offset_243, 5);
  init_one_offset_array(offset_729, 6);
  init_one_offset_array(offset_2187, 7);
  init_one_offset_array(offset_6561, 8);
  init_one_offset_array(offset_19683, 9);
  init_one_offset_array(offset_59049, 10);

}

