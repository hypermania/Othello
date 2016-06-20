#include "state.h"

#include <stdlib.h>
#include <assert.h>
//#include <math.h>



#ifndef CONFIG_H
#define CONFIG_H

#define LOG_BOARD_SIZE 3
#define GAME_LENGTH 60

#define ATOM(r,c) (((unsigned long int) 0x8000000000000000) >> (((r) << LOG_BOARD_SIZE) + (c)))
#define ROW(r) (0xff00000000000000 >> (r << LOG_BOARD_SIZE)) // 0 <= r < 8
#define COL(c) (0x8080808080808080 >> (c))  // 0 <= c < 8
#define DIAG(d) (0x8040201008040201 >> (d)) // 0 <= d < 7
#define RDIAG(d) ((0x0102040810204080 >> (d))  &  (~(COL(0) >> (d))) ) // 0 <= d < 7

/*
  Config specification:
  1. Need to assure that no two configs within the same set of patterns
     can be obtained via reflection along diagonals, as the patterns are
     supposed to be symmetrized.
  2. In total weight computation, reflections of a config need to be considered.
     Given a configuration, all 4 reflections of the same config are matched
     against the board, and a weight is added for each reflection.
     If a config is symmetric along some diagonal, there is no need to account for
     over-counting, since the effect will be accounted for in weight fitting.
     (The weight fitted here is half the weight of the case in which the
     symmetric config is counted only once.)
     
  Process for pattern generation:
  1. pick a set of pattern
  2. generate all variations among these patterns
  3. for each pattern, filter the configs that appear with probability < 0.01%
  4. create a scheme for storing the patterns in a table
  5. filter combinations of configs that appear with probability < 0.01%
  6. 
 */

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

typedef unsigned long int Pattern;

Config create_and_init_config(void);
Config create_and_init_config_list(int length);

int init_config(Config config);
int free_config(Config config);

int check_board_as_config(Config_store conf);

int board_to_conf(Board board, Config config);

// match a maximum of n (converted) boards to a given config
// returns number of matches
int match_conf_nocreate(Config boards, Config config, int n);
int match_one_conf(Config boards, Config config);

//int symmetric_match_conf_nocreate(Config boards, Config config, int n);
int symmetric_match_one_conf(Config boards, Config config);

Config_store reflect_diag(Config_store config);
Config_store reflect_rdiag(Config_store config);
Config_store reflect_bdiag(Config_store config);

// variation generation (step 2 in the process above)
/* return the poiner to the variations generated
   and store the total number generated in "n"
 */
Config list_variations(Pattern pattern, int *n_var);

// filter invalid configs in a set of variations
/* count the (symmetric) number of matches to "boards" for each variation;
   returns the match number table */
int *match_variations(Config variations, Config boards, int n_v, int n_b);
/* returns the filtered table of configs
   stores the number of configs that passed the filter */
Config filter_variations(Config variations, int *matches, int n, int *k, double freq);

//3. for each pattern, filter the configs that appear with probability < 0.01%

// return number of boards/examples generated at success
// return 0 at failure (such as incorrect game sequence)
int genconf_from_seq(State state, Pos *seq, Config boards);



#endif
