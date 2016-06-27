#include "fct.h"

void free_fct_contents(FlatConfTable fct){
  free(fct.valid);
  free(fct.variations);
  free(fct.matches);
  free(fct.weights);
}
