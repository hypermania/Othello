#include "state.h"
#include <stdlib.h>
#include <assert.h>
//#include <math.h>

#ifndef CONFIG_H
#define CONFIG_H

#define LOG_BOARD_SIZE 3
#define ATOM(r,c) (((unsigned long int) 0x8000000000000000) >> ((r << LOG_BOARD_SIZE) + c))

typedef struct {
  /* The long ints here have 64 bits, 
     representing the board in row-major order.
     For b and w, a 0 bit denotes an empty spot, 
     and 1 denotes occupied spot. (by black or white, respectively)
   */
  /* should satisfy x&w == 0, w&b == 0, x&b==0 */
  /* board represents a config such that x^w^b == 0xff...ff*/
  unsigned long int x;
  unsigned long int w;
  unsigned long int b;

} Config_store, *Config;

Config create_and_init_config(void);
Config create_and_init_config_list(int length);

int init_config(Config config);
int free_config(Config config);

int check_board_as_config(Config_store conf);

int board_to_conf(Board board, Config config);

// match a maximum of n (converted) boards to a given config
// returns number of matches
int match_conf(Config boards, Config config, int n);

// return number of boards generated at success
// return 0 at failure (such as incorrect game sequence)
int genconf_from_seq(State state, Pos *seq, Config boards);




#endif
