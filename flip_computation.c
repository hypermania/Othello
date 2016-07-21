#include "flip_computation.h"

char flip_bitboard_w_00(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_4;
  if(opp & 0x4000000000000000){
    count_4 = 0;
    if(opp & 0x2000000000000000){
      count_4++;
      if(opp & 0x1000000000000000){
	count_4++;
	if(opp & 0x0800000000000000){
	  count_4++;
	  if(opp & 0x0400000000000000){
	    count_4++;
	    if(opp & 0x0200000000000000){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[0][4][count_4], 1)){
      board->b ^= rays_to_flip[0][4][count_4];
      board->w ^= rays_to_flip[0][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0080000000000000){
    count_6 = 0;
    if(opp & 0x0000800000000000){
      count_6++;
      if(opp & 0x0000008000000000){
	count_6++;
	if(opp & 0x0000000080000000){
	  count_6++;
	  if(opp & 0x0000000000800000){
	    count_6++;
	    if(opp & 0x0000000000008000){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[0][6][count_6], 8)){
      board->b ^= rays_to_flip[0][6][count_6];
      board->w ^= rays_to_flip[0][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0040000000000000){
    count_7 = 0;
    if(opp & 0x0000200000000000){
      count_7++;
      if(opp & 0x0000001000000000){
	count_7++;
	if(opp & 0x0000000008000000){
	  count_7++;
	  if(opp & 0x0000000000040000){
	    count_7++;
	    if(opp & 0x0000000000000200){
	      count_7++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[0][7][count_7], 9)){
      board->b ^= rays_to_flip[0][7][count_7];
      board->w ^= rays_to_flip[0][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x8000000000000000;

  return result;
}

char flip_bitboard_w_01(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_4;
  if(opp & 0x2000000000000000){
    count_4 = 0;
    if(opp & 0x1000000000000000){
      count_4++;
      if(opp & 0x0800000000000000){
	count_4++;
	if(opp & 0x0400000000000000){
	  count_4++;
	  if(opp & 0x0200000000000000){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[1][4][count_4], 1)){
      board->b ^= rays_to_flip[1][4][count_4];
      board->w ^= rays_to_flip[1][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0040000000000000){
    count_6 = 0;
    if(opp & 0x0000400000000000){
      count_6++;
      if(opp & 0x0000004000000000){
	count_6++;
	if(opp & 0x0000000040000000){
	  count_6++;
	  if(opp & 0x0000000000400000){
	    count_6++;
	    if(opp & 0x0000000000004000){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[1][6][count_6], 8)){
      board->b ^= rays_to_flip[1][6][count_6];
      board->w ^= rays_to_flip[1][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0020000000000000){
    count_7 = 0;
    if(opp & 0x0000100000000000){
      count_7++;
      if(opp & 0x0000000800000000){
	count_7++;
	if(opp & 0x0000000004000000){
	  count_7++;
	  if(opp & 0x0000000000020000){
	    count_7++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[1][7][count_7], 9)){
      board->b ^= rays_to_flip[1][7][count_7];
      board->w ^= rays_to_flip[1][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x4000000000000000;

  return result;
}

char flip_bitboard_w_02(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_3;
  if(opp & 0x4000000000000000){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[2][3][count_3], -1)){
      board->b ^= rays_to_flip[2][3][count_3];
      board->w ^= rays_to_flip[2][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x1000000000000000){
    count_4 = 0;
    if(opp & 0x0800000000000000){
      count_4++;
      if(opp & 0x0400000000000000){
	count_4++;
	if(opp & 0x0200000000000000){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[2][4][count_4], 1)){
      board->b ^= rays_to_flip[2][4][count_4];
      board->w ^= rays_to_flip[2][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0040000000000000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[2][5][count_5], 7)){
      board->b ^= rays_to_flip[2][5][count_5];
      board->w ^= rays_to_flip[2][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0020000000000000){
    count_6 = 0;
    if(opp & 0x0000200000000000){
      count_6++;
      if(opp & 0x0000002000000000){
	count_6++;
	if(opp & 0x0000000020000000){
	  count_6++;
	  if(opp & 0x0000000000200000){
	    count_6++;
	    if(opp & 0x0000000000002000){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[2][6][count_6], 8)){
      board->b ^= rays_to_flip[2][6][count_6];
      board->w ^= rays_to_flip[2][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0010000000000000){
    count_7 = 0;
    if(opp & 0x0000080000000000){
      count_7++;
      if(opp & 0x0000000400000000){
	count_7++;
	if(opp & 0x0000000002000000){
	  count_7++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[2][7][count_7], 9)){
      board->b ^= rays_to_flip[2][7][count_7];
      board->w ^= rays_to_flip[2][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x2000000000000000;

  return result;
}

char flip_bitboard_w_03(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_3;
  if(opp & 0x2000000000000000){
    count_3 = 0;
    if(opp & 0x4000000000000000){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[3][3][count_3], -1)){
      board->b ^= rays_to_flip[3][3][count_3];
      board->w ^= rays_to_flip[3][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0800000000000000){
    count_4 = 0;
    if(opp & 0x0400000000000000){
      count_4++;
      if(opp & 0x0200000000000000){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[3][4][count_4], 1)){
      board->b ^= rays_to_flip[3][4][count_4];
      board->w ^= rays_to_flip[3][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0020000000000000){
    count_5 = 0;
    if(opp & 0x0000400000000000){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[3][5][count_5], 7)){
      board->b ^= rays_to_flip[3][5][count_5];
      board->w ^= rays_to_flip[3][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0010000000000000){
    count_6 = 0;
    if(opp & 0x0000100000000000){
      count_6++;
      if(opp & 0x0000001000000000){
	count_6++;
	if(opp & 0x0000000010000000){
	  count_6++;
	  if(opp & 0x0000000000100000){
	    count_6++;
	    if(opp & 0x0000000000001000){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[3][6][count_6], 8)){
      board->b ^= rays_to_flip[3][6][count_6];
      board->w ^= rays_to_flip[3][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0008000000000000){
    count_7 = 0;
    if(opp & 0x0000040000000000){
      count_7++;
      if(opp & 0x0000000200000000){
	count_7++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[3][7][count_7], 9)){
      board->b ^= rays_to_flip[3][7][count_7];
      board->w ^= rays_to_flip[3][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x1000000000000000;

  return result;
}

char flip_bitboard_w_04(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_3;
  if(opp & 0x1000000000000000){
    count_3 = 0;
    if(opp & 0x2000000000000000){
      count_3++;
      if(opp & 0x4000000000000000){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[4][3][count_3], -1)){
      board->b ^= rays_to_flip[4][3][count_3];
      board->w ^= rays_to_flip[4][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0400000000000000){
    count_4 = 0;
    if(opp & 0x0200000000000000){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[4][4][count_4], 1)){
      board->b ^= rays_to_flip[4][4][count_4];
      board->w ^= rays_to_flip[4][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0010000000000000){
    count_5 = 0;
    if(opp & 0x0000200000000000){
      count_5++;
      if(opp & 0x0000004000000000){
	count_5++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[4][5][count_5], 7)){
      board->b ^= rays_to_flip[4][5][count_5];
      board->w ^= rays_to_flip[4][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0008000000000000){
    count_6 = 0;
    if(opp & 0x0000080000000000){
      count_6++;
      if(opp & 0x0000000800000000){
	count_6++;
	if(opp & 0x0000000008000000){
	  count_6++;
	  if(opp & 0x0000000000080000){
	    count_6++;
	    if(opp & 0x0000000000000800){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[4][6][count_6], 8)){
      board->b ^= rays_to_flip[4][6][count_6];
      board->w ^= rays_to_flip[4][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0004000000000000){
    count_7 = 0;
    if(opp & 0x0000020000000000){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[4][7][count_7], 9)){
      board->b ^= rays_to_flip[4][7][count_7];
      board->w ^= rays_to_flip[4][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0800000000000000;

  return result;
}

char flip_bitboard_w_05(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_3;
  if(opp & 0x0800000000000000){
    count_3 = 0;
    if(opp & 0x1000000000000000){
      count_3++;
      if(opp & 0x2000000000000000){
	count_3++;
	if(opp & 0x4000000000000000){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[5][3][count_3], -1)){
      board->b ^= rays_to_flip[5][3][count_3];
      board->w ^= rays_to_flip[5][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0200000000000000){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[5][4][count_4], 1)){
      board->b ^= rays_to_flip[5][4][count_4];
      board->w ^= rays_to_flip[5][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0008000000000000){
    count_5 = 0;
    if(opp & 0x0000100000000000){
      count_5++;
      if(opp & 0x0000002000000000){
	count_5++;
	if(opp & 0x0000000040000000){
	  count_5++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[5][5][count_5], 7)){
      board->b ^= rays_to_flip[5][5][count_5];
      board->w ^= rays_to_flip[5][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0004000000000000){
    count_6 = 0;
    if(opp & 0x0000040000000000){
      count_6++;
      if(opp & 0x0000000400000000){
	count_6++;
	if(opp & 0x0000000004000000){
	  count_6++;
	  if(opp & 0x0000000000040000){
	    count_6++;
	    if(opp & 0x0000000000000400){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[5][6][count_6], 8)){
      board->b ^= rays_to_flip[5][6][count_6];
      board->w ^= rays_to_flip[5][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0002000000000000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[5][7][count_7], 9)){
      board->b ^= rays_to_flip[5][7][count_7];
      board->w ^= rays_to_flip[5][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0400000000000000;

  return result;
}

char flip_bitboard_w_06(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_3;
  if(opp & 0x0400000000000000){
    count_3 = 0;
    if(opp & 0x0800000000000000){
      count_3++;
      if(opp & 0x1000000000000000){
	count_3++;
	if(opp & 0x2000000000000000){
	  count_3++;
	  if(opp & 0x4000000000000000){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[6][3][count_3], -1)){
      board->b ^= rays_to_flip[6][3][count_3];
      board->w ^= rays_to_flip[6][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0004000000000000){
    count_5 = 0;
    if(opp & 0x0000080000000000){
      count_5++;
      if(opp & 0x0000001000000000){
	count_5++;
	if(opp & 0x0000000020000000){
	  count_5++;
	  if(opp & 0x0000000000400000){
	    count_5++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[6][5][count_5], 7)){
      board->b ^= rays_to_flip[6][5][count_5];
      board->w ^= rays_to_flip[6][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0002000000000000){
    count_6 = 0;
    if(opp & 0x0000020000000000){
      count_6++;
      if(opp & 0x0000000200000000){
	count_6++;
	if(opp & 0x0000000002000000){
	  count_6++;
	  if(opp & 0x0000000000020000){
	    count_6++;
	    if(opp & 0x0000000000000200){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[6][6][count_6], 8)){
      board->b ^= rays_to_flip[6][6][count_6];
      board->w ^= rays_to_flip[6][6][count_6];
      result |= 0x40;
    }
  }

  board->w |= 0x0200000000000000;

  return result;
}

char flip_bitboard_w_07(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_3;
  if(opp & 0x0200000000000000){
    count_3 = 0;
    if(opp & 0x0400000000000000){
      count_3++;
      if(opp & 0x0800000000000000){
	count_3++;
	if(opp & 0x1000000000000000){
	  count_3++;
	  if(opp & 0x2000000000000000){
	    count_3++;
	    if(opp & 0x4000000000000000){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[7][3][count_3], -1)){
      board->b ^= rays_to_flip[7][3][count_3];
      board->w ^= rays_to_flip[7][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0002000000000000){
    count_5 = 0;
    if(opp & 0x0000040000000000){
      count_5++;
      if(opp & 0x0000000800000000){
	count_5++;
	if(opp & 0x0000000010000000){
	  count_5++;
	  if(opp & 0x0000000000200000){
	    count_5++;
	    if(opp & 0x0000000000004000){
	      count_5++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[7][5][count_5], 7)){
      board->b ^= rays_to_flip[7][5][count_5];
      board->w ^= rays_to_flip[7][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0001000000000000){
    count_6 = 0;
    if(opp & 0x0000010000000000){
      count_6++;
      if(opp & 0x0000000100000000){
	count_6++;
	if(opp & 0x0000000001000000){
	  count_6++;
	  if(opp & 0x0000000000010000){
	    count_6++;
	    if(opp & 0x0000000000000100){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[7][6][count_6], 8)){
      board->b ^= rays_to_flip[7][6][count_6];
      board->w ^= rays_to_flip[7][6][count_6];
      result |= 0x40;
    }
  }

  board->w |= 0x0100000000000000;

  return result;
}

char flip_bitboard_w_08(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_4;
  if(opp & 0x0040000000000000){
    count_4 = 0;
    if(opp & 0x0020000000000000){
      count_4++;
      if(opp & 0x0010000000000000){
	count_4++;
	if(opp & 0x0008000000000000){
	  count_4++;
	  if(opp & 0x0004000000000000){
	    count_4++;
	    if(opp & 0x0002000000000000){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[8][4][count_4], 1)){
      board->b ^= rays_to_flip[8][4][count_4];
      board->w ^= rays_to_flip[8][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000800000000000){
    count_6 = 0;
    if(opp & 0x0000008000000000){
      count_6++;
      if(opp & 0x0000000080000000){
	count_6++;
	if(opp & 0x0000000000800000){
	  count_6++;
	  if(opp & 0x0000000000008000){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[8][6][count_6], 8)){
      board->b ^= rays_to_flip[8][6][count_6];
      board->w ^= rays_to_flip[8][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000400000000000){
    count_7 = 0;
    if(opp & 0x0000002000000000){
      count_7++;
      if(opp & 0x0000000010000000){
	count_7++;
	if(opp & 0x0000000000080000){
	  count_7++;
	  if(opp & 0x0000000000000400){
	    count_7++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[8][7][count_7], 9)){
      board->b ^= rays_to_flip[8][7][count_7];
      board->w ^= rays_to_flip[8][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0080000000000000;

  return result;
}

char flip_bitboard_w_09(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_4;
  if(opp & 0x0020000000000000){
    count_4 = 0;
    if(opp & 0x0010000000000000){
      count_4++;
      if(opp & 0x0008000000000000){
	count_4++;
	if(opp & 0x0004000000000000){
	  count_4++;
	  if(opp & 0x0002000000000000){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[9][4][count_4], 1)){
      board->b ^= rays_to_flip[9][4][count_4];
      board->w ^= rays_to_flip[9][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000400000000000){
    count_6 = 0;
    if(opp & 0x0000004000000000){
      count_6++;
      if(opp & 0x0000000040000000){
	count_6++;
	if(opp & 0x0000000000400000){
	  count_6++;
	  if(opp & 0x0000000000004000){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[9][6][count_6], 8)){
      board->b ^= rays_to_flip[9][6][count_6];
      board->w ^= rays_to_flip[9][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000200000000000){
    count_7 = 0;
    if(opp & 0x0000001000000000){
      count_7++;
      if(opp & 0x0000000008000000){
	count_7++;
	if(opp & 0x0000000000040000){
	  count_7++;
	  if(opp & 0x0000000000000200){
	    count_7++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[9][7][count_7], 9)){
      board->b ^= rays_to_flip[9][7][count_7];
      board->w ^= rays_to_flip[9][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0040000000000000;

  return result;
}

char flip_bitboard_w_10(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_3;
  if(opp & 0x0040000000000000){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[10][3][count_3], -1)){
      board->b ^= rays_to_flip[10][3][count_3];
      board->w ^= rays_to_flip[10][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0010000000000000){
    count_4 = 0;
    if(opp & 0x0008000000000000){
      count_4++;
      if(opp & 0x0004000000000000){
	count_4++;
	if(opp & 0x0002000000000000){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[10][4][count_4], 1)){
      board->b ^= rays_to_flip[10][4][count_4];
      board->w ^= rays_to_flip[10][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000400000000000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[10][5][count_5], 7)){
      board->b ^= rays_to_flip[10][5][count_5];
      board->w ^= rays_to_flip[10][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000200000000000){
    count_6 = 0;
    if(opp & 0x0000002000000000){
      count_6++;
      if(opp & 0x0000000020000000){
	count_6++;
	if(opp & 0x0000000000200000){
	  count_6++;
	  if(opp & 0x0000000000002000){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[10][6][count_6], 8)){
      board->b ^= rays_to_flip[10][6][count_6];
      board->w ^= rays_to_flip[10][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000100000000000){
    count_7 = 0;
    if(opp & 0x0000000800000000){
      count_7++;
      if(opp & 0x0000000004000000){
	count_7++;
	if(opp & 0x0000000000020000){
	  count_7++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[10][7][count_7], 9)){
      board->b ^= rays_to_flip[10][7][count_7];
      board->w ^= rays_to_flip[10][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0020000000000000;

  return result;
}

char flip_bitboard_w_11(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_3;
  if(opp & 0x0020000000000000){
    count_3 = 0;
    if(opp & 0x0040000000000000){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[11][3][count_3], -1)){
      board->b ^= rays_to_flip[11][3][count_3];
      board->w ^= rays_to_flip[11][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0008000000000000){
    count_4 = 0;
    if(opp & 0x0004000000000000){
      count_4++;
      if(opp & 0x0002000000000000){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[11][4][count_4], 1)){
      board->b ^= rays_to_flip[11][4][count_4];
      board->w ^= rays_to_flip[11][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000200000000000){
    count_5 = 0;
    if(opp & 0x0000004000000000){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[11][5][count_5], 7)){
      board->b ^= rays_to_flip[11][5][count_5];
      board->w ^= rays_to_flip[11][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000100000000000){
    count_6 = 0;
    if(opp & 0x0000001000000000){
      count_6++;
      if(opp & 0x0000000010000000){
	count_6++;
	if(opp & 0x0000000000100000){
	  count_6++;
	  if(opp & 0x0000000000001000){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[11][6][count_6], 8)){
      board->b ^= rays_to_flip[11][6][count_6];
      board->w ^= rays_to_flip[11][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000080000000000){
    count_7 = 0;
    if(opp & 0x0000000400000000){
      count_7++;
      if(opp & 0x0000000002000000){
	count_7++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[11][7][count_7], 9)){
      board->b ^= rays_to_flip[11][7][count_7];
      board->w ^= rays_to_flip[11][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0010000000000000;

  return result;
}

char flip_bitboard_w_12(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_3;
  if(opp & 0x0010000000000000){
    count_3 = 0;
    if(opp & 0x0020000000000000){
      count_3++;
      if(opp & 0x0040000000000000){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[12][3][count_3], -1)){
      board->b ^= rays_to_flip[12][3][count_3];
      board->w ^= rays_to_flip[12][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0004000000000000){
    count_4 = 0;
    if(opp & 0x0002000000000000){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[12][4][count_4], 1)){
      board->b ^= rays_to_flip[12][4][count_4];
      board->w ^= rays_to_flip[12][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000100000000000){
    count_5 = 0;
    if(opp & 0x0000002000000000){
      count_5++;
      if(opp & 0x0000000040000000){
	count_5++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[12][5][count_5], 7)){
      board->b ^= rays_to_flip[12][5][count_5];
      board->w ^= rays_to_flip[12][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000080000000000){
    count_6 = 0;
    if(opp & 0x0000000800000000){
      count_6++;
      if(opp & 0x0000000008000000){
	count_6++;
	if(opp & 0x0000000000080000){
	  count_6++;
	  if(opp & 0x0000000000000800){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[12][6][count_6], 8)){
      board->b ^= rays_to_flip[12][6][count_6];
      board->w ^= rays_to_flip[12][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000040000000000){
    count_7 = 0;
    if(opp & 0x0000000200000000){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[12][7][count_7], 9)){
      board->b ^= rays_to_flip[12][7][count_7];
      board->w ^= rays_to_flip[12][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0008000000000000;

  return result;
}

char flip_bitboard_w_13(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_3;
  if(opp & 0x0008000000000000){
    count_3 = 0;
    if(opp & 0x0010000000000000){
      count_3++;
      if(opp & 0x0020000000000000){
	count_3++;
	if(opp & 0x0040000000000000){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[13][3][count_3], -1)){
      board->b ^= rays_to_flip[13][3][count_3];
      board->w ^= rays_to_flip[13][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0002000000000000){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[13][4][count_4], 1)){
      board->b ^= rays_to_flip[13][4][count_4];
      board->w ^= rays_to_flip[13][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000080000000000){
    count_5 = 0;
    if(opp & 0x0000001000000000){
      count_5++;
      if(opp & 0x0000000020000000){
	count_5++;
	if(opp & 0x0000000000400000){
	  count_5++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[13][5][count_5], 7)){
      board->b ^= rays_to_flip[13][5][count_5];
      board->w ^= rays_to_flip[13][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000040000000000){
    count_6 = 0;
    if(opp & 0x0000000400000000){
      count_6++;
      if(opp & 0x0000000004000000){
	count_6++;
	if(opp & 0x0000000000040000){
	  count_6++;
	  if(opp & 0x0000000000000400){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[13][6][count_6], 8)){
      board->b ^= rays_to_flip[13][6][count_6];
      board->w ^= rays_to_flip[13][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000020000000000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[13][7][count_7], 9)){
      board->b ^= rays_to_flip[13][7][count_7];
      board->w ^= rays_to_flip[13][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0004000000000000;

  return result;
}

char flip_bitboard_w_14(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_3;
  if(opp & 0x0004000000000000){
    count_3 = 0;
    if(opp & 0x0008000000000000){
      count_3++;
      if(opp & 0x0010000000000000){
	count_3++;
	if(opp & 0x0020000000000000){
	  count_3++;
	  if(opp & 0x0040000000000000){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[14][3][count_3], -1)){
      board->b ^= rays_to_flip[14][3][count_3];
      board->w ^= rays_to_flip[14][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000040000000000){
    count_5 = 0;
    if(opp & 0x0000000800000000){
      count_5++;
      if(opp & 0x0000000010000000){
	count_5++;
	if(opp & 0x0000000000200000){
	  count_5++;
	  if(opp & 0x0000000000004000){
	    count_5++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[14][5][count_5], 7)){
      board->b ^= rays_to_flip[14][5][count_5];
      board->w ^= rays_to_flip[14][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000020000000000){
    count_6 = 0;
    if(opp & 0x0000000200000000){
      count_6++;
      if(opp & 0x0000000002000000){
	count_6++;
	if(opp & 0x0000000000020000){
	  count_6++;
	  if(opp & 0x0000000000000200){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[14][6][count_6], 8)){
      board->b ^= rays_to_flip[14][6][count_6];
      board->w ^= rays_to_flip[14][6][count_6];
      result |= 0x40;
    }
  }

  board->w |= 0x0002000000000000;

  return result;
}

char flip_bitboard_w_15(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_3;
  if(opp & 0x0002000000000000){
    count_3 = 0;
    if(opp & 0x0004000000000000){
      count_3++;
      if(opp & 0x0008000000000000){
	count_3++;
	if(opp & 0x0010000000000000){
	  count_3++;
	  if(opp & 0x0020000000000000){
	    count_3++;
	    if(opp & 0x0040000000000000){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[15][3][count_3], -1)){
      board->b ^= rays_to_flip[15][3][count_3];
      board->w ^= rays_to_flip[15][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000020000000000){
    count_5 = 0;
    if(opp & 0x0000000400000000){
      count_5++;
      if(opp & 0x0000000008000000){
	count_5++;
	if(opp & 0x0000000000100000){
	  count_5++;
	  if(opp & 0x0000000000002000){
	    count_5++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[15][5][count_5], 7)){
      board->b ^= rays_to_flip[15][5][count_5];
      board->w ^= rays_to_flip[15][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000010000000000){
    count_6 = 0;
    if(opp & 0x0000000100000000){
      count_6++;
      if(opp & 0x0000000001000000){
	count_6++;
	if(opp & 0x0000000000010000){
	  count_6++;
	  if(opp & 0x0000000000000100){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[15][6][count_6], 8)){
      board->b ^= rays_to_flip[15][6][count_6];
      board->w ^= rays_to_flip[15][6][count_6];
      result |= 0x40;
    }
  }

  board->w |= 0x0001000000000000;

  return result;
}

char flip_bitboard_w_16(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_1;
  if(opp & 0x0080000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[16][1][count_1], -8)){
      board->b ^= rays_to_flip[16][1][count_1];
      board->w ^= rays_to_flip[16][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0040000000000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[16][2][count_2], -7)){
      board->b ^= rays_to_flip[16][2][count_2];
      board->w ^= rays_to_flip[16][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000400000000000){
    count_4 = 0;
    if(opp & 0x0000200000000000){
      count_4++;
      if(opp & 0x0000100000000000){
	count_4++;
	if(opp & 0x0000080000000000){
	  count_4++;
	  if(opp & 0x0000040000000000){
	    count_4++;
	    if(opp & 0x0000020000000000){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[16][4][count_4], 1)){
      board->b ^= rays_to_flip[16][4][count_4];
      board->w ^= rays_to_flip[16][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000008000000000){
    count_6 = 0;
    if(opp & 0x0000000080000000){
      count_6++;
      if(opp & 0x0000000000800000){
	count_6++;
	if(opp & 0x0000000000008000){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[16][6][count_6], 8)){
      board->b ^= rays_to_flip[16][6][count_6];
      board->w ^= rays_to_flip[16][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000004000000000){
    count_7 = 0;
    if(opp & 0x0000000020000000){
      count_7++;
      if(opp & 0x0000000000100000){
	count_7++;
	if(opp & 0x0000000000000800){
	  count_7++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[16][7][count_7], 9)){
      board->b ^= rays_to_flip[16][7][count_7];
      board->w ^= rays_to_flip[16][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000800000000000;

  return result;
}

char flip_bitboard_w_17(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_1;
  if(opp & 0x0040000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[17][1][count_1], -8)){
      board->b ^= rays_to_flip[17][1][count_1];
      board->w ^= rays_to_flip[17][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0020000000000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[17][2][count_2], -7)){
      board->b ^= rays_to_flip[17][2][count_2];
      board->w ^= rays_to_flip[17][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000200000000000){
    count_4 = 0;
    if(opp & 0x0000100000000000){
      count_4++;
      if(opp & 0x0000080000000000){
	count_4++;
	if(opp & 0x0000040000000000){
	  count_4++;
	  if(opp & 0x0000020000000000){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[17][4][count_4], 1)){
      board->b ^= rays_to_flip[17][4][count_4];
      board->w ^= rays_to_flip[17][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000004000000000){
    count_6 = 0;
    if(opp & 0x0000000040000000){
      count_6++;
      if(opp & 0x0000000000400000){
	count_6++;
	if(opp & 0x0000000000004000){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[17][6][count_6], 8)){
      board->b ^= rays_to_flip[17][6][count_6];
      board->w ^= rays_to_flip[17][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000002000000000){
    count_7 = 0;
    if(opp & 0x0000000010000000){
      count_7++;
      if(opp & 0x0000000000080000){
	count_7++;
	if(opp & 0x0000000000000400){
	  count_7++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[17][7][count_7], 9)){
      board->b ^= rays_to_flip[17][7][count_7];
      board->w ^= rays_to_flip[17][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000400000000000;

  return result;
}

char flip_bitboard_w_18(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0040000000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[18][0][count_0], -9)){
      board->b ^= rays_to_flip[18][0][count_0];
      board->w ^= rays_to_flip[18][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0020000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[18][1][count_1], -8)){
      board->b ^= rays_to_flip[18][1][count_1];
      board->w ^= rays_to_flip[18][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0010000000000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[18][2][count_2], -7)){
      board->b ^= rays_to_flip[18][2][count_2];
      board->w ^= rays_to_flip[18][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000400000000000){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[18][3][count_3], -1)){
      board->b ^= rays_to_flip[18][3][count_3];
      board->w ^= rays_to_flip[18][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000100000000000){
    count_4 = 0;
    if(opp & 0x0000080000000000){
      count_4++;
      if(opp & 0x0000040000000000){
	count_4++;
	if(opp & 0x0000020000000000){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[18][4][count_4], 1)){
      board->b ^= rays_to_flip[18][4][count_4];
      board->w ^= rays_to_flip[18][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000004000000000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[18][5][count_5], 7)){
      board->b ^= rays_to_flip[18][5][count_5];
      board->w ^= rays_to_flip[18][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000002000000000){
    count_6 = 0;
    if(opp & 0x0000000020000000){
      count_6++;
      if(opp & 0x0000000000200000){
	count_6++;
	if(opp & 0x0000000000002000){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[18][6][count_6], 8)){
      board->b ^= rays_to_flip[18][6][count_6];
      board->w ^= rays_to_flip[18][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000001000000000){
    count_7 = 0;
    if(opp & 0x0000000008000000){
      count_7++;
      if(opp & 0x0000000000040000){
	count_7++;
	if(opp & 0x0000000000000200){
	  count_7++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[18][7][count_7], 9)){
      board->b ^= rays_to_flip[18][7][count_7];
      board->w ^= rays_to_flip[18][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000200000000000;

  return result;
}

char flip_bitboard_w_19(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0020000000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[19][0][count_0], -9)){
      board->b ^= rays_to_flip[19][0][count_0];
      board->w ^= rays_to_flip[19][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0010000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[19][1][count_1], -8)){
      board->b ^= rays_to_flip[19][1][count_1];
      board->w ^= rays_to_flip[19][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0008000000000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[19][2][count_2], -7)){
      board->b ^= rays_to_flip[19][2][count_2];
      board->w ^= rays_to_flip[19][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000200000000000){
    count_3 = 0;
    if(opp & 0x0000400000000000){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[19][3][count_3], -1)){
      board->b ^= rays_to_flip[19][3][count_3];
      board->w ^= rays_to_flip[19][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000080000000000){
    count_4 = 0;
    if(opp & 0x0000040000000000){
      count_4++;
      if(opp & 0x0000020000000000){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[19][4][count_4], 1)){
      board->b ^= rays_to_flip[19][4][count_4];
      board->w ^= rays_to_flip[19][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000002000000000){
    count_5 = 0;
    if(opp & 0x0000000040000000){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[19][5][count_5], 7)){
      board->b ^= rays_to_flip[19][5][count_5];
      board->w ^= rays_to_flip[19][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000001000000000){
    count_6 = 0;
    if(opp & 0x0000000010000000){
      count_6++;
      if(opp & 0x0000000000100000){
	count_6++;
	if(opp & 0x0000000000001000){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[19][6][count_6], 8)){
      board->b ^= rays_to_flip[19][6][count_6];
      board->w ^= rays_to_flip[19][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000800000000){
    count_7 = 0;
    if(opp & 0x0000000004000000){
      count_7++;
      if(opp & 0x0000000000020000){
	count_7++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[19][7][count_7], 9)){
      board->b ^= rays_to_flip[19][7][count_7];
      board->w ^= rays_to_flip[19][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000100000000000;

  return result;
}

char flip_bitboard_w_20(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0010000000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[20][0][count_0], -9)){
      board->b ^= rays_to_flip[20][0][count_0];
      board->w ^= rays_to_flip[20][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0008000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[20][1][count_1], -8)){
      board->b ^= rays_to_flip[20][1][count_1];
      board->w ^= rays_to_flip[20][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0004000000000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[20][2][count_2], -7)){
      board->b ^= rays_to_flip[20][2][count_2];
      board->w ^= rays_to_flip[20][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000100000000000){
    count_3 = 0;
    if(opp & 0x0000200000000000){
      count_3++;
      if(opp & 0x0000400000000000){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[20][3][count_3], -1)){
      board->b ^= rays_to_flip[20][3][count_3];
      board->w ^= rays_to_flip[20][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000040000000000){
    count_4 = 0;
    if(opp & 0x0000020000000000){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[20][4][count_4], 1)){
      board->b ^= rays_to_flip[20][4][count_4];
      board->w ^= rays_to_flip[20][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000001000000000){
    count_5 = 0;
    if(opp & 0x0000000020000000){
      count_5++;
      if(opp & 0x0000000000400000){
	count_5++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[20][5][count_5], 7)){
      board->b ^= rays_to_flip[20][5][count_5];
      board->w ^= rays_to_flip[20][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000800000000){
    count_6 = 0;
    if(opp & 0x0000000008000000){
      count_6++;
      if(opp & 0x0000000000080000){
	count_6++;
	if(opp & 0x0000000000000800){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[20][6][count_6], 8)){
      board->b ^= rays_to_flip[20][6][count_6];
      board->w ^= rays_to_flip[20][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000400000000){
    count_7 = 0;
    if(opp & 0x0000000002000000){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[20][7][count_7], 9)){
      board->b ^= rays_to_flip[20][7][count_7];
      board->w ^= rays_to_flip[20][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000080000000000;

  return result;
}

char flip_bitboard_w_21(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0008000000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[21][0][count_0], -9)){
      board->b ^= rays_to_flip[21][0][count_0];
      board->w ^= rays_to_flip[21][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0004000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[21][1][count_1], -8)){
      board->b ^= rays_to_flip[21][1][count_1];
      board->w ^= rays_to_flip[21][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0002000000000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[21][2][count_2], -7)){
      board->b ^= rays_to_flip[21][2][count_2];
      board->w ^= rays_to_flip[21][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000080000000000){
    count_3 = 0;
    if(opp & 0x0000100000000000){
      count_3++;
      if(opp & 0x0000200000000000){
	count_3++;
	if(opp & 0x0000400000000000){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[21][3][count_3], -1)){
      board->b ^= rays_to_flip[21][3][count_3];
      board->w ^= rays_to_flip[21][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000020000000000){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[21][4][count_4], 1)){
      board->b ^= rays_to_flip[21][4][count_4];
      board->w ^= rays_to_flip[21][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000800000000){
    count_5 = 0;
    if(opp & 0x0000000010000000){
      count_5++;
      if(opp & 0x0000000000200000){
	count_5++;
	if(opp & 0x0000000000004000){
	  count_5++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[21][5][count_5], 7)){
      board->b ^= rays_to_flip[21][5][count_5];
      board->w ^= rays_to_flip[21][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000400000000){
    count_6 = 0;
    if(opp & 0x0000000004000000){
      count_6++;
      if(opp & 0x0000000000040000){
	count_6++;
	if(opp & 0x0000000000000400){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[21][6][count_6], 8)){
      board->b ^= rays_to_flip[21][6][count_6];
      board->w ^= rays_to_flip[21][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000200000000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[21][7][count_7], 9)){
      board->b ^= rays_to_flip[21][7][count_7];
      board->w ^= rays_to_flip[21][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000040000000000;

  return result;
}

char flip_bitboard_w_22(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0004000000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[22][0][count_0], -9)){
      board->b ^= rays_to_flip[22][0][count_0];
      board->w ^= rays_to_flip[22][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0002000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[22][1][count_1], -8)){
      board->b ^= rays_to_flip[22][1][count_1];
      board->w ^= rays_to_flip[22][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000040000000000){
    count_3 = 0;
    if(opp & 0x0000080000000000){
      count_3++;
      if(opp & 0x0000100000000000){
	count_3++;
	if(opp & 0x0000200000000000){
	  count_3++;
	  if(opp & 0x0000400000000000){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[22][3][count_3], -1)){
      board->b ^= rays_to_flip[22][3][count_3];
      board->w ^= rays_to_flip[22][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000400000000){
    count_5 = 0;
    if(opp & 0x0000000008000000){
      count_5++;
      if(opp & 0x0000000000100000){
	count_5++;
	if(opp & 0x0000000000002000){
	  count_5++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[22][5][count_5], 7)){
      board->b ^= rays_to_flip[22][5][count_5];
      board->w ^= rays_to_flip[22][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000200000000){
    count_6 = 0;
    if(opp & 0x0000000002000000){
      count_6++;
      if(opp & 0x0000000000020000){
	count_6++;
	if(opp & 0x0000000000000200){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[22][6][count_6], 8)){
      board->b ^= rays_to_flip[22][6][count_6];
      board->w ^= rays_to_flip[22][6][count_6];
      result |= 0x40;
    }
  }

  board->w |= 0x0000020000000000;

  return result;
}

char flip_bitboard_w_23(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0002000000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[23][0][count_0], -9)){
      board->b ^= rays_to_flip[23][0][count_0];
      board->w ^= rays_to_flip[23][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0001000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[23][1][count_1], -8)){
      board->b ^= rays_to_flip[23][1][count_1];
      board->w ^= rays_to_flip[23][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000020000000000){
    count_3 = 0;
    if(opp & 0x0000040000000000){
      count_3++;
      if(opp & 0x0000080000000000){
	count_3++;
	if(opp & 0x0000100000000000){
	  count_3++;
	  if(opp & 0x0000200000000000){
	    count_3++;
	    if(opp & 0x0000400000000000){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[23][3][count_3], -1)){
      board->b ^= rays_to_flip[23][3][count_3];
      board->w ^= rays_to_flip[23][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000200000000){
    count_5 = 0;
    if(opp & 0x0000000004000000){
      count_5++;
      if(opp & 0x0000000000080000){
	count_5++;
	if(opp & 0x0000000000001000){
	  count_5++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[23][5][count_5], 7)){
      board->b ^= rays_to_flip[23][5][count_5];
      board->w ^= rays_to_flip[23][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000100000000){
    count_6 = 0;
    if(opp & 0x0000000001000000){
      count_6++;
      if(opp & 0x0000000000010000){
	count_6++;
	if(opp & 0x0000000000000100){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[23][6][count_6], 8)){
      board->b ^= rays_to_flip[23][6][count_6];
      board->w ^= rays_to_flip[23][6][count_6];
      result |= 0x40;
    }
  }

  board->w |= 0x0000010000000000;

  return result;
}

char flip_bitboard_w_24(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_1;
  if(opp & 0x0000800000000000){
    count_1 = 0;
    if(opp & 0x0080000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[24][1][count_1], -8)){
      board->b ^= rays_to_flip[24][1][count_1];
      board->w ^= rays_to_flip[24][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000400000000000){
    count_2 = 0;
    if(opp & 0x0020000000000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[24][2][count_2], -7)){
      board->b ^= rays_to_flip[24][2][count_2];
      board->w ^= rays_to_flip[24][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000004000000000){
    count_4 = 0;
    if(opp & 0x0000002000000000){
      count_4++;
      if(opp & 0x0000001000000000){
	count_4++;
	if(opp & 0x0000000800000000){
	  count_4++;
	  if(opp & 0x0000000400000000){
	    count_4++;
	    if(opp & 0x0000000200000000){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[24][4][count_4], 1)){
      board->b ^= rays_to_flip[24][4][count_4];
      board->w ^= rays_to_flip[24][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000000080000000){
    count_6 = 0;
    if(opp & 0x0000000000800000){
      count_6++;
      if(opp & 0x0000000000008000){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[24][6][count_6], 8)){
      board->b ^= rays_to_flip[24][6][count_6];
      board->w ^= rays_to_flip[24][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000040000000){
    count_7 = 0;
    if(opp & 0x0000000000200000){
      count_7++;
      if(opp & 0x0000000000001000){
	count_7++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[24][7][count_7], 9)){
      board->b ^= rays_to_flip[24][7][count_7];
      board->w ^= rays_to_flip[24][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000008000000000;

  return result;
}

char flip_bitboard_w_25(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_1;
  if(opp & 0x0000400000000000){
    count_1 = 0;
    if(opp & 0x0040000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[25][1][count_1], -8)){
      board->b ^= rays_to_flip[25][1][count_1];
      board->w ^= rays_to_flip[25][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000200000000000){
    count_2 = 0;
    if(opp & 0x0010000000000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[25][2][count_2], -7)){
      board->b ^= rays_to_flip[25][2][count_2];
      board->w ^= rays_to_flip[25][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000002000000000){
    count_4 = 0;
    if(opp & 0x0000001000000000){
      count_4++;
      if(opp & 0x0000000800000000){
	count_4++;
	if(opp & 0x0000000400000000){
	  count_4++;
	  if(opp & 0x0000000200000000){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[25][4][count_4], 1)){
      board->b ^= rays_to_flip[25][4][count_4];
      board->w ^= rays_to_flip[25][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000000040000000){
    count_6 = 0;
    if(opp & 0x0000000000400000){
      count_6++;
      if(opp & 0x0000000000004000){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[25][6][count_6], 8)){
      board->b ^= rays_to_flip[25][6][count_6];
      board->w ^= rays_to_flip[25][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000020000000){
    count_7 = 0;
    if(opp & 0x0000000000100000){
      count_7++;
      if(opp & 0x0000000000000800){
	count_7++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[25][7][count_7], 9)){
      board->b ^= rays_to_flip[25][7][count_7];
      board->w ^= rays_to_flip[25][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000004000000000;

  return result;
}

char flip_bitboard_w_26(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000400000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[26][0][count_0], -9)){
      board->b ^= rays_to_flip[26][0][count_0];
      board->w ^= rays_to_flip[26][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000200000000000){
    count_1 = 0;
    if(opp & 0x0020000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[26][1][count_1], -8)){
      board->b ^= rays_to_flip[26][1][count_1];
      board->w ^= rays_to_flip[26][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000100000000000){
    count_2 = 0;
    if(opp & 0x0008000000000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[26][2][count_2], -7)){
      board->b ^= rays_to_flip[26][2][count_2];
      board->w ^= rays_to_flip[26][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000004000000000){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[26][3][count_3], -1)){
      board->b ^= rays_to_flip[26][3][count_3];
      board->w ^= rays_to_flip[26][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000001000000000){
    count_4 = 0;
    if(opp & 0x0000000800000000){
      count_4++;
      if(opp & 0x0000000400000000){
	count_4++;
	if(opp & 0x0000000200000000){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[26][4][count_4], 1)){
      board->b ^= rays_to_flip[26][4][count_4];
      board->w ^= rays_to_flip[26][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000040000000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[26][5][count_5], 7)){
      board->b ^= rays_to_flip[26][5][count_5];
      board->w ^= rays_to_flip[26][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000020000000){
    count_6 = 0;
    if(opp & 0x0000000000200000){
      count_6++;
      if(opp & 0x0000000000002000){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[26][6][count_6], 8)){
      board->b ^= rays_to_flip[26][6][count_6];
      board->w ^= rays_to_flip[26][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000010000000){
    count_7 = 0;
    if(opp & 0x0000000000080000){
      count_7++;
      if(opp & 0x0000000000000400){
	count_7++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[26][7][count_7], 9)){
      board->b ^= rays_to_flip[26][7][count_7];
      board->w ^= rays_to_flip[26][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000002000000000;

  return result;
}

char flip_bitboard_w_27(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000200000000000){
    count_0 = 0;
    if(opp & 0x0040000000000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[27][0][count_0], -9)){
      board->b ^= rays_to_flip[27][0][count_0];
      board->w ^= rays_to_flip[27][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000100000000000){
    count_1 = 0;
    if(opp & 0x0010000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[27][1][count_1], -8)){
      board->b ^= rays_to_flip[27][1][count_1];
      board->w ^= rays_to_flip[27][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000080000000000){
    count_2 = 0;
    if(opp & 0x0004000000000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[27][2][count_2], -7)){
      board->b ^= rays_to_flip[27][2][count_2];
      board->w ^= rays_to_flip[27][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000002000000000){
    count_3 = 0;
    if(opp & 0x0000004000000000){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[27][3][count_3], -1)){
      board->b ^= rays_to_flip[27][3][count_3];
      board->w ^= rays_to_flip[27][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000800000000){
    count_4 = 0;
    if(opp & 0x0000000400000000){
      count_4++;
      if(opp & 0x0000000200000000){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[27][4][count_4], 1)){
      board->b ^= rays_to_flip[27][4][count_4];
      board->w ^= rays_to_flip[27][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000020000000){
    count_5 = 0;
    if(opp & 0x0000000000400000){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[27][5][count_5], 7)){
      board->b ^= rays_to_flip[27][5][count_5];
      board->w ^= rays_to_flip[27][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000010000000){
    count_6 = 0;
    if(opp & 0x0000000000100000){
      count_6++;
      if(opp & 0x0000000000001000){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[27][6][count_6], 8)){
      board->b ^= rays_to_flip[27][6][count_6];
      board->w ^= rays_to_flip[27][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000008000000){
    count_7 = 0;
    if(opp & 0x0000000000040000){
      count_7++;
      if(opp & 0x0000000000000200){
	count_7++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[27][7][count_7], 9)){
      board->b ^= rays_to_flip[27][7][count_7];
      board->w ^= rays_to_flip[27][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000001000000000;

  return result;
}

char flip_bitboard_w_28(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000100000000000){
    count_0 = 0;
    if(opp & 0x0020000000000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[28][0][count_0], -9)){
      board->b ^= rays_to_flip[28][0][count_0];
      board->w ^= rays_to_flip[28][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000080000000000){
    count_1 = 0;
    if(opp & 0x0008000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[28][1][count_1], -8)){
      board->b ^= rays_to_flip[28][1][count_1];
      board->w ^= rays_to_flip[28][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000040000000000){
    count_2 = 0;
    if(opp & 0x0002000000000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[28][2][count_2], -7)){
      board->b ^= rays_to_flip[28][2][count_2];
      board->w ^= rays_to_flip[28][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000001000000000){
    count_3 = 0;
    if(opp & 0x0000002000000000){
      count_3++;
      if(opp & 0x0000004000000000){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[28][3][count_3], -1)){
      board->b ^= rays_to_flip[28][3][count_3];
      board->w ^= rays_to_flip[28][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000400000000){
    count_4 = 0;
    if(opp & 0x0000000200000000){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[28][4][count_4], 1)){
      board->b ^= rays_to_flip[28][4][count_4];
      board->w ^= rays_to_flip[28][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000010000000){
    count_5 = 0;
    if(opp & 0x0000000000200000){
      count_5++;
      if(opp & 0x0000000000004000){
	count_5++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[28][5][count_5], 7)){
      board->b ^= rays_to_flip[28][5][count_5];
      board->w ^= rays_to_flip[28][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000008000000){
    count_6 = 0;
    if(opp & 0x0000000000080000){
      count_6++;
      if(opp & 0x0000000000000800){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[28][6][count_6], 8)){
      board->b ^= rays_to_flip[28][6][count_6];
      board->w ^= rays_to_flip[28][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000004000000){
    count_7 = 0;
    if(opp & 0x0000000000020000){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[28][7][count_7], 9)){
      board->b ^= rays_to_flip[28][7][count_7];
      board->w ^= rays_to_flip[28][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000000800000000;

  return result;
}

char flip_bitboard_w_29(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000080000000000){
    count_0 = 0;
    if(opp & 0x0010000000000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[29][0][count_0], -9)){
      board->b ^= rays_to_flip[29][0][count_0];
      board->w ^= rays_to_flip[29][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000040000000000){
    count_1 = 0;
    if(opp & 0x0004000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[29][1][count_1], -8)){
      board->b ^= rays_to_flip[29][1][count_1];
      board->w ^= rays_to_flip[29][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000020000000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[29][2][count_2], -7)){
      board->b ^= rays_to_flip[29][2][count_2];
      board->w ^= rays_to_flip[29][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000800000000){
    count_3 = 0;
    if(opp & 0x0000001000000000){
      count_3++;
      if(opp & 0x0000002000000000){
	count_3++;
	if(opp & 0x0000004000000000){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[29][3][count_3], -1)){
      board->b ^= rays_to_flip[29][3][count_3];
      board->w ^= rays_to_flip[29][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000200000000){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[29][4][count_4], 1)){
      board->b ^= rays_to_flip[29][4][count_4];
      board->w ^= rays_to_flip[29][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000008000000){
    count_5 = 0;
    if(opp & 0x0000000000100000){
      count_5++;
      if(opp & 0x0000000000002000){
	count_5++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[29][5][count_5], 7)){
      board->b ^= rays_to_flip[29][5][count_5];
      board->w ^= rays_to_flip[29][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000004000000){
    count_6 = 0;
    if(opp & 0x0000000000040000){
      count_6++;
      if(opp & 0x0000000000000400){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[29][6][count_6], 8)){
      board->b ^= rays_to_flip[29][6][count_6];
      board->w ^= rays_to_flip[29][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000002000000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[29][7][count_7], 9)){
      board->b ^= rays_to_flip[29][7][count_7];
      board->w ^= rays_to_flip[29][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000000400000000;

  return result;
}

char flip_bitboard_w_30(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000040000000000){
    count_0 = 0;
    if(opp & 0x0008000000000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[30][0][count_0], -9)){
      board->b ^= rays_to_flip[30][0][count_0];
      board->w ^= rays_to_flip[30][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000020000000000){
    count_1 = 0;
    if(opp & 0x0002000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[30][1][count_1], -8)){
      board->b ^= rays_to_flip[30][1][count_1];
      board->w ^= rays_to_flip[30][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000400000000){
    count_3 = 0;
    if(opp & 0x0000000800000000){
      count_3++;
      if(opp & 0x0000001000000000){
	count_3++;
	if(opp & 0x0000002000000000){
	  count_3++;
	  if(opp & 0x0000004000000000){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[30][3][count_3], -1)){
      board->b ^= rays_to_flip[30][3][count_3];
      board->w ^= rays_to_flip[30][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000004000000){
    count_5 = 0;
    if(opp & 0x0000000000080000){
      count_5++;
      if(opp & 0x0000000000001000){
	count_5++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[30][5][count_5], 7)){
      board->b ^= rays_to_flip[30][5][count_5];
      board->w ^= rays_to_flip[30][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000002000000){
    count_6 = 0;
    if(opp & 0x0000000000020000){
      count_6++;
      if(opp & 0x0000000000000200){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[30][6][count_6], 8)){
      board->b ^= rays_to_flip[30][6][count_6];
      board->w ^= rays_to_flip[30][6][count_6];
      result |= 0x40;
    }
  }

  board->w |= 0x0000000200000000;

  return result;
}

char flip_bitboard_w_31(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000020000000000){
    count_0 = 0;
    if(opp & 0x0004000000000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[31][0][count_0], -9)){
      board->b ^= rays_to_flip[31][0][count_0];
      board->w ^= rays_to_flip[31][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000010000000000){
    count_1 = 0;
    if(opp & 0x0001000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[31][1][count_1], -8)){
      board->b ^= rays_to_flip[31][1][count_1];
      board->w ^= rays_to_flip[31][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000200000000){
    count_3 = 0;
    if(opp & 0x0000000400000000){
      count_3++;
      if(opp & 0x0000000800000000){
	count_3++;
	if(opp & 0x0000001000000000){
	  count_3++;
	  if(opp & 0x0000002000000000){
	    count_3++;
	    if(opp & 0x0000004000000000){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[31][3][count_3], -1)){
      board->b ^= rays_to_flip[31][3][count_3];
      board->w ^= rays_to_flip[31][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000002000000){
    count_5 = 0;
    if(opp & 0x0000000000040000){
      count_5++;
      if(opp & 0x0000000000000800){
	count_5++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[31][5][count_5], 7)){
      board->b ^= rays_to_flip[31][5][count_5];
      board->w ^= rays_to_flip[31][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000001000000){
    count_6 = 0;
    if(opp & 0x0000000000010000){
      count_6++;
      if(opp & 0x0000000000000100){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[31][6][count_6], 8)){
      board->b ^= rays_to_flip[31][6][count_6];
      board->w ^= rays_to_flip[31][6][count_6];
      result |= 0x40;
    }
  }

  board->w |= 0x0000000100000000;

  return result;
}

char flip_bitboard_w_32(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_1;
  if(opp & 0x0000008000000000){
    count_1 = 0;
    if(opp & 0x0000800000000000){
      count_1++;
      if(opp & 0x0080000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[32][1][count_1], -8)){
      board->b ^= rays_to_flip[32][1][count_1];
      board->w ^= rays_to_flip[32][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000004000000000){
    count_2 = 0;
    if(opp & 0x0000200000000000){
      count_2++;
      if(opp & 0x0010000000000000){
	count_2++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[32][2][count_2], -7)){
      board->b ^= rays_to_flip[32][2][count_2];
      board->w ^= rays_to_flip[32][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000040000000){
    count_4 = 0;
    if(opp & 0x0000000020000000){
      count_4++;
      if(opp & 0x0000000010000000){
	count_4++;
	if(opp & 0x0000000008000000){
	  count_4++;
	  if(opp & 0x0000000004000000){
	    count_4++;
	    if(opp & 0x0000000002000000){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[32][4][count_4], 1)){
      board->b ^= rays_to_flip[32][4][count_4];
      board->w ^= rays_to_flip[32][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000000000800000){
    count_6 = 0;
    if(opp & 0x0000000000008000){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[32][6][count_6], 8)){
      board->b ^= rays_to_flip[32][6][count_6];
      board->w ^= rays_to_flip[32][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000400000){
    count_7 = 0;
    if(opp & 0x0000000000002000){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[32][7][count_7], 9)){
      board->b ^= rays_to_flip[32][7][count_7];
      board->w ^= rays_to_flip[32][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000000080000000;

  return result;
}

char flip_bitboard_w_33(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_1;
  if(opp & 0x0000004000000000){
    count_1 = 0;
    if(opp & 0x0000400000000000){
      count_1++;
      if(opp & 0x0040000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[33][1][count_1], -8)){
      board->b ^= rays_to_flip[33][1][count_1];
      board->w ^= rays_to_flip[33][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000002000000000){
    count_2 = 0;
    if(opp & 0x0000100000000000){
      count_2++;
      if(opp & 0x0008000000000000){
	count_2++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[33][2][count_2], -7)){
      board->b ^= rays_to_flip[33][2][count_2];
      board->w ^= rays_to_flip[33][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000020000000){
    count_4 = 0;
    if(opp & 0x0000000010000000){
      count_4++;
      if(opp & 0x0000000008000000){
	count_4++;
	if(opp & 0x0000000004000000){
	  count_4++;
	  if(opp & 0x0000000002000000){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[33][4][count_4], 1)){
      board->b ^= rays_to_flip[33][4][count_4];
      board->w ^= rays_to_flip[33][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000000000400000){
    count_6 = 0;
    if(opp & 0x0000000000004000){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[33][6][count_6], 8)){
      board->b ^= rays_to_flip[33][6][count_6];
      board->w ^= rays_to_flip[33][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000200000){
    count_7 = 0;
    if(opp & 0x0000000000001000){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[33][7][count_7], 9)){
      board->b ^= rays_to_flip[33][7][count_7];
      board->w ^= rays_to_flip[33][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000000040000000;

  return result;
}

char flip_bitboard_w_34(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000004000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[34][0][count_0], -9)){
      board->b ^= rays_to_flip[34][0][count_0];
      board->w ^= rays_to_flip[34][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000002000000000){
    count_1 = 0;
    if(opp & 0x0000200000000000){
      count_1++;
      if(opp & 0x0020000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[34][1][count_1], -8)){
      board->b ^= rays_to_flip[34][1][count_1];
      board->w ^= rays_to_flip[34][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000001000000000){
    count_2 = 0;
    if(opp & 0x0000080000000000){
      count_2++;
      if(opp & 0x0004000000000000){
	count_2++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[34][2][count_2], -7)){
      board->b ^= rays_to_flip[34][2][count_2];
      board->w ^= rays_to_flip[34][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000040000000){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[34][3][count_3], -1)){
      board->b ^= rays_to_flip[34][3][count_3];
      board->w ^= rays_to_flip[34][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000010000000){
    count_4 = 0;
    if(opp & 0x0000000008000000){
      count_4++;
      if(opp & 0x0000000004000000){
	count_4++;
	if(opp & 0x0000000002000000){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[34][4][count_4], 1)){
      board->b ^= rays_to_flip[34][4][count_4];
      board->w ^= rays_to_flip[34][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000400000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[34][5][count_5], 7)){
      board->b ^= rays_to_flip[34][5][count_5];
      board->w ^= rays_to_flip[34][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000200000){
    count_6 = 0;
    if(opp & 0x0000000000002000){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[34][6][count_6], 8)){
      board->b ^= rays_to_flip[34][6][count_6];
      board->w ^= rays_to_flip[34][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000100000){
    count_7 = 0;
    if(opp & 0x0000000000000800){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[34][7][count_7], 9)){
      board->b ^= rays_to_flip[34][7][count_7];
      board->w ^= rays_to_flip[34][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000000020000000;

  return result;
}

char flip_bitboard_w_35(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000002000000000){
    count_0 = 0;
    if(opp & 0x0000400000000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[35][0][count_0], -9)){
      board->b ^= rays_to_flip[35][0][count_0];
      board->w ^= rays_to_flip[35][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000001000000000){
    count_1 = 0;
    if(opp & 0x0000100000000000){
      count_1++;
      if(opp & 0x0010000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[35][1][count_1], -8)){
      board->b ^= rays_to_flip[35][1][count_1];
      board->w ^= rays_to_flip[35][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000800000000){
    count_2 = 0;
    if(opp & 0x0000040000000000){
      count_2++;
      if(opp & 0x0002000000000000){
	count_2++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[35][2][count_2], -7)){
      board->b ^= rays_to_flip[35][2][count_2];
      board->w ^= rays_to_flip[35][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000020000000){
    count_3 = 0;
    if(opp & 0x0000000040000000){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[35][3][count_3], -1)){
      board->b ^= rays_to_flip[35][3][count_3];
      board->w ^= rays_to_flip[35][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000008000000){
    count_4 = 0;
    if(opp & 0x0000000004000000){
      count_4++;
      if(opp & 0x0000000002000000){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[35][4][count_4], 1)){
      board->b ^= rays_to_flip[35][4][count_4];
      board->w ^= rays_to_flip[35][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000200000){
    count_5 = 0;
    if(opp & 0x0000000000004000){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[35][5][count_5], 7)){
      board->b ^= rays_to_flip[35][5][count_5];
      board->w ^= rays_to_flip[35][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000100000){
    count_6 = 0;
    if(opp & 0x0000000000001000){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[35][6][count_6], 8)){
      board->b ^= rays_to_flip[35][6][count_6];
      board->w ^= rays_to_flip[35][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000080000){
    count_7 = 0;
    if(opp & 0x0000000000000400){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[35][7][count_7], 9)){
      board->b ^= rays_to_flip[35][7][count_7];
      board->w ^= rays_to_flip[35][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000000010000000;

  return result;
}

char flip_bitboard_w_36(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000001000000000){
    count_0 = 0;
    if(opp & 0x0000200000000000){
      count_0++;
      if(opp & 0x0040000000000000){
	count_0++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[36][0][count_0], -9)){
      board->b ^= rays_to_flip[36][0][count_0];
      board->w ^= rays_to_flip[36][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000800000000){
    count_1 = 0;
    if(opp & 0x0000080000000000){
      count_1++;
      if(opp & 0x0008000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[36][1][count_1], -8)){
      board->b ^= rays_to_flip[36][1][count_1];
      board->w ^= rays_to_flip[36][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000400000000){
    count_2 = 0;
    if(opp & 0x0000020000000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[36][2][count_2], -7)){
      board->b ^= rays_to_flip[36][2][count_2];
      board->w ^= rays_to_flip[36][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000010000000){
    count_3 = 0;
    if(opp & 0x0000000020000000){
      count_3++;
      if(opp & 0x0000000040000000){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[36][3][count_3], -1)){
      board->b ^= rays_to_flip[36][3][count_3];
      board->w ^= rays_to_flip[36][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000004000000){
    count_4 = 0;
    if(opp & 0x0000000002000000){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[36][4][count_4], 1)){
      board->b ^= rays_to_flip[36][4][count_4];
      board->w ^= rays_to_flip[36][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000100000){
    count_5 = 0;
    if(opp & 0x0000000000002000){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[36][5][count_5], 7)){
      board->b ^= rays_to_flip[36][5][count_5];
      board->w ^= rays_to_flip[36][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000080000){
    count_6 = 0;
    if(opp & 0x0000000000000800){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[36][6][count_6], 8)){
      board->b ^= rays_to_flip[36][6][count_6];
      board->w ^= rays_to_flip[36][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000040000){
    count_7 = 0;
    if(opp & 0x0000000000000200){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[36][7][count_7], 9)){
      board->b ^= rays_to_flip[36][7][count_7];
      board->w ^= rays_to_flip[36][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000000008000000;

  return result;
}

char flip_bitboard_w_37(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000800000000){
    count_0 = 0;
    if(opp & 0x0000100000000000){
      count_0++;
      if(opp & 0x0020000000000000){
	count_0++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[37][0][count_0], -9)){
      board->b ^= rays_to_flip[37][0][count_0];
      board->w ^= rays_to_flip[37][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000400000000){
    count_1 = 0;
    if(opp & 0x0000040000000000){
      count_1++;
      if(opp & 0x0004000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[37][1][count_1], -8)){
      board->b ^= rays_to_flip[37][1][count_1];
      board->w ^= rays_to_flip[37][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000200000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[37][2][count_2], -7)){
      board->b ^= rays_to_flip[37][2][count_2];
      board->w ^= rays_to_flip[37][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000008000000){
    count_3 = 0;
    if(opp & 0x0000000010000000){
      count_3++;
      if(opp & 0x0000000020000000){
	count_3++;
	if(opp & 0x0000000040000000){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[37][3][count_3], -1)){
      board->b ^= rays_to_flip[37][3][count_3];
      board->w ^= rays_to_flip[37][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000002000000){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[37][4][count_4], 1)){
      board->b ^= rays_to_flip[37][4][count_4];
      board->w ^= rays_to_flip[37][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000080000){
    count_5 = 0;
    if(opp & 0x0000000000001000){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[37][5][count_5], 7)){
      board->b ^= rays_to_flip[37][5][count_5];
      board->w ^= rays_to_flip[37][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000040000){
    count_6 = 0;
    if(opp & 0x0000000000000400){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[37][6][count_6], 8)){
      board->b ^= rays_to_flip[37][6][count_6];
      board->w ^= rays_to_flip[37][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000020000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[37][7][count_7], 9)){
      board->b ^= rays_to_flip[37][7][count_7];
      board->w ^= rays_to_flip[37][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000000004000000;

  return result;
}

char flip_bitboard_w_38(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000400000000){
    count_0 = 0;
    if(opp & 0x0000080000000000){
      count_0++;
      if(opp & 0x0010000000000000){
	count_0++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[38][0][count_0], -9)){
      board->b ^= rays_to_flip[38][0][count_0];
      board->w ^= rays_to_flip[38][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000200000000){
    count_1 = 0;
    if(opp & 0x0000020000000000){
      count_1++;
      if(opp & 0x0002000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[38][1][count_1], -8)){
      board->b ^= rays_to_flip[38][1][count_1];
      board->w ^= rays_to_flip[38][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000004000000){
    count_3 = 0;
    if(opp & 0x0000000008000000){
      count_3++;
      if(opp & 0x0000000010000000){
	count_3++;
	if(opp & 0x0000000020000000){
	  count_3++;
	  if(opp & 0x0000000040000000){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[38][3][count_3], -1)){
      board->b ^= rays_to_flip[38][3][count_3];
      board->w ^= rays_to_flip[38][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000000040000){
    count_5 = 0;
    if(opp & 0x0000000000000800){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[38][5][count_5], 7)){
      board->b ^= rays_to_flip[38][5][count_5];
      board->w ^= rays_to_flip[38][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000020000){
    count_6 = 0;
    if(opp & 0x0000000000000200){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[38][6][count_6], 8)){
      board->b ^= rays_to_flip[38][6][count_6];
      board->w ^= rays_to_flip[38][6][count_6];
      result |= 0x40;
    }
  }

  board->w |= 0x0000000002000000;

  return result;
}

char flip_bitboard_w_39(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000200000000){
    count_0 = 0;
    if(opp & 0x0000040000000000){
      count_0++;
      if(opp & 0x0008000000000000){
	count_0++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[39][0][count_0], -9)){
      board->b ^= rays_to_flip[39][0][count_0];
      board->w ^= rays_to_flip[39][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000100000000){
    count_1 = 0;
    if(opp & 0x0000010000000000){
      count_1++;
      if(opp & 0x0001000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[39][1][count_1], -8)){
      board->b ^= rays_to_flip[39][1][count_1];
      board->w ^= rays_to_flip[39][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000002000000){
    count_3 = 0;
    if(opp & 0x0000000004000000){
      count_3++;
      if(opp & 0x0000000008000000){
	count_3++;
	if(opp & 0x0000000010000000){
	  count_3++;
	  if(opp & 0x0000000020000000){
	    count_3++;
	    if(opp & 0x0000000040000000){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[39][3][count_3], -1)){
      board->b ^= rays_to_flip[39][3][count_3];
      board->w ^= rays_to_flip[39][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000000020000){
    count_5 = 0;
    if(opp & 0x0000000000000400){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[39][5][count_5], 7)){
      board->b ^= rays_to_flip[39][5][count_5];
      board->w ^= rays_to_flip[39][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000010000){
    count_6 = 0;
    if(opp & 0x0000000000000100){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[39][6][count_6], 8)){
      board->b ^= rays_to_flip[39][6][count_6];
      board->w ^= rays_to_flip[39][6][count_6];
      result |= 0x40;
    }
  }

  board->w |= 0x0000000001000000;

  return result;
}

char flip_bitboard_w_40(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_1;
  if(opp & 0x0000000080000000){
    count_1 = 0;
    if(opp & 0x0000008000000000){
      count_1++;
      if(opp & 0x0000800000000000){
	count_1++;
	if(opp & 0x0080000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[40][1][count_1], -8)){
      board->b ^= rays_to_flip[40][1][count_1];
      board->w ^= rays_to_flip[40][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000040000000){
    count_2 = 0;
    if(opp & 0x0000002000000000){
      count_2++;
      if(opp & 0x0000100000000000){
	count_2++;
	if(opp & 0x0008000000000000){
	  count_2++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[40][2][count_2], -7)){
      board->b ^= rays_to_flip[40][2][count_2];
      board->w ^= rays_to_flip[40][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000000400000){
    count_4 = 0;
    if(opp & 0x0000000000200000){
      count_4++;
      if(opp & 0x0000000000100000){
	count_4++;
	if(opp & 0x0000000000080000){
	  count_4++;
	  if(opp & 0x0000000000040000){
	    count_4++;
	    if(opp & 0x0000000000020000){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[40][4][count_4], 1)){
      board->b ^= rays_to_flip[40][4][count_4];
      board->w ^= rays_to_flip[40][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000000000008000){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[40][6][count_6], 8)){
      board->b ^= rays_to_flip[40][6][count_6];
      board->w ^= rays_to_flip[40][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000004000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[40][7][count_7], 9)){
      board->b ^= rays_to_flip[40][7][count_7];
      board->w ^= rays_to_flip[40][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000000000800000;

  return result;
}

char flip_bitboard_w_41(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_1;
  if(opp & 0x0000000040000000){
    count_1 = 0;
    if(opp & 0x0000004000000000){
      count_1++;
      if(opp & 0x0000400000000000){
	count_1++;
	if(opp & 0x0040000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[41][1][count_1], -8)){
      board->b ^= rays_to_flip[41][1][count_1];
      board->w ^= rays_to_flip[41][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000020000000){
    count_2 = 0;
    if(opp & 0x0000001000000000){
      count_2++;
      if(opp & 0x0000080000000000){
	count_2++;
	if(opp & 0x0004000000000000){
	  count_2++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[41][2][count_2], -7)){
      board->b ^= rays_to_flip[41][2][count_2];
      board->w ^= rays_to_flip[41][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000000200000){
    count_4 = 0;
    if(opp & 0x0000000000100000){
      count_4++;
      if(opp & 0x0000000000080000){
	count_4++;
	if(opp & 0x0000000000040000){
	  count_4++;
	  if(opp & 0x0000000000020000){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[41][4][count_4], 1)){
      board->b ^= rays_to_flip[41][4][count_4];
      board->w ^= rays_to_flip[41][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000000000004000){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[41][6][count_6], 8)){
      board->b ^= rays_to_flip[41][6][count_6];
      board->w ^= rays_to_flip[41][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000002000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[41][7][count_7], 9)){
      board->b ^= rays_to_flip[41][7][count_7];
      board->w ^= rays_to_flip[41][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000000000400000;

  return result;
}

char flip_bitboard_w_42(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000040000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[42][0][count_0], -9)){
      board->b ^= rays_to_flip[42][0][count_0];
      board->w ^= rays_to_flip[42][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000020000000){
    count_1 = 0;
    if(opp & 0x0000002000000000){
      count_1++;
      if(opp & 0x0000200000000000){
	count_1++;
	if(opp & 0x0020000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[42][1][count_1], -8)){
      board->b ^= rays_to_flip[42][1][count_1];
      board->w ^= rays_to_flip[42][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000010000000){
    count_2 = 0;
    if(opp & 0x0000000800000000){
      count_2++;
      if(opp & 0x0000040000000000){
	count_2++;
	if(opp & 0x0002000000000000){
	  count_2++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[42][2][count_2], -7)){
      board->b ^= rays_to_flip[42][2][count_2];
      board->w ^= rays_to_flip[42][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000400000){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[42][3][count_3], -1)){
      board->b ^= rays_to_flip[42][3][count_3];
      board->w ^= rays_to_flip[42][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000100000){
    count_4 = 0;
    if(opp & 0x0000000000080000){
      count_4++;
      if(opp & 0x0000000000040000){
	count_4++;
	if(opp & 0x0000000000020000){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[42][4][count_4], 1)){
      board->b ^= rays_to_flip[42][4][count_4];
      board->w ^= rays_to_flip[42][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000004000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[42][5][count_5], 7)){
      board->b ^= rays_to_flip[42][5][count_5];
      board->w ^= rays_to_flip[42][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000002000){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[42][6][count_6], 8)){
      board->b ^= rays_to_flip[42][6][count_6];
      board->w ^= rays_to_flip[42][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000001000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[42][7][count_7], 9)){
      board->b ^= rays_to_flip[42][7][count_7];
      board->w ^= rays_to_flip[42][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000000000200000;

  return result;
}

char flip_bitboard_w_43(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000020000000){
    count_0 = 0;
    if(opp & 0x0000004000000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[43][0][count_0], -9)){
      board->b ^= rays_to_flip[43][0][count_0];
      board->w ^= rays_to_flip[43][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000010000000){
    count_1 = 0;
    if(opp & 0x0000001000000000){
      count_1++;
      if(opp & 0x0000100000000000){
	count_1++;
	if(opp & 0x0010000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[43][1][count_1], -8)){
      board->b ^= rays_to_flip[43][1][count_1];
      board->w ^= rays_to_flip[43][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000008000000){
    count_2 = 0;
    if(opp & 0x0000000400000000){
      count_2++;
      if(opp & 0x0000020000000000){
	count_2++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[43][2][count_2], -7)){
      board->b ^= rays_to_flip[43][2][count_2];
      board->w ^= rays_to_flip[43][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000200000){
    count_3 = 0;
    if(opp & 0x0000000000400000){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[43][3][count_3], -1)){
      board->b ^= rays_to_flip[43][3][count_3];
      board->w ^= rays_to_flip[43][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000080000){
    count_4 = 0;
    if(opp & 0x0000000000040000){
      count_4++;
      if(opp & 0x0000000000020000){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[43][4][count_4], 1)){
      board->b ^= rays_to_flip[43][4][count_4];
      board->w ^= rays_to_flip[43][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000002000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[43][5][count_5], 7)){
      board->b ^= rays_to_flip[43][5][count_5];
      board->w ^= rays_to_flip[43][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000001000){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[43][6][count_6], 8)){
      board->b ^= rays_to_flip[43][6][count_6];
      board->w ^= rays_to_flip[43][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000000800){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[43][7][count_7], 9)){
      board->b ^= rays_to_flip[43][7][count_7];
      board->w ^= rays_to_flip[43][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000000000100000;

  return result;
}

char flip_bitboard_w_44(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000010000000){
    count_0 = 0;
    if(opp & 0x0000002000000000){
      count_0++;
      if(opp & 0x0000400000000000){
	count_0++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[44][0][count_0], -9)){
      board->b ^= rays_to_flip[44][0][count_0];
      board->w ^= rays_to_flip[44][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000008000000){
    count_1 = 0;
    if(opp & 0x0000000800000000){
      count_1++;
      if(opp & 0x0000080000000000){
	count_1++;
	if(opp & 0x0008000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[44][1][count_1], -8)){
      board->b ^= rays_to_flip[44][1][count_1];
      board->w ^= rays_to_flip[44][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000004000000){
    count_2 = 0;
    if(opp & 0x0000000200000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[44][2][count_2], -7)){
      board->b ^= rays_to_flip[44][2][count_2];
      board->w ^= rays_to_flip[44][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000100000){
    count_3 = 0;
    if(opp & 0x0000000000200000){
      count_3++;
      if(opp & 0x0000000000400000){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[44][3][count_3], -1)){
      board->b ^= rays_to_flip[44][3][count_3];
      board->w ^= rays_to_flip[44][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000040000){
    count_4 = 0;
    if(opp & 0x0000000000020000){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[44][4][count_4], 1)){
      board->b ^= rays_to_flip[44][4][count_4];
      board->w ^= rays_to_flip[44][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000001000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[44][5][count_5], 7)){
      board->b ^= rays_to_flip[44][5][count_5];
      board->w ^= rays_to_flip[44][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000000800){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[44][6][count_6], 8)){
      board->b ^= rays_to_flip[44][6][count_6];
      board->w ^= rays_to_flip[44][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000000400){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[44][7][count_7], 9)){
      board->b ^= rays_to_flip[44][7][count_7];
      board->w ^= rays_to_flip[44][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000000000080000;

  return result;
}

char flip_bitboard_w_45(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000008000000){
    count_0 = 0;
    if(opp & 0x0000001000000000){
      count_0++;
      if(opp & 0x0000200000000000){
	count_0++;
	if(opp & 0x0040000000000000){
	  count_0++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[45][0][count_0], -9)){
      board->b ^= rays_to_flip[45][0][count_0];
      board->w ^= rays_to_flip[45][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000004000000){
    count_1 = 0;
    if(opp & 0x0000000400000000){
      count_1++;
      if(opp & 0x0000040000000000){
	count_1++;
	if(opp & 0x0004000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[45][1][count_1], -8)){
      board->b ^= rays_to_flip[45][1][count_1];
      board->w ^= rays_to_flip[45][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000002000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[45][2][count_2], -7)){
      board->b ^= rays_to_flip[45][2][count_2];
      board->w ^= rays_to_flip[45][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000080000){
    count_3 = 0;
    if(opp & 0x0000000000100000){
      count_3++;
      if(opp & 0x0000000000200000){
	count_3++;
	if(opp & 0x0000000000400000){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[45][3][count_3], -1)){
      board->b ^= rays_to_flip[45][3][count_3];
      board->w ^= rays_to_flip[45][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000020000){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[45][4][count_4], 1)){
      board->b ^= rays_to_flip[45][4][count_4];
      board->w ^= rays_to_flip[45][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000000800){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[45][5][count_5], 7)){
      board->b ^= rays_to_flip[45][5][count_5];
      board->w ^= rays_to_flip[45][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000000400){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[45][6][count_6], 8)){
      board->b ^= rays_to_flip[45][6][count_6];
      board->w ^= rays_to_flip[45][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000000200){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[45][7][count_7], 9)){
      board->b ^= rays_to_flip[45][7][count_7];
      board->w ^= rays_to_flip[45][7][count_7];
      result |= 0x80;
    }
  }

  board->w |= 0x0000000000040000;

  return result;
}

char flip_bitboard_w_46(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000004000000){
    count_0 = 0;
    if(opp & 0x0000000800000000){
      count_0++;
      if(opp & 0x0000100000000000){
	count_0++;
	if(opp & 0x0020000000000000){
	  count_0++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[46][0][count_0], -9)){
      board->b ^= rays_to_flip[46][0][count_0];
      board->w ^= rays_to_flip[46][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000002000000){
    count_1 = 0;
    if(opp & 0x0000000200000000){
      count_1++;
      if(opp & 0x0000020000000000){
	count_1++;
	if(opp & 0x0002000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[46][1][count_1], -8)){
      board->b ^= rays_to_flip[46][1][count_1];
      board->w ^= rays_to_flip[46][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000000040000){
    count_3 = 0;
    if(opp & 0x0000000000080000){
      count_3++;
      if(opp & 0x0000000000100000){
	count_3++;
	if(opp & 0x0000000000200000){
	  count_3++;
	  if(opp & 0x0000000000400000){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[46][3][count_3], -1)){
      board->b ^= rays_to_flip[46][3][count_3];
      board->w ^= rays_to_flip[46][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000000000400){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[46][5][count_5], 7)){
      board->b ^= rays_to_flip[46][5][count_5];
      board->w ^= rays_to_flip[46][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000000200){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[46][6][count_6], 8)){
      board->b ^= rays_to_flip[46][6][count_6];
      board->w ^= rays_to_flip[46][6][count_6];
      result |= 0x40;
    }
  }

  board->w |= 0x0000000000020000;

  return result;
}

char flip_bitboard_w_47(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000002000000){
    count_0 = 0;
    if(opp & 0x0000000400000000){
      count_0++;
      if(opp & 0x0000080000000000){
	count_0++;
	if(opp & 0x0010000000000000){
	  count_0++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[47][0][count_0], -9)){
      board->b ^= rays_to_flip[47][0][count_0];
      board->w ^= rays_to_flip[47][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000001000000){
    count_1 = 0;
    if(opp & 0x0000000100000000){
      count_1++;
      if(opp & 0x0000010000000000){
	count_1++;
	if(opp & 0x0001000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[47][1][count_1], -8)){
      board->b ^= rays_to_flip[47][1][count_1];
      board->w ^= rays_to_flip[47][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000000020000){
    count_3 = 0;
    if(opp & 0x0000000000040000){
      count_3++;
      if(opp & 0x0000000000080000){
	count_3++;
	if(opp & 0x0000000000100000){
	  count_3++;
	  if(opp & 0x0000000000200000){
	    count_3++;
	    if(opp & 0x0000000000400000){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[47][3][count_3], -1)){
      board->b ^= rays_to_flip[47][3][count_3];
      board->w ^= rays_to_flip[47][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000000000200){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[47][5][count_5], 7)){
      board->b ^= rays_to_flip[47][5][count_5];
      board->w ^= rays_to_flip[47][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000000100){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[47][6][count_6], 8)){
      board->b ^= rays_to_flip[47][6][count_6];
      board->w ^= rays_to_flip[47][6][count_6];
      result |= 0x40;
    }
  }

  board->w |= 0x0000000000010000;

  return result;
}

char flip_bitboard_w_48(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_1;
  if(opp & 0x0000000000800000){
    count_1 = 0;
    if(opp & 0x0000000080000000){
      count_1++;
      if(opp & 0x0000008000000000){
	count_1++;
	if(opp & 0x0000800000000000){
	  count_1++;
	  if(opp & 0x0080000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[48][1][count_1], -8)){
      board->b ^= rays_to_flip[48][1][count_1];
      board->w ^= rays_to_flip[48][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000400000){
    count_2 = 0;
    if(opp & 0x0000000020000000){
      count_2++;
      if(opp & 0x0000001000000000){
	count_2++;
	if(opp & 0x0000080000000000){
	  count_2++;
	  if(opp & 0x0004000000000000){
	    count_2++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[48][2][count_2], -7)){
      board->b ^= rays_to_flip[48][2][count_2];
      board->w ^= rays_to_flip[48][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000000004000){
    count_4 = 0;
    if(opp & 0x0000000000002000){
      count_4++;
      if(opp & 0x0000000000001000){
	count_4++;
	if(opp & 0x0000000000000800){
	  count_4++;
	  if(opp & 0x0000000000000400){
	    count_4++;
	    if(opp & 0x0000000000000200){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[48][4][count_4], 1)){
      board->b ^= rays_to_flip[48][4][count_4];
      board->w ^= rays_to_flip[48][4][count_4];
      result |= 0x10;
    }
  }

  board->w |= 0x0000000000008000;

  return result;
}

char flip_bitboard_w_49(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_1;
  if(opp & 0x0000000000400000){
    count_1 = 0;
    if(opp & 0x0000000040000000){
      count_1++;
      if(opp & 0x0000004000000000){
	count_1++;
	if(opp & 0x0000400000000000){
	  count_1++;
	  if(opp & 0x0040000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[49][1][count_1], -8)){
      board->b ^= rays_to_flip[49][1][count_1];
      board->w ^= rays_to_flip[49][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000200000){
    count_2 = 0;
    if(opp & 0x0000000010000000){
      count_2++;
      if(opp & 0x0000000800000000){
	count_2++;
	if(opp & 0x0000040000000000){
	  count_2++;
	  if(opp & 0x0002000000000000){
	    count_2++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[49][2][count_2], -7)){
      board->b ^= rays_to_flip[49][2][count_2];
      board->w ^= rays_to_flip[49][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000000002000){
    count_4 = 0;
    if(opp & 0x0000000000001000){
      count_4++;
      if(opp & 0x0000000000000800){
	count_4++;
	if(opp & 0x0000000000000400){
	  count_4++;
	  if(opp & 0x0000000000000200){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[49][4][count_4], 1)){
      board->b ^= rays_to_flip[49][4][count_4];
      board->w ^= rays_to_flip[49][4][count_4];
      result |= 0x10;
    }
  }

  board->w |= 0x0000000000004000;

  return result;
}

char flip_bitboard_w_50(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000400000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[50][0][count_0], -9)){
      board->b ^= rays_to_flip[50][0][count_0];
      board->w ^= rays_to_flip[50][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000200000){
    count_1 = 0;
    if(opp & 0x0000000020000000){
      count_1++;
      if(opp & 0x0000002000000000){
	count_1++;
	if(opp & 0x0000200000000000){
	  count_1++;
	  if(opp & 0x0020000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[50][1][count_1], -8)){
      board->b ^= rays_to_flip[50][1][count_1];
      board->w ^= rays_to_flip[50][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000100000){
    count_2 = 0;
    if(opp & 0x0000000008000000){
      count_2++;
      if(opp & 0x0000000400000000){
	count_2++;
	if(opp & 0x0000020000000000){
	  count_2++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[50][2][count_2], -7)){
      board->b ^= rays_to_flip[50][2][count_2];
      board->w ^= rays_to_flip[50][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000004000){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[50][3][count_3], -1)){
      board->b ^= rays_to_flip[50][3][count_3];
      board->w ^= rays_to_flip[50][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000001000){
    count_4 = 0;
    if(opp & 0x0000000000000800){
      count_4++;
      if(opp & 0x0000000000000400){
	count_4++;
	if(opp & 0x0000000000000200){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[50][4][count_4], 1)){
      board->b ^= rays_to_flip[50][4][count_4];
      board->w ^= rays_to_flip[50][4][count_4];
      result |= 0x10;
    }
  }

  board->w |= 0x0000000000002000;

  return result;
}

char flip_bitboard_w_51(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000200000){
    count_0 = 0;
    if(opp & 0x0000000040000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[51][0][count_0], -9)){
      board->b ^= rays_to_flip[51][0][count_0];
      board->w ^= rays_to_flip[51][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000100000){
    count_1 = 0;
    if(opp & 0x0000000010000000){
      count_1++;
      if(opp & 0x0000001000000000){
	count_1++;
	if(opp & 0x0000100000000000){
	  count_1++;
	  if(opp & 0x0010000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[51][1][count_1], -8)){
      board->b ^= rays_to_flip[51][1][count_1];
      board->w ^= rays_to_flip[51][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000080000){
    count_2 = 0;
    if(opp & 0x0000000004000000){
      count_2++;
      if(opp & 0x0000000200000000){
	count_2++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[51][2][count_2], -7)){
      board->b ^= rays_to_flip[51][2][count_2];
      board->w ^= rays_to_flip[51][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000002000){
    count_3 = 0;
    if(opp & 0x0000000000004000){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[51][3][count_3], -1)){
      board->b ^= rays_to_flip[51][3][count_3];
      board->w ^= rays_to_flip[51][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000000800){
    count_4 = 0;
    if(opp & 0x0000000000000400){
      count_4++;
      if(opp & 0x0000000000000200){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[51][4][count_4], 1)){
      board->b ^= rays_to_flip[51][4][count_4];
      board->w ^= rays_to_flip[51][4][count_4];
      result |= 0x10;
    }
  }

  board->w |= 0x0000000000001000;

  return result;
}

char flip_bitboard_w_52(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000100000){
    count_0 = 0;
    if(opp & 0x0000000020000000){
      count_0++;
      if(opp & 0x0000004000000000){
	count_0++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[52][0][count_0], -9)){
      board->b ^= rays_to_flip[52][0][count_0];
      board->w ^= rays_to_flip[52][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000080000){
    count_1 = 0;
    if(opp & 0x0000000008000000){
      count_1++;
      if(opp & 0x0000000800000000){
	count_1++;
	if(opp & 0x0000080000000000){
	  count_1++;
	  if(opp & 0x0008000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[52][1][count_1], -8)){
      board->b ^= rays_to_flip[52][1][count_1];
      board->w ^= rays_to_flip[52][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000040000){
    count_2 = 0;
    if(opp & 0x0000000002000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[52][2][count_2], -7)){
      board->b ^= rays_to_flip[52][2][count_2];
      board->w ^= rays_to_flip[52][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000001000){
    count_3 = 0;
    if(opp & 0x0000000000002000){
      count_3++;
      if(opp & 0x0000000000004000){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[52][3][count_3], -1)){
      board->b ^= rays_to_flip[52][3][count_3];
      board->w ^= rays_to_flip[52][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000000400){
    count_4 = 0;
    if(opp & 0x0000000000000200){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[52][4][count_4], 1)){
      board->b ^= rays_to_flip[52][4][count_4];
      board->w ^= rays_to_flip[52][4][count_4];
      result |= 0x10;
    }
  }

  board->w |= 0x0000000000000800;

  return result;
}

char flip_bitboard_w_53(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000080000){
    count_0 = 0;
    if(opp & 0x0000000010000000){
      count_0++;
      if(opp & 0x0000002000000000){
	count_0++;
	if(opp & 0x0000400000000000){
	  count_0++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[53][0][count_0], -9)){
      board->b ^= rays_to_flip[53][0][count_0];
      board->w ^= rays_to_flip[53][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000040000){
    count_1 = 0;
    if(opp & 0x0000000004000000){
      count_1++;
      if(opp & 0x0000000400000000){
	count_1++;
	if(opp & 0x0000040000000000){
	  count_1++;
	  if(opp & 0x0004000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[53][1][count_1], -8)){
      board->b ^= rays_to_flip[53][1][count_1];
      board->w ^= rays_to_flip[53][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000020000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[53][2][count_2], -7)){
      board->b ^= rays_to_flip[53][2][count_2];
      board->w ^= rays_to_flip[53][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000000800){
    count_3 = 0;
    if(opp & 0x0000000000001000){
      count_3++;
      if(opp & 0x0000000000002000){
	count_3++;
	if(opp & 0x0000000000004000){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[53][3][count_3], -1)){
      board->b ^= rays_to_flip[53][3][count_3];
      board->w ^= rays_to_flip[53][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000000200){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[53][4][count_4], 1)){
      board->b ^= rays_to_flip[53][4][count_4];
      board->w ^= rays_to_flip[53][4][count_4];
      result |= 0x10;
    }
  }

  board->w |= 0x0000000000000400;

  return result;
}

char flip_bitboard_w_54(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000040000){
    count_0 = 0;
    if(opp & 0x0000000008000000){
      count_0++;
      if(opp & 0x0000001000000000){
	count_0++;
	if(opp & 0x0000200000000000){
	  count_0++;
	  if(opp & 0x0040000000000000){
	    count_0++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[54][0][count_0], -9)){
      board->b ^= rays_to_flip[54][0][count_0];
      board->w ^= rays_to_flip[54][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000020000){
    count_1 = 0;
    if(opp & 0x0000000002000000){
      count_1++;
      if(opp & 0x0000000200000000){
	count_1++;
	if(opp & 0x0000020000000000){
	  count_1++;
	  if(opp & 0x0002000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[54][1][count_1], -8)){
      board->b ^= rays_to_flip[54][1][count_1];
      board->w ^= rays_to_flip[54][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000000000400){
    count_3 = 0;
    if(opp & 0x0000000000000800){
      count_3++;
      if(opp & 0x0000000000001000){
	count_3++;
	if(opp & 0x0000000000002000){
	  count_3++;
	  if(opp & 0x0000000000004000){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[54][3][count_3], -1)){
      board->b ^= rays_to_flip[54][3][count_3];
      board->w ^= rays_to_flip[54][3][count_3];
      result |= 0x08;
    }
  }

  board->w |= 0x0000000000000200;

  return result;
}

char flip_bitboard_w_55(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000020000){
    count_0 = 0;
    if(opp & 0x0000000004000000){
      count_0++;
      if(opp & 0x0000000800000000){
	count_0++;
	if(opp & 0x0000100000000000){
	  count_0++;
	  if(opp & 0x0020000000000000){
	    count_0++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[55][0][count_0], -9)){
      board->b ^= rays_to_flip[55][0][count_0];
      board->w ^= rays_to_flip[55][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000010000){
    count_1 = 0;
    if(opp & 0x0000000001000000){
      count_1++;
      if(opp & 0x0000000100000000){
	count_1++;
	if(opp & 0x0000010000000000){
	  count_1++;
	  if(opp & 0x0001000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[55][1][count_1], -8)){
      board->b ^= rays_to_flip[55][1][count_1];
      board->w ^= rays_to_flip[55][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000000000200){
    count_3 = 0;
    if(opp & 0x0000000000000400){
      count_3++;
      if(opp & 0x0000000000000800){
	count_3++;
	if(opp & 0x0000000000001000){
	  count_3++;
	  if(opp & 0x0000000000002000){
	    count_3++;
	    if(opp & 0x0000000000004000){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[55][3][count_3], -1)){
      board->b ^= rays_to_flip[55][3][count_3];
      board->w ^= rays_to_flip[55][3][count_3];
      result |= 0x08;
    }
  }

  board->w |= 0x0000000000000100;

  return result;
}

char flip_bitboard_w_56(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_1;
  if(opp & 0x0000000000008000){
    count_1 = 0;
    if(opp & 0x0000000000800000){
      count_1++;
      if(opp & 0x0000000080000000){
	count_1++;
	if(opp & 0x0000008000000000){
	  count_1++;
	  if(opp & 0x0000800000000000){
	    count_1++;
	    if(opp & 0x0080000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[56][1][count_1], -8)){
      board->b ^= rays_to_flip[56][1][count_1];
      board->w ^= rays_to_flip[56][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000004000){
    count_2 = 0;
    if(opp & 0x0000000000200000){
      count_2++;
      if(opp & 0x0000000010000000){
	count_2++;
	if(opp & 0x0000000800000000){
	  count_2++;
	  if(opp & 0x0000040000000000){
	    count_2++;
	    if(opp & 0x0002000000000000){
	      count_2++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[56][2][count_2], -7)){
      board->b ^= rays_to_flip[56][2][count_2];
      board->w ^= rays_to_flip[56][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000000000040){
    count_4 = 0;
    if(opp & 0x0000000000000020){
      count_4++;
      if(opp & 0x0000000000000010){
	count_4++;
	if(opp & 0x0000000000000008){
	  count_4++;
	  if(opp & 0x0000000000000004){
	    count_4++;
	    if(opp & 0x0000000000000002){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[56][4][count_4], 1)){
      board->b ^= rays_to_flip[56][4][count_4];
      board->w ^= rays_to_flip[56][4][count_4];
      result |= 0x10;
    }
  }

  board->w |= 0x0000000000000080;

  return result;
}

char flip_bitboard_w_57(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_1;
  if(opp & 0x0000000000004000){
    count_1 = 0;
    if(opp & 0x0000000000400000){
      count_1++;
      if(opp & 0x0000000040000000){
	count_1++;
	if(opp & 0x0000004000000000){
	  count_1++;
	  if(opp & 0x0000400000000000){
	    count_1++;
	    if(opp & 0x0040000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[57][1][count_1], -8)){
      board->b ^= rays_to_flip[57][1][count_1];
      board->w ^= rays_to_flip[57][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000002000){
    count_2 = 0;
    if(opp & 0x0000000000100000){
      count_2++;
      if(opp & 0x0000000008000000){
	count_2++;
	if(opp & 0x0000000400000000){
	  count_2++;
	  if(opp & 0x0000020000000000){
	    count_2++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[57][2][count_2], -7)){
      board->b ^= rays_to_flip[57][2][count_2];
      board->w ^= rays_to_flip[57][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000000000020){
    count_4 = 0;
    if(opp & 0x0000000000000010){
      count_4++;
      if(opp & 0x0000000000000008){
	count_4++;
	if(opp & 0x0000000000000004){
	  count_4++;
	  if(opp & 0x0000000000000002){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[57][4][count_4], 1)){
      board->b ^= rays_to_flip[57][4][count_4];
      board->w ^= rays_to_flip[57][4][count_4];
      result |= 0x10;
    }
  }

  board->w |= 0x0000000000000040;

  return result;
}

char flip_bitboard_w_58(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000004000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[58][0][count_0], -9)){
      board->b ^= rays_to_flip[58][0][count_0];
      board->w ^= rays_to_flip[58][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000002000){
    count_1 = 0;
    if(opp & 0x0000000000200000){
      count_1++;
      if(opp & 0x0000000020000000){
	count_1++;
	if(opp & 0x0000002000000000){
	  count_1++;
	  if(opp & 0x0000200000000000){
	    count_1++;
	    if(opp & 0x0020000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[58][1][count_1], -8)){
      board->b ^= rays_to_flip[58][1][count_1];
      board->w ^= rays_to_flip[58][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000001000){
    count_2 = 0;
    if(opp & 0x0000000000080000){
      count_2++;
      if(opp & 0x0000000004000000){
	count_2++;
	if(opp & 0x0000000200000000){
	  count_2++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[58][2][count_2], -7)){
      board->b ^= rays_to_flip[58][2][count_2];
      board->w ^= rays_to_flip[58][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000000040){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[58][3][count_3], -1)){
      board->b ^= rays_to_flip[58][3][count_3];
      board->w ^= rays_to_flip[58][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000000010){
    count_4 = 0;
    if(opp & 0x0000000000000008){
      count_4++;
      if(opp & 0x0000000000000004){
	count_4++;
	if(opp & 0x0000000000000002){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[58][4][count_4], 1)){
      board->b ^= rays_to_flip[58][4][count_4];
      board->w ^= rays_to_flip[58][4][count_4];
      result |= 0x10;
    }
  }

  board->w |= 0x0000000000000020;

  return result;
}

char flip_bitboard_w_59(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000002000){
    count_0 = 0;
    if(opp & 0x0000000000400000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[59][0][count_0], -9)){
      board->b ^= rays_to_flip[59][0][count_0];
      board->w ^= rays_to_flip[59][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000001000){
    count_1 = 0;
    if(opp & 0x0000000000100000){
      count_1++;
      if(opp & 0x0000000010000000){
	count_1++;
	if(opp & 0x0000001000000000){
	  count_1++;
	  if(opp & 0x0000100000000000){
	    count_1++;
	    if(opp & 0x0010000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[59][1][count_1], -8)){
      board->b ^= rays_to_flip[59][1][count_1];
      board->w ^= rays_to_flip[59][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000000800){
    count_2 = 0;
    if(opp & 0x0000000000040000){
      count_2++;
      if(opp & 0x0000000002000000){
	count_2++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[59][2][count_2], -7)){
      board->b ^= rays_to_flip[59][2][count_2];
      board->w ^= rays_to_flip[59][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000000020){
    count_3 = 0;
    if(opp & 0x0000000000000040){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[59][3][count_3], -1)){
      board->b ^= rays_to_flip[59][3][count_3];
      board->w ^= rays_to_flip[59][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000000008){
    count_4 = 0;
    if(opp & 0x0000000000000004){
      count_4++;
      if(opp & 0x0000000000000002){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[59][4][count_4], 1)){
      board->b ^= rays_to_flip[59][4][count_4];
      board->w ^= rays_to_flip[59][4][count_4];
      result |= 0x10;
    }
  }

  board->w |= 0x0000000000000010;

  return result;
}

char flip_bitboard_w_60(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000001000){
    count_0 = 0;
    if(opp & 0x0000000000200000){
      count_0++;
      if(opp & 0x0000000040000000){
	count_0++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[60][0][count_0], -9)){
      board->b ^= rays_to_flip[60][0][count_0];
      board->w ^= rays_to_flip[60][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000000800){
    count_1 = 0;
    if(opp & 0x0000000000080000){
      count_1++;
      if(opp & 0x0000000008000000){
	count_1++;
	if(opp & 0x0000000800000000){
	  count_1++;
	  if(opp & 0x0000080000000000){
	    count_1++;
	    if(opp & 0x0008000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[60][1][count_1], -8)){
      board->b ^= rays_to_flip[60][1][count_1];
      board->w ^= rays_to_flip[60][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000000400){
    count_2 = 0;
    if(opp & 0x0000000000020000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[60][2][count_2], -7)){
      board->b ^= rays_to_flip[60][2][count_2];
      board->w ^= rays_to_flip[60][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000000010){
    count_3 = 0;
    if(opp & 0x0000000000000020){
      count_3++;
      if(opp & 0x0000000000000040){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[60][3][count_3], -1)){
      board->b ^= rays_to_flip[60][3][count_3];
      board->w ^= rays_to_flip[60][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000000004){
    count_4 = 0;
    if(opp & 0x0000000000000002){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[60][4][count_4], 1)){
      board->b ^= rays_to_flip[60][4][count_4];
      board->w ^= rays_to_flip[60][4][count_4];
      result |= 0x10;
    }
  }

  board->w |= 0x0000000000000008;

  return result;
}

char flip_bitboard_w_61(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000000800){
    count_0 = 0;
    if(opp & 0x0000000000100000){
      count_0++;
      if(opp & 0x0000000020000000){
	count_0++;
	if(opp & 0x0000004000000000){
	  count_0++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[61][0][count_0], -9)){
      board->b ^= rays_to_flip[61][0][count_0];
      board->w ^= rays_to_flip[61][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000000400){
    count_1 = 0;
    if(opp & 0x0000000000040000){
      count_1++;
      if(opp & 0x0000000004000000){
	count_1++;
	if(opp & 0x0000000400000000){
	  count_1++;
	  if(opp & 0x0000040000000000){
	    count_1++;
	    if(opp & 0x0004000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[61][1][count_1], -8)){
      board->b ^= rays_to_flip[61][1][count_1];
      board->w ^= rays_to_flip[61][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000000200){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[61][2][count_2], -7)){
      board->b ^= rays_to_flip[61][2][count_2];
      board->w ^= rays_to_flip[61][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000000008){
    count_3 = 0;
    if(opp & 0x0000000000000010){
      count_3++;
      if(opp & 0x0000000000000020){
	count_3++;
	if(opp & 0x0000000000000040){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[61][3][count_3], -1)){
      board->b ^= rays_to_flip[61][3][count_3];
      board->w ^= rays_to_flip[61][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000000002){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[61][4][count_4], 1)){
      board->b ^= rays_to_flip[61][4][count_4];
      board->w ^= rays_to_flip[61][4][count_4];
      result |= 0x10;
    }
  }

  board->w |= 0x0000000000000004;

  return result;
}

char flip_bitboard_w_62(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000000400){
    count_0 = 0;
    if(opp & 0x0000000000080000){
      count_0++;
      if(opp & 0x0000000010000000){
	count_0++;
	if(opp & 0x0000002000000000){
	  count_0++;
	  if(opp & 0x0000400000000000){
	    count_0++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[62][0][count_0], -9)){
      board->b ^= rays_to_flip[62][0][count_0];
      board->w ^= rays_to_flip[62][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000000200){
    count_1 = 0;
    if(opp & 0x0000000000020000){
      count_1++;
      if(opp & 0x0000000002000000){
	count_1++;
	if(opp & 0x0000000200000000){
	  count_1++;
	  if(opp & 0x0000020000000000){
	    count_1++;
	    if(opp & 0x0002000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[62][1][count_1], -8)){
      board->b ^= rays_to_flip[62][1][count_1];
      board->w ^= rays_to_flip[62][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000000000004){
    count_3 = 0;
    if(opp & 0x0000000000000008){
      count_3++;
      if(opp & 0x0000000000000010){
	count_3++;
	if(opp & 0x0000000000000020){
	  count_3++;
	  if(opp & 0x0000000000000040){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[62][3][count_3], -1)){
      board->b ^= rays_to_flip[62][3][count_3];
      board->w ^= rays_to_flip[62][3][count_3];
      result |= 0x08;
    }
  }

  board->w |= 0x0000000000000002;

  return result;
}

char flip_bitboard_w_63(BitBoard *board){
  uint64_t my = board->w;
  uint64_t opp = board->b;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000000200){
    count_0 = 0;
    if(opp & 0x0000000000040000){
      count_0++;
      if(opp & 0x0000000008000000){
	count_0++;
	if(opp & 0x0000001000000000){
	  count_0++;
	  if(opp & 0x0000200000000000){
	    count_0++;
	    if(opp & 0x0040000000000000){
	      count_0++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[63][0][count_0], -9)){
      board->b ^= rays_to_flip[63][0][count_0];
      board->w ^= rays_to_flip[63][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000000100){
    count_1 = 0;
    if(opp & 0x0000000000010000){
      count_1++;
      if(opp & 0x0000000001000000){
	count_1++;
	if(opp & 0x0000000100000000){
	  count_1++;
	  if(opp & 0x0000010000000000){
	    count_1++;
	    if(opp & 0x0001000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[63][1][count_1], -8)){
      board->b ^= rays_to_flip[63][1][count_1];
      board->w ^= rays_to_flip[63][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000000000002){
    count_3 = 0;
    if(opp & 0x0000000000000004){
      count_3++;
      if(opp & 0x0000000000000008){
	count_3++;
	if(opp & 0x0000000000000010){
	  count_3++;
	  if(opp & 0x0000000000000020){
	    count_3++;
	    if(opp & 0x0000000000000040){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[63][3][count_3], -1)){
      board->b ^= rays_to_flip[63][3][count_3];
      board->w ^= rays_to_flip[63][3][count_3];
      result |= 0x08;
    }
  }

  board->w |= 0x0000000000000001;

  return result;
}

char flip_bitboard_b_00(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_4;
  if(opp & 0x4000000000000000){
    count_4 = 0;
    if(opp & 0x2000000000000000){
      count_4++;
      if(opp & 0x1000000000000000){
	count_4++;
	if(opp & 0x0800000000000000){
	  count_4++;
	  if(opp & 0x0400000000000000){
	    count_4++;
	    if(opp & 0x0200000000000000){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[0][4][count_4], 1)){
      board->b ^= rays_to_flip[0][4][count_4];
      board->w ^= rays_to_flip[0][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0080000000000000){
    count_6 = 0;
    if(opp & 0x0000800000000000){
      count_6++;
      if(opp & 0x0000008000000000){
	count_6++;
	if(opp & 0x0000000080000000){
	  count_6++;
	  if(opp & 0x0000000000800000){
	    count_6++;
	    if(opp & 0x0000000000008000){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[0][6][count_6], 8)){
      board->b ^= rays_to_flip[0][6][count_6];
      board->w ^= rays_to_flip[0][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0040000000000000){
    count_7 = 0;
    if(opp & 0x0000200000000000){
      count_7++;
      if(opp & 0x0000001000000000){
	count_7++;
	if(opp & 0x0000000008000000){
	  count_7++;
	  if(opp & 0x0000000000040000){
	    count_7++;
	    if(opp & 0x0000000000000200){
	      count_7++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[0][7][count_7], 9)){
      board->b ^= rays_to_flip[0][7][count_7];
      board->w ^= rays_to_flip[0][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x8000000000000000;

  return result;
}

char flip_bitboard_b_01(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_4;
  if(opp & 0x2000000000000000){
    count_4 = 0;
    if(opp & 0x1000000000000000){
      count_4++;
      if(opp & 0x0800000000000000){
	count_4++;
	if(opp & 0x0400000000000000){
	  count_4++;
	  if(opp & 0x0200000000000000){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[1][4][count_4], 1)){
      board->b ^= rays_to_flip[1][4][count_4];
      board->w ^= rays_to_flip[1][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0040000000000000){
    count_6 = 0;
    if(opp & 0x0000400000000000){
      count_6++;
      if(opp & 0x0000004000000000){
	count_6++;
	if(opp & 0x0000000040000000){
	  count_6++;
	  if(opp & 0x0000000000400000){
	    count_6++;
	    if(opp & 0x0000000000004000){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[1][6][count_6], 8)){
      board->b ^= rays_to_flip[1][6][count_6];
      board->w ^= rays_to_flip[1][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0020000000000000){
    count_7 = 0;
    if(opp & 0x0000100000000000){
      count_7++;
      if(opp & 0x0000000800000000){
	count_7++;
	if(opp & 0x0000000004000000){
	  count_7++;
	  if(opp & 0x0000000000020000){
	    count_7++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[1][7][count_7], 9)){
      board->b ^= rays_to_flip[1][7][count_7];
      board->w ^= rays_to_flip[1][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x4000000000000000;

  return result;
}

char flip_bitboard_b_02(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_3;
  if(opp & 0x4000000000000000){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[2][3][count_3], -1)){
      board->b ^= rays_to_flip[2][3][count_3];
      board->w ^= rays_to_flip[2][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x1000000000000000){
    count_4 = 0;
    if(opp & 0x0800000000000000){
      count_4++;
      if(opp & 0x0400000000000000){
	count_4++;
	if(opp & 0x0200000000000000){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[2][4][count_4], 1)){
      board->b ^= rays_to_flip[2][4][count_4];
      board->w ^= rays_to_flip[2][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0040000000000000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[2][5][count_5], 7)){
      board->b ^= rays_to_flip[2][5][count_5];
      board->w ^= rays_to_flip[2][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0020000000000000){
    count_6 = 0;
    if(opp & 0x0000200000000000){
      count_6++;
      if(opp & 0x0000002000000000){
	count_6++;
	if(opp & 0x0000000020000000){
	  count_6++;
	  if(opp & 0x0000000000200000){
	    count_6++;
	    if(opp & 0x0000000000002000){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[2][6][count_6], 8)){
      board->b ^= rays_to_flip[2][6][count_6];
      board->w ^= rays_to_flip[2][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0010000000000000){
    count_7 = 0;
    if(opp & 0x0000080000000000){
      count_7++;
      if(opp & 0x0000000400000000){
	count_7++;
	if(opp & 0x0000000002000000){
	  count_7++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[2][7][count_7], 9)){
      board->b ^= rays_to_flip[2][7][count_7];
      board->w ^= rays_to_flip[2][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x2000000000000000;

  return result;
}

char flip_bitboard_b_03(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_3;
  if(opp & 0x2000000000000000){
    count_3 = 0;
    if(opp & 0x4000000000000000){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[3][3][count_3], -1)){
      board->b ^= rays_to_flip[3][3][count_3];
      board->w ^= rays_to_flip[3][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0800000000000000){
    count_4 = 0;
    if(opp & 0x0400000000000000){
      count_4++;
      if(opp & 0x0200000000000000){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[3][4][count_4], 1)){
      board->b ^= rays_to_flip[3][4][count_4];
      board->w ^= rays_to_flip[3][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0020000000000000){
    count_5 = 0;
    if(opp & 0x0000400000000000){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[3][5][count_5], 7)){
      board->b ^= rays_to_flip[3][5][count_5];
      board->w ^= rays_to_flip[3][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0010000000000000){
    count_6 = 0;
    if(opp & 0x0000100000000000){
      count_6++;
      if(opp & 0x0000001000000000){
	count_6++;
	if(opp & 0x0000000010000000){
	  count_6++;
	  if(opp & 0x0000000000100000){
	    count_6++;
	    if(opp & 0x0000000000001000){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[3][6][count_6], 8)){
      board->b ^= rays_to_flip[3][6][count_6];
      board->w ^= rays_to_flip[3][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0008000000000000){
    count_7 = 0;
    if(opp & 0x0000040000000000){
      count_7++;
      if(opp & 0x0000000200000000){
	count_7++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[3][7][count_7], 9)){
      board->b ^= rays_to_flip[3][7][count_7];
      board->w ^= rays_to_flip[3][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x1000000000000000;

  return result;
}

char flip_bitboard_b_04(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_3;
  if(opp & 0x1000000000000000){
    count_3 = 0;
    if(opp & 0x2000000000000000){
      count_3++;
      if(opp & 0x4000000000000000){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[4][3][count_3], -1)){
      board->b ^= rays_to_flip[4][3][count_3];
      board->w ^= rays_to_flip[4][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0400000000000000){
    count_4 = 0;
    if(opp & 0x0200000000000000){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[4][4][count_4], 1)){
      board->b ^= rays_to_flip[4][4][count_4];
      board->w ^= rays_to_flip[4][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0010000000000000){
    count_5 = 0;
    if(opp & 0x0000200000000000){
      count_5++;
      if(opp & 0x0000004000000000){
	count_5++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[4][5][count_5], 7)){
      board->b ^= rays_to_flip[4][5][count_5];
      board->w ^= rays_to_flip[4][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0008000000000000){
    count_6 = 0;
    if(opp & 0x0000080000000000){
      count_6++;
      if(opp & 0x0000000800000000){
	count_6++;
	if(opp & 0x0000000008000000){
	  count_6++;
	  if(opp & 0x0000000000080000){
	    count_6++;
	    if(opp & 0x0000000000000800){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[4][6][count_6], 8)){
      board->b ^= rays_to_flip[4][6][count_6];
      board->w ^= rays_to_flip[4][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0004000000000000){
    count_7 = 0;
    if(opp & 0x0000020000000000){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[4][7][count_7], 9)){
      board->b ^= rays_to_flip[4][7][count_7];
      board->w ^= rays_to_flip[4][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0800000000000000;

  return result;
}

char flip_bitboard_b_05(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_3;
  if(opp & 0x0800000000000000){
    count_3 = 0;
    if(opp & 0x1000000000000000){
      count_3++;
      if(opp & 0x2000000000000000){
	count_3++;
	if(opp & 0x4000000000000000){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[5][3][count_3], -1)){
      board->b ^= rays_to_flip[5][3][count_3];
      board->w ^= rays_to_flip[5][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0200000000000000){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[5][4][count_4], 1)){
      board->b ^= rays_to_flip[5][4][count_4];
      board->w ^= rays_to_flip[5][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0008000000000000){
    count_5 = 0;
    if(opp & 0x0000100000000000){
      count_5++;
      if(opp & 0x0000002000000000){
	count_5++;
	if(opp & 0x0000000040000000){
	  count_5++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[5][5][count_5], 7)){
      board->b ^= rays_to_flip[5][5][count_5];
      board->w ^= rays_to_flip[5][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0004000000000000){
    count_6 = 0;
    if(opp & 0x0000040000000000){
      count_6++;
      if(opp & 0x0000000400000000){
	count_6++;
	if(opp & 0x0000000004000000){
	  count_6++;
	  if(opp & 0x0000000000040000){
	    count_6++;
	    if(opp & 0x0000000000000400){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[5][6][count_6], 8)){
      board->b ^= rays_to_flip[5][6][count_6];
      board->w ^= rays_to_flip[5][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0002000000000000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[5][7][count_7], 9)){
      board->b ^= rays_to_flip[5][7][count_7];
      board->w ^= rays_to_flip[5][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0400000000000000;

  return result;
}

char flip_bitboard_b_06(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_3;
  if(opp & 0x0400000000000000){
    count_3 = 0;
    if(opp & 0x0800000000000000){
      count_3++;
      if(opp & 0x1000000000000000){
	count_3++;
	if(opp & 0x2000000000000000){
	  count_3++;
	  if(opp & 0x4000000000000000){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[6][3][count_3], -1)){
      board->b ^= rays_to_flip[6][3][count_3];
      board->w ^= rays_to_flip[6][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0004000000000000){
    count_5 = 0;
    if(opp & 0x0000080000000000){
      count_5++;
      if(opp & 0x0000001000000000){
	count_5++;
	if(opp & 0x0000000020000000){
	  count_5++;
	  if(opp & 0x0000000000400000){
	    count_5++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[6][5][count_5], 7)){
      board->b ^= rays_to_flip[6][5][count_5];
      board->w ^= rays_to_flip[6][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0002000000000000){
    count_6 = 0;
    if(opp & 0x0000020000000000){
      count_6++;
      if(opp & 0x0000000200000000){
	count_6++;
	if(opp & 0x0000000002000000){
	  count_6++;
	  if(opp & 0x0000000000020000){
	    count_6++;
	    if(opp & 0x0000000000000200){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[6][6][count_6], 8)){
      board->b ^= rays_to_flip[6][6][count_6];
      board->w ^= rays_to_flip[6][6][count_6];
      result |= 0x40;
    }
  }

  board->b |= 0x0200000000000000;

  return result;
}

char flip_bitboard_b_07(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_3;
  if(opp & 0x0200000000000000){
    count_3 = 0;
    if(opp & 0x0400000000000000){
      count_3++;
      if(opp & 0x0800000000000000){
	count_3++;
	if(opp & 0x1000000000000000){
	  count_3++;
	  if(opp & 0x2000000000000000){
	    count_3++;
	    if(opp & 0x4000000000000000){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[7][3][count_3], -1)){
      board->b ^= rays_to_flip[7][3][count_3];
      board->w ^= rays_to_flip[7][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0002000000000000){
    count_5 = 0;
    if(opp & 0x0000040000000000){
      count_5++;
      if(opp & 0x0000000800000000){
	count_5++;
	if(opp & 0x0000000010000000){
	  count_5++;
	  if(opp & 0x0000000000200000){
	    count_5++;
	    if(opp & 0x0000000000004000){
	      count_5++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[7][5][count_5], 7)){
      board->b ^= rays_to_flip[7][5][count_5];
      board->w ^= rays_to_flip[7][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0001000000000000){
    count_6 = 0;
    if(opp & 0x0000010000000000){
      count_6++;
      if(opp & 0x0000000100000000){
	count_6++;
	if(opp & 0x0000000001000000){
	  count_6++;
	  if(opp & 0x0000000000010000){
	    count_6++;
	    if(opp & 0x0000000000000100){
	      count_6++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[7][6][count_6], 8)){
      board->b ^= rays_to_flip[7][6][count_6];
      board->w ^= rays_to_flip[7][6][count_6];
      result |= 0x40;
    }
  }

  board->b |= 0x0100000000000000;

  return result;
}

char flip_bitboard_b_08(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_4;
  if(opp & 0x0040000000000000){
    count_4 = 0;
    if(opp & 0x0020000000000000){
      count_4++;
      if(opp & 0x0010000000000000){
	count_4++;
	if(opp & 0x0008000000000000){
	  count_4++;
	  if(opp & 0x0004000000000000){
	    count_4++;
	    if(opp & 0x0002000000000000){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[8][4][count_4], 1)){
      board->b ^= rays_to_flip[8][4][count_4];
      board->w ^= rays_to_flip[8][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000800000000000){
    count_6 = 0;
    if(opp & 0x0000008000000000){
      count_6++;
      if(opp & 0x0000000080000000){
	count_6++;
	if(opp & 0x0000000000800000){
	  count_6++;
	  if(opp & 0x0000000000008000){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[8][6][count_6], 8)){
      board->b ^= rays_to_flip[8][6][count_6];
      board->w ^= rays_to_flip[8][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000400000000000){
    count_7 = 0;
    if(opp & 0x0000002000000000){
      count_7++;
      if(opp & 0x0000000010000000){
	count_7++;
	if(opp & 0x0000000000080000){
	  count_7++;
	  if(opp & 0x0000000000000400){
	    count_7++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[8][7][count_7], 9)){
      board->b ^= rays_to_flip[8][7][count_7];
      board->w ^= rays_to_flip[8][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0080000000000000;

  return result;
}

char flip_bitboard_b_09(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_4;
  if(opp & 0x0020000000000000){
    count_4 = 0;
    if(opp & 0x0010000000000000){
      count_4++;
      if(opp & 0x0008000000000000){
	count_4++;
	if(opp & 0x0004000000000000){
	  count_4++;
	  if(opp & 0x0002000000000000){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[9][4][count_4], 1)){
      board->b ^= rays_to_flip[9][4][count_4];
      board->w ^= rays_to_flip[9][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000400000000000){
    count_6 = 0;
    if(opp & 0x0000004000000000){
      count_6++;
      if(opp & 0x0000000040000000){
	count_6++;
	if(opp & 0x0000000000400000){
	  count_6++;
	  if(opp & 0x0000000000004000){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[9][6][count_6], 8)){
      board->b ^= rays_to_flip[9][6][count_6];
      board->w ^= rays_to_flip[9][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000200000000000){
    count_7 = 0;
    if(opp & 0x0000001000000000){
      count_7++;
      if(opp & 0x0000000008000000){
	count_7++;
	if(opp & 0x0000000000040000){
	  count_7++;
	  if(opp & 0x0000000000000200){
	    count_7++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[9][7][count_7], 9)){
      board->b ^= rays_to_flip[9][7][count_7];
      board->w ^= rays_to_flip[9][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0040000000000000;

  return result;
}

char flip_bitboard_b_10(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_3;
  if(opp & 0x0040000000000000){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[10][3][count_3], -1)){
      board->b ^= rays_to_flip[10][3][count_3];
      board->w ^= rays_to_flip[10][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0010000000000000){
    count_4 = 0;
    if(opp & 0x0008000000000000){
      count_4++;
      if(opp & 0x0004000000000000){
	count_4++;
	if(opp & 0x0002000000000000){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[10][4][count_4], 1)){
      board->b ^= rays_to_flip[10][4][count_4];
      board->w ^= rays_to_flip[10][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000400000000000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[10][5][count_5], 7)){
      board->b ^= rays_to_flip[10][5][count_5];
      board->w ^= rays_to_flip[10][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000200000000000){
    count_6 = 0;
    if(opp & 0x0000002000000000){
      count_6++;
      if(opp & 0x0000000020000000){
	count_6++;
	if(opp & 0x0000000000200000){
	  count_6++;
	  if(opp & 0x0000000000002000){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[10][6][count_6], 8)){
      board->b ^= rays_to_flip[10][6][count_6];
      board->w ^= rays_to_flip[10][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000100000000000){
    count_7 = 0;
    if(opp & 0x0000000800000000){
      count_7++;
      if(opp & 0x0000000004000000){
	count_7++;
	if(opp & 0x0000000000020000){
	  count_7++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[10][7][count_7], 9)){
      board->b ^= rays_to_flip[10][7][count_7];
      board->w ^= rays_to_flip[10][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0020000000000000;

  return result;
}

char flip_bitboard_b_11(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_3;
  if(opp & 0x0020000000000000){
    count_3 = 0;
    if(opp & 0x0040000000000000){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[11][3][count_3], -1)){
      board->b ^= rays_to_flip[11][3][count_3];
      board->w ^= rays_to_flip[11][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0008000000000000){
    count_4 = 0;
    if(opp & 0x0004000000000000){
      count_4++;
      if(opp & 0x0002000000000000){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[11][4][count_4], 1)){
      board->b ^= rays_to_flip[11][4][count_4];
      board->w ^= rays_to_flip[11][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000200000000000){
    count_5 = 0;
    if(opp & 0x0000004000000000){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[11][5][count_5], 7)){
      board->b ^= rays_to_flip[11][5][count_5];
      board->w ^= rays_to_flip[11][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000100000000000){
    count_6 = 0;
    if(opp & 0x0000001000000000){
      count_6++;
      if(opp & 0x0000000010000000){
	count_6++;
	if(opp & 0x0000000000100000){
	  count_6++;
	  if(opp & 0x0000000000001000){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[11][6][count_6], 8)){
      board->b ^= rays_to_flip[11][6][count_6];
      board->w ^= rays_to_flip[11][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000080000000000){
    count_7 = 0;
    if(opp & 0x0000000400000000){
      count_7++;
      if(opp & 0x0000000002000000){
	count_7++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[11][7][count_7], 9)){
      board->b ^= rays_to_flip[11][7][count_7];
      board->w ^= rays_to_flip[11][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0010000000000000;

  return result;
}

char flip_bitboard_b_12(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_3;
  if(opp & 0x0010000000000000){
    count_3 = 0;
    if(opp & 0x0020000000000000){
      count_3++;
      if(opp & 0x0040000000000000){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[12][3][count_3], -1)){
      board->b ^= rays_to_flip[12][3][count_3];
      board->w ^= rays_to_flip[12][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0004000000000000){
    count_4 = 0;
    if(opp & 0x0002000000000000){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[12][4][count_4], 1)){
      board->b ^= rays_to_flip[12][4][count_4];
      board->w ^= rays_to_flip[12][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000100000000000){
    count_5 = 0;
    if(opp & 0x0000002000000000){
      count_5++;
      if(opp & 0x0000000040000000){
	count_5++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[12][5][count_5], 7)){
      board->b ^= rays_to_flip[12][5][count_5];
      board->w ^= rays_to_flip[12][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000080000000000){
    count_6 = 0;
    if(opp & 0x0000000800000000){
      count_6++;
      if(opp & 0x0000000008000000){
	count_6++;
	if(opp & 0x0000000000080000){
	  count_6++;
	  if(opp & 0x0000000000000800){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[12][6][count_6], 8)){
      board->b ^= rays_to_flip[12][6][count_6];
      board->w ^= rays_to_flip[12][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000040000000000){
    count_7 = 0;
    if(opp & 0x0000000200000000){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[12][7][count_7], 9)){
      board->b ^= rays_to_flip[12][7][count_7];
      board->w ^= rays_to_flip[12][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0008000000000000;

  return result;
}

char flip_bitboard_b_13(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_3;
  if(opp & 0x0008000000000000){
    count_3 = 0;
    if(opp & 0x0010000000000000){
      count_3++;
      if(opp & 0x0020000000000000){
	count_3++;
	if(opp & 0x0040000000000000){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[13][3][count_3], -1)){
      board->b ^= rays_to_flip[13][3][count_3];
      board->w ^= rays_to_flip[13][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0002000000000000){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[13][4][count_4], 1)){
      board->b ^= rays_to_flip[13][4][count_4];
      board->w ^= rays_to_flip[13][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000080000000000){
    count_5 = 0;
    if(opp & 0x0000001000000000){
      count_5++;
      if(opp & 0x0000000020000000){
	count_5++;
	if(opp & 0x0000000000400000){
	  count_5++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[13][5][count_5], 7)){
      board->b ^= rays_to_flip[13][5][count_5];
      board->w ^= rays_to_flip[13][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000040000000000){
    count_6 = 0;
    if(opp & 0x0000000400000000){
      count_6++;
      if(opp & 0x0000000004000000){
	count_6++;
	if(opp & 0x0000000000040000){
	  count_6++;
	  if(opp & 0x0000000000000400){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[13][6][count_6], 8)){
      board->b ^= rays_to_flip[13][6][count_6];
      board->w ^= rays_to_flip[13][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000020000000000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[13][7][count_7], 9)){
      board->b ^= rays_to_flip[13][7][count_7];
      board->w ^= rays_to_flip[13][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0004000000000000;

  return result;
}

char flip_bitboard_b_14(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_3;
  if(opp & 0x0004000000000000){
    count_3 = 0;
    if(opp & 0x0008000000000000){
      count_3++;
      if(opp & 0x0010000000000000){
	count_3++;
	if(opp & 0x0020000000000000){
	  count_3++;
	  if(opp & 0x0040000000000000){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[14][3][count_3], -1)){
      board->b ^= rays_to_flip[14][3][count_3];
      board->w ^= rays_to_flip[14][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000040000000000){
    count_5 = 0;
    if(opp & 0x0000000800000000){
      count_5++;
      if(opp & 0x0000000010000000){
	count_5++;
	if(opp & 0x0000000000200000){
	  count_5++;
	  if(opp & 0x0000000000004000){
	    count_5++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[14][5][count_5], 7)){
      board->b ^= rays_to_flip[14][5][count_5];
      board->w ^= rays_to_flip[14][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000020000000000){
    count_6 = 0;
    if(opp & 0x0000000200000000){
      count_6++;
      if(opp & 0x0000000002000000){
	count_6++;
	if(opp & 0x0000000000020000){
	  count_6++;
	  if(opp & 0x0000000000000200){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[14][6][count_6], 8)){
      board->b ^= rays_to_flip[14][6][count_6];
      board->w ^= rays_to_flip[14][6][count_6];
      result |= 0x40;
    }
  }

  board->b |= 0x0002000000000000;

  return result;
}

char flip_bitboard_b_15(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_3;
  if(opp & 0x0002000000000000){
    count_3 = 0;
    if(opp & 0x0004000000000000){
      count_3++;
      if(opp & 0x0008000000000000){
	count_3++;
	if(opp & 0x0010000000000000){
	  count_3++;
	  if(opp & 0x0020000000000000){
	    count_3++;
	    if(opp & 0x0040000000000000){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[15][3][count_3], -1)){
      board->b ^= rays_to_flip[15][3][count_3];
      board->w ^= rays_to_flip[15][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000020000000000){
    count_5 = 0;
    if(opp & 0x0000000400000000){
      count_5++;
      if(opp & 0x0000000008000000){
	count_5++;
	if(opp & 0x0000000000100000){
	  count_5++;
	  if(opp & 0x0000000000002000){
	    count_5++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[15][5][count_5], 7)){
      board->b ^= rays_to_flip[15][5][count_5];
      board->w ^= rays_to_flip[15][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000010000000000){
    count_6 = 0;
    if(opp & 0x0000000100000000){
      count_6++;
      if(opp & 0x0000000001000000){
	count_6++;
	if(opp & 0x0000000000010000){
	  count_6++;
	  if(opp & 0x0000000000000100){
	    count_6++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[15][6][count_6], 8)){
      board->b ^= rays_to_flip[15][6][count_6];
      board->w ^= rays_to_flip[15][6][count_6];
      result |= 0x40;
    }
  }

  board->b |= 0x0001000000000000;

  return result;
}

char flip_bitboard_b_16(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_1;
  if(opp & 0x0080000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[16][1][count_1], -8)){
      board->b ^= rays_to_flip[16][1][count_1];
      board->w ^= rays_to_flip[16][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0040000000000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[16][2][count_2], -7)){
      board->b ^= rays_to_flip[16][2][count_2];
      board->w ^= rays_to_flip[16][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000400000000000){
    count_4 = 0;
    if(opp & 0x0000200000000000){
      count_4++;
      if(opp & 0x0000100000000000){
	count_4++;
	if(opp & 0x0000080000000000){
	  count_4++;
	  if(opp & 0x0000040000000000){
	    count_4++;
	    if(opp & 0x0000020000000000){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[16][4][count_4], 1)){
      board->b ^= rays_to_flip[16][4][count_4];
      board->w ^= rays_to_flip[16][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000008000000000){
    count_6 = 0;
    if(opp & 0x0000000080000000){
      count_6++;
      if(opp & 0x0000000000800000){
	count_6++;
	if(opp & 0x0000000000008000){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[16][6][count_6], 8)){
      board->b ^= rays_to_flip[16][6][count_6];
      board->w ^= rays_to_flip[16][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000004000000000){
    count_7 = 0;
    if(opp & 0x0000000020000000){
      count_7++;
      if(opp & 0x0000000000100000){
	count_7++;
	if(opp & 0x0000000000000800){
	  count_7++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[16][7][count_7], 9)){
      board->b ^= rays_to_flip[16][7][count_7];
      board->w ^= rays_to_flip[16][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000800000000000;

  return result;
}

char flip_bitboard_b_17(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_1;
  if(opp & 0x0040000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[17][1][count_1], -8)){
      board->b ^= rays_to_flip[17][1][count_1];
      board->w ^= rays_to_flip[17][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0020000000000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[17][2][count_2], -7)){
      board->b ^= rays_to_flip[17][2][count_2];
      board->w ^= rays_to_flip[17][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000200000000000){
    count_4 = 0;
    if(opp & 0x0000100000000000){
      count_4++;
      if(opp & 0x0000080000000000){
	count_4++;
	if(opp & 0x0000040000000000){
	  count_4++;
	  if(opp & 0x0000020000000000){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[17][4][count_4], 1)){
      board->b ^= rays_to_flip[17][4][count_4];
      board->w ^= rays_to_flip[17][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000004000000000){
    count_6 = 0;
    if(opp & 0x0000000040000000){
      count_6++;
      if(opp & 0x0000000000400000){
	count_6++;
	if(opp & 0x0000000000004000){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[17][6][count_6], 8)){
      board->b ^= rays_to_flip[17][6][count_6];
      board->w ^= rays_to_flip[17][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000002000000000){
    count_7 = 0;
    if(opp & 0x0000000010000000){
      count_7++;
      if(opp & 0x0000000000080000){
	count_7++;
	if(opp & 0x0000000000000400){
	  count_7++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[17][7][count_7], 9)){
      board->b ^= rays_to_flip[17][7][count_7];
      board->w ^= rays_to_flip[17][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000400000000000;

  return result;
}

char flip_bitboard_b_18(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0040000000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[18][0][count_0], -9)){
      board->b ^= rays_to_flip[18][0][count_0];
      board->w ^= rays_to_flip[18][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0020000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[18][1][count_1], -8)){
      board->b ^= rays_to_flip[18][1][count_1];
      board->w ^= rays_to_flip[18][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0010000000000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[18][2][count_2], -7)){
      board->b ^= rays_to_flip[18][2][count_2];
      board->w ^= rays_to_flip[18][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000400000000000){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[18][3][count_3], -1)){
      board->b ^= rays_to_flip[18][3][count_3];
      board->w ^= rays_to_flip[18][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000100000000000){
    count_4 = 0;
    if(opp & 0x0000080000000000){
      count_4++;
      if(opp & 0x0000040000000000){
	count_4++;
	if(opp & 0x0000020000000000){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[18][4][count_4], 1)){
      board->b ^= rays_to_flip[18][4][count_4];
      board->w ^= rays_to_flip[18][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000004000000000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[18][5][count_5], 7)){
      board->b ^= rays_to_flip[18][5][count_5];
      board->w ^= rays_to_flip[18][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000002000000000){
    count_6 = 0;
    if(opp & 0x0000000020000000){
      count_6++;
      if(opp & 0x0000000000200000){
	count_6++;
	if(opp & 0x0000000000002000){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[18][6][count_6], 8)){
      board->b ^= rays_to_flip[18][6][count_6];
      board->w ^= rays_to_flip[18][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000001000000000){
    count_7 = 0;
    if(opp & 0x0000000008000000){
      count_7++;
      if(opp & 0x0000000000040000){
	count_7++;
	if(opp & 0x0000000000000200){
	  count_7++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[18][7][count_7], 9)){
      board->b ^= rays_to_flip[18][7][count_7];
      board->w ^= rays_to_flip[18][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000200000000000;

  return result;
}

char flip_bitboard_b_19(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0020000000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[19][0][count_0], -9)){
      board->b ^= rays_to_flip[19][0][count_0];
      board->w ^= rays_to_flip[19][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0010000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[19][1][count_1], -8)){
      board->b ^= rays_to_flip[19][1][count_1];
      board->w ^= rays_to_flip[19][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0008000000000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[19][2][count_2], -7)){
      board->b ^= rays_to_flip[19][2][count_2];
      board->w ^= rays_to_flip[19][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000200000000000){
    count_3 = 0;
    if(opp & 0x0000400000000000){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[19][3][count_3], -1)){
      board->b ^= rays_to_flip[19][3][count_3];
      board->w ^= rays_to_flip[19][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000080000000000){
    count_4 = 0;
    if(opp & 0x0000040000000000){
      count_4++;
      if(opp & 0x0000020000000000){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[19][4][count_4], 1)){
      board->b ^= rays_to_flip[19][4][count_4];
      board->w ^= rays_to_flip[19][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000002000000000){
    count_5 = 0;
    if(opp & 0x0000000040000000){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[19][5][count_5], 7)){
      board->b ^= rays_to_flip[19][5][count_5];
      board->w ^= rays_to_flip[19][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000001000000000){
    count_6 = 0;
    if(opp & 0x0000000010000000){
      count_6++;
      if(opp & 0x0000000000100000){
	count_6++;
	if(opp & 0x0000000000001000){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[19][6][count_6], 8)){
      board->b ^= rays_to_flip[19][6][count_6];
      board->w ^= rays_to_flip[19][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000800000000){
    count_7 = 0;
    if(opp & 0x0000000004000000){
      count_7++;
      if(opp & 0x0000000000020000){
	count_7++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[19][7][count_7], 9)){
      board->b ^= rays_to_flip[19][7][count_7];
      board->w ^= rays_to_flip[19][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000100000000000;

  return result;
}

char flip_bitboard_b_20(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0010000000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[20][0][count_0], -9)){
      board->b ^= rays_to_flip[20][0][count_0];
      board->w ^= rays_to_flip[20][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0008000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[20][1][count_1], -8)){
      board->b ^= rays_to_flip[20][1][count_1];
      board->w ^= rays_to_flip[20][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0004000000000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[20][2][count_2], -7)){
      board->b ^= rays_to_flip[20][2][count_2];
      board->w ^= rays_to_flip[20][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000100000000000){
    count_3 = 0;
    if(opp & 0x0000200000000000){
      count_3++;
      if(opp & 0x0000400000000000){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[20][3][count_3], -1)){
      board->b ^= rays_to_flip[20][3][count_3];
      board->w ^= rays_to_flip[20][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000040000000000){
    count_4 = 0;
    if(opp & 0x0000020000000000){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[20][4][count_4], 1)){
      board->b ^= rays_to_flip[20][4][count_4];
      board->w ^= rays_to_flip[20][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000001000000000){
    count_5 = 0;
    if(opp & 0x0000000020000000){
      count_5++;
      if(opp & 0x0000000000400000){
	count_5++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[20][5][count_5], 7)){
      board->b ^= rays_to_flip[20][5][count_5];
      board->w ^= rays_to_flip[20][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000800000000){
    count_6 = 0;
    if(opp & 0x0000000008000000){
      count_6++;
      if(opp & 0x0000000000080000){
	count_6++;
	if(opp & 0x0000000000000800){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[20][6][count_6], 8)){
      board->b ^= rays_to_flip[20][6][count_6];
      board->w ^= rays_to_flip[20][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000400000000){
    count_7 = 0;
    if(opp & 0x0000000002000000){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[20][7][count_7], 9)){
      board->b ^= rays_to_flip[20][7][count_7];
      board->w ^= rays_to_flip[20][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000080000000000;

  return result;
}

char flip_bitboard_b_21(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0008000000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[21][0][count_0], -9)){
      board->b ^= rays_to_flip[21][0][count_0];
      board->w ^= rays_to_flip[21][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0004000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[21][1][count_1], -8)){
      board->b ^= rays_to_flip[21][1][count_1];
      board->w ^= rays_to_flip[21][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0002000000000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[21][2][count_2], -7)){
      board->b ^= rays_to_flip[21][2][count_2];
      board->w ^= rays_to_flip[21][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000080000000000){
    count_3 = 0;
    if(opp & 0x0000100000000000){
      count_3++;
      if(opp & 0x0000200000000000){
	count_3++;
	if(opp & 0x0000400000000000){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[21][3][count_3], -1)){
      board->b ^= rays_to_flip[21][3][count_3];
      board->w ^= rays_to_flip[21][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000020000000000){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[21][4][count_4], 1)){
      board->b ^= rays_to_flip[21][4][count_4];
      board->w ^= rays_to_flip[21][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000800000000){
    count_5 = 0;
    if(opp & 0x0000000010000000){
      count_5++;
      if(opp & 0x0000000000200000){
	count_5++;
	if(opp & 0x0000000000004000){
	  count_5++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[21][5][count_5], 7)){
      board->b ^= rays_to_flip[21][5][count_5];
      board->w ^= rays_to_flip[21][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000400000000){
    count_6 = 0;
    if(opp & 0x0000000004000000){
      count_6++;
      if(opp & 0x0000000000040000){
	count_6++;
	if(opp & 0x0000000000000400){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[21][6][count_6], 8)){
      board->b ^= rays_to_flip[21][6][count_6];
      board->w ^= rays_to_flip[21][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000200000000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[21][7][count_7], 9)){
      board->b ^= rays_to_flip[21][7][count_7];
      board->w ^= rays_to_flip[21][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000040000000000;

  return result;
}

char flip_bitboard_b_22(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0004000000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[22][0][count_0], -9)){
      board->b ^= rays_to_flip[22][0][count_0];
      board->w ^= rays_to_flip[22][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0002000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[22][1][count_1], -8)){
      board->b ^= rays_to_flip[22][1][count_1];
      board->w ^= rays_to_flip[22][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000040000000000){
    count_3 = 0;
    if(opp & 0x0000080000000000){
      count_3++;
      if(opp & 0x0000100000000000){
	count_3++;
	if(opp & 0x0000200000000000){
	  count_3++;
	  if(opp & 0x0000400000000000){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[22][3][count_3], -1)){
      board->b ^= rays_to_flip[22][3][count_3];
      board->w ^= rays_to_flip[22][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000400000000){
    count_5 = 0;
    if(opp & 0x0000000008000000){
      count_5++;
      if(opp & 0x0000000000100000){
	count_5++;
	if(opp & 0x0000000000002000){
	  count_5++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[22][5][count_5], 7)){
      board->b ^= rays_to_flip[22][5][count_5];
      board->w ^= rays_to_flip[22][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000200000000){
    count_6 = 0;
    if(opp & 0x0000000002000000){
      count_6++;
      if(opp & 0x0000000000020000){
	count_6++;
	if(opp & 0x0000000000000200){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[22][6][count_6], 8)){
      board->b ^= rays_to_flip[22][6][count_6];
      board->w ^= rays_to_flip[22][6][count_6];
      result |= 0x40;
    }
  }

  board->b |= 0x0000020000000000;

  return result;
}

char flip_bitboard_b_23(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0002000000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[23][0][count_0], -9)){
      board->b ^= rays_to_flip[23][0][count_0];
      board->w ^= rays_to_flip[23][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0001000000000000){
    count_1 = 0;
    if(my & offset_bitmask(rays_to_flip[23][1][count_1], -8)){
      board->b ^= rays_to_flip[23][1][count_1];
      board->w ^= rays_to_flip[23][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000020000000000){
    count_3 = 0;
    if(opp & 0x0000040000000000){
      count_3++;
      if(opp & 0x0000080000000000){
	count_3++;
	if(opp & 0x0000100000000000){
	  count_3++;
	  if(opp & 0x0000200000000000){
	    count_3++;
	    if(opp & 0x0000400000000000){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[23][3][count_3], -1)){
      board->b ^= rays_to_flip[23][3][count_3];
      board->w ^= rays_to_flip[23][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000200000000){
    count_5 = 0;
    if(opp & 0x0000000004000000){
      count_5++;
      if(opp & 0x0000000000080000){
	count_5++;
	if(opp & 0x0000000000001000){
	  count_5++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[23][5][count_5], 7)){
      board->b ^= rays_to_flip[23][5][count_5];
      board->w ^= rays_to_flip[23][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000100000000){
    count_6 = 0;
    if(opp & 0x0000000001000000){
      count_6++;
      if(opp & 0x0000000000010000){
	count_6++;
	if(opp & 0x0000000000000100){
	  count_6++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[23][6][count_6], 8)){
      board->b ^= rays_to_flip[23][6][count_6];
      board->w ^= rays_to_flip[23][6][count_6];
      result |= 0x40;
    }
  }

  board->b |= 0x0000010000000000;

  return result;
}

char flip_bitboard_b_24(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_1;
  if(opp & 0x0000800000000000){
    count_1 = 0;
    if(opp & 0x0080000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[24][1][count_1], -8)){
      board->b ^= rays_to_flip[24][1][count_1];
      board->w ^= rays_to_flip[24][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000400000000000){
    count_2 = 0;
    if(opp & 0x0020000000000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[24][2][count_2], -7)){
      board->b ^= rays_to_flip[24][2][count_2];
      board->w ^= rays_to_flip[24][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000004000000000){
    count_4 = 0;
    if(opp & 0x0000002000000000){
      count_4++;
      if(opp & 0x0000001000000000){
	count_4++;
	if(opp & 0x0000000800000000){
	  count_4++;
	  if(opp & 0x0000000400000000){
	    count_4++;
	    if(opp & 0x0000000200000000){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[24][4][count_4], 1)){
      board->b ^= rays_to_flip[24][4][count_4];
      board->w ^= rays_to_flip[24][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000000080000000){
    count_6 = 0;
    if(opp & 0x0000000000800000){
      count_6++;
      if(opp & 0x0000000000008000){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[24][6][count_6], 8)){
      board->b ^= rays_to_flip[24][6][count_6];
      board->w ^= rays_to_flip[24][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000040000000){
    count_7 = 0;
    if(opp & 0x0000000000200000){
      count_7++;
      if(opp & 0x0000000000001000){
	count_7++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[24][7][count_7], 9)){
      board->b ^= rays_to_flip[24][7][count_7];
      board->w ^= rays_to_flip[24][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000008000000000;

  return result;
}

char flip_bitboard_b_25(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_1;
  if(opp & 0x0000400000000000){
    count_1 = 0;
    if(opp & 0x0040000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[25][1][count_1], -8)){
      board->b ^= rays_to_flip[25][1][count_1];
      board->w ^= rays_to_flip[25][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000200000000000){
    count_2 = 0;
    if(opp & 0x0010000000000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[25][2][count_2], -7)){
      board->b ^= rays_to_flip[25][2][count_2];
      board->w ^= rays_to_flip[25][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000002000000000){
    count_4 = 0;
    if(opp & 0x0000001000000000){
      count_4++;
      if(opp & 0x0000000800000000){
	count_4++;
	if(opp & 0x0000000400000000){
	  count_4++;
	  if(opp & 0x0000000200000000){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[25][4][count_4], 1)){
      board->b ^= rays_to_flip[25][4][count_4];
      board->w ^= rays_to_flip[25][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000000040000000){
    count_6 = 0;
    if(opp & 0x0000000000400000){
      count_6++;
      if(opp & 0x0000000000004000){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[25][6][count_6], 8)){
      board->b ^= rays_to_flip[25][6][count_6];
      board->w ^= rays_to_flip[25][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000020000000){
    count_7 = 0;
    if(opp & 0x0000000000100000){
      count_7++;
      if(opp & 0x0000000000000800){
	count_7++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[25][7][count_7], 9)){
      board->b ^= rays_to_flip[25][7][count_7];
      board->w ^= rays_to_flip[25][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000004000000000;

  return result;
}

char flip_bitboard_b_26(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000400000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[26][0][count_0], -9)){
      board->b ^= rays_to_flip[26][0][count_0];
      board->w ^= rays_to_flip[26][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000200000000000){
    count_1 = 0;
    if(opp & 0x0020000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[26][1][count_1], -8)){
      board->b ^= rays_to_flip[26][1][count_1];
      board->w ^= rays_to_flip[26][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000100000000000){
    count_2 = 0;
    if(opp & 0x0008000000000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[26][2][count_2], -7)){
      board->b ^= rays_to_flip[26][2][count_2];
      board->w ^= rays_to_flip[26][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000004000000000){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[26][3][count_3], -1)){
      board->b ^= rays_to_flip[26][3][count_3];
      board->w ^= rays_to_flip[26][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000001000000000){
    count_4 = 0;
    if(opp & 0x0000000800000000){
      count_4++;
      if(opp & 0x0000000400000000){
	count_4++;
	if(opp & 0x0000000200000000){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[26][4][count_4], 1)){
      board->b ^= rays_to_flip[26][4][count_4];
      board->w ^= rays_to_flip[26][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000040000000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[26][5][count_5], 7)){
      board->b ^= rays_to_flip[26][5][count_5];
      board->w ^= rays_to_flip[26][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000020000000){
    count_6 = 0;
    if(opp & 0x0000000000200000){
      count_6++;
      if(opp & 0x0000000000002000){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[26][6][count_6], 8)){
      board->b ^= rays_to_flip[26][6][count_6];
      board->w ^= rays_to_flip[26][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000010000000){
    count_7 = 0;
    if(opp & 0x0000000000080000){
      count_7++;
      if(opp & 0x0000000000000400){
	count_7++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[26][7][count_7], 9)){
      board->b ^= rays_to_flip[26][7][count_7];
      board->w ^= rays_to_flip[26][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000002000000000;

  return result;
}

char flip_bitboard_b_27(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000200000000000){
    count_0 = 0;
    if(opp & 0x0040000000000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[27][0][count_0], -9)){
      board->b ^= rays_to_flip[27][0][count_0];
      board->w ^= rays_to_flip[27][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000100000000000){
    count_1 = 0;
    if(opp & 0x0010000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[27][1][count_1], -8)){
      board->b ^= rays_to_flip[27][1][count_1];
      board->w ^= rays_to_flip[27][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000080000000000){
    count_2 = 0;
    if(opp & 0x0004000000000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[27][2][count_2], -7)){
      board->b ^= rays_to_flip[27][2][count_2];
      board->w ^= rays_to_flip[27][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000002000000000){
    count_3 = 0;
    if(opp & 0x0000004000000000){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[27][3][count_3], -1)){
      board->b ^= rays_to_flip[27][3][count_3];
      board->w ^= rays_to_flip[27][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000800000000){
    count_4 = 0;
    if(opp & 0x0000000400000000){
      count_4++;
      if(opp & 0x0000000200000000){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[27][4][count_4], 1)){
      board->b ^= rays_to_flip[27][4][count_4];
      board->w ^= rays_to_flip[27][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000020000000){
    count_5 = 0;
    if(opp & 0x0000000000400000){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[27][5][count_5], 7)){
      board->b ^= rays_to_flip[27][5][count_5];
      board->w ^= rays_to_flip[27][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000010000000){
    count_6 = 0;
    if(opp & 0x0000000000100000){
      count_6++;
      if(opp & 0x0000000000001000){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[27][6][count_6], 8)){
      board->b ^= rays_to_flip[27][6][count_6];
      board->w ^= rays_to_flip[27][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000008000000){
    count_7 = 0;
    if(opp & 0x0000000000040000){
      count_7++;
      if(opp & 0x0000000000000200){
	count_7++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[27][7][count_7], 9)){
      board->b ^= rays_to_flip[27][7][count_7];
      board->w ^= rays_to_flip[27][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000001000000000;

  return result;
}

char flip_bitboard_b_28(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000100000000000){
    count_0 = 0;
    if(opp & 0x0020000000000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[28][0][count_0], -9)){
      board->b ^= rays_to_flip[28][0][count_0];
      board->w ^= rays_to_flip[28][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000080000000000){
    count_1 = 0;
    if(opp & 0x0008000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[28][1][count_1], -8)){
      board->b ^= rays_to_flip[28][1][count_1];
      board->w ^= rays_to_flip[28][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000040000000000){
    count_2 = 0;
    if(opp & 0x0002000000000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[28][2][count_2], -7)){
      board->b ^= rays_to_flip[28][2][count_2];
      board->w ^= rays_to_flip[28][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000001000000000){
    count_3 = 0;
    if(opp & 0x0000002000000000){
      count_3++;
      if(opp & 0x0000004000000000){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[28][3][count_3], -1)){
      board->b ^= rays_to_flip[28][3][count_3];
      board->w ^= rays_to_flip[28][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000400000000){
    count_4 = 0;
    if(opp & 0x0000000200000000){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[28][4][count_4], 1)){
      board->b ^= rays_to_flip[28][4][count_4];
      board->w ^= rays_to_flip[28][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000010000000){
    count_5 = 0;
    if(opp & 0x0000000000200000){
      count_5++;
      if(opp & 0x0000000000004000){
	count_5++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[28][5][count_5], 7)){
      board->b ^= rays_to_flip[28][5][count_5];
      board->w ^= rays_to_flip[28][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000008000000){
    count_6 = 0;
    if(opp & 0x0000000000080000){
      count_6++;
      if(opp & 0x0000000000000800){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[28][6][count_6], 8)){
      board->b ^= rays_to_flip[28][6][count_6];
      board->w ^= rays_to_flip[28][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000004000000){
    count_7 = 0;
    if(opp & 0x0000000000020000){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[28][7][count_7], 9)){
      board->b ^= rays_to_flip[28][7][count_7];
      board->w ^= rays_to_flip[28][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000000800000000;

  return result;
}

char flip_bitboard_b_29(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000080000000000){
    count_0 = 0;
    if(opp & 0x0010000000000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[29][0][count_0], -9)){
      board->b ^= rays_to_flip[29][0][count_0];
      board->w ^= rays_to_flip[29][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000040000000000){
    count_1 = 0;
    if(opp & 0x0004000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[29][1][count_1], -8)){
      board->b ^= rays_to_flip[29][1][count_1];
      board->w ^= rays_to_flip[29][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000020000000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[29][2][count_2], -7)){
      board->b ^= rays_to_flip[29][2][count_2];
      board->w ^= rays_to_flip[29][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000800000000){
    count_3 = 0;
    if(opp & 0x0000001000000000){
      count_3++;
      if(opp & 0x0000002000000000){
	count_3++;
	if(opp & 0x0000004000000000){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[29][3][count_3], -1)){
      board->b ^= rays_to_flip[29][3][count_3];
      board->w ^= rays_to_flip[29][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000200000000){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[29][4][count_4], 1)){
      board->b ^= rays_to_flip[29][4][count_4];
      board->w ^= rays_to_flip[29][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000008000000){
    count_5 = 0;
    if(opp & 0x0000000000100000){
      count_5++;
      if(opp & 0x0000000000002000){
	count_5++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[29][5][count_5], 7)){
      board->b ^= rays_to_flip[29][5][count_5];
      board->w ^= rays_to_flip[29][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000004000000){
    count_6 = 0;
    if(opp & 0x0000000000040000){
      count_6++;
      if(opp & 0x0000000000000400){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[29][6][count_6], 8)){
      board->b ^= rays_to_flip[29][6][count_6];
      board->w ^= rays_to_flip[29][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000002000000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[29][7][count_7], 9)){
      board->b ^= rays_to_flip[29][7][count_7];
      board->w ^= rays_to_flip[29][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000000400000000;

  return result;
}

char flip_bitboard_b_30(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000040000000000){
    count_0 = 0;
    if(opp & 0x0008000000000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[30][0][count_0], -9)){
      board->b ^= rays_to_flip[30][0][count_0];
      board->w ^= rays_to_flip[30][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000020000000000){
    count_1 = 0;
    if(opp & 0x0002000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[30][1][count_1], -8)){
      board->b ^= rays_to_flip[30][1][count_1];
      board->w ^= rays_to_flip[30][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000400000000){
    count_3 = 0;
    if(opp & 0x0000000800000000){
      count_3++;
      if(opp & 0x0000001000000000){
	count_3++;
	if(opp & 0x0000002000000000){
	  count_3++;
	  if(opp & 0x0000004000000000){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[30][3][count_3], -1)){
      board->b ^= rays_to_flip[30][3][count_3];
      board->w ^= rays_to_flip[30][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000004000000){
    count_5 = 0;
    if(opp & 0x0000000000080000){
      count_5++;
      if(opp & 0x0000000000001000){
	count_5++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[30][5][count_5], 7)){
      board->b ^= rays_to_flip[30][5][count_5];
      board->w ^= rays_to_flip[30][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000002000000){
    count_6 = 0;
    if(opp & 0x0000000000020000){
      count_6++;
      if(opp & 0x0000000000000200){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[30][6][count_6], 8)){
      board->b ^= rays_to_flip[30][6][count_6];
      board->w ^= rays_to_flip[30][6][count_6];
      result |= 0x40;
    }
  }

  board->b |= 0x0000000200000000;

  return result;
}

char flip_bitboard_b_31(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000020000000000){
    count_0 = 0;
    if(opp & 0x0004000000000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[31][0][count_0], -9)){
      board->b ^= rays_to_flip[31][0][count_0];
      board->w ^= rays_to_flip[31][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000010000000000){
    count_1 = 0;
    if(opp & 0x0001000000000000){
      count_1++;
    }
    if(my & offset_bitmask(rays_to_flip[31][1][count_1], -8)){
      board->b ^= rays_to_flip[31][1][count_1];
      board->w ^= rays_to_flip[31][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000200000000){
    count_3 = 0;
    if(opp & 0x0000000400000000){
      count_3++;
      if(opp & 0x0000000800000000){
	count_3++;
	if(opp & 0x0000001000000000){
	  count_3++;
	  if(opp & 0x0000002000000000){
	    count_3++;
	    if(opp & 0x0000004000000000){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[31][3][count_3], -1)){
      board->b ^= rays_to_flip[31][3][count_3];
      board->w ^= rays_to_flip[31][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000002000000){
    count_5 = 0;
    if(opp & 0x0000000000040000){
      count_5++;
      if(opp & 0x0000000000000800){
	count_5++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[31][5][count_5], 7)){
      board->b ^= rays_to_flip[31][5][count_5];
      board->w ^= rays_to_flip[31][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000001000000){
    count_6 = 0;
    if(opp & 0x0000000000010000){
      count_6++;
      if(opp & 0x0000000000000100){
	count_6++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[31][6][count_6], 8)){
      board->b ^= rays_to_flip[31][6][count_6];
      board->w ^= rays_to_flip[31][6][count_6];
      result |= 0x40;
    }
  }

  board->b |= 0x0000000100000000;

  return result;
}

char flip_bitboard_b_32(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_1;
  if(opp & 0x0000008000000000){
    count_1 = 0;
    if(opp & 0x0000800000000000){
      count_1++;
      if(opp & 0x0080000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[32][1][count_1], -8)){
      board->b ^= rays_to_flip[32][1][count_1];
      board->w ^= rays_to_flip[32][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000004000000000){
    count_2 = 0;
    if(opp & 0x0000200000000000){
      count_2++;
      if(opp & 0x0010000000000000){
	count_2++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[32][2][count_2], -7)){
      board->b ^= rays_to_flip[32][2][count_2];
      board->w ^= rays_to_flip[32][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000040000000){
    count_4 = 0;
    if(opp & 0x0000000020000000){
      count_4++;
      if(opp & 0x0000000010000000){
	count_4++;
	if(opp & 0x0000000008000000){
	  count_4++;
	  if(opp & 0x0000000004000000){
	    count_4++;
	    if(opp & 0x0000000002000000){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[32][4][count_4], 1)){
      board->b ^= rays_to_flip[32][4][count_4];
      board->w ^= rays_to_flip[32][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000000000800000){
    count_6 = 0;
    if(opp & 0x0000000000008000){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[32][6][count_6], 8)){
      board->b ^= rays_to_flip[32][6][count_6];
      board->w ^= rays_to_flip[32][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000400000){
    count_7 = 0;
    if(opp & 0x0000000000002000){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[32][7][count_7], 9)){
      board->b ^= rays_to_flip[32][7][count_7];
      board->w ^= rays_to_flip[32][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000000080000000;

  return result;
}

char flip_bitboard_b_33(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_1;
  if(opp & 0x0000004000000000){
    count_1 = 0;
    if(opp & 0x0000400000000000){
      count_1++;
      if(opp & 0x0040000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[33][1][count_1], -8)){
      board->b ^= rays_to_flip[33][1][count_1];
      board->w ^= rays_to_flip[33][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000002000000000){
    count_2 = 0;
    if(opp & 0x0000100000000000){
      count_2++;
      if(opp & 0x0008000000000000){
	count_2++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[33][2][count_2], -7)){
      board->b ^= rays_to_flip[33][2][count_2];
      board->w ^= rays_to_flip[33][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000020000000){
    count_4 = 0;
    if(opp & 0x0000000010000000){
      count_4++;
      if(opp & 0x0000000008000000){
	count_4++;
	if(opp & 0x0000000004000000){
	  count_4++;
	  if(opp & 0x0000000002000000){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[33][4][count_4], 1)){
      board->b ^= rays_to_flip[33][4][count_4];
      board->w ^= rays_to_flip[33][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000000000400000){
    count_6 = 0;
    if(opp & 0x0000000000004000){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[33][6][count_6], 8)){
      board->b ^= rays_to_flip[33][6][count_6];
      board->w ^= rays_to_flip[33][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000200000){
    count_7 = 0;
    if(opp & 0x0000000000001000){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[33][7][count_7], 9)){
      board->b ^= rays_to_flip[33][7][count_7];
      board->w ^= rays_to_flip[33][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000000040000000;

  return result;
}

char flip_bitboard_b_34(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000004000000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[34][0][count_0], -9)){
      board->b ^= rays_to_flip[34][0][count_0];
      board->w ^= rays_to_flip[34][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000002000000000){
    count_1 = 0;
    if(opp & 0x0000200000000000){
      count_1++;
      if(opp & 0x0020000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[34][1][count_1], -8)){
      board->b ^= rays_to_flip[34][1][count_1];
      board->w ^= rays_to_flip[34][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000001000000000){
    count_2 = 0;
    if(opp & 0x0000080000000000){
      count_2++;
      if(opp & 0x0004000000000000){
	count_2++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[34][2][count_2], -7)){
      board->b ^= rays_to_flip[34][2][count_2];
      board->w ^= rays_to_flip[34][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000040000000){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[34][3][count_3], -1)){
      board->b ^= rays_to_flip[34][3][count_3];
      board->w ^= rays_to_flip[34][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000010000000){
    count_4 = 0;
    if(opp & 0x0000000008000000){
      count_4++;
      if(opp & 0x0000000004000000){
	count_4++;
	if(opp & 0x0000000002000000){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[34][4][count_4], 1)){
      board->b ^= rays_to_flip[34][4][count_4];
      board->w ^= rays_to_flip[34][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000400000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[34][5][count_5], 7)){
      board->b ^= rays_to_flip[34][5][count_5];
      board->w ^= rays_to_flip[34][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000200000){
    count_6 = 0;
    if(opp & 0x0000000000002000){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[34][6][count_6], 8)){
      board->b ^= rays_to_flip[34][6][count_6];
      board->w ^= rays_to_flip[34][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000100000){
    count_7 = 0;
    if(opp & 0x0000000000000800){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[34][7][count_7], 9)){
      board->b ^= rays_to_flip[34][7][count_7];
      board->w ^= rays_to_flip[34][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000000020000000;

  return result;
}

char flip_bitboard_b_35(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000002000000000){
    count_0 = 0;
    if(opp & 0x0000400000000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[35][0][count_0], -9)){
      board->b ^= rays_to_flip[35][0][count_0];
      board->w ^= rays_to_flip[35][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000001000000000){
    count_1 = 0;
    if(opp & 0x0000100000000000){
      count_1++;
      if(opp & 0x0010000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[35][1][count_1], -8)){
      board->b ^= rays_to_flip[35][1][count_1];
      board->w ^= rays_to_flip[35][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000800000000){
    count_2 = 0;
    if(opp & 0x0000040000000000){
      count_2++;
      if(opp & 0x0002000000000000){
	count_2++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[35][2][count_2], -7)){
      board->b ^= rays_to_flip[35][2][count_2];
      board->w ^= rays_to_flip[35][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000020000000){
    count_3 = 0;
    if(opp & 0x0000000040000000){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[35][3][count_3], -1)){
      board->b ^= rays_to_flip[35][3][count_3];
      board->w ^= rays_to_flip[35][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000008000000){
    count_4 = 0;
    if(opp & 0x0000000004000000){
      count_4++;
      if(opp & 0x0000000002000000){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[35][4][count_4], 1)){
      board->b ^= rays_to_flip[35][4][count_4];
      board->w ^= rays_to_flip[35][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000200000){
    count_5 = 0;
    if(opp & 0x0000000000004000){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[35][5][count_5], 7)){
      board->b ^= rays_to_flip[35][5][count_5];
      board->w ^= rays_to_flip[35][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000100000){
    count_6 = 0;
    if(opp & 0x0000000000001000){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[35][6][count_6], 8)){
      board->b ^= rays_to_flip[35][6][count_6];
      board->w ^= rays_to_flip[35][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000080000){
    count_7 = 0;
    if(opp & 0x0000000000000400){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[35][7][count_7], 9)){
      board->b ^= rays_to_flip[35][7][count_7];
      board->w ^= rays_to_flip[35][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000000010000000;

  return result;
}

char flip_bitboard_b_36(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000001000000000){
    count_0 = 0;
    if(opp & 0x0000200000000000){
      count_0++;
      if(opp & 0x0040000000000000){
	count_0++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[36][0][count_0], -9)){
      board->b ^= rays_to_flip[36][0][count_0];
      board->w ^= rays_to_flip[36][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000800000000){
    count_1 = 0;
    if(opp & 0x0000080000000000){
      count_1++;
      if(opp & 0x0008000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[36][1][count_1], -8)){
      board->b ^= rays_to_flip[36][1][count_1];
      board->w ^= rays_to_flip[36][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000400000000){
    count_2 = 0;
    if(opp & 0x0000020000000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[36][2][count_2], -7)){
      board->b ^= rays_to_flip[36][2][count_2];
      board->w ^= rays_to_flip[36][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000010000000){
    count_3 = 0;
    if(opp & 0x0000000020000000){
      count_3++;
      if(opp & 0x0000000040000000){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[36][3][count_3], -1)){
      board->b ^= rays_to_flip[36][3][count_3];
      board->w ^= rays_to_flip[36][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000004000000){
    count_4 = 0;
    if(opp & 0x0000000002000000){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[36][4][count_4], 1)){
      board->b ^= rays_to_flip[36][4][count_4];
      board->w ^= rays_to_flip[36][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000100000){
    count_5 = 0;
    if(opp & 0x0000000000002000){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[36][5][count_5], 7)){
      board->b ^= rays_to_flip[36][5][count_5];
      board->w ^= rays_to_flip[36][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000080000){
    count_6 = 0;
    if(opp & 0x0000000000000800){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[36][6][count_6], 8)){
      board->b ^= rays_to_flip[36][6][count_6];
      board->w ^= rays_to_flip[36][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000040000){
    count_7 = 0;
    if(opp & 0x0000000000000200){
      count_7++;
    }
    if(my & offset_bitmask(rays_to_flip[36][7][count_7], 9)){
      board->b ^= rays_to_flip[36][7][count_7];
      board->w ^= rays_to_flip[36][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000000008000000;

  return result;
}

char flip_bitboard_b_37(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000800000000){
    count_0 = 0;
    if(opp & 0x0000100000000000){
      count_0++;
      if(opp & 0x0020000000000000){
	count_0++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[37][0][count_0], -9)){
      board->b ^= rays_to_flip[37][0][count_0];
      board->w ^= rays_to_flip[37][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000400000000){
    count_1 = 0;
    if(opp & 0x0000040000000000){
      count_1++;
      if(opp & 0x0004000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[37][1][count_1], -8)){
      board->b ^= rays_to_flip[37][1][count_1];
      board->w ^= rays_to_flip[37][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000200000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[37][2][count_2], -7)){
      board->b ^= rays_to_flip[37][2][count_2];
      board->w ^= rays_to_flip[37][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000008000000){
    count_3 = 0;
    if(opp & 0x0000000010000000){
      count_3++;
      if(opp & 0x0000000020000000){
	count_3++;
	if(opp & 0x0000000040000000){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[37][3][count_3], -1)){
      board->b ^= rays_to_flip[37][3][count_3];
      board->w ^= rays_to_flip[37][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000002000000){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[37][4][count_4], 1)){
      board->b ^= rays_to_flip[37][4][count_4];
      board->w ^= rays_to_flip[37][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000080000){
    count_5 = 0;
    if(opp & 0x0000000000001000){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[37][5][count_5], 7)){
      board->b ^= rays_to_flip[37][5][count_5];
      board->w ^= rays_to_flip[37][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000040000){
    count_6 = 0;
    if(opp & 0x0000000000000400){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[37][6][count_6], 8)){
      board->b ^= rays_to_flip[37][6][count_6];
      board->w ^= rays_to_flip[37][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000020000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[37][7][count_7], 9)){
      board->b ^= rays_to_flip[37][7][count_7];
      board->w ^= rays_to_flip[37][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000000004000000;

  return result;
}

char flip_bitboard_b_38(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000400000000){
    count_0 = 0;
    if(opp & 0x0000080000000000){
      count_0++;
      if(opp & 0x0010000000000000){
	count_0++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[38][0][count_0], -9)){
      board->b ^= rays_to_flip[38][0][count_0];
      board->w ^= rays_to_flip[38][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000200000000){
    count_1 = 0;
    if(opp & 0x0000020000000000){
      count_1++;
      if(opp & 0x0002000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[38][1][count_1], -8)){
      board->b ^= rays_to_flip[38][1][count_1];
      board->w ^= rays_to_flip[38][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000004000000){
    count_3 = 0;
    if(opp & 0x0000000008000000){
      count_3++;
      if(opp & 0x0000000010000000){
	count_3++;
	if(opp & 0x0000000020000000){
	  count_3++;
	  if(opp & 0x0000000040000000){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[38][3][count_3], -1)){
      board->b ^= rays_to_flip[38][3][count_3];
      board->w ^= rays_to_flip[38][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000000040000){
    count_5 = 0;
    if(opp & 0x0000000000000800){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[38][5][count_5], 7)){
      board->b ^= rays_to_flip[38][5][count_5];
      board->w ^= rays_to_flip[38][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000020000){
    count_6 = 0;
    if(opp & 0x0000000000000200){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[38][6][count_6], 8)){
      board->b ^= rays_to_flip[38][6][count_6];
      board->w ^= rays_to_flip[38][6][count_6];
      result |= 0x40;
    }
  }

  board->b |= 0x0000000002000000;

  return result;
}

char flip_bitboard_b_39(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000200000000){
    count_0 = 0;
    if(opp & 0x0000040000000000){
      count_0++;
      if(opp & 0x0008000000000000){
	count_0++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[39][0][count_0], -9)){
      board->b ^= rays_to_flip[39][0][count_0];
      board->w ^= rays_to_flip[39][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000100000000){
    count_1 = 0;
    if(opp & 0x0000010000000000){
      count_1++;
      if(opp & 0x0001000000000000){
	count_1++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[39][1][count_1], -8)){
      board->b ^= rays_to_flip[39][1][count_1];
      board->w ^= rays_to_flip[39][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000002000000){
    count_3 = 0;
    if(opp & 0x0000000004000000){
      count_3++;
      if(opp & 0x0000000008000000){
	count_3++;
	if(opp & 0x0000000010000000){
	  count_3++;
	  if(opp & 0x0000000020000000){
	    count_3++;
	    if(opp & 0x0000000040000000){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[39][3][count_3], -1)){
      board->b ^= rays_to_flip[39][3][count_3];
      board->w ^= rays_to_flip[39][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000000020000){
    count_5 = 0;
    if(opp & 0x0000000000000400){
      count_5++;
    }
    if(my & offset_bitmask(rays_to_flip[39][5][count_5], 7)){
      board->b ^= rays_to_flip[39][5][count_5];
      board->w ^= rays_to_flip[39][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000010000){
    count_6 = 0;
    if(opp & 0x0000000000000100){
      count_6++;
    }
    if(my & offset_bitmask(rays_to_flip[39][6][count_6], 8)){
      board->b ^= rays_to_flip[39][6][count_6];
      board->w ^= rays_to_flip[39][6][count_6];
      result |= 0x40;
    }
  }

  board->b |= 0x0000000001000000;

  return result;
}

char flip_bitboard_b_40(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_1;
  if(opp & 0x0000000080000000){
    count_1 = 0;
    if(opp & 0x0000008000000000){
      count_1++;
      if(opp & 0x0000800000000000){
	count_1++;
	if(opp & 0x0080000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[40][1][count_1], -8)){
      board->b ^= rays_to_flip[40][1][count_1];
      board->w ^= rays_to_flip[40][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000040000000){
    count_2 = 0;
    if(opp & 0x0000002000000000){
      count_2++;
      if(opp & 0x0000100000000000){
	count_2++;
	if(opp & 0x0008000000000000){
	  count_2++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[40][2][count_2], -7)){
      board->b ^= rays_to_flip[40][2][count_2];
      board->w ^= rays_to_flip[40][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000000400000){
    count_4 = 0;
    if(opp & 0x0000000000200000){
      count_4++;
      if(opp & 0x0000000000100000){
	count_4++;
	if(opp & 0x0000000000080000){
	  count_4++;
	  if(opp & 0x0000000000040000){
	    count_4++;
	    if(opp & 0x0000000000020000){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[40][4][count_4], 1)){
      board->b ^= rays_to_flip[40][4][count_4];
      board->w ^= rays_to_flip[40][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000000000008000){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[40][6][count_6], 8)){
      board->b ^= rays_to_flip[40][6][count_6];
      board->w ^= rays_to_flip[40][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000004000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[40][7][count_7], 9)){
      board->b ^= rays_to_flip[40][7][count_7];
      board->w ^= rays_to_flip[40][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000000000800000;

  return result;
}

char flip_bitboard_b_41(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_1;
  if(opp & 0x0000000040000000){
    count_1 = 0;
    if(opp & 0x0000004000000000){
      count_1++;
      if(opp & 0x0000400000000000){
	count_1++;
	if(opp & 0x0040000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[41][1][count_1], -8)){
      board->b ^= rays_to_flip[41][1][count_1];
      board->w ^= rays_to_flip[41][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000020000000){
    count_2 = 0;
    if(opp & 0x0000001000000000){
      count_2++;
      if(opp & 0x0000080000000000){
	count_2++;
	if(opp & 0x0004000000000000){
	  count_2++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[41][2][count_2], -7)){
      board->b ^= rays_to_flip[41][2][count_2];
      board->w ^= rays_to_flip[41][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000000200000){
    count_4 = 0;
    if(opp & 0x0000000000100000){
      count_4++;
      if(opp & 0x0000000000080000){
	count_4++;
	if(opp & 0x0000000000040000){
	  count_4++;
	  if(opp & 0x0000000000020000){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[41][4][count_4], 1)){
      board->b ^= rays_to_flip[41][4][count_4];
      board->w ^= rays_to_flip[41][4][count_4];
      result |= 0x10;
    }
  }
  int count_6;
  if(opp & 0x0000000000004000){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[41][6][count_6], 8)){
      board->b ^= rays_to_flip[41][6][count_6];
      board->w ^= rays_to_flip[41][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000002000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[41][7][count_7], 9)){
      board->b ^= rays_to_flip[41][7][count_7];
      board->w ^= rays_to_flip[41][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000000000400000;

  return result;
}

char flip_bitboard_b_42(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000040000000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[42][0][count_0], -9)){
      board->b ^= rays_to_flip[42][0][count_0];
      board->w ^= rays_to_flip[42][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000020000000){
    count_1 = 0;
    if(opp & 0x0000002000000000){
      count_1++;
      if(opp & 0x0000200000000000){
	count_1++;
	if(opp & 0x0020000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[42][1][count_1], -8)){
      board->b ^= rays_to_flip[42][1][count_1];
      board->w ^= rays_to_flip[42][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000010000000){
    count_2 = 0;
    if(opp & 0x0000000800000000){
      count_2++;
      if(opp & 0x0000040000000000){
	count_2++;
	if(opp & 0x0002000000000000){
	  count_2++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[42][2][count_2], -7)){
      board->b ^= rays_to_flip[42][2][count_2];
      board->w ^= rays_to_flip[42][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000400000){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[42][3][count_3], -1)){
      board->b ^= rays_to_flip[42][3][count_3];
      board->w ^= rays_to_flip[42][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000100000){
    count_4 = 0;
    if(opp & 0x0000000000080000){
      count_4++;
      if(opp & 0x0000000000040000){
	count_4++;
	if(opp & 0x0000000000020000){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[42][4][count_4], 1)){
      board->b ^= rays_to_flip[42][4][count_4];
      board->w ^= rays_to_flip[42][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000004000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[42][5][count_5], 7)){
      board->b ^= rays_to_flip[42][5][count_5];
      board->w ^= rays_to_flip[42][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000002000){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[42][6][count_6], 8)){
      board->b ^= rays_to_flip[42][6][count_6];
      board->w ^= rays_to_flip[42][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000001000){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[42][7][count_7], 9)){
      board->b ^= rays_to_flip[42][7][count_7];
      board->w ^= rays_to_flip[42][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000000000200000;

  return result;
}

char flip_bitboard_b_43(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000020000000){
    count_0 = 0;
    if(opp & 0x0000004000000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[43][0][count_0], -9)){
      board->b ^= rays_to_flip[43][0][count_0];
      board->w ^= rays_to_flip[43][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000010000000){
    count_1 = 0;
    if(opp & 0x0000001000000000){
      count_1++;
      if(opp & 0x0000100000000000){
	count_1++;
	if(opp & 0x0010000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[43][1][count_1], -8)){
      board->b ^= rays_to_flip[43][1][count_1];
      board->w ^= rays_to_flip[43][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000008000000){
    count_2 = 0;
    if(opp & 0x0000000400000000){
      count_2++;
      if(opp & 0x0000020000000000){
	count_2++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[43][2][count_2], -7)){
      board->b ^= rays_to_flip[43][2][count_2];
      board->w ^= rays_to_flip[43][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000200000){
    count_3 = 0;
    if(opp & 0x0000000000400000){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[43][3][count_3], -1)){
      board->b ^= rays_to_flip[43][3][count_3];
      board->w ^= rays_to_flip[43][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000080000){
    count_4 = 0;
    if(opp & 0x0000000000040000){
      count_4++;
      if(opp & 0x0000000000020000){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[43][4][count_4], 1)){
      board->b ^= rays_to_flip[43][4][count_4];
      board->w ^= rays_to_flip[43][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000002000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[43][5][count_5], 7)){
      board->b ^= rays_to_flip[43][5][count_5];
      board->w ^= rays_to_flip[43][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000001000){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[43][6][count_6], 8)){
      board->b ^= rays_to_flip[43][6][count_6];
      board->w ^= rays_to_flip[43][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000000800){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[43][7][count_7], 9)){
      board->b ^= rays_to_flip[43][7][count_7];
      board->w ^= rays_to_flip[43][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000000000100000;

  return result;
}

char flip_bitboard_b_44(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000010000000){
    count_0 = 0;
    if(opp & 0x0000002000000000){
      count_0++;
      if(opp & 0x0000400000000000){
	count_0++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[44][0][count_0], -9)){
      board->b ^= rays_to_flip[44][0][count_0];
      board->w ^= rays_to_flip[44][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000008000000){
    count_1 = 0;
    if(opp & 0x0000000800000000){
      count_1++;
      if(opp & 0x0000080000000000){
	count_1++;
	if(opp & 0x0008000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[44][1][count_1], -8)){
      board->b ^= rays_to_flip[44][1][count_1];
      board->w ^= rays_to_flip[44][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000004000000){
    count_2 = 0;
    if(opp & 0x0000000200000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[44][2][count_2], -7)){
      board->b ^= rays_to_flip[44][2][count_2];
      board->w ^= rays_to_flip[44][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000100000){
    count_3 = 0;
    if(opp & 0x0000000000200000){
      count_3++;
      if(opp & 0x0000000000400000){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[44][3][count_3], -1)){
      board->b ^= rays_to_flip[44][3][count_3];
      board->w ^= rays_to_flip[44][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000040000){
    count_4 = 0;
    if(opp & 0x0000000000020000){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[44][4][count_4], 1)){
      board->b ^= rays_to_flip[44][4][count_4];
      board->w ^= rays_to_flip[44][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000001000){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[44][5][count_5], 7)){
      board->b ^= rays_to_flip[44][5][count_5];
      board->w ^= rays_to_flip[44][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000000800){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[44][6][count_6], 8)){
      board->b ^= rays_to_flip[44][6][count_6];
      board->w ^= rays_to_flip[44][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000000400){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[44][7][count_7], 9)){
      board->b ^= rays_to_flip[44][7][count_7];
      board->w ^= rays_to_flip[44][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000000000080000;

  return result;
}

char flip_bitboard_b_45(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000008000000){
    count_0 = 0;
    if(opp & 0x0000001000000000){
      count_0++;
      if(opp & 0x0000200000000000){
	count_0++;
	if(opp & 0x0040000000000000){
	  count_0++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[45][0][count_0], -9)){
      board->b ^= rays_to_flip[45][0][count_0];
      board->w ^= rays_to_flip[45][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000004000000){
    count_1 = 0;
    if(opp & 0x0000000400000000){
      count_1++;
      if(opp & 0x0000040000000000){
	count_1++;
	if(opp & 0x0004000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[45][1][count_1], -8)){
      board->b ^= rays_to_flip[45][1][count_1];
      board->w ^= rays_to_flip[45][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000002000000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[45][2][count_2], -7)){
      board->b ^= rays_to_flip[45][2][count_2];
      board->w ^= rays_to_flip[45][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000080000){
    count_3 = 0;
    if(opp & 0x0000000000100000){
      count_3++;
      if(opp & 0x0000000000200000){
	count_3++;
	if(opp & 0x0000000000400000){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[45][3][count_3], -1)){
      board->b ^= rays_to_flip[45][3][count_3];
      board->w ^= rays_to_flip[45][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000020000){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[45][4][count_4], 1)){
      board->b ^= rays_to_flip[45][4][count_4];
      board->w ^= rays_to_flip[45][4][count_4];
      result |= 0x10;
    }
  }
  int count_5;
  if(opp & 0x0000000000000800){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[45][5][count_5], 7)){
      board->b ^= rays_to_flip[45][5][count_5];
      board->w ^= rays_to_flip[45][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000000400){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[45][6][count_6], 8)){
      board->b ^= rays_to_flip[45][6][count_6];
      board->w ^= rays_to_flip[45][6][count_6];
      result |= 0x40;
    }
  }
  int count_7;
  if(opp & 0x0000000000000200){
    count_7 = 0;
    if(my & offset_bitmask(rays_to_flip[45][7][count_7], 9)){
      board->b ^= rays_to_flip[45][7][count_7];
      board->w ^= rays_to_flip[45][7][count_7];
      result |= 0x80;
    }
  }

  board->b |= 0x0000000000040000;

  return result;
}

char flip_bitboard_b_46(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000004000000){
    count_0 = 0;
    if(opp & 0x0000000800000000){
      count_0++;
      if(opp & 0x0000100000000000){
	count_0++;
	if(opp & 0x0020000000000000){
	  count_0++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[46][0][count_0], -9)){
      board->b ^= rays_to_flip[46][0][count_0];
      board->w ^= rays_to_flip[46][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000002000000){
    count_1 = 0;
    if(opp & 0x0000000200000000){
      count_1++;
      if(opp & 0x0000020000000000){
	count_1++;
	if(opp & 0x0002000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[46][1][count_1], -8)){
      board->b ^= rays_to_flip[46][1][count_1];
      board->w ^= rays_to_flip[46][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000000040000){
    count_3 = 0;
    if(opp & 0x0000000000080000){
      count_3++;
      if(opp & 0x0000000000100000){
	count_3++;
	if(opp & 0x0000000000200000){
	  count_3++;
	  if(opp & 0x0000000000400000){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[46][3][count_3], -1)){
      board->b ^= rays_to_flip[46][3][count_3];
      board->w ^= rays_to_flip[46][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000000000400){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[46][5][count_5], 7)){
      board->b ^= rays_to_flip[46][5][count_5];
      board->w ^= rays_to_flip[46][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000000200){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[46][6][count_6], 8)){
      board->b ^= rays_to_flip[46][6][count_6];
      board->w ^= rays_to_flip[46][6][count_6];
      result |= 0x40;
    }
  }

  board->b |= 0x0000000000020000;

  return result;
}

char flip_bitboard_b_47(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000002000000){
    count_0 = 0;
    if(opp & 0x0000000400000000){
      count_0++;
      if(opp & 0x0000080000000000){
	count_0++;
	if(opp & 0x0010000000000000){
	  count_0++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[47][0][count_0], -9)){
      board->b ^= rays_to_flip[47][0][count_0];
      board->w ^= rays_to_flip[47][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000001000000){
    count_1 = 0;
    if(opp & 0x0000000100000000){
      count_1++;
      if(opp & 0x0000010000000000){
	count_1++;
	if(opp & 0x0001000000000000){
	  count_1++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[47][1][count_1], -8)){
      board->b ^= rays_to_flip[47][1][count_1];
      board->w ^= rays_to_flip[47][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000000020000){
    count_3 = 0;
    if(opp & 0x0000000000040000){
      count_3++;
      if(opp & 0x0000000000080000){
	count_3++;
	if(opp & 0x0000000000100000){
	  count_3++;
	  if(opp & 0x0000000000200000){
	    count_3++;
	    if(opp & 0x0000000000400000){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[47][3][count_3], -1)){
      board->b ^= rays_to_flip[47][3][count_3];
      board->w ^= rays_to_flip[47][3][count_3];
      result |= 0x08;
    }
  }
  int count_5;
  if(opp & 0x0000000000000200){
    count_5 = 0;
    if(my & offset_bitmask(rays_to_flip[47][5][count_5], 7)){
      board->b ^= rays_to_flip[47][5][count_5];
      board->w ^= rays_to_flip[47][5][count_5];
      result |= 0x20;
    }
  }
  int count_6;
  if(opp & 0x0000000000000100){
    count_6 = 0;
    if(my & offset_bitmask(rays_to_flip[47][6][count_6], 8)){
      board->b ^= rays_to_flip[47][6][count_6];
      board->w ^= rays_to_flip[47][6][count_6];
      result |= 0x40;
    }
  }

  board->b |= 0x0000000000010000;

  return result;
}

char flip_bitboard_b_48(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_1;
  if(opp & 0x0000000000800000){
    count_1 = 0;
    if(opp & 0x0000000080000000){
      count_1++;
      if(opp & 0x0000008000000000){
	count_1++;
	if(opp & 0x0000800000000000){
	  count_1++;
	  if(opp & 0x0080000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[48][1][count_1], -8)){
      board->b ^= rays_to_flip[48][1][count_1];
      board->w ^= rays_to_flip[48][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000400000){
    count_2 = 0;
    if(opp & 0x0000000020000000){
      count_2++;
      if(opp & 0x0000001000000000){
	count_2++;
	if(opp & 0x0000080000000000){
	  count_2++;
	  if(opp & 0x0004000000000000){
	    count_2++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[48][2][count_2], -7)){
      board->b ^= rays_to_flip[48][2][count_2];
      board->w ^= rays_to_flip[48][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000000004000){
    count_4 = 0;
    if(opp & 0x0000000000002000){
      count_4++;
      if(opp & 0x0000000000001000){
	count_4++;
	if(opp & 0x0000000000000800){
	  count_4++;
	  if(opp & 0x0000000000000400){
	    count_4++;
	    if(opp & 0x0000000000000200){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[48][4][count_4], 1)){
      board->b ^= rays_to_flip[48][4][count_4];
      board->w ^= rays_to_flip[48][4][count_4];
      result |= 0x10;
    }
  }

  board->b |= 0x0000000000008000;

  return result;
}

char flip_bitboard_b_49(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_1;
  if(opp & 0x0000000000400000){
    count_1 = 0;
    if(opp & 0x0000000040000000){
      count_1++;
      if(opp & 0x0000004000000000){
	count_1++;
	if(opp & 0x0000400000000000){
	  count_1++;
	  if(opp & 0x0040000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[49][1][count_1], -8)){
      board->b ^= rays_to_flip[49][1][count_1];
      board->w ^= rays_to_flip[49][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000200000){
    count_2 = 0;
    if(opp & 0x0000000010000000){
      count_2++;
      if(opp & 0x0000000800000000){
	count_2++;
	if(opp & 0x0000040000000000){
	  count_2++;
	  if(opp & 0x0002000000000000){
	    count_2++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[49][2][count_2], -7)){
      board->b ^= rays_to_flip[49][2][count_2];
      board->w ^= rays_to_flip[49][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000000002000){
    count_4 = 0;
    if(opp & 0x0000000000001000){
      count_4++;
      if(opp & 0x0000000000000800){
	count_4++;
	if(opp & 0x0000000000000400){
	  count_4++;
	  if(opp & 0x0000000000000200){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[49][4][count_4], 1)){
      board->b ^= rays_to_flip[49][4][count_4];
      board->w ^= rays_to_flip[49][4][count_4];
      result |= 0x10;
    }
  }

  board->b |= 0x0000000000004000;

  return result;
}

char flip_bitboard_b_50(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000400000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[50][0][count_0], -9)){
      board->b ^= rays_to_flip[50][0][count_0];
      board->w ^= rays_to_flip[50][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000200000){
    count_1 = 0;
    if(opp & 0x0000000020000000){
      count_1++;
      if(opp & 0x0000002000000000){
	count_1++;
	if(opp & 0x0000200000000000){
	  count_1++;
	  if(opp & 0x0020000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[50][1][count_1], -8)){
      board->b ^= rays_to_flip[50][1][count_1];
      board->w ^= rays_to_flip[50][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000100000){
    count_2 = 0;
    if(opp & 0x0000000008000000){
      count_2++;
      if(opp & 0x0000000400000000){
	count_2++;
	if(opp & 0x0000020000000000){
	  count_2++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[50][2][count_2], -7)){
      board->b ^= rays_to_flip[50][2][count_2];
      board->w ^= rays_to_flip[50][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000004000){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[50][3][count_3], -1)){
      board->b ^= rays_to_flip[50][3][count_3];
      board->w ^= rays_to_flip[50][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000001000){
    count_4 = 0;
    if(opp & 0x0000000000000800){
      count_4++;
      if(opp & 0x0000000000000400){
	count_4++;
	if(opp & 0x0000000000000200){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[50][4][count_4], 1)){
      board->b ^= rays_to_flip[50][4][count_4];
      board->w ^= rays_to_flip[50][4][count_4];
      result |= 0x10;
    }
  }

  board->b |= 0x0000000000002000;

  return result;
}

char flip_bitboard_b_51(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000200000){
    count_0 = 0;
    if(opp & 0x0000000040000000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[51][0][count_0], -9)){
      board->b ^= rays_to_flip[51][0][count_0];
      board->w ^= rays_to_flip[51][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000100000){
    count_1 = 0;
    if(opp & 0x0000000010000000){
      count_1++;
      if(opp & 0x0000001000000000){
	count_1++;
	if(opp & 0x0000100000000000){
	  count_1++;
	  if(opp & 0x0010000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[51][1][count_1], -8)){
      board->b ^= rays_to_flip[51][1][count_1];
      board->w ^= rays_to_flip[51][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000080000){
    count_2 = 0;
    if(opp & 0x0000000004000000){
      count_2++;
      if(opp & 0x0000000200000000){
	count_2++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[51][2][count_2], -7)){
      board->b ^= rays_to_flip[51][2][count_2];
      board->w ^= rays_to_flip[51][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000002000){
    count_3 = 0;
    if(opp & 0x0000000000004000){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[51][3][count_3], -1)){
      board->b ^= rays_to_flip[51][3][count_3];
      board->w ^= rays_to_flip[51][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000000800){
    count_4 = 0;
    if(opp & 0x0000000000000400){
      count_4++;
      if(opp & 0x0000000000000200){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[51][4][count_4], 1)){
      board->b ^= rays_to_flip[51][4][count_4];
      board->w ^= rays_to_flip[51][4][count_4];
      result |= 0x10;
    }
  }

  board->b |= 0x0000000000001000;

  return result;
}

char flip_bitboard_b_52(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000100000){
    count_0 = 0;
    if(opp & 0x0000000020000000){
      count_0++;
      if(opp & 0x0000004000000000){
	count_0++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[52][0][count_0], -9)){
      board->b ^= rays_to_flip[52][0][count_0];
      board->w ^= rays_to_flip[52][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000080000){
    count_1 = 0;
    if(opp & 0x0000000008000000){
      count_1++;
      if(opp & 0x0000000800000000){
	count_1++;
	if(opp & 0x0000080000000000){
	  count_1++;
	  if(opp & 0x0008000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[52][1][count_1], -8)){
      board->b ^= rays_to_flip[52][1][count_1];
      board->w ^= rays_to_flip[52][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000040000){
    count_2 = 0;
    if(opp & 0x0000000002000000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[52][2][count_2], -7)){
      board->b ^= rays_to_flip[52][2][count_2];
      board->w ^= rays_to_flip[52][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000001000){
    count_3 = 0;
    if(opp & 0x0000000000002000){
      count_3++;
      if(opp & 0x0000000000004000){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[52][3][count_3], -1)){
      board->b ^= rays_to_flip[52][3][count_3];
      board->w ^= rays_to_flip[52][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000000400){
    count_4 = 0;
    if(opp & 0x0000000000000200){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[52][4][count_4], 1)){
      board->b ^= rays_to_flip[52][4][count_4];
      board->w ^= rays_to_flip[52][4][count_4];
      result |= 0x10;
    }
  }

  board->b |= 0x0000000000000800;

  return result;
}

char flip_bitboard_b_53(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000080000){
    count_0 = 0;
    if(opp & 0x0000000010000000){
      count_0++;
      if(opp & 0x0000002000000000){
	count_0++;
	if(opp & 0x0000400000000000){
	  count_0++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[53][0][count_0], -9)){
      board->b ^= rays_to_flip[53][0][count_0];
      board->w ^= rays_to_flip[53][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000040000){
    count_1 = 0;
    if(opp & 0x0000000004000000){
      count_1++;
      if(opp & 0x0000000400000000){
	count_1++;
	if(opp & 0x0000040000000000){
	  count_1++;
	  if(opp & 0x0004000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[53][1][count_1], -8)){
      board->b ^= rays_to_flip[53][1][count_1];
      board->w ^= rays_to_flip[53][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000020000){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[53][2][count_2], -7)){
      board->b ^= rays_to_flip[53][2][count_2];
      board->w ^= rays_to_flip[53][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000000800){
    count_3 = 0;
    if(opp & 0x0000000000001000){
      count_3++;
      if(opp & 0x0000000000002000){
	count_3++;
	if(opp & 0x0000000000004000){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[53][3][count_3], -1)){
      board->b ^= rays_to_flip[53][3][count_3];
      board->w ^= rays_to_flip[53][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000000200){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[53][4][count_4], 1)){
      board->b ^= rays_to_flip[53][4][count_4];
      board->w ^= rays_to_flip[53][4][count_4];
      result |= 0x10;
    }
  }

  board->b |= 0x0000000000000400;

  return result;
}

char flip_bitboard_b_54(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000040000){
    count_0 = 0;
    if(opp & 0x0000000008000000){
      count_0++;
      if(opp & 0x0000001000000000){
	count_0++;
	if(opp & 0x0000200000000000){
	  count_0++;
	  if(opp & 0x0040000000000000){
	    count_0++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[54][0][count_0], -9)){
      board->b ^= rays_to_flip[54][0][count_0];
      board->w ^= rays_to_flip[54][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000020000){
    count_1 = 0;
    if(opp & 0x0000000002000000){
      count_1++;
      if(opp & 0x0000000200000000){
	count_1++;
	if(opp & 0x0000020000000000){
	  count_1++;
	  if(opp & 0x0002000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[54][1][count_1], -8)){
      board->b ^= rays_to_flip[54][1][count_1];
      board->w ^= rays_to_flip[54][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000000000400){
    count_3 = 0;
    if(opp & 0x0000000000000800){
      count_3++;
      if(opp & 0x0000000000001000){
	count_3++;
	if(opp & 0x0000000000002000){
	  count_3++;
	  if(opp & 0x0000000000004000){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[54][3][count_3], -1)){
      board->b ^= rays_to_flip[54][3][count_3];
      board->w ^= rays_to_flip[54][3][count_3];
      result |= 0x08;
    }
  }

  board->b |= 0x0000000000000200;

  return result;
}

char flip_bitboard_b_55(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000020000){
    count_0 = 0;
    if(opp & 0x0000000004000000){
      count_0++;
      if(opp & 0x0000000800000000){
	count_0++;
	if(opp & 0x0000100000000000){
	  count_0++;
	  if(opp & 0x0020000000000000){
	    count_0++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[55][0][count_0], -9)){
      board->b ^= rays_to_flip[55][0][count_0];
      board->w ^= rays_to_flip[55][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000010000){
    count_1 = 0;
    if(opp & 0x0000000001000000){
      count_1++;
      if(opp & 0x0000000100000000){
	count_1++;
	if(opp & 0x0000010000000000){
	  count_1++;
	  if(opp & 0x0001000000000000){
	    count_1++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[55][1][count_1], -8)){
      board->b ^= rays_to_flip[55][1][count_1];
      board->w ^= rays_to_flip[55][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000000000200){
    count_3 = 0;
    if(opp & 0x0000000000000400){
      count_3++;
      if(opp & 0x0000000000000800){
	count_3++;
	if(opp & 0x0000000000001000){
	  count_3++;
	  if(opp & 0x0000000000002000){
	    count_3++;
	    if(opp & 0x0000000000004000){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[55][3][count_3], -1)){
      board->b ^= rays_to_flip[55][3][count_3];
      board->w ^= rays_to_flip[55][3][count_3];
      result |= 0x08;
    }
  }

  board->b |= 0x0000000000000100;

  return result;
}

char flip_bitboard_b_56(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_1;
  if(opp & 0x0000000000008000){
    count_1 = 0;
    if(opp & 0x0000000000800000){
      count_1++;
      if(opp & 0x0000000080000000){
	count_1++;
	if(opp & 0x0000008000000000){
	  count_1++;
	  if(opp & 0x0000800000000000){
	    count_1++;
	    if(opp & 0x0080000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[56][1][count_1], -8)){
      board->b ^= rays_to_flip[56][1][count_1];
      board->w ^= rays_to_flip[56][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000004000){
    count_2 = 0;
    if(opp & 0x0000000000200000){
      count_2++;
      if(opp & 0x0000000010000000){
	count_2++;
	if(opp & 0x0000000800000000){
	  count_2++;
	  if(opp & 0x0000040000000000){
	    count_2++;
	    if(opp & 0x0002000000000000){
	      count_2++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[56][2][count_2], -7)){
      board->b ^= rays_to_flip[56][2][count_2];
      board->w ^= rays_to_flip[56][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000000000040){
    count_4 = 0;
    if(opp & 0x0000000000000020){
      count_4++;
      if(opp & 0x0000000000000010){
	count_4++;
	if(opp & 0x0000000000000008){
	  count_4++;
	  if(opp & 0x0000000000000004){
	    count_4++;
	    if(opp & 0x0000000000000002){
	      count_4++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[56][4][count_4], 1)){
      board->b ^= rays_to_flip[56][4][count_4];
      board->w ^= rays_to_flip[56][4][count_4];
      result |= 0x10;
    }
  }

  board->b |= 0x0000000000000080;

  return result;
}

char flip_bitboard_b_57(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_1;
  if(opp & 0x0000000000004000){
    count_1 = 0;
    if(opp & 0x0000000000400000){
      count_1++;
      if(opp & 0x0000000040000000){
	count_1++;
	if(opp & 0x0000004000000000){
	  count_1++;
	  if(opp & 0x0000400000000000){
	    count_1++;
	    if(opp & 0x0040000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[57][1][count_1], -8)){
      board->b ^= rays_to_flip[57][1][count_1];
      board->w ^= rays_to_flip[57][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000002000){
    count_2 = 0;
    if(opp & 0x0000000000100000){
      count_2++;
      if(opp & 0x0000000008000000){
	count_2++;
	if(opp & 0x0000000400000000){
	  count_2++;
	  if(opp & 0x0000020000000000){
	    count_2++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[57][2][count_2], -7)){
      board->b ^= rays_to_flip[57][2][count_2];
      board->w ^= rays_to_flip[57][2][count_2];
      result |= 0x04;
    }
  }
  int count_4;
  if(opp & 0x0000000000000020){
    count_4 = 0;
    if(opp & 0x0000000000000010){
      count_4++;
      if(opp & 0x0000000000000008){
	count_4++;
	if(opp & 0x0000000000000004){
	  count_4++;
	  if(opp & 0x0000000000000002){
	    count_4++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[57][4][count_4], 1)){
      board->b ^= rays_to_flip[57][4][count_4];
      board->w ^= rays_to_flip[57][4][count_4];
      result |= 0x10;
    }
  }

  board->b |= 0x0000000000000040;

  return result;
}

char flip_bitboard_b_58(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000004000){
    count_0 = 0;
    if(my & offset_bitmask(rays_to_flip[58][0][count_0], -9)){
      board->b ^= rays_to_flip[58][0][count_0];
      board->w ^= rays_to_flip[58][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000002000){
    count_1 = 0;
    if(opp & 0x0000000000200000){
      count_1++;
      if(opp & 0x0000000020000000){
	count_1++;
	if(opp & 0x0000002000000000){
	  count_1++;
	  if(opp & 0x0000200000000000){
	    count_1++;
	    if(opp & 0x0020000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[58][1][count_1], -8)){
      board->b ^= rays_to_flip[58][1][count_1];
      board->w ^= rays_to_flip[58][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000001000){
    count_2 = 0;
    if(opp & 0x0000000000080000){
      count_2++;
      if(opp & 0x0000000004000000){
	count_2++;
	if(opp & 0x0000000200000000){
	  count_2++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[58][2][count_2], -7)){
      board->b ^= rays_to_flip[58][2][count_2];
      board->w ^= rays_to_flip[58][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000000040){
    count_3 = 0;
    if(my & offset_bitmask(rays_to_flip[58][3][count_3], -1)){
      board->b ^= rays_to_flip[58][3][count_3];
      board->w ^= rays_to_flip[58][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000000010){
    count_4 = 0;
    if(opp & 0x0000000000000008){
      count_4++;
      if(opp & 0x0000000000000004){
	count_4++;
	if(opp & 0x0000000000000002){
	  count_4++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[58][4][count_4], 1)){
      board->b ^= rays_to_flip[58][4][count_4];
      board->w ^= rays_to_flip[58][4][count_4];
      result |= 0x10;
    }
  }

  board->b |= 0x0000000000000020;

  return result;
}

char flip_bitboard_b_59(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000002000){
    count_0 = 0;
    if(opp & 0x0000000000400000){
      count_0++;
    }
    if(my & offset_bitmask(rays_to_flip[59][0][count_0], -9)){
      board->b ^= rays_to_flip[59][0][count_0];
      board->w ^= rays_to_flip[59][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000001000){
    count_1 = 0;
    if(opp & 0x0000000000100000){
      count_1++;
      if(opp & 0x0000000010000000){
	count_1++;
	if(opp & 0x0000001000000000){
	  count_1++;
	  if(opp & 0x0000100000000000){
	    count_1++;
	    if(opp & 0x0010000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[59][1][count_1], -8)){
      board->b ^= rays_to_flip[59][1][count_1];
      board->w ^= rays_to_flip[59][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000000800){
    count_2 = 0;
    if(opp & 0x0000000000040000){
      count_2++;
      if(opp & 0x0000000002000000){
	count_2++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[59][2][count_2], -7)){
      board->b ^= rays_to_flip[59][2][count_2];
      board->w ^= rays_to_flip[59][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000000020){
    count_3 = 0;
    if(opp & 0x0000000000000040){
      count_3++;
    }
    if(my & offset_bitmask(rays_to_flip[59][3][count_3], -1)){
      board->b ^= rays_to_flip[59][3][count_3];
      board->w ^= rays_to_flip[59][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000000008){
    count_4 = 0;
    if(opp & 0x0000000000000004){
      count_4++;
      if(opp & 0x0000000000000002){
	count_4++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[59][4][count_4], 1)){
      board->b ^= rays_to_flip[59][4][count_4];
      board->w ^= rays_to_flip[59][4][count_4];
      result |= 0x10;
    }
  }

  board->b |= 0x0000000000000010;

  return result;
}

char flip_bitboard_b_60(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000001000){
    count_0 = 0;
    if(opp & 0x0000000000200000){
      count_0++;
      if(opp & 0x0000000040000000){
	count_0++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[60][0][count_0], -9)){
      board->b ^= rays_to_flip[60][0][count_0];
      board->w ^= rays_to_flip[60][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000000800){
    count_1 = 0;
    if(opp & 0x0000000000080000){
      count_1++;
      if(opp & 0x0000000008000000){
	count_1++;
	if(opp & 0x0000000800000000){
	  count_1++;
	  if(opp & 0x0000080000000000){
	    count_1++;
	    if(opp & 0x0008000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[60][1][count_1], -8)){
      board->b ^= rays_to_flip[60][1][count_1];
      board->w ^= rays_to_flip[60][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000000400){
    count_2 = 0;
    if(opp & 0x0000000000020000){
      count_2++;
    }
    if(my & offset_bitmask(rays_to_flip[60][2][count_2], -7)){
      board->b ^= rays_to_flip[60][2][count_2];
      board->w ^= rays_to_flip[60][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000000010){
    count_3 = 0;
    if(opp & 0x0000000000000020){
      count_3++;
      if(opp & 0x0000000000000040){
	count_3++;
      }
    }
    if(my & offset_bitmask(rays_to_flip[60][3][count_3], -1)){
      board->b ^= rays_to_flip[60][3][count_3];
      board->w ^= rays_to_flip[60][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000000004){
    count_4 = 0;
    if(opp & 0x0000000000000002){
      count_4++;
    }
    if(my & offset_bitmask(rays_to_flip[60][4][count_4], 1)){
      board->b ^= rays_to_flip[60][4][count_4];
      board->w ^= rays_to_flip[60][4][count_4];
      result |= 0x10;
    }
  }

  board->b |= 0x0000000000000008;

  return result;
}

char flip_bitboard_b_61(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000000800){
    count_0 = 0;
    if(opp & 0x0000000000100000){
      count_0++;
      if(opp & 0x0000000020000000){
	count_0++;
	if(opp & 0x0000004000000000){
	  count_0++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[61][0][count_0], -9)){
      board->b ^= rays_to_flip[61][0][count_0];
      board->w ^= rays_to_flip[61][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000000400){
    count_1 = 0;
    if(opp & 0x0000000000040000){
      count_1++;
      if(opp & 0x0000000004000000){
	count_1++;
	if(opp & 0x0000000400000000){
	  count_1++;
	  if(opp & 0x0000040000000000){
	    count_1++;
	    if(opp & 0x0004000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[61][1][count_1], -8)){
      board->b ^= rays_to_flip[61][1][count_1];
      board->w ^= rays_to_flip[61][1][count_1];
      result |= 0x02;
    }
  }
  int count_2;
  if(opp & 0x0000000000000200){
    count_2 = 0;
    if(my & offset_bitmask(rays_to_flip[61][2][count_2], -7)){
      board->b ^= rays_to_flip[61][2][count_2];
      board->w ^= rays_to_flip[61][2][count_2];
      result |= 0x04;
    }
  }
  int count_3;
  if(opp & 0x0000000000000008){
    count_3 = 0;
    if(opp & 0x0000000000000010){
      count_3++;
      if(opp & 0x0000000000000020){
	count_3++;
	if(opp & 0x0000000000000040){
	  count_3++;
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[61][3][count_3], -1)){
      board->b ^= rays_to_flip[61][3][count_3];
      board->w ^= rays_to_flip[61][3][count_3];
      result |= 0x08;
    }
  }
  int count_4;
  if(opp & 0x0000000000000002){
    count_4 = 0;
    if(my & offset_bitmask(rays_to_flip[61][4][count_4], 1)){
      board->b ^= rays_to_flip[61][4][count_4];
      board->w ^= rays_to_flip[61][4][count_4];
      result |= 0x10;
    }
  }

  board->b |= 0x0000000000000004;

  return result;
}

char flip_bitboard_b_62(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000000400){
    count_0 = 0;
    if(opp & 0x0000000000080000){
      count_0++;
      if(opp & 0x0000000010000000){
	count_0++;
	if(opp & 0x0000002000000000){
	  count_0++;
	  if(opp & 0x0000400000000000){
	    count_0++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[62][0][count_0], -9)){
      board->b ^= rays_to_flip[62][0][count_0];
      board->w ^= rays_to_flip[62][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000000200){
    count_1 = 0;
    if(opp & 0x0000000000020000){
      count_1++;
      if(opp & 0x0000000002000000){
	count_1++;
	if(opp & 0x0000000200000000){
	  count_1++;
	  if(opp & 0x0000020000000000){
	    count_1++;
	    if(opp & 0x0002000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[62][1][count_1], -8)){
      board->b ^= rays_to_flip[62][1][count_1];
      board->w ^= rays_to_flip[62][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000000000004){
    count_3 = 0;
    if(opp & 0x0000000000000008){
      count_3++;
      if(opp & 0x0000000000000010){
	count_3++;
	if(opp & 0x0000000000000020){
	  count_3++;
	  if(opp & 0x0000000000000040){
	    count_3++;
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[62][3][count_3], -1)){
      board->b ^= rays_to_flip[62][3][count_3];
      board->w ^= rays_to_flip[62][3][count_3];
      result |= 0x08;
    }
  }

  board->b |= 0x0000000000000002;

  return result;
}

char flip_bitboard_b_63(BitBoard *board){
  uint64_t my = board->b;
  uint64_t opp = board->w;
  char result = 0;
  int count_0;
  if(opp & 0x0000000000000200){
    count_0 = 0;
    if(opp & 0x0000000000040000){
      count_0++;
      if(opp & 0x0000000008000000){
	count_0++;
	if(opp & 0x0000001000000000){
	  count_0++;
	  if(opp & 0x0000200000000000){
	    count_0++;
	    if(opp & 0x0040000000000000){
	      count_0++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[63][0][count_0], -9)){
      board->b ^= rays_to_flip[63][0][count_0];
      board->w ^= rays_to_flip[63][0][count_0];
      result |= 0x01;
    }
  }
  int count_1;
  if(opp & 0x0000000000000100){
    count_1 = 0;
    if(opp & 0x0000000000010000){
      count_1++;
      if(opp & 0x0000000001000000){
	count_1++;
	if(opp & 0x0000000100000000){
	  count_1++;
	  if(opp & 0x0000010000000000){
	    count_1++;
	    if(opp & 0x0001000000000000){
	      count_1++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[63][1][count_1], -8)){
      board->b ^= rays_to_flip[63][1][count_1];
      board->w ^= rays_to_flip[63][1][count_1];
      result |= 0x02;
    }
  }
  int count_3;
  if(opp & 0x0000000000000002){
    count_3 = 0;
    if(opp & 0x0000000000000004){
      count_3++;
      if(opp & 0x0000000000000008){
	count_3++;
	if(opp & 0x0000000000000010){
	  count_3++;
	  if(opp & 0x0000000000000020){
	    count_3++;
	    if(opp & 0x0000000000000040){
	      count_3++;
	    }
	  }
	}
      }
    }
    if(my & offset_bitmask(rays_to_flip[63][3][count_3], -1)){
      board->b ^= rays_to_flip[63][3][count_3];
      board->w ^= rays_to_flip[63][3][count_3];
      result |= 0x08;
    }
  }

  board->b |= 0x0000000000000001;

  return result;
}

char (* const flip_bitboard_w[BOARD_SIZE_SQR])(BitBoard *) = {
  flip_bitboard_w_00,
  flip_bitboard_w_01,
  flip_bitboard_w_02,
  flip_bitboard_w_03,
  flip_bitboard_w_04,
  flip_bitboard_w_05,
  flip_bitboard_w_06,
  flip_bitboard_w_07,
  flip_bitboard_w_08,
  flip_bitboard_w_09,
  flip_bitboard_w_10,
  flip_bitboard_w_11,
  flip_bitboard_w_12,
  flip_bitboard_w_13,
  flip_bitboard_w_14,
  flip_bitboard_w_15,
  flip_bitboard_w_16,
  flip_bitboard_w_17,
  flip_bitboard_w_18,
  flip_bitboard_w_19,
  flip_bitboard_w_20,
  flip_bitboard_w_21,
  flip_bitboard_w_22,
  flip_bitboard_w_23,
  flip_bitboard_w_24,
  flip_bitboard_w_25,
  flip_bitboard_w_26,
  flip_bitboard_w_27,
  flip_bitboard_w_28,
  flip_bitboard_w_29,
  flip_bitboard_w_30,
  flip_bitboard_w_31,
  flip_bitboard_w_32,
  flip_bitboard_w_33,
  flip_bitboard_w_34,
  flip_bitboard_w_35,
  flip_bitboard_w_36,
  flip_bitboard_w_37,
  flip_bitboard_w_38,
  flip_bitboard_w_39,
  flip_bitboard_w_40,
  flip_bitboard_w_41,
  flip_bitboard_w_42,
  flip_bitboard_w_43,
  flip_bitboard_w_44,
  flip_bitboard_w_45,
  flip_bitboard_w_46,
  flip_bitboard_w_47,
  flip_bitboard_w_48,
  flip_bitboard_w_49,
  flip_bitboard_w_50,
  flip_bitboard_w_51,
  flip_bitboard_w_52,
  flip_bitboard_w_53,
  flip_bitboard_w_54,
  flip_bitboard_w_55,
  flip_bitboard_w_56,
  flip_bitboard_w_57,
  flip_bitboard_w_58,
  flip_bitboard_w_59,
  flip_bitboard_w_60,
  flip_bitboard_w_61,
  flip_bitboard_w_62,
  flip_bitboard_w_63
};

char (* const flip_bitboard_b[BOARD_SIZE_SQR])(BitBoard *) = {
  flip_bitboard_b_00,
  flip_bitboard_b_01,
  flip_bitboard_b_02,
  flip_bitboard_b_03,
  flip_bitboard_b_04,
  flip_bitboard_b_05,
  flip_bitboard_b_06,
  flip_bitboard_b_07,
  flip_bitboard_b_08,
  flip_bitboard_b_09,
  flip_bitboard_b_10,
  flip_bitboard_b_11,
  flip_bitboard_b_12,
  flip_bitboard_b_13,
  flip_bitboard_b_14,
  flip_bitboard_b_15,
  flip_bitboard_b_16,
  flip_bitboard_b_17,
  flip_bitboard_b_18,
  flip_bitboard_b_19,
  flip_bitboard_b_20,
  flip_bitboard_b_21,
  flip_bitboard_b_22,
  flip_bitboard_b_23,
  flip_bitboard_b_24,
  flip_bitboard_b_25,
  flip_bitboard_b_26,
  flip_bitboard_b_27,
  flip_bitboard_b_28,
  flip_bitboard_b_29,
  flip_bitboard_b_30,
  flip_bitboard_b_31,
  flip_bitboard_b_32,
  flip_bitboard_b_33,
  flip_bitboard_b_34,
  flip_bitboard_b_35,
  flip_bitboard_b_36,
  flip_bitboard_b_37,
  flip_bitboard_b_38,
  flip_bitboard_b_39,
  flip_bitboard_b_40,
  flip_bitboard_b_41,
  flip_bitboard_b_42,
  flip_bitboard_b_43,
  flip_bitboard_b_44,
  flip_bitboard_b_45,
  flip_bitboard_b_46,
  flip_bitboard_b_47,
  flip_bitboard_b_48,
  flip_bitboard_b_49,
  flip_bitboard_b_50,
  flip_bitboard_b_51,
  flip_bitboard_b_52,
  flip_bitboard_b_53,
  flip_bitboard_b_54,
  flip_bitboard_b_55,
  flip_bitboard_b_56,
  flip_bitboard_b_57,
  flip_bitboard_b_58,
  flip_bitboard_b_59,
  flip_bitboard_b_60,
  flip_bitboard_b_61,
  flip_bitboard_b_62,
  flip_bitboard_b_63
};
