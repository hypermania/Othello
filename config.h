#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "const.h"
#include "macro.h"

typedef struct {
  /* The long ints here have 64 bits, 
     representing the board in row-major order.
     For b and w, a 0 bit denotes an empty spot, 
     and 1 denotes occupied spot. (by black or white, respectively)
   */
  /* should satisfy x&w == 0, w&b == 0, x&b==0 */
  /* board represents a config such that x^w^b == 0xff...ff */
  unsigned long int x;
  unsigned long int w;
  unsigned long int b;

} Config_store, *Config;

Config create_and_init_config(void);
Config create_and_init_config_list(int length);

int init_config(Config config);
int free_config(Config config);


int check_board_as_config(Config_store conf);
//int board_to_conf(Board board, Config config);
//Config_store board_to_conf_nocreate(Board board);



// match a maximum of n (converted) boards to a given config
// returns number of matches
int match_conf_nocreate(Config boards, Config config, int n);
int match_one_conf(Config boards, Config config);

int match_one_conf_inline(Config_store boards, Config_store config);

//int symmetric_match_conf_nocreate(Config boards, Config config, int n);
int symmetric_match_one_conf(Config boards, Config config);
int symmetric_match_one_conf_inline(Config_store boards, Config_store config);

Config_store reflect_diag(Config_store config);
Config_store reflect_rdiag(Config_store config);
Config_store reflect_bdiag(Config_store config);



#endif
