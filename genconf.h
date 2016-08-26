#ifndef GENCONF_H
#define GENCONF_H


#include "state.h"
#include "fct.h"

#include "hash.h"

#include "index_computation.h"

#include "const.h"
#include "macro.h"
#include "util.h"

#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <math.h>
#include <limits.h>




/* pattern related utilities */

// 2. generate all variations among these patterns

// variation generation (step 2 in the process above)
/* return the poiner to the variations generated
   and store the total number generated in "n"
 */
Config list_variations(Pattern pattern, int *n_var);


// 3. for each pattern, filter the configs that appear with probability < 0.01%

// filter invalid configs in a set of variations
/* count the (symmetric) number of matches to "boards" for each variation;
   returns the match number table */
int *match_variations(Config variations, Config boards, int n_v, int n_b, int symmetrize);
/* returns the filtered table of configs
   stores the number of configs that passed the filter */
Config filter_variations(Config variations, int *matches, int n_v, int n_b, int *k, double threshold);


// 4. create a scheme for storing the patterns in a table

// not symmetrized
int *match_std_variation_list(Pattern pattern, Config boards, int n_b);
FlatConfTable genconf_single_pattern(Pattern pattern, Config boards, int n_b, int threshold);
int init_weights_for_fct(FlatConfTable *fct);


// repeat
/* "Multiplying" two sets of variations together:
   For each pair of variation, if they are compatible,
   join them to form a new variation.
   Return this set of variations.
*/
Config cross_match(Config variations_1, Config variations_2, int n_v1, int n_v2, int *total);

/* Join two configs.
   Requirement: the two configs be compatible
 */
Config_store config_join(Config_store config_1, Config_store config_2);
int match_pair_conf(Config_store config_1, Config_store config_2);



#endif
