#include "symmetry_map.h"


// defining maps
uint32_t map_reverse_256[256];
uint32_t map_reverse_128[128];
uint32_t map_reverse_64[64];
uint32_t map_reverse_32[32];
uint32_t map_reverse_16[16];

uint32_t map_corner_33[19683];
uint32_t map_edge_xx[59049];


void init_maps(void){
  
  uint64_t index;
  for(index = 0; index < 256; index++){
    uint64_t result = (index * 0x0202020202ULL & 0x010884422010ULL) % 1023;
    map_reverse_256[index] = result;
  }
  for(index = 0; index < 128; index++){
    uint64_t result = map_reverse_256[index << 1];
    map_reverse_128[index] = result;
  }
  for(index = 0; index < 64; index++){
    uint64_t result = map_reverse_256[index << 2];
    map_reverse_64[index] = result;
  }
  for(index = 0; index < 32; index++){
    uint64_t result = map_reverse_256[index << 3];
    map_reverse_32[index] = result;
  }
  for(index = 0; index < 16; index++){
    uint64_t result = map_reverse_256[index << 4];
    map_reverse_16[index] = result;
  }

  uint64_t white, black;
  for(white = 0; white < 512; white++){
    for(black = 0; black < 512; black++){
      if(white & black){
	continue;
      }
      uint64_t result_w = 0;
      uint64_t result_b = 0;
      int r, c;
      for(r = 0; r < 3; r++){
	for(c = 0; c < 3; c++){
	  uint64_t orig_mask = 1 << (c + 3 * r);
	  uint64_t reversed_mask = 1 << (r + 3 * c);
	  if(orig_mask & white){
	    result_w |= reversed_mask;
	  }
	  if(orig_mask & black){
	    result_b |= reversed_mask;
	  }
	  
	}
      }

      int orig_index = offset_19683[white] + _pext_u32(black, ~white);
      int result_index = offset_19683[result_w] + _pext_u32(result_b, ~result_w);

      map_corner_33[orig_index] = result_index;
      
    }
  }

  for(white = 0; white < 1024; white++){
    for(black = 0; black < 1024; black++){
      if(white & black){
	continue;
      }
      uint64_t result_w = map_reverse_256[white >> 2] << 2;
      uint64_t result_b = map_reverse_256[black >> 2] << 2;
      result_w |= map_reverse_256[white & 0x3] >> 6;
      result_b |= map_reverse_256[black & 0x3] >> 6;

      int orig_index = offset_59049[white] + _pext_u32(black, ~white);
      int result_index = offset_59049[result_w] + _pext_u32(result_b, ~result_w);

      map_edge_xx[orig_index] = result_index;
      
    }
  }
  
}


