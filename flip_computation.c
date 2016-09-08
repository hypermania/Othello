#include "flip_computation.h"

uint8_t flipped_bits[8][256][256];
uint64_t diags_store[15];
uint64_t anti_diags[15];

uint64_t * const diags = diags_store + 7;

void init_flipped_bits(void){
  
  memset(flipped_bits, 0, sizeof(flipped_bits));
  // flipped_bits[pos][my][opp]
  uint32_t my, opp;
  int pos;
  for(pos = 0; pos < 8; pos++){
    for(my = 0; my < 256; my++){
      for(opp = 0; opp < 256; opp++){
	if(my & opp){
	  continue;
	}
	uint32_t pos_mask = 0x80 >> pos;
	if((pos_mask & my) || (pos_mask & opp)){
	  continue;
	}
	
	uint32_t flipped = 0;
	uint32_t temp_mask;
	int is_flipped;
	// flipping right-hand-side discs
	is_flipped = 0;
	temp_mask = pos_mask >> 1;
	while(temp_mask & opp){
	  temp_mask >>= 1;
	}
	if(temp_mask & my){
	  is_flipped = 1;
	}
	if(is_flipped){
	  temp_mask <<= 1;
	  while(temp_mask & opp){
	    flipped |= temp_mask;
	    temp_mask <<= 1;
	  }
	}

	// flipping left-hand-side discs
	is_flipped = 0;
	temp_mask = pos_mask << 1;
	while(temp_mask & opp){
	  temp_mask <<= 1;
	}
	if(temp_mask & my){
	  is_flipped = 1;
	}
	if(is_flipped){
	  temp_mask >>= 1;
	  while(temp_mask & opp){
	    flipped |= temp_mask;
	    temp_mask >>= 1;
	  }
	}

	// flipping the placed disc
	if(flipped != 0){
	  flipped |= pos_mask;
	}
	
	// storing result
	flipped_bits[pos][my][opp] = flipped;
	
      }
    }
  }
}

void init_diags(void){
  /*
  memset(diags_store, 0, sizeof(diags_store));
  memset(anti_diags, 0, sizeof(anti_diags));
  
  int shift;
  
  uint64_t mid_diag = 0x8040201008040201;
  for(shift = 0; shift <= 7; shift++){
    diags[shift] = (mid_diag >> shift) & ((~0) << (shift * 8));
  }
  for(shift = 1; shift <= 7; shift++){
    diags[-shift] = (mid_diag << shift) & ((~0) >> (shift * 8));
  }
  */
  diags[-7] = 0x0000000000000080;
  diags[-6] = 0x0000000000008040;
  diags[-5] = 0x0000000000804020;
  diags[-4] = 0x0000000080402010;
  diags[-3] = 0x0000008040201008;
  diags[-2] = 0x0000804020100804;
  diags[-1] = 0x0080402010080402;
  diags[0] = 0x8040201008040201;
  diags[1] = 0x4020100804020100;
  diags[2] = 0x2010080402010000;
  diags[3] = 0x1008040201000000;
  diags[4] = 0x0804020100000000;
  diags[5] = 0x0402010000000000;
  diags[6] = 0x0201000000000000;
  diags[7] = 0x0100000000000000;

  anti_diags[0] = 0x8000000000000000;
  anti_diags[1] = 0x4080000000000000;
  anti_diags[2] = 0x2040800000000000;
  anti_diags[3] = 0x1020408000000000;
  anti_diags[4] = 0x0810204080000000;
  anti_diags[5] = 0x0408102040800000;
  anti_diags[6] = 0x0204081020408000;
  anti_diags[7] = 0x0102040810204080;
  anti_diags[8] = 0x0001020408102040;
  anti_diags[9] = 0x0000010204081020;
  anti_diags[10] = 0x0000000102040810;
  anti_diags[11] = 0x0000000001020408;
  anti_diags[12] = 0x0000000000010204;
  anti_diags[13] = 0x0000000000000102;
  anti_diags[14] = 0x0000000000000001;
  
}

void REGPARM(2) flip_bitboard_via_pext_w(BitBoard *board, int pos_index){
  int r = pos_index / 8;
  int c = pos_index % 8;

  int index_1, index_2;
  index_1 = c - r;
  index_2 = c + r;
  
  uint64_t row = ROW(r);
  uint64_t col = COL(c);
  uint64_t diag = diags[index_1];
  uint64_t anti_diag = anti_diags[index_2];
  
  uint8_t row_w = _pext_u64(board->w, row);
  uint8_t row_b = _pext_u64(board->b, row);
  uint8_t col_w = _pext_u64(board->w, col);
  uint8_t col_b = _pext_u64(board->b, col);

  uint8_t diag_w = _pext_u64(board->w, diag);
  uint8_t diag_b = _pext_u64(board->b, diag);
  uint8_t anti_diag_w = _pext_u64(board->w, anti_diag);
  uint8_t anti_diag_b = _pext_u64(board->b, anti_diag);

  int diag_pos = (index_1 > 0) ? c : r;
  int anti_diag_pos = (index_2 - 7 > 0) ? r : (7 - c);
  uint8_t row_flipped = flipped_bits[c][row_w][row_b];
  uint8_t col_flipped = flipped_bits[r][col_w][col_b];
  uint8_t diag_flipped = flipped_bits[diag_pos][diag_w][diag_b];
  uint8_t anti_diag_flipped = flipped_bits[anti_diag_pos][anti_diag_w][anti_diag_b];
  

  uint64_t row_mask = _pdep_u64(row_flipped, row);
  uint64_t col_mask = _pdep_u64(col_flipped, col);
  uint64_t diag_mask = _pdep_u64(diag_flipped, diag);
  uint64_t anti_diag_mask = _pdep_u64(anti_diag_flipped, anti_diag);

  uint64_t flipped = row_mask | col_mask | diag_mask | anti_diag_mask;

  board->w |= flipped;
  board->b &= ~flipped;
}

void REGPARM(2) flip_bitboard_via_pext_b(BitBoard *board, int pos_index){
  int r = pos_index / 8;
  int c = pos_index % 8;

  int index_1, index_2;
  index_1 = c - r;
  index_2 = c + r;
  
  uint64_t row = ROW(r);
  uint64_t col = COL(c);
  uint64_t diag = diags[index_1];
  uint64_t anti_diag = anti_diags[index_2];

  uint8_t row_w = _pext_u64(board->w, row);
  uint8_t row_b = _pext_u64(board->b, row);
  uint8_t col_w = _pext_u64(board->w, col);
  uint8_t col_b = _pext_u64(board->b, col);

  uint8_t diag_w = _pext_u64(board->w, diag);
  uint8_t diag_b = _pext_u64(board->b, diag);
  uint8_t anti_diag_w = _pext_u64(board->w, anti_diag);
  uint8_t anti_diag_b = _pext_u64(board->b, anti_diag);
  
  int diag_pos = (index_1 > 0) ? c : r;
  int anti_diag_pos = (index_2 - 7 > 0) ? r : (7 - c);
  uint8_t row_flipped = flipped_bits[c][row_b][row_w];
  uint8_t col_flipped = flipped_bits[r][col_b][col_w];
  uint8_t diag_flipped = flipped_bits[diag_pos][diag_b][diag_w];
  uint8_t anti_diag_flipped = flipped_bits[anti_diag_pos][anti_diag_b][anti_diag_w];
  
  //printf("anti_diag_w = %u, anti_diag_b = %u\n", anti_diag_w, anti_diag_b);
  //printf("anti_diag_pos = %u\n", anti_diag_pos);

  uint64_t row_mask = _pdep_u64(row_flipped, row);
  uint64_t col_mask = _pdep_u64(col_flipped, col);
  uint64_t diag_mask = _pdep_u64(diag_flipped, diag);
  uint64_t anti_diag_mask = _pdep_u64(anti_diag_flipped, anti_diag);

  uint64_t flipped = row_mask | col_mask | diag_mask | anti_diag_mask;

  board->b |= flipped;
  board->w &= ~flipped;
}

// TODO
void REGPARM(2) flip_bitboard_w_assembly(BitBoard *board, int pos_index){
  // %rdi : 1st argument
  // %rsi : 2nd argument
  asm (
       "push %r15\n"
       "push %r14\n"
       "push %r13\n"
       "push %r12\n"
       "push %rbp\n"
       "push %rbx\n"
       "movl %esi, %ebp\n"
       "shr $0x3, %esi\n" // int r
       "andl $0x7, %ebp\n" // int c
       "movl %esi, %ecx\n"
       "movl %ebp, %edx\n"
       "subl %esi, %ecx\n"
       "addl %esi, %edx\n"
       "movabs $0xff00000000000000, %r8\n"
       "movabs $0x8080808080808080, %r9\n"
       "shl $0x3, %rsi\n" // r -> 8 * r
       "shrx %rsi, %r8, %r8\n"
       "shrx %rbp, %r9, %r9\n"
       "shr $0x3, %rsi\n"
       

       
       "pop %rbx\n"
       "pop %rbp\n"
       "pop %r12\n"
       "pop %r13\n"
       "pop %r14\n"
       "pop %r15\n"
       );
}

