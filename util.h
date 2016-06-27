#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdio.h>

#include "pattern.h"

/* miscellaneous function */

int ipow(int base, int exp);

void binarize_items(Pattern *patterns, int *indices, int n);

#endif
