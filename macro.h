#ifndef MACRO_H
#define MACRO_H

/* Board macros */

#define BOARD_SIZE 8
#define BOARD_SIZE_SQR (BOARD_SIZE * BOARD_SIZE)
#define POS_STORE_SIZE (BOARD_SIZE * BOARD_SIZE / 2)
#define ADJ_SIZE 8
#define X 0
#define W 1
#define B 2


/* Pattern/Config macros */

#define LOG_BOARD_SIZE 3
#define GAME_LENGTH 60

#define ATOM(r,c) (((unsigned long int) 0x8000000000000000) >> (((r) << LOG_BOARD_SIZE) + (c)))
#define ROW(r) (0xff00000000000000 >> (r << LOG_BOARD_SIZE)) // 0 <= r < 8
#define COL(c) (0x8080808080808080 >> (c))  // 0 <= c < 8
#define DIAG(d) (0x8040201008040201 >> (d)) // 0 <= d < 7
#define RDIAG(d) ((0x0102040810204080 >> (d))  &  (~(COL(0) >> (d))) ) // 0 <= d < 7

/* Weight fitting macros */

#define CATEGORY_SIZE 4
#define INIT_PIECE_NUM 4
#define CAT_NUM ((BOARD_SIZE_SQR - INIT_PIECE_NUM)/CATEGORY_SIZE)
#define CAT(pieces) (((pieces) - 1 - INIT_PIECE_NUM) / CATEGORY_SIZE)


/* Multi-threading macros */

#define TH_NUM 4

/* IO macros */

#define BUFF_SIZE 256

/* Game control macros */

//#define HUMAN 0
//#define RANDOM 1
//#define AB_PRUNING 2
//#define NEGAMAX 3

#endif
