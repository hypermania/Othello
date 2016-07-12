#ifndef PREPROCESS_H
#define PREPROCESS_H

//#include "genconf.h"
#include "example.h"
#include "state.h"
#include "io.h"
#include "config.h"
#include "board.h"
#include "ai.h"

/* preprocessors */

// given "examples" and "example_size":
// stores the categorized examples into "categories"
//  stores the number of examples in each cateogry into "category_sizes"
int sort_examples_into_categories(Example *examples, Example **categories, int *cat_sizes, int example_size);
// write to the example ptr all (board,score) pair in the game
int example_from_seq(State state, Pos *seq, Example *example);

Example *append_filed_games_to_examples(Example *examples, int *n_e, const char *filename);
Example *append_random_games_to_examples(Example *examples, int *n_e, int n_g);
Example *append_mixed_games_to_examples(Example *examples, int *n_e, int n_g);


#endif

