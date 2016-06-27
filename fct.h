#ifndef FCT_H
#define FCT_H

//#include "genconf.h"
#include "config.h"
#include "pattern.h"

typedef struct {
  int n;
  Pattern pattern;
  char *valid;
  Config variations;
  int *matches;
  double *weights;
} FlatConfTable;


#endif
