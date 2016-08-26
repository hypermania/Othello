#ifndef PATTERN_H
#define PATTERN_H


#include <stdlib.h>
#include <string.h>

#include "const.h"
#include "macro.h"

typedef uint64_t Pattern;

/* pattern utilities */
// dihedral group
Pattern pattern_reflect_diag(Pattern pattern);
Pattern pattern_rotate_90(Pattern pattern);
Pattern pattern_rotate_180(Pattern pattern);
Pattern pattern_rotate_270(Pattern pattern);

/* complete the pattern set via rotation/reflection
   stores the total number of patterns generated in n_c
*/
Pattern *complete_pattern_set(Pattern *pattern, int n_p, int *n_c);


#endif
